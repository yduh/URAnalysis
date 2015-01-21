import FWCore.ParameterSet.Config as cms

def skim(process, **collections):
   process.hiptMuons = cms.EDFilter(
      "PATMuonSelector",
      src = cms.InputTag(collections['muons']),
      cut = cms.string('pt > 20 && abs(eta) < 2.5 && (isGlobalMuon || isTrackerMuon)')
      )

   process.muonFilter = cms.EDFilter(
      "CandViewCountFilter",
      src = cms.InputTag('hiptMuons'),
      minNumber = cms.uint32(1)
      )

   process.hiPtJets = cms.EDFilter(
      "PATJetSelector",
      src = cms.InputTag(collections['jets']),
      cut = cms.string('pt > 20 && abs(eta) < 4')
      )

   process.jetFilter = cms.EDFilter(
      "CandViewCountFilter",
      src = cms.InputTag("hiPtJets"),
      minNumber = cms.uint32(3)
      )

   process.ttbarToMuJets = cms.Sequence(
      process.hiptMuons *
      process.muonFilter *
      process.hiPtJets *
      process.jetFilter
      )
   return process.ttbarToMuJets.label_()