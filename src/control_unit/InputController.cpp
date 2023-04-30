#include <iostream>
#include <memory>
#include <thread>


#include "SDL.h"
#include "InputController.h"
#include "Controller.h"

void InputController::HandleInput(shared_ptr<Controller> controller, bool& running) const {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        cout << "InputController: Received Event" << endl;
        if(e.type == SDL_QUIT || e.key.keysym.sym == SDLK_c) {
            cout << "InputController: Received QUIT" << endl;
            controller->shutdown();
            this_thread::sleep_for(chrono::milliseconds(1000));
            running = false;
            return;
        } 
        else if (e.type == SDL_KEYDOWN) {
            cout << "InputController: Received Key: " << e.key.keysym.sym << endl;
            if ( e.key.keysym.sym == SDLK_s) {
                cout << "InputController: Toogle measurement" << endl;
                cout << controller->printStatus() << endl;
                controller->toggle();
            }
        }
    }    
}