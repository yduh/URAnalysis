// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "URAnalysis/Ntuplizer/interface/Obj2BranchBase.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "TTree.h"
#include <iostream>

class EvtIDProducer: public Obj2BranchBase{
public:
  EvtIDProducer(edm::ParameterSet cfg);
  ~EvtIDProducer(){}

private:
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  unsigned int lumi_;
  unsigned int run_;
  unsigned long long evt_;
};

EvtIDProducer::EvtIDProducer(edm::ParameterSet cfg):
  Obj2BranchBase(cfg)
{
  //book fixed branches
  tree_.branch("run/i", &run_);
  tree_.branch("lumi/i", &lumi_);
  tree_.branch("evt/l", &evt_);
}

void EvtIDProducer::analyze(const edm::Event& evt, const edm::EventSetup&)
{
  lumi_= evt.id().luminosityBlock();
  run_ = evt.id().run();
  evt_ = evt.id().event();
}

//define CMSSW plug-ins
DEFINE_FWK_MODULE(EvtIDProducer);



