#include "Physics.hpp"
#include <iostream>
#include <cmath>


Physics::Physics()
{
    this->total_mass = 0;
}

void Physics::update(std::vector<CelestialBody>& bodies,float deltaTime)
{
    calculateForce(bodies);
    calculateMotion(bodies,deltaTime);
    calculatePosition(bodies,deltaTime);
}



void Physics::initOrbitalVelocity(std::vector<CelestialBody>& bodies)
{
    Physics::calculateBaryCenter(bodies);
    for(auto& body:bodies)
    {
        float u = 0;
        sf::Vector2f r_vector = { body.x-bary_center.x,body.y-bary_center.y };
        float r = sqrt(pow(r_vector.x,2)+pow(r_vector.y,2));
        // std::cout<<r;
        if (r<0.1)
        {
            continue;
        }
        float v_magnitude = sqrt(G * total_mass/r );
        // std::cout<<"Orbital velocity of "<<body.name<<" = "<<v_magnitude;
        body.v = {r_vector.y/r *  v_magnitude,-1 * r_vector.x/r * v_magnitude};
    }
}

void Physics::calculateBaryCenter(std::vector<CelestialBody>& bodies)
{
    
    float bary_center_x = 0;
    float bary_center_y = 0;
    for(auto& body:bodies)
    {
        bary_center_x += body.x * body.mass;
        bary_center_y += body.y * body.mass;
        total_mass += body.mass;
    }
    bary_center_x /=  total_mass;
    bary_center_y /=  total_mass;
    this->bary_center = sf::Vector2f({bary_center_x,bary_center_y});
}

void Physics::calculateForce(std::vector<CelestialBody>& bodies)
{
    for(auto& body:bodies){
        body.net_force={0,0};
    }
    for(int i=0;i<bodies.size();i++){
        CelestialBody& body1 = bodies[i];
        for(int j=i+1;j<bodies.size();j++){
            CelestialBody& body2 = bodies[j];
            // std::cout << "Calculating force between "<<body1.name<<" and "<<body2.name<<"\n";

            float d_x = body2.x-body1.x;
            float d_y = body2.y-body1.y;
            float d = std::sqrt((d_x*d_x)+(d_y*d_y));
            sf::Vector2f direction = {d_x/d,d_y/d};
            float F_g = (G * body1.mass * body2.mass)/pow(d,2);
            sf::Vector2f F_1 = direction*F_g;
            sf::Vector2f F_2 = -F_1;
            // std::cout<<"Force = " << F_g<<"\n";
            body1.net_force+=F_1; 
            body2.net_force+=F_2;
        }
    }
}

void Physics::calculateMotion(std::vector<CelestialBody>& bodies,float deltaTime)
{
    for(auto& body:bodies)
    {
        sf::Vector2f acc = body.net_force/body.mass;
        sf::Vector2f v =body.v + acc*float(deltaTime);
        body.v= v; 
        // std::cout<<"Velocity of "<<body.name<<" = " <<v.x<<","<<v.y<<"\n";
    }
}

void Physics::calculatePosition(std::vector<CelestialBody>& bodies,float deltaTime){
    for(auto& body:bodies)
    {
        sf::Vector2f disp = body.v * deltaTime;
        body.x += disp.x;
        body.y += disp.y;
    }
}