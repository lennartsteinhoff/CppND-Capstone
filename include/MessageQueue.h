#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

#include <deque>

template<typename T> 
class MessageQueue {
    
    private:
    std::deque<T> _queue;

};

#endif