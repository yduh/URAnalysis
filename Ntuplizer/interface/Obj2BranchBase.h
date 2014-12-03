#ifndef Obj2BranchBase_H
#define Obj2BranchBase_H

namespace edm{
  class Event;
}

class Obj2BranchBase{
 public:
  virtual void fill(const edm::Event &) = 0;
  virtual void clear() {};
  virtual void debug() {};
 private:
};

#endif
