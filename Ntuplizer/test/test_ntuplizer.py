import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(200) )
process.source = cms.Source(
    "PoolSource",
    # replace 'myfile.root' with the source file you want to use                                                                                                                                                                          
    fileNames = cms.untracked.vstring(
        '/store/relval/CMSSW_7_0_6/RelValTTbarLepton_13/MINIAODSIM/PLS170_V6AN1-v1/00000/CA50900E-43FA-E311-B663-0025905A48EC.root'
        ),
    #skipEvents=cms.untracked.uint32(0)
)

#process.Tracer = cms.Service("Tracer")
process.TFileService = cms.Service(
        "TFileService",
        fileName = cms.string("test_ntuple.root")
)

process.load('URAnalysis.Ntuplizer.ntuplizer_cfi')
process.p = cms.Path(process.ntuple)
process.end = cms.EndPath(
   process.ntupleEnd
)
process.schedule = cms.Schedule(
   process.p,
   process.end
)
