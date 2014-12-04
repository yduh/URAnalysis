import FWCore.ParameterSet.Config as cms

ntuple = cms.EDAnalyzer(
   'URNTuplizer',
   treeName = cms.string('events'),
   objects = cms.PSet(
      muons = cms.PSet(
         src = cms.InputTag('slimmedMuons'),
         type = cms.string('MuonCollection2Branch'),
         branches = cms.PSet(
            pt = cms.string('pt'),
            eta = cms.string('eta'),
            phi = cms.string('phi'),
            charge = cms.string('charge'),
            )
         ),
      jets = cms.PSet(
         src = cms.InputTag('slimmedJets'),
         type = cms.string('JetCollection2Branch'),
         branches = cms.PSet(
            pt = cms.string('pt'),
            eta = cms.string('eta'),
            phi = cms.string('phi'),
            charge = cms.string('charge'),
            )
         ),

      #jets....                                                                                                                                           
      )
   )
