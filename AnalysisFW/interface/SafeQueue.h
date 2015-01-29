#ifndef SafeQueue_h
#define SafeQueue_h

/*
Threaded-safe version of STL queue, because, surprisingly,
no official implementation exists. 

author: Mauro Verzetti (UR)
 */

#include <queue>
#include <mutex>

template<typename T>
class SafeQueue{
public:
  SafeQueue():
    mutex_(),
    queue_(){}

  bool empty()
  {
    mutex_.lock();
    bool val = queue_.empty();
    mutex_.unlock();
    return val;
  }
  size_t size()
  {
    mutex_.lock();
    size_t val = queue_.size();
    mutex_.unlock();
    return val;
  }
  T pop()
  {
    mutex_.lock();
    T val = queue_.front();
    queue_.pop();
    mutex_.unlock();
    return val;
  }
  void push(T &val)
  {
    mutex_.lock();
    queue_.push(val);
    mutex_.unlock();
  }

private:
  std::mutex mutex_;
  std::queue<T> queue_;
};
#endif
