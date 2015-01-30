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
    std::lock_guard<std::mutex> lock(mutex_);
    bool val = queue_.empty();
    return val;
  }
  size_t size()
  {
    std::lock_guard<std::mutex> lock(mutex_);
    size_t val = queue_.size();
    return val;
  }
  T pop()
  {
    std::lock_guard<std::mutex> lock(mutex_);
    T val = queue_.front();
    queue_.pop();
    return val;
  }
  void push(T &val)
  {
    std::lock_guard<std::mutex> lock(mutex_);
    queue_.push(val);
  }

private:
  std::mutex mutex_;
  std::queue<T> queue_;
};
#endif
