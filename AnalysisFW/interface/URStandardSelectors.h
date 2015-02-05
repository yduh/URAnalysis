#ifndef URStandardSelectors_h
#define URStandardSelectors_h

#include "../../AnalysisTools/scripts/URStreamer.h"
#include "URSelector.h"



class URMuonsSelector: public URSelector
{
  public:
    URMuonsSelector(){isConfigured_ = false; ptMin_ = 0; etaMax_ = 0; nMin_ = 999; getConfiguration();};
    virtual bool select(URStreamer* event);
    bool select(const Muon& muon);
    void getConfiguration() override;
    
    typedef bool (URMuonsSelector::*muonSelection)(const Muon&);

  private:
    bool tightSelection(const Muon& muon);
    bool passThroughSelection(const Muon& muon);
    void setMuonSelection();
    bool isConfigured_;
    double ptMin_;
    double etaMax_;
    int nMin_;
    std::string selectionName_;
    muonSelection muonSelection_;
    
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



class URMETSelector: public URSelector
{
  public:
    virtual bool select(URStreamer* event) {return true;}
};



#endif // URStandardSelectors_h
