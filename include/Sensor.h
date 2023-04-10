#ifndef SENSOR_H
#define SENSOR_H

#include <iostream>
#include <chrono> 
#include <thread>
#include <memory>
#include <deque>

#include "Network.h"

using namespace std;

enum class SensorState {sleep, running};

class Sensor {
public:
    void run();
    void updateInput();
    void setNetwork(shared_ptr<SensorNetworkInterface>);
private:
    SensorState _state = SensorState::sleep;
    shared_ptr<SensorNetworkInterface> _network;
};

#endif
