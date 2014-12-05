#ifndef VObjBranchExpr_H
#define VObjBranchExpr_H

#include "CommonTools/Utils/interface/StringObjectFunction.h"
#include "TTree.h"
#include <vector>
#include <iostream>
#include <memory>
#include "TMath.h"

template<typename T> T as(double x){ return static_cast<T>(x);} //for long ints should be reinterpret cast both sides (parser too) 
template<> double as<Double_t>(double x) { return x; } //do nothing
template<> float as<Float_t>(double x) { return x; } //do nothing
template<> int as<Int_t>(double x) { return TMath::Nint(x); } //avoid rounding errors

template <typename EDObject, typename VType>
class VObjBranchExpr {
public:
  VObjBranchExpr(std::string branch_name, TTree* tree, std::string &expr):
    branch_vals_(),
    functor_(expr),
    name_(branch_name)
  {
    //std::cout<<name_ <<": set branch to vals addr: " << &branch_vals_ << std::endl;
    branch_ = tree->Branch(branch_name.c_str(), &branch_vals_);
    //std::cout<<name_ <<": set branch to vals addr: " << &branch_vals_ << std::endl;
  }

  ~VObjBranchExpr(){ /*delete branch_vals_;*/ }
  void fill(const EDObject &obj) {branch_vals_.push_back( as<VType>(functor_(obj)));}
  void reserve(size_t i) {branch_vals_.reserve(i);}
  void clear() {branch_vals_.clear();}
  void debug() {std::cout<<name_ <<" vals addr: "<< &branch_vals_<< " branch addr: "<< (std::vector<VType>*) branch_->GetAddress() << std::endl;}

private:
  std::vector<VType> branch_vals_;
  TBranch *branch_;
  StringObjectFunction<EDObject> functor_;
  std::string name_;
};

#endif 
