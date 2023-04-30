#ifndef NETWORK_H
#define NETWORK_H

#include <deque>
#include <chrono>

#include "Socket.h"
#include "MessageQueue.h"

using namespace std;

class Network {
    public:
    Network(){};
    Network(Network const&) = delete;
    Network(Network &&);
    Network& operator=(Network const&) = delete;
    Network& operator=(Network &&);

    ~Network(){
    };
    void run();
    bool hasMessage();
    void send(string);
    string recv();
    void shutdown();
    
    string printNetworkActivity() {
        string s {"tx: " + to_string(_tx) + " bytes, rx: " + to_string(_rx) + "bytes"};
        _tx = 0;
        _rx = 0;
        return s;
    }

 private:   
    void recv_loop();
    void send_loop();
    bool _running = true;

    Socket _socket;
    uint _port;
    bool _isServer;
    int _tx;
    int _rx;
    deque<string> _send_queue;
    deque<string> _recv_queue;
    mutex _rcv_mtx;
    mutex _snd_mtx;
    friend class SensorNetworkAdapter;
    friend class ControllerNetworkAdapter;


};


class ControllerNetworkAdapter : public Network {
    public:
    ControllerNetworkAdapter(string ip, int port);
    private:
    string _ip;
};


class SensorNetworkAdapter : public Network {
    public:
    SensorNetworkAdapter(int port);
};

#endif