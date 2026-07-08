#pragma once

#include <vector>
#include "CelestialBody.hpp"

class Physics{
    public:
        static constexpr double G = 1.1904e-19;
        sf::Vector2f bary_center;
        float total_mass;

        Physics();
        void update(std::vector<CelestialBody>& bodies,float deltaTime);
        void initOrbitalVelocity(std::vector<CelestialBody>& bodies);
        void calculateForce(std::vector<CelestialBody>& bodies);
        void calculateMotion(std::vector<CelestialBody>& bodies,float deltaTime);
        void calculatePosition(std::vector<CelestialBody>& bodies,float deltaTime);
        void calculateBaryCenter(std::vector<CelestialBody>& bodies);

};