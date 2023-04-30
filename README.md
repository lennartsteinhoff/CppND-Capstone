# CPPND: Capstone Sensor Network Simulation

This projects simulates a senor contected to a controller over ethernet, as it can be found for radars in the automotive industrie.

The networking code is build upon: https://tldp.org/LDP/LG/issue74/tougher.html
The visualzation and main loops builds upon: https://github.com/udacity/CppND-Capstone-Snake-Game

The protocol, the messages and the implementation of the communication between the statemachines is a the core of the project.

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it terminal 1: `./sensor`
5. Run it terminal 2: `./control`

## User Interaction

Start/Stop Measurement by pressing "s", when SLD_Window is open and selected
Press c or ctrl-c to trigger the shutdown process for both components

## Structure:

The projects contains of two main programms control_unit/control_main.cpp and sensor/sensor_main.cpp that simulate a simple network protocol.

The important classes are:
    - Network.h: 
        - uses Linux sockets to implement the massage passings
        - uses threads and protected queues to provide a simple interface for higher layers
        - USES TECHNICES: Classes, Multithreading, Mutexes, IO, Rule of 3, Conditional Variables
        - Conditional variables used to provide: void Network::waitForMessages()
    - (main) sensor_main.cpp & Sensor.h: 
        - uses the network class to communicate with the control_unit
        - runs a simple state machine that reacts on network requests
        - creates random numbers to mock a measurement
        - USES TECHNICES: Classes, IO
    - (main) control_main.cpp, Controller.h & InputController.h
        - composed of Controller.h and InputController.h, where the controller controls the sensor over networking using the user input.
        - Implementation is based to the Game Loop provided in the project instructions
        - USES TECHNICES: Classes, IO, Shared Pointers
    - Messages.h:
        - Implements a wrapper class to handle and passed the transfered string messages
        - USES TECHNICES: Classes, Shared Pointers, Rule of 5
    - Display.h:
        - Uses SDL.h to visualize the measurements
        - USES TECHNICES: IO


## Protocol:

Protocol User and Controller:
1. User sends "event: start_stop_toggle" to start and stop a measurement
2. User sends "event: shutdown" to exit the application


Protocol Controller and Sensor:
1. Controller starts communication by sending: "control: start_sensor" to start the measurement
2. The sensor sends data in comma-separeted x y float value pairs, each float value pair seperated by a space
3. Once completed the measurement the controller sends: "control: sleep_sensor"
4. If shutting down, the controller sends "control: sleep_sensor"

## Messages:

### control:
String payload = "control: start_sensor"
String payload = "control: sleep_sensor"
String payload = "control: restart_sensor"
String payload = "control: shutdown_sensor"

### status_senor:
String payload = "status_sensor: sleeping"
String payload = "status_sensor: running"
String payload = "status_sensor: error"


### data:
String payload = "data:<float x> <float y>, <float x> <float y>, ..."


## Core ToDos
1. Correct Readme                                          (/)
1.1 Define Protocol                                        (/)
2.0 Correct shutdown behavior                              (/)
2. Define Messages in Readme                               (/)
3. Implement Message incl. Rule of Five                    (/)
4. Complete Network Abstraction                            (/) 
5. Do Data Transfer to Control Unit                        (/)
6. Visualize Data                                          (/)
7. Implement recation to keyboard events                   (/)
8. Threadprotect:: Queues, socket, cout                    (/)
     
## Improvments:
Implement Queues in Controller                              (/)
Implement Rule of Five: Message, Network                    (/)
Move Semantics in Message, Network                          (/)
Improve runNetwork loop by "Conditional Variable"
Improve sleep(10) by waiting
8. timing in gaming loop (Precise Time for every comp)



Ideas:
Better Eventloop in Main                                           
Reactive to: Random failures, Mouse clicks
Better recovery from Error states


Out of scope:
Set frequency of sensor 
Implement Better Messages in efficient Binary Format 
3. Do logging  
2.0 Implement restart behavior  
3.0 Get rid of sending deadlock unlock message for network receive call by controller during shutdown;  

