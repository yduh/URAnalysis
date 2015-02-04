#ifndef ProgressBar_h
#define ProgressBar_h

//
// Simple class to provide a ProgressBar, because C++ 
// does not have any nice libs
//

#include <atomic>

#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <iostream>
#include <iomanip>
#include <mutex>

class ProgressBar{
public:
  ProgressBar(unsigned int max, unsigned int update=1):
    mutex_(),
    max_(max),
    update_every_(update),
    counter_(0)
  {
    struct winsize size;
    ioctl( 0, TIOCSWINSZ, (char *) &size );
    wsize_ = size.ws_row;
  }

  //inline to be faster
  inline void update(){
    std::lock_guard<std::mutex> lock(mutex_);
    counter_++;
    if(counter_ % update_every_ != 0) return;
    
    float ratio  =  counter_/(float)max_;
    int   c      =  ratio * wsize_;
    std::cout << setw(3) << (int)(ratio*100) << "% [";
    for (int x=0; x<c; x++) std::cout << "=";
    for (int x=c; x<w; x++) std::cout << " ";
    std::cout << "]\r" << std::flush;
  }  
private:
  std::mutex mutex_;
  const unsigned int max_, update_every_;
  std::atomic_uint counter_;
  int wsize_;
};

#endif
