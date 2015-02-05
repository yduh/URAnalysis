#ifndef URSelector_cc
#define URSelector_cc

#include "URSelector.h"



void URSelector::getConfiguration()
{
  if(!baseIsConfigured)
  {
    // here gets the getConfiguration
    URParser& parser = URParser::instance();
    // Put any configuration parameters for the base class here
    
    baseIsConfigured = true;
  }
}



URSelector& URSelector::operator||(URSelector& other)
{
  URSelectorOR* result = new URSelectorOR(*this,other);
  return *result;
}



URSelector& URSelector::operator&&(URSelector& other)
{
  URSelectorAND* result = new URSelectorAND(*this,other);
  return *result;
}



#endif // URSelector_cc
