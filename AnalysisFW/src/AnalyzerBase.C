#ifndef AnalyzerBase_cxx
#define AnalyzerBase_cxx

#include <typeinfo>

#include "AnalyzerBase.h"



AnalyzerBase::~AnalyzerBase()
{
  outFile_.Close();
}

#endif // AnalyzerBase_cxx
