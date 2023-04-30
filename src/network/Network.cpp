#include <iostream>
#include <thread>
#include <chrono>

#include "Network.h"
#include "NetworkError.h"


ControllerNetworkAdapter::ControllerNetworkAdapter(string ip, int port) {
    _port = port; 
    _ip = ip;
    if(!_socket.create() ) {throw NetworkError("Error");}
    if(!_socket.connect(ip, port)) {throw NetworkError("Error");}
    _socket.set_non_blocking(false);
    _isServer = false;
}


SensorNetworkAdapter::SensorNetworkAdapter(int port) {
    _port = port;  
    if(!_socket.create() ) {throw NetworkError("Error");}
    if(!_socket.bind(_port))  {throw NetworkError("Error");}
    if(!_socket.listen())    {throw NetworkError("Error");}  
    _socket.set_non_blocking(false);
    _isServer = true;
}

void Network::run() {
    if(_isServer) {
        std::cout << "Waiting for connection on: " << _port << "\n";
        _socket.accept (_socket);
        std::cout << "Accepted connection on: " << _port << "\n";
    }

    thread recv_thread(&Network::recv_loop, this);
    thread send_thread(&Network::send_loop, this);
    std::cout << "Started network thread on port: " << _port << "\n";
    recv_thread.join();
    send_thread.join();
}

void Network::recv_loop() {
    while(_running) {
        string s;
        if(_socket.recv(s)) {
            _recv_queue.push_back(s);
            _rx += s.size();
        }
        this_thread::sleep_for(chrono::milliseconds(10));
    }
    

}

void Network::send_loop() {
    while (_running) {
        if(!_send_queue.empty()) {
            auto data = _send_queue.front();
            _send_queue.pop_front();
            _socket.send(data);
            _tx += data.size();
        }
        this_thread::sleep_for(chrono::milliseconds(10));
    }
    
}

bool Network::hasMessage() {
    return !_recv_queue.empty();
}

string Network::recv() {
    if(!_recv_queue.empty()) {
        auto ret = _recv_queue.back();
        _recv_queue.pop_back();
        return ret;
    }
    return "";

}

void Network::send(string s) {
    _send_queue.emplace_back(s);
}

void Network::shutdown() {
    _running = false;
}