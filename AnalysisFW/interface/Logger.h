#ifndef Logger_h
#define Logger_h

/*
  class Logger:
  Singleton to handle logging within c++ commands
  in a python-like way
 */
#include <ostream>

class Logger
{
public:
  enum Level{DEBUG, INFO, WARNING, ERROR, FATAL, DISABLED};
  void setLevel(Level lv) {level_ = lv;}
  static Logger& log()
  {
    static Logger val;
    return val;
  }
  
  //void dbg(Level lv) {std::cout << "level " << level_ << ", required: " << lv << std::endl;}
  std::ostream& debug()  {return (level_ <= DEBUG) ? std::cout : null_;}
  std::ostream& info()   {return (level_ <= INFO) ? std::cout : null_;}
  std::ostream& warning(){return (level_ <= WARNING) ? std::cout : null_;}
  std::ostream& error()  {return (level_ <= ERROR) ? std::cout : null_;}
  std::ostream& fatal()  {return (level_ <= FATAL) ? std::cout : null_;}

private:
  Logger():
    level_(DISABLED),
    null_(0){}
  
  //No need to implement those
  Logger(Logger const&);
  void operator=(Logger const&);

  Level level_;
  std::ostream null_;
};

#endif
