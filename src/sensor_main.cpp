#include <iostream>
#include <string>
#include <thread>

#include "Socket.h"
#include "Network.h"


using namespace std;

int main ( int argc, const char** argv ) {

    int port = std::stoi(string(argv[1]));
    SensorNetworkInterface network(port);

    network.run();

    return 0;
}
/*
    Socket socket;
    if (! socket.create() ) {return 0;}
        
    if(!socket.bind(port))  {return 0;}
    if(!socket.listen())    {return 0;}

    std::cout << "Set up a listener socket on port: " << port << std::endl;
    socket.set_non_blocking(false);


    std::string s;
    while (true)
    {
        std::cout << "Waiting for connection on: " << port << "\n";
        Socket new_sock;
        new_sock.set_non_blocking(false);
	    socket.accept (new_sock);
	    std::cout << "Created new socket." << "\n";
        socket.set_non_blocking(false);

        std::this_thread::sleep_for(chrono::seconds(20));

        while(true) {
            new_sock.recv(s);
            std::cout << "Received: " << s << std::endl;
            std::this_thread::sleep_for(chrono::seconds(1));
        }

    } 

    std::cout << "Received" << s << std::endl;
}

*/