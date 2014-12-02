#ifndef ConverterFactory_H
#define ConverterFactory_H

#include <string>
#include "URAnalysis/Ntuplizer/interface/Obj2BranchBase.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "TTree.h"

//Obj2BranchBase* make_converter(std::string, std::string, edm::ParameterSet, TTree*);
#include <string>
//#include "URAnalysis/Ntuplizer/interface/ConverterFactory.h"
#include "URAnalysis/Ntuplizer/interface/Collection2Branch.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "TTree.h"

//PAT Includes                                                                                                                                                                                                                              
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

Obj2BranchBase* make_converter(std::string type, std::string prefix, edm::ParameterSet cfg, TTree* tree)
{
  if( type == "MuonCollection2Branch" ) return new Collection2Branch<pat::Muon>(prefix, cfg, tree);
  else if( type == "ElectrononCollection2Branch" ) return new Collection2Branch<pat::Electron>(prefix, cfg, tree);
  else if( type == "JetCollection2Branch" ) return new Collection2Branch<pat::Jet>(prefix, cfg, tree);
  else {
    throw edm::Exception(edm::errors::Configuration)
      << "No converter found with name " << type << "\n"
      << "If it has not been a mistake please add such option in:\n"
      << "URAnalysis/Ntuplizer/interface/ConverterFactory.h\n"
      << "and then recompile";
  }
  return 0;
}

#endif
