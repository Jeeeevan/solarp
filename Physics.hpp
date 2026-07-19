#pragma once

#include <vector>
#include "CelestialBody.hpp"

class Physics{
    public:
        static constexpr double G = 1.1904e-19;
        sf::Vector2f bary_center;
        float total_mass;
        float accumulator = 0.0;
        const float TIME_SCALE = 1e6f;
        const float TIME_STEP = 0.02; // same as Unity, 50 times a sec in real-time
        const float MAXIMUM_ALLOWED_TIMESTEP = 0.1;

        Physics();
        void update(std::vector<CelestialBody>& bodies,float deltaTime);
        void initOrbitalVelocity(std::vector<CelestialBody>& bodies);
        void calculateForce(std::vector<CelestialBody>& bodies);
        void calculateMotion(std::vector<CelestialBody>& bodies,float deltaTime);
        void calculatePosition(std::vector<CelestialBody>& bodies,float deltaTime);
        void calculateBaryCenter(std::vector<CelestialBody>& bodies);

};