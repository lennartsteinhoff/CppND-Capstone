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

    auto t0 = chrono::system_clock::now();
    auto t1 = chrono::system_clock::now();

    while (_running) {
        t0 = chrono::system_clock::now();
        _network->waitForMessage();
        t1 = chrono::system_clock::now();
        _message_counter++;
        _ms_waited_for_network += (chrono::duration_cast<std::chrono::milliseconds>(t1-t0)).count();
        while(_network->hasMessage()){
            received_data = _network->recv();
            m.setPayload(received_data);
            
            if(m.type() == Message::Type::data) {
                lock_guard lock1(_data_mtx);
                _data.emplace_back(m);
            } else {
                lock_guard lock2(_events_mtx);
                _events.emplace_back(m);
            }
        } 
    }
}

void Controller::shutdown()
{
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

string Controller::printStatus()
{
    string status = _measurementMode ? "ongoing" : "stopped";
    return "Controller: Measurement " + status + "\n"
            + "Network: " + _network->printNetworkActivity() + "\n"
            + "Avertime Waited for Message: " + (_message_counter ? to_string(int(_ms_waited_for_network / _message_counter)) : " N/A") + " ms\n"
            + "Messages received: " + to_string(_message_counter) + "\n";
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

void Controller::toggle() 
{
    _measurementMode = !_measurementMode;
    _ms_waited_for_network = 0;
}