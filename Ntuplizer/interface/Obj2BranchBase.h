#ifndef Obj2BranchBase_H
#define Obj2BranchBase_H

#include <string>
#include "URAnalysis/Ntuplizer/interface/EventTree.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

namespace edm{
  class Event;
  class Run;
  class EventSetup;
  class LuminosityBlock;
}

class Obj2BranchBase: public edm::EDAnalyzer {
public:
  explicit Obj2BranchBase(const edm::ParameterSet& cfg):
    tree_(EventTree::getTree())
  {
    if(cfg.existsAs<std::string>("label")){
      prefix_ = cfg.getParameter<std::string>("label");
    }else{
      prefix_ = cfg.getParameter<std::string>("@module_label");
    }

    //check for no _ in the prefix
    if(prefix_.find("_") != std::string::npos){
      throw edm::Exception(edm::errors::Configuration)
	<< "Module labels and prefix labels containing underscores ('_')"
	<< " are forbidden within the URAnalysis framework as they are "
	<< "internally used for branch bookkeeping purposes, please "
	<< "behave accordingly.";
    }
  }

private:
  virtual void beginJob() {};
  virtual void endJob() {};

  virtual void beginRun(edm::Run const&, edm::EventSetup const&){};
  virtual void endRun(edm::Run const&, edm::EventSetup const&){};
  virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&){};
  virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&){};

protected:
  std::string prefix_;
  EventTree & tree_;
};

#endif
