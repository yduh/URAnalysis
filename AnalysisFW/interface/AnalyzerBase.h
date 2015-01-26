#ifndef AnalyzerBase_h
#define AnalyzerBase_h

#include "AnalyzerBase.C"
#include "../../AnalysisTools/scripts/URStreamer.h"
// #include "../../AnalysisTools/scripts/Dict.cxx"
//#include "HistoPlotter.C"



class URSelector;

class AnalyzerBase
{
  public:
//     AnalyzerBase() 
//     {
//       std::cout << "AnalyzerBase: Please call constructor with arguments!\n";
//     };
    AnalyzerBase(const std::string myName_, const std::string sampleName_, const std::string text_, const int maxEvents_ = -1, TTree* tree=0) : 
    event(new URStreamer(tree)) 
    {
      Initialize(myName_, sampleName_, text_, maxEvents_);
      InitSelector();
    };
    ~AnalyzerBase();

    friend class URSelector;

  private:
    void InitSelector();
    void Initialize(const std::string myName_, const std::string sampleName_, const std::string text_, const int maxEvents_);
    std::string myName;
    
  protected:
    URStreamer* event;
    URSelector* s;
    std::string sampleName;
    int maxEvents;
    std::string text;
    TFile* outFile;
    TTree* tree;
};

#endif // AnalyzerBase_h
