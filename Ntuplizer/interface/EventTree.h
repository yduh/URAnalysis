/*
Singleton class that provides the instance of the TTree where to write the events

Author: Mauro Verzetti (UR)
 */
#ifndef EventTree_h
#define EventTree_h


#include "TTree.h"
#include "TFile.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include <string>
#include <set>
#include <iostream>

class EventTree{
 public:
  static EventTree& getTree(){
    static EventTree instance;
    return instance; //instance.tree();
    //return instance;
  }
  //TTree* tree(){return tree_;}

  template<typename ... Args>
  TBranch* branch(std::string name, Args ... args){
    //std::cout<< "trying to create branch: " << name << std::endl;
    if(branch_names_.find(name) != branch_names_.end()){
      throw edm::Exception(edm::errors::Configuration) 
	<< "branch name: " << name << " has been already defined!";
    }
    branch_names_.insert(name);
    return tree_->Branch(name.c_str(), args ...);
  }

  void fill(){tree_->Fill();}

  ~EventTree(){
    edm::Service<TFileService> fs;
    fs->file().cd();
    tree_->Write();
  }
 private:
  EventTree(){
    edm::Service<TFileService> fs;
    fs->file().cd();
    tree_ = new TTree("Events", "test");
  }
  EventTree(EventTree const&);             
  void operator=(EventTree const&);
  TTree *tree_;
  std::set<std::string> branch_names_;
};

#endif
