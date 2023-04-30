#ifndef SENSOR_H
#define SENSOR_H

#include <iostream>
#include <chrono>
#include <thread>
#include <memory>
#include <deque>
#include <string>

#include "Network.h"

using namespace std;

enum class SensorState
{
    sleep,
    running,
    shutdown
};

class Sensor
{
public:
    void run();
    void updateInput();
    void setNetwork(shared_ptr<Network>);
    string simulateMeasurement();

private:
    SensorState _state = SensorState::sleep;
    shared_ptr<Network> _network;
    bool _shutdownPhase{false};
    SensorState _prev_state;
    string _prev_input;
};

#endif
