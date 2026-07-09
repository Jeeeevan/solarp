#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "CelestialBody.hpp"

class Renderer{
    public:
        enum class AppEvent {
            togglePause,
            close
        };
        
        sf::RenderWindow window;
        unsigned int WINDOW_WIDTH;
        unsigned int WINDOW_HEIGHT;
        std::string name;
        sf::Font font;

        bool trail = true;
        float distanceScale;
        float targetRadius; 
        int TRAIL_LENGTH = 10000;

        std::vector<AppEvent> events;

        Renderer(unsigned int WINDOW_WIDTH,unsigned int WINDOW_HEIGHT,std::string name,bool isMaximise = false);
        
        void update(std::vector<CelestialBody>& bodies);
        
        
        bool isWindowOpen();
        void handleEvents();
        void closeWindow();
        void maximiseWindow();
        void draw(std::vector<CelestialBody>& bodies);
        void drawBody(CelestialBody& body);
        void calculateOrbitTrail(CelestialBody& body);
        void drawOrbitTrail(CelestialBody& body);
        void loadFont(std::string path);
        void calculateScreenPosition(std::vector<CelestialBody>& bodies);
        void initScale(std::vector<CelestialBody>& bodies);
};