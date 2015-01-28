#ifndef URStandardSelectors_h
#define URStandardSelectors_h

#include <string>

#include "../../AnalysisTools/scripts/URStreamer.h"
#include "URSelector.h"



class URMuonsSelector: public URSelector
{
  public:
    virtual bool select(URStreamer* event) {if(event->muons().size() > 1) return true; return false;};
};



class URElectronsSelector: public URSelector
{
  public:
    virtual bool select(URStreamer* event) {if(event->electrons().size() > 1) return true; return false;};
};



class URJetsSelector: public URSelector
{
  public:
    virtual bool select(URStreamer* event) {if(event->jets().size() > 4) return true; return false;};
};



#endif // URStandardSelectors_h