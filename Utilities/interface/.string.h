#ifndef ur_string_H
#define ur_string_H

#include <string>
#include <vector>

namespace ur{
  class string: public std::string{
  public:
    //should not need constructors, 
    //given that this class only adds methods
    std::vector<string> split(const std::string &) const;
    string join(const std::vector<std::string &>) const;
    string upper() const;
    string lower() const;
    string replace(const std::string &, const std::string &) const;
    bool startswith(const std::string &) const;
    string slice(const int i, const int j) const;
    std::string cpp_str() const {return std::string(data());}
    //format
  };
}

#endif
