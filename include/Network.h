#ifndef NETWORK_H
#define NETWORK_H

#include <deque>
#include "Socket.h"
#include "MessageQueue.h"

using namespace std;

class Network {
    public:
    Network(){};
    ~Network(){};
    void run();


 private:   
    Socket _socket;
    uint _port;
    deque<string> _send_queue;
    deque<string> _recv_queue;
    string recv();
    void send(string);
    friend class SensorNetworkInterface;
    friend class ControllerNetworkInterface;
};




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
    bool hasMessage();
    void sendMessage(string);
    string getMessage();
};

#endif