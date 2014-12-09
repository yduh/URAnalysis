#ifndef Collection2Branch_H
#define Collection2Branch_H

#include "URAnalysis/Ntuplizer/interface/Obj2BranchBase.h"
#include "URAnalysis/Ntuplizer/interface/VObjBranchExpr.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include <vector>
#include <string>
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Common/interface/Handle.h"
#include "TTree.h"
#include "FWCore/Framework/interface/Event.h"
#include <iostream>

template <class EDObject>
class Collection2Branch: public Obj2BranchBase{
public:
  Collection2Branch(std::string prefix, edm::ParameterSet cfg, TTree *tree):
    src_(cfg.getParameter<edm::InputTag>("src"))
  {
    std::vector< edm::InputTag > branches = cfg.getParameter<std::vector< edm::InputTag > >("branches");
    branches_.reserve(branches.size());
    for(auto&& branch : branches)
      {
	BranchInfo info(prefix, branch);
	try
	  {
	    branches_.push_back(VObjBranchExprFactory<EDObject>(info, tree));
	  }
	catch(cms::Exception& iException)
	  {
	    iException << "Caught exception in building branch: "
		       << info.name << " with formula: " << info.expr;
	    throw;
	  }
      }
  }

  ~Collection2Branch(){ for(size_t i=0; i<branches_.size(); i++) delete branches_[i]; }
  virtual void fill(const edm::Event &evt)
  {
    edm::Handle< std::vector<EDObject> > handle;
    evt.getByLabel(src_, handle);

    size_t size = handle->size();
    //std::cout << "got " << src_ << " with size: " << size << std::endl;
    for(auto&& branch : branches_)
      {
	branch->reserve(size);
      }

    //std::cout << "reserved space" << std::endl;
    for(auto&& obj : *handle)
      {
	for(auto&& branch : branches_)
	  {
	    branch->fill(obj);
	  }
      }
    //std::cout << "filled branches" << std::endl;
  }
  virtual void clear(){for(auto&& branch : branches_) branch->clear();}
  virtual void debug(){for(auto&& branch : branches_) branch->debug();}
private:
  std::string prefix_;
  edm::InputTag src_;
  std::vector< ObjExpression<EDObject>* > branches_;
};

#endif //Collection2Branch
