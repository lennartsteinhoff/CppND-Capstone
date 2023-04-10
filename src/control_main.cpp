#include <iostream>
#include <string>
#include <thread>

#include "Socket.h"

using namespace std;

int main() {
    int port = 30000;
    Socket socket;
    

    if(! socket.create() ) {return -1;}
    if(! socket.connect("localhost", port) ) {return -1;}

    std::cout << "Connected: " << port  << std::endl;
    std::this_thread::sleep_for(chrono::seconds(10));
    
    while (true)
    {
        std::cout << "Try to send" << std::endl; 
        socket.send("running");
        std::this_thread::sleep_for(chrono::seconds(5));

        std::cout << "Try to send" << std::endl; 
        socket.send("sleep");
        std::this_thread::sleep_for(chrono::seconds(5));
    }

}