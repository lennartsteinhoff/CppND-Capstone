#include <vector>
#include <stdlib.h> 
#include <memory>
#include <iostream>
#include <thread>
#include <sstream>
#include <string>
#include <chrono>

#include "Controller.h"
#include "Network.h"
#include "Message.h"

using namespace std;

void Controller::runNetwork() 
{
    _running = true;
    string received_data;
    Message m;

    while (_running) {
        _data_mtx.lock();
        _events_mtx.lock();
        while(_network->hasMessage()){
            received_data = _network->recv();
            m.setPayload(received_data);
            
            if(m.type() == Message::Type::data) {
                _data.emplace_back(m);
            } else {
                _events.emplace_back(m);
            }
        }
        _data_mtx.unlock();
        _events_mtx.unlock();  
        std::this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void Controller::runStateMachine() 
{

    while(_running) {
        string s = _measurementMode ? "running" : "sleep";
        //std::cout << "Network Controller: Send:" << s << std::endl; 
        _network->send(s);
        std::this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

Message::Data Controller::GetMeasurement() 
{
    lock_guard lock1(_data_mtx);
    lock_guard lock2(_events_mtx);
    _events.clear();
    vector<vector<double>> measurement {};
    while(!_data.empty()) 
    {
        auto m = _data.front();
        _data.pop_front();
        for(auto& e : m.data()) {
            measurement.emplace_back(e);
        }
    }
    return move(measurement);
}