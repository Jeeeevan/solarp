#include "CelestialBody.hpp"
#include <cmath>
#include <vector>
#define _USE_MATH_DEFINES

CelestialBody::CelestialBody(std::string name,float x,float y, float radius,float mass,sf::Color color,int dot_density){
    this->name =name;
    this->x = x;
    this->y = y; 
    this->radius=radius;
    this->mass=mass;
    this->color = color;
    this->dot_density =dot_density;
    this->v ={0,0};
    this->net_force={0,0};
}


void CelestialBody::Draw(sf::RenderWindow& window,sf::Font& font){
    
    sf::CircleShape boundary(radius);
    boundary.setPosition({pos_x-radius,pos_y-radius});
    boundary.setOutlineColor(sf::Color::Transparent);
    boundary.setOutlineThickness(1.f);
    boundary.setFillColor(sf::Color::Transparent);
    float spacing = radius / dot_density;
    sf::VertexArray dots(sf::PrimitiveType::Points);

    for(float i = pos_x-radius;i<=pos_x+radius;i=i+spacing)
    {
        for(float j = pos_y-radius;j<=pos_y+radius;j=j+spacing)
        {
            if(((i-x)*(i-x) + (j-y)*(j-y))<=(radius*radius*0.95*0.95)) // 5% circle edge cropping
            {
                dots.append(sf::Vertex({i,j},color));
            }
        }
    }
    window.draw(boundary);
    window.draw(dots); 
    // Draw the body name below the circle
    sf::Text text(font, name, 16);   
    text.setFillColor(color);
    // Center the text horizontally
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin({bounds.position.x + bounds.size.x / 2.f, 0.f});

    // Position below the circle
    text.setPosition({x, y + radius + 8.f});
    window.draw(text);
}