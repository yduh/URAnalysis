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
    edm::ParameterSet branches = cfg.getParameter<edm::ParameterSet>("branches");
    std::vector< std::string > branch_names = branches.getParameterNames();
    branches_.reserve(branch_names.size());
    for(auto&& name : branch_names)
      {
	std::string expr = branches.getParameter<std::string>(name);
	std::string full_name = prefix+"_"+name;
	try
	  {
	       branches_.push_back(new VObjBranchExpr<EDObject>(full_name, tree, expr));
	  }
	catch(cms::Exception& iException)
	  {
	    iException << "Caught exception in building branch: "
		       << full_name << " with formula: " << expr;
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
  std::vector< VObjBranchExpr<EDObject>* > branches_;
};

#endif //Collection2Branch
