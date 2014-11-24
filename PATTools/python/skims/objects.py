#
#Defines basic object selection
#to be used in pattuplization/ntuplization
#
#Author Mauro Verzetti
#
import FWCore.ParameterSet.Config as cms

skimmedMuons = cms.EDFilter(
    "PATMuonSelector",
    src = cms.InputTag("slimmedMuons"),
    cut = cms.string('pt > 15 && abs(eta) < 2.5')
)

skimmedJets = cms.EDFilter(
    "PATJetSelector",
    src = cms.InputTag("slimmedJets"),
    cut = cms.string('pt > 20 && abs(eta) < 4')
)

objectsSkim = cms.Sequence(
    skimmedMuons+
    skimmedJets
)
