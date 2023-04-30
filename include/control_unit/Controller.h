#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>
#include <memory>
#include <deque>
#include <thread>

#include "Network.h"
#include "Message.h"

using namespace std;

class Point {};

class Controller {
    public:
    Controller(unique_ptr<Network> network) {
        _network = network.get();
        _network_thread = thread(&Network::run, move(network));
    }
    ~Controller() {
        _network_thread.join();
    }
    string printStatus();
    
    void runNetwork();
    void runStateMachine();
    void sendEvent(Message);
    void shutdown();

    void toggle();

    Message::Data GetMeasurement();


    private:
    deque<Message> _events;
    deque<Message> _data;
    mutex _data_mtx;
    mutex _events_mtx;
    thread _network_thread;
    Network* _network = nullptr;
    bool _running {true};
    bool _measurementMode {false};
    int _ms_waited_for_network = 0;
    int _message_counter = 0;
    
};

#endif
