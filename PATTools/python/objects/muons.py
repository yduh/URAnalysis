import FWCore.ParameterSet.Config as cms

urSkimmedMuons = cms.EDFilter(
    "PATMuonSelector",
    src = cms.InputTag("fixme"),
    cut = cms.string('pt > 15 && abs(eta) < 2.5 && (isGlobalMuon || isTrackerMuon)')
)
customMuons = cms.Sequence(urSkimmedMuons)

#trigger match
from URAnalysis.PATTools.objects.trigger import trigger_paths, match_template

matchers = []
mupaths = [i for i in trigger_paths if 'Mu' in i]
for path in mupaths:
   matcher_name = 'matchMuons%s' % path.replace('_','')
   matchers.append(matcher_name)
   globals()[matcher_name] = match_template.clone(
      src = cms.InputTag('urSkimmedMuons'),
      matchedCuts = cms.string('path("HLT_%s_v*") || type("TriggerMuon")' % path)
      )
   #print matcher_name, globals()[matcher_name].matchedCuts
   customMuons *= globals()[matcher_name]

urMuons = cms.EDProducer(
   'PATMuonsEmbedder',
   src = cms.InputTag('fixme'),
   trigMatches = cms.VInputTag(
      cms.InputTag(i) for i in matchers
      ),
   trigPaths = cms.vstring(
      mupaths
      )
)
customMuons *= urMuons

## #JUST FOR CHECKING I AM DOING THE RIGHT THING!
## Does not work, don't know why
## xcheckMuons = cms.EDProducer(
##   "PATTriggerMatchMuonEmbedder",
##   src = cms.InputTag( 'fixme' ),
##   matches = cms.VInputTag(
##     cms.InputTag('matchMuonsIsoMu20eta2p1')
##     )
##   )
## customMuons *= xcheckMuons
