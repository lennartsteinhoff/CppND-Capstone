#include <iostream>
#include <chrono> 
#include <thread>
#include <memory>
#include <deque>
#include <vector>
#include <string>

#include "Socket.h"
#include "Sensor.h"
#include "Network.h"

using namespace std;

void Sensor::run() {
    while (!_shutdownPhase)
    {
        auto prev_state = _state;
        if (_network) updateInput();
        

        if(_shutdownPhase) {
                cout << "Sensor: Shutdown secquence started" << endl;
                _network->shutdown();
                cout << "Sensor: Network shutdown started" << endl;
                return;
        }

        switch (_state)
        {
            case SensorState::sleep:
                if (prev_state != _state) cout << "Sensor: Sleeping" << endl;              
                break;
            
            case SensorState::running:
                if (prev_state != _state) cout << "Sensor: Running" << endl; 
                _network->send("state: running");
                _network->send(simulateMeasurement());
                cout << "Network activity: " << _network->printNetworkActivity() << endl; 
                break;
            case SensorState::shutdown:
                break;
        }
        this_thread::sleep_for(chrono::milliseconds(50));
    }
}

void Sensor::updateInput() {
    while(_network->hasMessage()) {
        std::string s = _network->recv();
        if(s != _prev_input) cout << "Received Input: " << s << endl;
        if(s == "control: sleep_sensor") {
            _state = SensorState::sleep;
        }
        if(s == "control: start_sensor") {
            _state = SensorState::running;
        }
        if(s == "control: shutdown_sensor") {
            _state = SensorState::shutdown;
            _shutdownPhase = true;
        }
        _prev_input = s;
    }

}

string Sensor::simulateMeasurement() {
    uint size = rand() % 10 + 1;
    vector<vector<double>> m;
    for(int i=0; i<size; i++) {
        m.push_back({double(rand() % 600 ), double(rand() % 400)});
    }
    string ret {"data:"};
    for(auto& point: m) {
        double x = point[0];
        double y = point[1];
        ret += "" + to_string(x) + " " + to_string(y) + "";
        if (&point != &m.back()) {
            ret += ",";
        }
    }
    return ret;
}

void Sensor::setNetwork(shared_ptr<Network> network) {
    _network = network;
}


