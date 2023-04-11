#include <iostream>
#include <thread>
#include <chrono>

#include "Network.h"
#include "NetworkError.h"


ControlerNetworkAdapter::ControlerNetworkAdapter(string ip, int port) {
    if(!_socket.create() ) {throw NetworkError("Error");}
    if(!_socket.connect(ip, port)) {throw NetworkError("Error");}
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
    while (true)
    { 
        if(_isServer) {
            std::cout << "Waiting for connection on: " << _port << "\n";
            _socket.accept (_socket);
            std::cout << "Accepted connection on: " << _port << "\n";
        }

        while(true) {
            string s;
            if(_socket.recv(s)) {
                _recv_queue.push_back(s);
                std::cout << "Received: " << std::endl;
                for (auto& x : _recv_queue) {
                    std::cout << x << " " << std::endl;
                }
                std::cout << std::endl;
            }
            std::this_thread::sleep_for(chrono::seconds(1));
        }

    } 
}

bool Network::hasMessage() {
    return !_recv_queue.empty();
}

string Network::recv() {
    auto ret = _recv_queue.back();
    _recv_queue.pop_back();
    return ret;
}

void Network::send(string s) {
    _send_queue.emplace_back(s);
}