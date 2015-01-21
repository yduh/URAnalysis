import FWCore.ParameterSet.Config as cms

urSkimmedElectrons = cms.EDFilter(
    "PATElectronSelector",
    src = cms.InputTag("fixme"),
    cut = cms.string('pt > 15 && abs(eta) < 2.5')
)

customElectrons = cms.Sequence(
   urSkimmedElectrons
)
