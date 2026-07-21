#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <print>
#include <iostream>
#include <Windows.h>

#include "CelestialBody.hpp"
#include "Physics.hpp"
#include "Renderer.hpp"
#include "Moon.hpp"

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
    std::vector<CelestialBody*> bodies = {
        new CelestialBody("Sun",      0.f,    0.f,  109.1f,   333000.f, sf::Color::White,          100, 0.0f),
        new CelestialBody("Mercury",  0.39f,  0.f,    0.383f,      0.0553f, sf::Color::Green,       10, 0.206f),
        new CelestialBody("Venus",    0.72f,  0.f,    0.949f,      0.815f,  sf::Color(255,198,73),  12, 0.007f),
        new CelestialBody("Earth",    1.0f,   0.f,    1.0f,        1.0f,    sf::Color::Blue,         12, 0.017f),
        new CelestialBody("Mars",     1.52f,  0.f,    0.532f,      0.107f,  sf::Color::Red,          12, 0.093f),
        new CelestialBody("Jupiter",  5.2f,   0.f,   10.97f,     317.8f,    sf::Color(255,165,0),    20, 0.049f),
        new CelestialBody("Saturn",   9.58f,  0.f,    9.14f,      95.2f,    sf::Color(210,180,140),  18, 0.057f),
        new CelestialBody("Uranus",  19.2f,   0.f,    3.98f,      14.5f,    sf::Color(173,216,230),  15, 0.046f),
        new CelestialBody("Neptune", 30.1f,   0.f,    3.86f,      17.1f,    sf::Color(70,130,180),   15, 0.010f)
    };
    
    std::vector<Moon*> moons = {
    // Earth
    new Moon("Moon", 1.00257, 0.0, 0.273, 0.0123, sf::Color(200,200,200), 50, 0.0549, bodies[3]),
    
    // Mars
    new Moon("Phobos", 1.520063, 0.0, 0.0002, 0.0000176, sf::Color(100,100,100), 50, 0.015, bodies[4]),
    new Moon("Deimos", 1.520157, 0.0, 0.0001, 0.000000022, sf::Color(80,80,80), 50, 0.0002, bodies[4]),
    
    // Jupiter
    new Moon("Io", 5.20282, 0.0, 0.286, 0.015, sf::Color(255,200,0), 50, 0.0041, bodies[5]),
    new Moon("Europa", 5.20448, 0.0, 0.245, 0.008, sf::Color(180,150,120), 50, 0.009, bodies[5]),
    new Moon("Ganymede", 5.20715, 0.0, 0.413, 0.025, sf::Color(150,120,100), 50, 0.0015, bodies[5]),
    new Moon("Callisto", 5.21258, 0.0, 0.378, 0.018, sf::Color(80,70,60), 50, 0.007, bodies[5]),
    
    // Saturn
    new Moon("Titan", 9.58817, 0.0, 0.404, 0.0225, sf::Color(255,200,100), 50, 0.029, bodies[6]),
    new Moon("Rhea", 9.58352, 0.0, 0.145, 0.0003, sf::Color(180,180,180), 50, 0.001, bodies[6]),
    new Moon("Dione", 9.58252, 0.0, 0.117, 0.00018, sf::Color(150,150,150), 50, 0.002, bodies[6]),
    new Moon("Tethys", 9.58197, 0.0, 0.146, 0.00017, sf::Color(200,200,200), 50, 0.001, bodies[6]),
    new Moon("Enceladus", 9.58159, 0.0, 0.074, 0.000018, sf::Color(220,220,220), 50, 0.005, bodies[6]),
    new Moon("Iapetus", 9.59238, 0.0, 0.234, 0.00027, sf::Color(100,100,100), 50, 0.03, bodies[6]),
    
    // Uranus
    new Moon("Titania", 19.20291, 0.0, 0.195, 0.00009, sf::Color(150,150,150), 50, 0.001, bodies[7]),
    new Moon("Oberon", 19.20390, 0.0, 0.189, 0.00009, sf::Color(120,120,120), 50, 0.001, bodies[7]),
    new Moon("Umbriel", 19.20178, 0.0, 0.117, 0.00007, sf::Color(80,80,80), 50, 0.005, bodies[7]),
    new Moon("Ariel", 19.20128, 0.0, 0.108, 0.00006, sf::Color(180,180,200), 50, 0.001, bodies[7]),
    
    // Neptune
    new Moon("Triton", 30.10237, 0.0, 0.212, 0.0029, sf::Color(100,150,200), 50, 0.00016, bodies[8])
    };

    physics.initOrbitalVelocity(bodies);
    physics.initMoonVelocity(moons);
    for(auto moon : moons) 
    {
    bodies.push_back(moon);
    }
    std::cout << "Starting gameloop..."<<"\n";
    sf::Clock deltaClock;
    while (renderer.isWindowOpen()) {
        
        
        renderer.handleEvents(bodies);
        
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
        
        if(!state.running){
            renderer.closeWindow();
        }

        if(state.paused){
            
            renderer.update(bodies);
            renderer.draw(bodies);
            continue;
        }
            
        float deltaTime = deltaClock.restart().asSeconds();
        physics.update(bodies,deltaTime);
        
        renderer.update(bodies);

        renderer.draw(bodies);
    }

    return 0;
}