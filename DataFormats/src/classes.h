#include "URAnalysis/DataFormats/interface/TriggerEvent.h"
#include "DataFormats/Common/interface/Wrapper.h"

namespace {
  struct URAnalysis_DataFormats_dicts {
    ura::TriggerEvent dummyTrigEvent;
    ura::TriggerEvent::TrigInfo dummyTrigInfo;
    std::vector< ura::TriggerEvent::TrigInfo > dummyVector;
    edm::Wrapper<ura::TriggerEvent> dummyTrigEventWrapped;
  };
}
