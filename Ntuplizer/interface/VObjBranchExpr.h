#ifndef VObjBranchExpr_H
#define VObjBranchExpr_H

#include "CommonTools/Utils/interface/StringObjectFunction.h"
#include "TTree.h"
#include <vector>

template <typename EDObject>
class VObjBranchExpr {
public:
  VObjBranchExpr(std::string branch_name, TTree* tree, std::string &expr):
    functor_(expr)
  {
    tree->Branch(branch_name.c_str(), &branch_vals_ );
  }
  void fill(const EDObject &obj) {branch_vals_.push_back(functor_(obj));}
  void reserve(size_t i) {branch_vals_.reserve(i);}
  void clear() {branch_vals_.clear();}
private:
  std::vector<double> branch_vals_;
  StringObjectFunction<EDObject> functor_;
};

#endif 
