#pragma once

#include <deque>
#include <SFML/Graphics.hpp>
class CelestialBody{
    public:
        std::string name;
        float radius; //(Earth radius unit)
        float x; // x coordinate in space (AU unit)
        float y; // y coordinate in space (AU unit)
        float pos_x; // x coordinate in screen (pixel unit)
        float pos_y; // y coordinate in screen (pixel unit)
        std::deque<sf::Vector2f>  trail;
        sf::Vector2f v; // AU/s
        sf::Vector2f net_force; // AU.Em/s^2
        float mass; // (Earth mass unit)
        int dot_density;
        float dot_radius;
        sf::Color color;
        CelestialBody(std::string name,float x, float y, float radius, float mass,sf::Color color,int dot_density);
        void Draw(sf::RenderWindow& window,sf::Font& font);
};