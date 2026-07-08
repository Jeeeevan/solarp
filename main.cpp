#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <print>
#include <iostream>
#include <Windows.h>

#include "CelestialBody.hpp"
#include "Physics.hpp"
#include "Renderer.hpp"


int main() {
    
    //Instantiating Physics class
    std::cout<<"Instantiating Physics class";
    Physics physics;

    //Instantiating Renderer class
    std::cout<<"Instantiating Renderer class";
    Renderer renderer(1900,1060,"Solarp System",true); // true to maximise the window

    const float TIME_SCALE = 1e6f;
    
    // Load the font
    renderer.loadFont("font.ttf");
    
    std::cout << "Intializing Celestial Bodies..."<<"\n";
    std::vector<CelestialBody> bodies = {
        CelestialBody("Sun",     0.f,     0.f,    50.f,  333000.f,  sf::Color::White,          25),
        CelestialBody("Mercury", 0.39f,   0.f,    3.f,   0.0553f,  sf::Color::Green,    10),
        CelestialBody("Venus",   0.72f,   0.f,    5.f,   0.815f,   sf::Color(255,198,73),     12),
        CelestialBody("Earth",   1.0f,    0.f,    5.f,   1.0f,   sf::Color::Blue,           12),
        CelestialBody("Mars",    1.52f,   0.f,    4.f,   0.107f,  sf::Color::Red,            12),
        CelestialBody("Jupiter", 5.2f,    0.f,    20.f,  317.8f,    sf::Color(255,165,0),      20),
        CelestialBody("Saturn",  9.58f,   0.f,    17.f,  95.2f,    sf::Color(210,180,140),    18),
        CelestialBody("Uranus",  19.2f,   0.f,    12.f,  14.5f,    sf::Color(173,216,230),    15),
        CelestialBody("Neptune", 30.1f,   0.f,    11.f,  17.1f,    sf::Color(70,130,180),     15)
    };
    
    std::cout << "Starting gameloop..."<<"\n";
    physics.initOrbitalVelocity(bodies);
    renderer.initScale(bodies);
    sf::Clock deltaClock;
    while (renderer.isWindowOpen()) {
        renderer.handleEvents(); //Start listening for events
        if(renderer.closed){
            renderer.closeWindow();
        }
        float deltaTime = deltaClock.restart().asSeconds() * TIME_SCALE;
        
        physics.update(bodies,deltaTime);
        
        renderer.update(bodies);
        renderer.draw(bodies);
    }

    return 0;
}