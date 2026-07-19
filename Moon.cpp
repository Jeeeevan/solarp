#include "Moon.hpp"

Moon::Moon(std::string name, float x, float y, float radius, float mass,sf::Color color, int dot_density, float e, CelestialBody* parentBody): CelestialBody(name, x, y, radius, mass, color, dot_density, e), parent(parentBody)
{
}