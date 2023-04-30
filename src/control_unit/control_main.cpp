#include <iostream>
#include <string>
#include <thread>
#include <memory>

#include "Network.h"
#include "NetworkError.h"
#include "InputController.h"
#include "Display.h"


using namespace std;

int main() {
    int port = 30000;
    string ip = "localhost";

    unique_ptr<ControllerNetworkAdapter> network;
    
    while (!network)
    {
        try {
            network = make_unique<ControllerNetworkAdapter>(ip, port);
        } catch (NetworkError &e) {
            cout << "Received: " << e.description() << " during startup. No sensor available on port: " << port << ". Try again in 1 seconds " << endl;
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
    


    InputController input;
    shared_ptr<Controller> controller = make_shared<Controller>(move(network));

    thread c1(&Controller::runNetwork, controller);
    thread c2(&Controller::runStateMachine, controller);

    Display display(600, 400, 1, 1);

    bool run(true);
    Message::Data measurement;
    

    while(run) {
        input.HandleInput(controller, run);
        measurement = controller->GetMeasurement();
        cout << controller->printStatus() << endl;
        display.VisualizeMeasurement(measurement);
        
        std::this_thread::sleep_for(chrono::milliseconds(1000));
    }

    c1.join();
    c2.join();

}