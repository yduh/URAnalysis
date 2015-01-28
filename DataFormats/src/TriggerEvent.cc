#include "URAnalysis/DataFormats/interface/TriggerEvent.h"
#include "FWCore/Utilities/interface/RegexMatch.h"
#include <boost/regex.hpp>

namespace ura{
  std::vector<TriggerEvent::TrigInfo> TriggerEvent::matching_paths(std::string &pattern) const
  {
    boost::regex matcher(edm::glob2reg(pattern));
    std::vector<TriggerEvent::TrigInfo> ret_val;
    for(auto it = path_info_.cbegin(); it != path_info_.cend(); ++it){
      if( boost::regex_match(it->name, matcher) ) ret_val.push_back(*it);
    }
    return ret_val;
  }

  TriggerEvent::TrigInfo TriggerEvent::matching_path(std::string &pattern) const
  {
    std::vector<TriggerEvent::TrigInfo> matched = matching_paths(pattern);
    if(matched.size() > 0)
      return matched[0];
    else
      return TriggerEvent::TrigInfo(); 
  }

  bool TriggerEvent::has_path(std::string &pattern) const
  {
    //code matching again to increase computation speed
    boost::regex matcher(edm::glob2reg(pattern));
    for(auto it = path_info_.cbegin(); it != path_info_.cend(); ++it){
      if( boost::regex_match(it->name, matcher) ) return true;
    }
    return false;
  }
}
