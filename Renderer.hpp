#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "CelestialBody.hpp"
#include "Camera.hpp"

class Renderer{
    private:
        Camera camera;
        unsigned int WINDOW_WIDTH;
        unsigned int WINDOW_HEIGHT;
    public:
        enum class AppEvent {
            togglePause,
            close
        };
        
        sf::RenderWindow window;
        std::string name;
        sf::Font font;
        CelestialBody* focusedBody = nullptr;

        bool trail = true;
        static constexpr float EARTH_RADIUS_AU = 4.26e-5f;
        static constexpr float MIN_PLANET_RADIUS_PX = 2.0f;
        int TRAIL_LENGTH = 10000;

        std::vector<AppEvent> events;

        Renderer(unsigned int WINDOW_WIDTH,unsigned int WINDOW_HEIGHT,std::string name,bool isMaximise = false);
        
        void update(std::vector<CelestialBody*>& bodies);
        
        
        bool isWindowOpen();
        void handleEvents(std::vector<CelestialBody*>& bodies);
        void closeWindow();
        void maximiseWindow();
        void draw(std::vector<CelestialBody*>& bodies);
        void drawBody(CelestialBody* body);
        void calculateOrbitTrail(CelestialBody* body);
        void drawOrbitTrail(CelestialBody* body);
        void loadFont(std::string path);
        void calculateScreenPosition(std::vector<CelestialBody*>& bodies);
        void refreshBodyLayout(std::vector<CelestialBody*>& bodies);
        void initScale(std::vector<CelestialBody*>& bodies);
        void calculateBodySize(CelestialBody* body);
        bool checkBodyClicked(sf::Vector2f clickPos,CelestialBody* body);
};