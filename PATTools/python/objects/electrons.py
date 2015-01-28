import FWCore.ParameterSet.Config as cms

urSkimmedElectrons = cms.EDFilter(
    "PATElectronSelector",
    src = cms.InputTag("fixme"),
    cut = cms.string('pt > 15 && abs(eta) < 2.5')
)
customElectrons = cms.Sequence(
   urSkimmedElectrons
)

#trigger match
from URAnalysis.PATTools.objects.trigger import trigger_paths, match_template

matchers = []
elpaths = [i for i in trigger_paths if 'Ele' in i]
for path in elpaths:
   matcher_name = 'matchElectrons%s' % path.replace('_','')
   matchers.append(matcher_name)
   globals()[matcher_name] = match_template.clone(
      src = cms.InputTag('urSkimmedElectrons'),
      matchedCuts = cms.string('path("HLT_%s_v*") || type("TriggerElectron")' % path)
      )
   customElectrons *= globals()[matcher_name]

urElectrons = cms.EDProducer(
   'PATElectronsEmbedder',
   src = cms.InputTag('fixme'),
   trigMatches = cms.VInputTag(
      cms.InputTag(i) for i in matchers
      ),
   trigPaths = cms.vstring(
      elpaths
      )
)
customElectrons *= urElectrons

