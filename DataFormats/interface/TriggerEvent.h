#ifndef URA_TriggerEvent_h
#define URA_TriggerEvent_h

#include <vector>
#include <string>

/*
  Class TriggerEvent:
  Fully custom Trigger event wrapper, so that we can have all information
  in one place. The pat one cannot be run on miniAOD.
 */


namespace ura{
  class TriggerEvent{
  public:
    struct TrigInfo {
      std::string name;
      bool accept, run, error;
      int prescale;
      TrigInfo():
	name(),
	accept(false), 
	run(false), 
	error(false),
	prescale(999){}
      TrigInfo(std::string &_name, bool _accept, bool _run, bool _error, int _prescale):
	name(_name),
	accept(_accept), 
	run(_run), 
	error(_error),
	prescale(_prescale){}
    };

    /*
      Only empty constructor, to make compilation faster,
      leave the filling to the plug-in, so if input collections
      change (due to a change in the miniAOD content) we do not 
      have to recompile the DataFormat, which is a pain.
     */
    TriggerEvent():
      path_info_(){}

    void add_path(std::string _name, bool _accept, bool _run, bool _error, int _prescale){
      path_info_.push_back(TrigInfo(_name, _accept, _run, _error, _prescale));
      // path_names_.push_back(name);
      // path_info_.push_back(TrigInfo(_accept, _run, _error, _prescale));
    }

    //returns a vector of paths matching the pattern (* allowed)
    std::vector<TrigInfo> matching_paths(std::string &pattern) const;

    //returns the first path matching the selection, if none is found an empty value is created
    TrigInfo matching_path(std::string &pattern) const;

    //returns if exists a path matching the pattern
    bool has_path(std::string &pattern) const;

    //TODO: should be cached somehow!
    //returns the list of filters that belong to the first path matching the pattern,
    //filters are ordered lexicographically (alphabetically)
    //std::vector<std::string> filters(std::string pattern) 
    
  private:
    //Store results in a vector and not in a map because later we want to 
    //enable regexes lookup, which would break map implementation
    std::vector< TrigInfo > path_info_;
    // std::vector<string> path_names_;
    // std::vector<TrigInfo> path_info_;
  };
}

#endif
