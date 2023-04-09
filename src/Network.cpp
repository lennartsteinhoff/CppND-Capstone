#include <iostream>
#include <thread>
#include <chrono>

#include "Network.h"
#include "NetworkError.h"


/* ControllerNetworkInterface::ControllerNetworkInterface(string ip, int port) {

}*/


SensorNetworkInterface::SensorNetworkInterface(int port) {
    _port = port;    
}

void SensorNetworkInterface::run() {

    uint16_t port = _port;
    Socket socket;
    if (! socket.create() ) {throw NetworkError("Error");}
        
    if(!socket.bind(port))  {throw NetworkError("Error");}
    if(!socket.listen())    {throw NetworkError("Error");}

    std::cout << "Set up a listener socket on port: " << port << std::endl;
    socket.set_non_blocking(false);


    std::string s;
    while (true)
    {
        std::cout << "Waiting for connection on: " << port << "\n";
        Socket new_sock;
	    socket.accept (new_sock);
	    std::cout << "Created new socket." << "\n";
        socket.set_non_blocking(false);


        while(true) {
            socket.recv(s);
            std::cout << "Received: " << s << std::endl;
            std::this_thread::sleep_for(chrono::seconds(1));
        }

    } 

    




}

string SensorNetworkInterface::recv() {
    return "test";
}

void SensorNetworkInterface::send(string s) {

}