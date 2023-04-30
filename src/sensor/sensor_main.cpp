#include <iostream>
#include <string>
#include <thread>
#include <memory.h>

#include "Network.h"
#include "Sensor.h"


using namespace std;

int main ( int argc, const char** argv ) {
    int port;
    if(argc <= 1) {
        port = 30000;
    } else {
        port = std::stoi(string(argv[1]));
    }
    auto network = make_shared<SensorNetworkAdapter>(port);
    thread t1 (&SensorNetworkAdapter::run, network);

    auto sensor = make_shared<Sensor>();
    sensor->setNetwork(network);
    thread t2 (&Sensor::run, sensor);

    t2.join();
    cout << "Sensor: StateMachine shutdown complete" << endl;

    cout << "Sensor: Waiting for network shutdown" << endl;
    t1.join();
    cout << "Sensor: shutdown complete" << endl;

    return 0;
}
