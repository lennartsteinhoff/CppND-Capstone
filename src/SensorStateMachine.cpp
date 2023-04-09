#include <iostream>
#include <chrono> 
#include <thread>
#include <memory>
#include <deque>

#include "Socket.h"

using namespace std;

enum class SensorState {sleep, running};

class Sensor {
public:
    void run() {
        while (true)
        {
            switch (_state)
            {
            case SensorState::sleep:
                cout << "Sleeping" << endl;
                break;
            
            case SensorState::running:
                cout << "Running" << endl;
                break;
            }
            this_thread::sleep_for(chrono::milliseconds(500));
        }
    }
    void input(string s) {
        cout << "Received Input: " << s << endl;
        if(s == "sleep") {
            _state = SensorState::sleep;
        }
        if(s == "running") {
            _state = SensorState::running;
        }
    }
private:
    SensorState _state = SensorState::running;
};



int main(int argc, char ** argv) {

    auto sensor = make_shared<Sensor>();
    thread main(&Sensor::run, sensor);
    

    this_thread::sleep_for(chrono::seconds(2));
    sensor->input("sleep");
    cout << "Called sleep" << endl;

    this_thread::sleep_for(chrono::seconds(2));
    sensor->input("running");

    main.join();

    return 0;
}