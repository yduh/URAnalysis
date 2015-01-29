#ifndef Worker_h
#define Worker_h

#include <thread>
#include <string>

/*
Simple generic implementation of a thread worker
 */

class Worker{
public:
  Worker(std::string &id):
    id_(id),
    thread_(){}

  void start(){thread_ = std::thread(&Worker::work, this);}
  void join(){thread_.join();}

private:
  virtual void work() = 0;
  std::thread thread_;

protected:
  std::string id_;
};

#endif
