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
    bool hasMessage();
    void send(string);
    string recv();

 private:   
    Socket _socket;
    uint _port;
    bool _isServer;
    deque<string> _send_queue;
    deque<string> _recv_queue;
    friend class SensorNetworkAdapter;
    friend class ControlerNetworkAdapter;
};





class ControlerNetworkAdapter : public Network {
    public:
    ControlerNetworkAdapter(string ip, int port);
};


class SensorNetworkAdapter : public Network {
    public:
    SensorNetworkAdapter(int port);
};

#endif