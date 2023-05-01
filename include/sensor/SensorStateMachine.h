#include <iostream>
#include <chrono>
#include <thread>
#include <memory>
#include <deque>

#include "Socket.h"

using namespace std;

enum class SensorState
{
    sleep,
    running
};

class Sensor
{
public:
    void run()
    {
        while (true)
        {
            switch (_state)
            {
            case SensorState::sleep:
                cout << "status_sensor: sleeping" << endl;
                break;

            case SensorState::running:
                cout << "status_sensor: running" << endl;
                break;
            }
            this_thread::sleep_for(chrono::milliseconds(500));
        }
    }
    void input(string s)
    {
        cout << "Received Input: " << s << endl;
        if (s == "control: sleep_sensor")
        {
            _state = SensorState::sleep;
        }
        if (s == "control: start_sensor")
        {
            _state = SensorState::running;
        }
    }

private:
    SensorState _state = SensorState::running;
};
