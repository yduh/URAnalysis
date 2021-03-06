#ifndef URAnalysisTest_cxx
#define URAnalysisTest_cxx


#include <vector>
#include <iostream>

#include "URAnalysisTest.h"
// #include "../utilities/constants.h"

void URAnalysisTest::begin()
{}



void URAnalysisTest::end()
{}



void URAnalysisTest::postProcess()
{}



void URAnalysisTest::analyze()
{
//   URMuonsSelector* muonSelector = new URMuonsSelector;

//   if (fChain == 0) return;

//   Long64_t nentries = (maxEvents == -1) ? fChain->GetEntries() : std::min((int)fChain->GetEntries(), maxEvents);

//   std::cout << "Analyzing " << nentries << " events.\n";

  // Book histograms here

  URMuonsSelector* muonSelector = new URMuonsSelector;
//   URElectronsSelector* electronSelector = new URElectronsSelector;
//   URJetsSelector* jetsSelector = new URJetsSelector;
//   URSelectorBase* muOrEleSelector = (*muonSelector)||electronSelector; 
//   URSelectorBase* muAndEleSelector = (*muonSelector)&&electronSelector;
//   URSelectorBase* complexSelector = (*muOrEleSelector)&&jetsSelector;
  
  
  URMuonsSelector muonSelector;
  URElectronsSelector electronSelector;
  URJetsSelector jetsSelector;
  URSelector& muOrEleSelector = muonSelector||electronSelector; 
  URSelector& muAndEleSelector = muonSelector&&electronSelector;
  URSelector& complexSelector = muOrEleSelector&&jetsSelector;
  
  URSelector& complexSelector2 = (muonSelector||electronSelector)&&jetsSelector;
  

  while(event->next())
//   URMuonsSelector muonSelector;
//   URElectronsSelector electronSelector;
//   URJetsSelector jetsSelector;
//   URSelector& muOrEleSelector = muonSelector||electronSelector; 
//   URSelector& muAndEleSelector = muonSelector&&electronSelector;
//   URSelector& complexSelector = muOrEleSelector&&jetsSelector;
//   
//   URSelector& complexSelector2 = (muonSelector||electronSelector)&&jetsSelector;
  std::cout << "tree_ is " << (unsigned long int) &tree_ << std::endl;
  tree_->Print();
  URStreamer event(tree_);
  std::cout << "event is " << (unsigned long int) &event << std::endl;
//   while(event->next())
  {
    std::cout << "inside the event loop\n";
//     const vector<Muon>& Muons = event->muons();
//     for(auto muon=Muons.begin(); muon!=Muons.end(); muon++)
//     {
//       float muon_pt = muon->pt();
//       std::cout << "muon pt = " << muon_pt << std::endl;
//       bool isGlobal = muon->isGlobal();
//       std::cout << "Muon is global = " << isGlobal << std::endl;
//       bool isMuSelected = muonSelector.select(event);
//       bool isEleSelected = electronSelector.select(event);
//       bool isJetsSelected = jetsSelector.select(event);
//       bool isMuOrEleSelected = muOrEleSelector.select(event);
//       bool isMuAndEleSelected = muAndEleSelector.select(event);
//       bool isComplexSelected = complexSelector.select(event);
//       bool isComplex2Selected = complexSelector2.select(event);
//       
//       std::cout << "isMuSelected = " << isMuSelected << ", isEleSelected = " << isEleSelected << ", isJetsSelected = " << isJetsSelected << std::endl;
//       std::cout << "isMuOrEleSelected = " << isMuOrEleSelected << ", isMuAndEleSelected = " << isMuAndEleSelected << ", isComplexSelected = " << isComplexSelected << ", isComplex2Selected = " << isComplex2Selected << std::endl;
//     }
    
  }

//   Long64_t nbytes = 0, nb = 0;
//   for (Long64_t jentry=0; jentry<nentries;jentry++)
//   {
//     if(jentry%1000 == 0)
//       std::cout << "Loop over entry " << jentry << "/" << nentries << ".\n";
//     Long64_t ientry = LoadTree(jentry);
//     if (ientry < 0) break;
//     nb = fChain->GetEntry(jentry);   nbytes += nb;
//     // if (Cut(ientry) < 0) continue;
//   }

  // Keep this line here!
//   outFile_.cd();

  // Create and write canvases here

  // Uncomment this line to write also the histograms to the file
//   outFile_.Write();
} 

#endif // URAnalysisTest_cxx
