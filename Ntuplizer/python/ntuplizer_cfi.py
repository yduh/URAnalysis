import FWCore.ParameterSet.Config as cms
import URAnalysis.Ntuplizer.branches as branches

ntuple = cms.Sequence()

evtid = cms.EDAnalyzer(
   'EvtIDProducer'
)
ntuple += evtid

muons = cms.EDAnalyzer(
   'NtupleMuonsProducer',
   src = cms.InputTag('slimmedMuons'),
   branches = cms.VPSet(
      branches.kinematics +
      branches.isolation +
      branches.muon_specific
      )
)
ntuple += muons

jets = cms.EDAnalyzer(
   'NtupleJetsProducer',
   src = cms.InputTag('slimmedJets'),
   branches = cms.VPSet(
      branches.kinematics +
      branches.jet_specific +
      branches.btaggging
      )
)
ntuple += jets

electrons = cms.EDAnalyzer(
   'NtupleElectronsProducer',
   src = cms.InputTag('slimmedElectrons'),
   branches = cms.VPSet(
      branches.kinematics +
      branches.isolation +
      branches.electron_specific +
      branches.ecal_cluster_specific + 
      branches.super_cluster_specific
      )
)
ntuple += electrons

photons = cms.EDAnalyzer(
   'NtuplePhotonsProducer',
   src = cms.InputTag('slimmedPhotons'),
   branches = cms.VPSet(
      branches.kinematics +
      branches.super_cluster_specific +
      branches.photon_specific
      )
)
ntuple += photons

vertexs = cms.EDAnalyzer(
   'NtupleVerticesProducer',
   src = cms.InputTag('offlineSlimmedPrimaryVertices'),
   branches = cms.VPSet(
      branches.vertex_specific
      )
)
ntuple += vertexs

METs = cms.EDAnalyzer(
   'NtupleMETProducer',
   src = cms.InputTag('slimmedMETs'),
   branches = cms.VPSet(
      branches.met_specific
      )
)
ntuple += METs

#############
#  MC Only
#############

#FIXME: add it!
#genInfo = cms.EDAnalyzer(
#   'NtupleGenInfoProducer',
#   src = cms.InputTag('generator'),
#   branches = cms.VPSet(
#      branches.geninfo_scpecific
#      )
#)
#ntuple += genInfo

PUInfos = cms.EDAnalyzer(
   'NtuplePUInfoProducer',
   src = cms.InputTag('addPileupInfo'),
   branches = cms.VPSet(
      branches.puinfo_specific
      )
)
ntuple += PUInfos

#genMET = cms.EDAnalyzer(
genParticles = cms.EDAnalyzer(
   'NtupleGenParticlesProducer',
   src = cms.InputTag('prunedGenParticles'),
   branches = cms.VPSet(
      branches.kinematics +
      branches.gen_particle_specific
      )
)
ntuple += genParticles

#genPInheritance = cms.EDAnalyzer(
#   'NTupleGenPaticleInheritance'
#   label = cms.string('genParticles'),
#   src = cms.InputTag('prunedGenParticles'),
#)

ntupleEnd = cms.EDAnalyzer('TreeFiller')

