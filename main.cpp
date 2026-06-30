#include <SFML/Graphics.hpp>
#include "CelestialBody.hpp"
#include <vector>
#include <cmath>
#include <print>
#include <iostream>
#include <Windows.h>

unsigned int WINDOW_WIDTH = 1900;
unsigned int WINDOW_HEIGHT = 1060;

void calculateForce(std::vector<CelestialBody>& bodies)
{
    for(auto& body:bodies){
        body.net_force={0,0};
    }
    constexpr double G = 6.6743; 
    for(int i=0;i<bodies.size();i++){
        CelestialBody& body1 = bodies[i];
        for(int j=i+1;j<bodies.size();j++){
            CelestialBody& body2 = bodies[j];
            std::cout << "Calculating force between "<<body1.name<<" and "<<body2.name<<"\n";

            float d_x = body2.x-body1.x;
            float d_y = body2.y-body1.y;
            float d = std::sqrt((d_x*d_x)+(d_y*d_y));
            sf::Vector2f direction = {d_x/d,d_y/d};
            float F_g = (G * body1.mass * body2.mass)/pow(d,2);
            sf::Vector2f F_1 = direction*F_g;
            sf::Vector2f F_2 = -F_1;
            std::cout<<"Force = " << F_g<<"\n";
            body1.net_force+=F_1;
            body2.net_force+=F_2;
        }
    }
}

void calculateMotion(std::vector<CelestialBody>& bodies,float deltaTime)
{
    for(auto& body:bodies)
    {
        sf::Vector2f acc = body.net_force/body.mass;
        sf::Vector2f v =body.v + acc*float(deltaTime);
        body.v= v; 
        std::cout<<"Velocity of "<<body.name<<" = " <<v.x<<","<<v.y<<"\n";
    }
}

void calculatePosition(std::vector<CelestialBody>& bodies,float deltaTime){
    for(auto& body:bodies)
    {
        sf::Vector2f disp = body.v * deltaTime;
        body.x += disp.x;
        body.y += disp.y;
    }
}

void calculateScreenPosition(std::vector<CelestialBody>& bodies)
{
    for(auto& body:bodies)
    {
        float distance = sqrt(pow(body.x,2)+pow(body.y,2));
        float angle = atan2(body.y,body.x);

        float scaled_distance = log(distance);
        body.pos_x = WINDOW_WIDTH/2 + scaled_distance * cos(angle);
        body.pos_y = WINDOW_HEIGHT/2 + scaled_distance * sin(angle);
    }
}

int main() {

    sf::Clock deltaClock;
    sf::Font font;
    if (!font.openFromFile("font.ttf"))
    std::cout << "Font failed to load\n";
    else
        std::cout << "Font loaded\n";

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Solar System");
    
    // Maximize the window.
    HWND hwnd = (HWND)window.getNativeHandle();
    ShowWindow(hwnd, SW_SHOWMAXIMIZED);
        
    std::cout << "Intializing Celestial Bodies..."<<"\n";
    std::vector<CelestialBody> bodies = {
        CelestialBody("Sun",     WINDOW_WIDTH/2,       WINDOW_HEIGHT/2,       100.f, 10000.f, sf::Color::White,                 25),
        CelestialBody("Mercury", WINDOW_WIDTH/2+150,   WINDOW_HEIGHT/2,       5.f,   1000.f,  sf::Color(169,169,169),           10),
        CelestialBody("Venus",   WINDOW_WIDTH/2+220,   WINDOW_HEIGHT/2,       8.f,   800.f,  sf::Color(255,198,73),            15),
        CelestialBody("Earth",   WINDOW_WIDTH/2+300,   WINDOW_HEIGHT/2,       9.f,   900.f,  sf::Color::Blue,                  15),
        CelestialBody("Mars",    WINDOW_WIDTH/2+400,   WINDOW_HEIGHT/2,       7.f,   70000.f,  sf::Color::Red,                   15),
        CelestialBody("Jupiter", WINDOW_WIDTH/2+550,   WINDOW_HEIGHT/2,       30.f,  300.f, sf::Color(255,165,0),             20),
        CelestialBody("Saturn",  WINDOW_WIDTH/2+700,   WINDOW_HEIGHT/2,       25.f,  2500.f, sf::Color(210,180,140),           20),
        CelestialBody("Uranus",  WINDOW_WIDTH/2+820,   WINDOW_HEIGHT/2,       18.f,  1800.f, sf::Color(173,216,230),           15),
        CelestialBody("Neptune", WINDOW_WIDTH/2+920,   WINDOW_HEIGHT/2,       17.f,  1700.f, sf::Color(70,130,180),            15)
    };

    std::cout << "Starting gameloop..."<<"\n";

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        float deltaTime = deltaClock.restart().asSeconds();
        window.clear(sf::Color::Black);
        calculateForce(bodies);
        calculateMotion(bodies,deltaTime);
        calculatePosition(bodies,deltaTime);
        calculateScreenPosition(bodies);
        for(auto& body : bodies){
            body.Draw(window,font);
        }
        window.display();
    }

    return 0;
}