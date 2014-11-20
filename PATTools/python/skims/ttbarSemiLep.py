import FWCore.ParameterSet.Config as cms

muonFilter = cms.EDFilter(
    "CandViewCountFilter",
    src = cms.InputTag("skimmedMuons"),
    minNumber = cms.uint32(1)
)

jetFilter = cms.EDFilter(
    "CandViewCountFilter",
    src = cms.InputTag("skimmedJets"),
    minNumber = cms.uint32(4)
)

ttbarSemiLepSkim = cms.Sequence(
    muonFilter *
    jetFilter
)
