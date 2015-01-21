import FWCore.ParameterSet.Config as cms

urSkimmedMuons = cms.EDFilter(
    "PATMuonSelector",
    src = cms.InputTag("fixme"),
    cut = cms.string('pt > 15 && abs(eta) < 2.5 && (isGlobalMuon || isTrackerMuon)')
)

customMuons = cms.Sequence(
   urSkimmedMuons
)
