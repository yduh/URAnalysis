import FWCore.ParameterSet.Config as cms

template = [
    cms.InputTag('pt'),
    cms.InputTag('eta'),
    cms.InputTag('phi'),
    cms.InputTag('charge','','/I'),
]

ntuple = cms.EDAnalyzer(
   'URNTuplizer',
   treeName = cms.string('events'),
   objects = cms.PSet(
      muons = cms.PSet(
         src = cms.InputTag('slimmedMuons'),
         type = cms.string('MuonCollection2Branch'),
         branches = cms.VInputTag(template)
         ),
      jets = cms.PSet(
         src = cms.InputTag('slimmedJets'),
         type = cms.string('JetCollection2Branch'),
         branches = cms.VInputTag(template)
         ),

      #jets....                                                                                                                                           
      )
   )
