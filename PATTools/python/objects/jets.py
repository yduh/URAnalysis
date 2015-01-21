import FWCore.ParameterSet.Config as cms

urSkimmedJets = cms.EDFilter(
    "PATJetSelector",
    src = cms.InputTag("fixme"),
    cut = cms.string('pt > 20 && abs(eta) < 4')
)

customJets = cms.Sequence(
   urSkimmedJets
)
