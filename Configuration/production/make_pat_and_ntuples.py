#! /bin/env cmsRun

#make it executable
from URAnalysis.Configuration.varparsing import options
import FWCore.ParameterSet.Config as cms
import URAnalysis.PATTools.custompat as urpat
import URAnalysis.PATTools.customskims as urskims
import URAnalysis.PATTools.meta  as meta
import URAnalysis.Ntuplizer.ntuplizer as ntuple
import TopQuarkAnalysis.TopEventProducers.producers.pseudoTop_cfi as pseudotop # for method 2

options.parseArguments()

process = cms.Process("PATPlusNtuple")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = options.reportEvery
process.MessageLogger.cerr.FwkSummary.reportEvery = options.reportEvery

process.options = cms.untracked.PSet(wantSummary=cms.untracked.bool(True))
process.maxEvents = cms.untracked.PSet(
   input = cms.untracked.int32(
      options.maxEvents
      )
)

process.source = cms.Source(
    "PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
      #'/store/relval/CMSSW_7_0_6/RelValTTbarLepton_13/MINIAODSIM/PLS170_V6AN1-v1/00000/CA50900E-43FA-E311-B663-0025905A48EC.root'
      options.inputFiles
      ),
)

process.TFileService = cms.Service(
        "TFileService",
        fileName = cms.string(options.outputFile)
)

collections = {
   'muons' : 'slimmedMuons',
   'electrons' : 'slimmedElectrons',
   'photons' : 'slimmedPhotons',
   'jets' : 'slimmedJets',
   'vertices' : 'offlineSlimmedPrimaryVertices',
   'METs' : 'slimmedMETs',
   'genParticles' : 'prunedGenParticles',
}

skim_sequences = urskims.add_skims(process, **collections)

#store meta
process.load("Configuration.StandardSequences.Services_cff")
process.load('URAnalysis.Ntuplizer.MetaNtuplize_cfi')
process.metaTree.isMC = cms.bool(options.isMC)
process.meta = cms.Sequence(
   meta.embed_meta(process, options.isMC) *
   process.metaTree
   )


#from pdb import set_trace
#set_trace()
#make custom PAT

custom_pat_sequence, collections = urpat.customize(
   process,
   options.isMC,
   **collections
)

ntuple_sequence, ntuple_end = ntuple.make_ntuple(
   process,
   options.isMC,
   **collections
   )

process.load("TopQuarkAnalysis.TopEventProducers.producers.pseudoTop_cfi")
ntuple_sequence += process.pseudoTop

process.pseudoTop = pseudotop.pseudoTop # methed 2

process.pseudoTop = cms.EDProducer("PseudoTopProducer",
    genParticles = cms.InputTag("prunedGenParticles"),
    finalStates = cms.InputTag("packedGenParticles"),
    leptonMinPt = cms.double(20),
    leptonMaxEta = cms.double(2.4),
    jetMinPt = cms.double(20),
    jetMaxEta = cms.double(2.4),
    leptonConeSize = cms.double(0.1),
    jetConeSize = cms.double(0.4),
    wMass = cms.double(80.4),
    tMass = cms.double(172.5),
)

process.pseudotop_step = cms.Path(process.pseudoTop)
process.schedule = cms.Schedule(process.pseudotop_step)
#make meta+skim+customPAT+Ntuple paths
#one for each skim sequence
#shared modules do not get rerun
#https://hypernews.cern.ch/HyperNews/CMS/get/edmFramework/3416/1.html

for skim in skim_sequences:
   path_name = skim+'Path0'
   #assure to make NEW path name
   idx = 1
   while hasattr(process, path_name):
      path_name = path_name[:-1]+str(idx)
      idx += 1
   setattr(
      process,
      path_name,
      cms.Path(
         process.meta *
         getattr(process, skim) *
         custom_pat_sequence *
         ntuple_sequence *
         ntuple_end
         )
      )
   process.schedule.append(
      getattr(process, path_name)
      )

## process.end = cms.EndPath(
##    ntuple_end
## )
## process.schedule.append(process.end)
