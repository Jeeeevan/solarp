#pragma once

#include "CelestialBody.hpp"

class Moon : public CelestialBody 
{
private:
    CelestialBody* parent;  // Reference to the planet it orbits
    
public:
    Moon(std::string name, float x, float y, float radius, float mass,
         sf::Color color, int dot_density, float e, CelestialBody* parentBody);
    
    CelestialBody* getParent() const { return parent; }
};