#include <iostream>
#include <chrono> 
#include <thread>
#include <memory>
#include <deque>

#include "Socket.h"
#include "Sensor.h"
#include "Network.h"

using namespace std;

void Sensor::run() {
    while (true)
    {
        if (_network) updateInput();

        switch (_state)
        {
            case SensorState::sleep:
                cout << "Sensor: Sleeping" << endl;
                break;
            
            case SensorState::running:
                cout << "Sensor: Running" << endl;
                break;
        }
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

void Sensor::updateInput() {
    if(_network->hasMessage()) {
        std::string s = _network->getMessage();
        cout << "Received Input: " << s << endl;
        if(s == "sleep") {
            _state = SensorState::sleep;
        }
        if(s == "running") {
            _state = SensorState::running;
        }
    }

}

void Sensor::setNetwork(shared_ptr<SensorNetworkInterface> network) {
    _network = network;
}


