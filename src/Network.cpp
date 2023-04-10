#include <iostream>
#include <thread>
#include <chrono>

#include "Network.h"
#include "NetworkError.h"


/* ControllerNetworkInterface::ControllerNetworkInterface(string ip, int port) {

}*/


SensorNetworkInterface::SensorNetworkInterface(int port) {
    _port = port;  
    if(!_socket.create() ) {throw NetworkError("Error");}
    if(!_socket.bind(_port))  {throw NetworkError("Error");}
    if(!_socket.listen())    {throw NetworkError("Error");}  
    _socket.set_non_blocking(false);
}

void SensorNetworkInterface::run() {
    std::string s;
    while (true)
    {
        std::cout << "Waiting for connection on: " << _port << "\n";
        Socket new_socket;
	    _socket.accept (new_socket);
	    std::cout << "Accepted connection on: " << _port << "\n";

        while(true) {
            if(new_socket.recv(s)) {
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

bool SensorNetworkInterface::hasMessage() {
    return !_recv_queue.empty();
}

string SensorNetworkInterface::getMessage() {
    auto ret = _recv_queue.back();
    _recv_queue.pop_back();
    return ret;
}

string SensorNetworkInterface::recv() {
    return "test";
}

void SensorNetworkInterface::send(string s) {

}