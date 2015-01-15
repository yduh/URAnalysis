/*
Singleton class that provides the instance of the TTree where to write the events

Author: Mauro Verzetti (UR)
 */

#include "TTree.h"
#include "TFile.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

class EventTree{
 public:
  static TTree* getTree(){
    static EventTree instance;
    return instance.tree();
    //return instance;
  }
  TTree* tree(){return tree_;}

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
};
