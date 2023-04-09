#ifndef NETWORK_H
#define NETWORK_H

#include <deque>
#include "Socket.h"

using namespace std;

class Network {
    public:
    Network(){};
    ~Network(){};
    void run();
    string recv();
    void send(string);
    
 private:   
    //Socket _socket;
    uint _port;
    friend class SensorNetworkInterface;
    friend class ControllerNetworkInterface;
};


#endif

/*
class ControllerNetworkInterface : public Network {
    public:
    ControllerNetworkInterface(string ip, int port);
    //void run() override;
    //string recv() override;
    //void send(string) override;
};

*/

class SensorNetworkInterface : public Network {
    public:
    SensorNetworkInterface(int port);
    void run() ;
    string recv();
    void send(string);
};