// -*- C++ -*-
//
// Package:    URNTuplizer
// Class:      URNTuplizer
// 
/**\class URNTuplizer URNTuplizer.cc URAnalysis/Ntuplizer/plugins/URNTuplizer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Yi-Ting Duh,28 2-007,+41227677897,
//         Created:  Wed Nov 12 12:12:59 CET 2014
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TTree.h"
#include "URAnalysis/Ntuplizer/interface/ConverterFactory.h"
#include <iostream>
//
// class declaration
//

class URNTuplizer : public edm::EDAnalyzer {
public:
  explicit URNTuplizer(const edm::ParameterSet&);
  ~URNTuplizer();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;

  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  virtual void endRun(edm::Run const&, edm::EventSetup const&);
  virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

  // ----------member data ---------------------------
  TTree *tree_;
  std::vector< std::shared_ptr<Obj2BranchBase> > object_dumpers_;
  //provides automatic garbage collection
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
URNTuplizer::URNTuplizer(const edm::ParameterSet& iConfig)
{
  typedef std::vector<std::string> vstring;
  typedef edm::ParameterSet PSet;
  //now do what ever initialization is needed
  edm::Service<TFileService> fs;
  std::string treeName = iConfig.getParameter<std::string>("treeName");
  tree_ = fs->make<TTree>(treeName.c_str(), "test");

  PSet objects = iConfig.getParameter<PSet>("objects");
  vstring object_names;
  objects.getParameterSetNames(object_names);
  for(vstring::const_iterator obj_name = object_names.begin(); obj_name != object_names.end(); ++obj_name)
    {
      PSet obj_cfg = objects.getParameter<PSet>(*obj_name);
      std::string type = obj_cfg.getParameter<std::string>("type");
      object_dumpers_.push_back( std::shared_ptr<Obj2BranchBase>(make_converter(type, *obj_name, obj_cfg, tree_)) );
    }
}


URNTuplizer::~URNTuplizer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
  
}


//
// member functions
//

// ------------ method called for each event  ------------
void
URNTuplizer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   for(auto&& dumper : object_dumpers_) dumper->clear();
   for(auto&& dumper : object_dumpers_) dumper->fill(iEvent);
   //std::cout << "tree dump: Entries: " << tree_->GetEntries() << std::endl;
   //for(auto&& dumper : object_dumpers_) dumper->debug();
   tree_->Fill();
}


// ------------ method called once each job just before starting event loop  ------------
void 
URNTuplizer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
URNTuplizer::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
URNTuplizer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
URNTuplizer::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
URNTuplizer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
URNTuplizer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
URNTuplizer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(URNTuplizer);
