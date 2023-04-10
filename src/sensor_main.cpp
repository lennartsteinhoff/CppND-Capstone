#include <iostream>
#include <string>
#include <thread>
#include <memory.h>

#include "Network.h"
#include "Sensor.h"


using namespace std;

int main ( int argc, const char** argv ) {

    int port = std::stoi(string(argv[1]));
    auto network = make_shared<SensorNetworkInterface>(port);
    thread t1 (&SensorNetworkInterface::run, network);

    auto sensor = make_shared<Sensor>();
    sensor->setNetwork(network);
    thread t2 (&Sensor::run, sensor);

    t1.join();
    t2.join();

    return 0;
}
