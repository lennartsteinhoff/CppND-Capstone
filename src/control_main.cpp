#include <iostream>
#include <string>
#include <thread>

#include "Socket.h"

using namespace std;

int main() {
    uint16_t port = 30000;
    Socket socket;
    

    if(! socket.create() ) {return -1;}
    if(! socket.connect("localhost", port) ) {return -1;}

    std::cout << "Connected: " << port  << std::endl;
    std::this_thread::sleep_for(chrono::seconds(10));
    
    std::string s= "Test";

    socket.send(s);
    std::cout << "Wait for 10s" << std::endl;
    std::this_thread::sleep_for(chrono::seconds(10));


    std::cout << "Try to send" << std::endl;

    std::cout << "Wait for 10 s" << std::endl;
    std::this_thread::sleep_for(chrono::seconds(10));

    std::cout << "Try to send" << std::endl;    
    socket.send(s);
    std::cout << "Wait for 10 s" << std::endl;
    std::this_thread::sleep_for(chrono::seconds(10));

    std::this_thread::sleep_for(chrono::seconds(5));
    socket.recv(s);

    std::cout << "Sent: " << std::endl;
    std::cout << "Wait 5s to shut down" << std::endl;
    std::this_thread::sleep_for(chrono::seconds(5));

}