#ifndef URStandardSelectors_cc
#define URStandardSelectors_cc

#include <string>

#include "URStandardSelectors.h"
#include "Logger.h"



bool URMuonsSelector::select(URStreamer* event)
{
  int nMuons = 0;
  for(auto muon = event->muons().begin(); muon != event->muons().end(); muon++)
  {
    if(select(*muon))
    {
      nMuons++;
    }
  }
  if(nMuons >= nMin_)
    return true;
  return false;
}



bool URMuonsSelector::select(const Muon& muon)
{
  if(muon.pt() > ptMin_ &&
     fabs(muon.eta()) < etaMax_)
  {
    return (this->*muonSelection_)(muon);
  }
  return false;
}



void URMuonsSelector::getConfiguration()
{
  URSelector::getConfiguration();
  if(!isConfigured_)
  {
    URParser& parser = URParser::instance();
    
    opts::options_description & muonsSelectorOptions = parser.optionGroup("MuonsSelector", "options related to the muons selector", URParser::CFG);
    muonsSelectorOptions.add_options()
      ("MuonsSelector.ptMin",opts::value<double>(),"Minimum pt threshold of muon selection.")
      ("MuonsSelector.etaMax", opts::value<double>(),"Maximum eta threshold of muon selection.")
      ("MuonsSelector.nMin", opts::value<int>(),"Minimum number of good muons required per event.")
      ("MuonsSelector.selectionName", opts::value<std::string>(),"Name of selection to apply.");
      
    parser.parseArguments();

    ptMin_ = (parser.values())["MuonsSelector.ptMin"].as<double>();
    etaMax_ = (parser.values())["MuonsSelector.etaMax"].as<double>();
    nMin_ = (parser.values())["MuonsSelector.nMin"].as<int>();
    selectionName_ = (parser.values())["MuonsSelector.selectionName"].as<std::string>();
   
    setMuonSelection();
    
    isConfigured_ = true;
  }
}



void URMuonsSelector::setMuonSelection()
{
  if(!selectionName_.compare("tight"))
    muonSelection_ = &URMuonsSelector::tightSelection;
  else
    muonSelection_ = &URMuonsSelector::passThroughSelection;
}



bool URMuonsSelector::tightSelection(const Muon& muon)
{
  return (muon.isGlobal() && muon.isTracker() && muon.validHits()>2);
}



bool URMuonsSelector::passThroughSelection(const Muon& muon)
{
  Logger::log().warning() << "W A R N I N G ! URMuonsSelector: using pass-through muon selection! Please set correct selection type in cfg file!\n";
  return true;
}



#endif //URStandardSelectors_cc
