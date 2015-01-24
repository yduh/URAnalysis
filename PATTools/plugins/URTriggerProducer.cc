/*
Produces a ura::TriggerEvent object from miniAOD content, making 
trigger information retreival easier

largely taken from:
https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookMiniAOD#Trigger

Author: Mauro Verzetti (UR)
 */

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/Handle.h"

#include "URAnalysis/DataFormats/interface/TriggerEvent.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"

#include <vector>
#include <string>
//
// class declaration
//

class URTriggerProducer : public edm::EDProducer {
public:
  explicit URTriggerProducer(const edm::ParameterSet&);
  ~URTriggerProducer();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  virtual void beginJob() override;
  virtual void produce(edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;
      
  // ----------member data ---------------------------
  
  edm::EDGetTokenT<edm::TriggerResults> triggerBits_;
  edm::EDGetTokenT<pat::PackedTriggerPrescales> triggerPrescales_;
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

URTriggerProducer::URTriggerProducer(const edm::ParameterSet& cfg):
  triggerBits_(consumes<edm::TriggerResults>(cfg.getParameter<edm::InputTag>("bits"))),
  triggerPrescales_(consumes<pat::PackedTriggerPrescales>(cfg.getParameter<edm::InputTag>("prescales")))
{
  produces<ura::TriggerEvent>();
}



URTriggerProducer::~URTriggerProducer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------

void
URTriggerProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  edm::Handle<edm::TriggerResults> triggerBits;
  edm::Handle<pat::PackedTriggerPrescales> triggerPrescales;

  iEvent.getByToken(triggerBits_, triggerBits);
  iEvent.getByToken(triggerPrescales_, triggerPrescales);

  const edm::TriggerNames &names = iEvent.triggerNames(*triggerBits);

  std::unique_ptr<ura::TriggerEvent> output(new ura::TriggerEvent());
  for (unsigned int i = 0, n = triggerBits->size(); i < n; ++i) {
    output->add_path( 
      names.triggerName(i), 
      triggerBits->accept(i), 
      triggerBits->wasrun(i), 
      triggerBits->error(i), 
      triggerPrescales->getPrescaleForIndex(i)
   );
  }

  iEvent.put(std::move(output)); 
}

// ------------ method called once each job just before starting event loop  ------------

void 
URTriggerProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------

void 
URTriggerProducer::endJob() {
}

// ------------ method called when starting to processes a run  ------------
/*
void
URTriggerProducer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
URTriggerProducer::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
URTriggerProducer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
URTriggerProducer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------

void
URTriggerProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define CMSSW plug-ins
DEFINE_FWK_MODULE(URTriggerProducer);

