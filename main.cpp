#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <print>
#include <iostream>
#include <Windows.h>

#include "CelestialBody.hpp"
#include "Physics.hpp"
#include "Renderer.hpp"

struct AppState {
    bool paused = false;
    bool running = true;
};

int main() {
    //Instantiating app state
    std::cout<<"Instantiating App state"<<"\n";
    AppState state;
    
    std::cout<<"Instantiating Physics class"<<"\n";
    Physics physics;

    //Instantiating Renderer class
    std::cout<<"Instantiating Renderer class"<<"\n";
    Renderer renderer(1900,1060,"Solarp System",true); // true to maximise the window

    const float TIME_SCALE = 1e6f;
    
    // Load the font
    renderer.loadFont("font.ttf");
    
    std::cout << "Intializing Celestial Bodies..."<<"\n";
    std::vector<CelestialBody> bodies = {
        CelestialBody("Sun",     0.f,     0.f,    50.f,  333000.f,  sf::Color::White,       25, 0.0f),
        CelestialBody("Mercury", 0.39f,   0.f,    3.f,   0.0553f,   sf::Color::Green,       10, 0.206f),
        CelestialBody("Venus",   0.72f,   0.f,    5.f,   0.815f,    sf::Color(255,198,73),  12, 0.007f),
        CelestialBody("Earth",   1.0f,    0.f,    5.f,   1.0f,      sf::Color::Blue,        12, 0.017f),
        CelestialBody("Mars",    1.52f,   0.f,    4.f,   0.107f,    sf::Color::Red,         12, 0.093f),
        CelestialBody("Jupiter", 5.2f,    0.f,    20.f,  317.8f,    sf::Color(255,165,0),   20, 0.049f),
        CelestialBody("Saturn",  9.58f,   0.f,    17.f,  95.2f,     sf::Color(210,180,140), 18, 0.057f),
        CelestialBody("Uranus",  19.2f,   0.f,    12.f,  14.5f,     sf::Color(173,216,230), 15, 0.046f),
        CelestialBody("Neptune", 30.1f,   0.f,    11.f,  17.1f,     sf::Color(70,130,180),  15, 0.010f)
    };
    
    
    physics.initOrbitalVelocity(bodies);
    renderer.initScale(bodies);
    std::cout << "Starting gameloop..."<<"\n";
    sf::Clock deltaClock;
    while (renderer.isWindowOpen()) {
        
        renderer.handleEvents(); //Start listening for events
        for(auto& e:renderer.events){
            switch(e) {
                case Renderer::AppEvent::close: {
                    state.running = false;
                    break;}
                case Renderer::AppEvent::togglePause:   {
                    state.paused = !state.paused; 
                    break;
                }
            }
        }
        renderer.events.clear();
        
        float deltaTime = deltaClock.restart().asSeconds();
        if(!state.running){
            renderer.closeWindow();
        }

        if(state.paused){

            continue;
        }
        
        physics.update(bodies,deltaTime);
        
        renderer.update(bodies);

        renderer.draw(bodies);
    }

    return 0;
}