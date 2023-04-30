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
    string printStatus(){
        string status = _measurementMode ? "ongoing" : "stopped";
        return "Controller: Measurement " + status + "Network: " + _network->printNetworkActivity();
    }
    
    void runNetwork();
    void runStateMachine();
    void sendEvent(Message);
    void shutdown() {
        _running = false;
        _network->send("control: shutdown_sensor");
        this_thread::sleep_for(chrono::milliseconds(1000));
        string s{"Unlock blocking network call on Sensor site"};
        cout << "Controller: " << s << endl;
        _network->send(s);
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout << "Controller: Shuttdown own network" << endl;
        _network->shutdown();
        this_thread::sleep_for(chrono::seconds(1));
        cout << "Controller: Exit shutdown sequence" << endl;
    }

    void toggle() {
        _measurementMode = !_measurementMode;
    }

    Message::Data GetMeasurement();


    private:
    deque<Message> _events;
    deque<Message> _data;
    thread _network_thread;
    Network* _network = nullptr;
    bool _running {true};
    bool _measurementMode {false};
};

#endif
