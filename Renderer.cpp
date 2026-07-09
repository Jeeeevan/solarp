#include "Renderer.hpp"
#include "CelestialBody.hpp"
#include <cmath>
#include <Windows.h>
#include <iostream>

Renderer::Renderer(unsigned int WINDOW_WIDTH,unsigned int WINDOW_HEIGHT,std::string name,bool isMaximise)
{
    this->WINDOW_WIDTH = WINDOW_WIDTH;
    this->WINDOW_HEIGHT = WINDOW_HEIGHT;
    this->name = name;
    window = sf::RenderWindow(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), name);
    if (isMaximise){
        maximiseWindow();
    }
}

void Renderer::update(std::vector<CelestialBody>& bodies)
{
    calculateScreenPosition(bodies);
    if(trail){
        for(auto& body:bodies)
            calculateOrbitTrail(body); 
    }
}

void Renderer::handleEvents()
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            events.push_back(AppEvent::close);

        }
        
        if(const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
            if(keyPressed->code == sf::Keyboard::Key::Space){
                events.push_back(AppEvent::togglePause);
            }
        }
    }
}



void Renderer::closeWindow()
{
    window.close();
}

bool Renderer::isWindowOpen()
{
    return window.isOpen();
}
void Renderer::maximiseWindow()
{
    HWND hwnd = (HWND)window.getNativeHandle();
    ShowWindow(hwnd, SW_SHOWMAXIMIZED);
}

void Renderer::loadFont(std::string path)
{
    if (!font.openFromFile(path))
        std::cout << "Font failed to load\n";
    else
        std::cout << "Font loaded\n";
}

void Renderer::initScale(std::vector<CelestialBody>& bodies)
{
    auto maxBody = std::max_element(bodies.begin(), bodies.end(), 
    [](const CelestialBody& a, const CelestialBody& b) {
        return (a.x*a.x + a.y*a.y) < (b.x*b.x + b.y*b.y);
    });
    float maxDistance = sqrt(maxBody->x * maxBody->x + maxBody->y * maxBody->y);
    distanceScale = log(1 + maxDistance);
    targetRadius = WINDOW_WIDTH / 2.0f - (2 * maxBody->radius); // Diameter of the furthest planet sized margin
    // targetRadius = std::min(WINDOW_WIDTH, WINDOW_HEIGHT) / 2.0f - (2 * maxBody->radius); // Diameter of the furthest planet sized margin
}

void Renderer::calculateScreenPosition(std::vector<CelestialBody>& bodies)
{
    for(auto& body:bodies)
    {
        float distance = sqrt(pow(body.x,2)+pow(body.y,2));
        float angle = atan2(body.y,body.x);

        float scaled_distance = log(1 + distance) * targetRadius/distanceScale;
        body.pos_x = WINDOW_WIDTH/2 + scaled_distance * cos(angle);
        body.pos_y = WINDOW_HEIGHT/2 + scaled_distance * sin(angle);
    }
}

void Renderer::draw(std::vector<CelestialBody>& bodies)
{
    window.clear(sf::Color::Black);

    for(auto& body : bodies){
            if(trail){
                drawOrbitTrail(body);
            }
            drawBody(body);
        }
    window.display();
}

void Renderer::drawBody(CelestialBody& body){
    
    float& radius = body.radius;
    float& pos_x = body.pos_x;
    float& pos_y = body.pos_y;
    int& dot_density = body.dot_density;
    sf::Color& color = body.color;
    std::string& name = body.name;

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
            if(((i-pos_x)*(i-pos_x) + (j-pos_y)*(j-pos_y))<=(radius*radius*0.95*0.95)) // 5% circle edge cropping
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
    text.setPosition({pos_x, pos_y + radius + 8.f});
    window.draw(text);
}

void Renderer::drawOrbitTrail(CelestialBody& body)
{
    sf::VertexArray dots(sf::PrimitiveType::LineStrip);
    int size = body.trail.size();
    for(int i = 0; i < size; i++)
    {
        float alpha = 255.f * (1.f - (float)i / size);
        sf::Color c = body.color;
        c.a = static_cast<uint8_t>(alpha);
        dots.append(sf::Vertex(body.trail[i], c));
    }
    window.draw(dots);
}

void Renderer::calculateOrbitTrail(CelestialBody& body)
{
    body.trail.push_front({body.pos_x,body.pos_y});

    if(body.trail.size()>TRAIL_LENGTH){
        body.trail.pop_back();
    }
}