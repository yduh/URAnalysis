/*
Filters events based on a trigger selection.
The selection is passed as a string and applied to a ura::TriggerEvent

Author: Mauro VErzett (UR)
 */


#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "URAnalysis/DataFormats/interface/TriggerEvent.h"
#include "CommonTools/Utils/interface/StringCutObjectSelector.h"

class URTriggerFilter : public edm::EDFilter {
public:
  URTriggerFilter(const edm::ParameterSet& pset);
  virtual ~URTriggerFilter(){}
  bool filter(edm::Event& evt, const edm::EventSetup& es);
private:
  edm::InputTag src_;
  StringCutObjectSelector<ura::TriggerEvent> cut_;
};

URTriggerFilter::URTriggerFilter(const edm::ParameterSet& pset):
  src_(pset.getParameter<edm::InputTag>("src")),
  cut_(pset.getParameter<std::string>("cut"), true) { }

bool URTriggerFilter::filter(edm::Event& evt, const edm::EventSetup& es) {
  edm::Handle<ura::TriggerEvent> trgevt;
  evt.getByLabel(src_, trgevt);
  return cut_(*trgevt);
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(URTriggerFilter);
