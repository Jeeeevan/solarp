#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "CelestialBody.hpp"

class Renderer{
    public:
        sf::RenderWindow window;
        unsigned int WINDOW_WIDTH;
        unsigned int WINDOW_HEIGHT;
        std::string name;
        sf::Font font;
        bool closed = false;
        float distanceScale;
        float targetRadius; 
        Renderer(unsigned int WINDOW_WIDTH,unsigned int WINDOW_HEIGHT,std::string name,bool isMaximise = false);
        
        bool isWindowOpen();
        void handleEvents();
        void closeWindow();
        void maximiseWindow();
        void draw(std::vector<CelestialBody>& bodies);
        void drawBody(CelestialBody& body);
        void loadFont(std::string path);
        void calculateScreenPosition(std::vector<CelestialBody>& bodies);
        void initScale(std::vector<CelestialBody>& bodies);
};