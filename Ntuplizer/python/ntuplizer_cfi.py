import FWCore.ParameterSet.Config as cms

template = [
    cms.InputTag('pt'),
    cms.InputTag('eta'),
    cms.InputTag('phi'),
    cms.InputTag('charge','','/I'),
    #cms.InputTag('IsoDB','(chargedIsolation()+max(photonIso()+neutralIso() - pileupIso(),0))')
]

evtid = cms.EDAnalyzer(
   'EvtIDProducer'
)

muons = cms.EDAnalyzer(
   'NtupleMuonsProducer',
   src = cms.InputTag('slimmedMuons'),
   branches = cms.VInputTag(template)
)

jets = cms.EDAnalyzer(
   'NtupleJetsProducer',
   src = cms.InputTag('slimmedJets'),
   branches = cms.VInputTag(template)
)

electrons = cms.EDAnalyzer(
   'NtupleElectronsProducer',
   src = cms.InputTag('slimmedElectrons'),
   branches = cms.VInputTag(template)
)

ntuple = cms.Sequence(
   evtid +
   muons +
   jets +
   electrons
)

ntupleEnd = cms.EDAnalyzer('TreeFiller')

