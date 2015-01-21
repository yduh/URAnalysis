from FWCore.ParameterSet.VarParsing import VarParsing

options = VarParsing("analysis")
#inputFiles, outputFile, maxEvents
#options come for free in the VarParsing
options.register(
   'globalTag',
   '',
   VarParsing.multiplicity.singleton,
   VarParsing.varType.string,
   'global tag to be used'
)
options.register(
   'isMC',
   False,
   VarParsing.multiplicity.singleton,
   VarParsing.varType.bool,
   'global tag to be used'
)
