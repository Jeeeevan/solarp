#pragma once

#include <vector>
#include "CelestialBody.hpp"

class Camera{
    private:
        unsigned int WINDOW_WIDTH;
        unsigned int WINDOW_HEIGHT;
        float centerX_AU = 0, centerY_AU = 0;  // Camera center in AU
        float pixelsPerAU = 80.0f;

    public:
        float getPixelsPerAU() const { return pixelsPerAU; }
        Camera(unsigned int WINDOW_WIDTH,unsigned int WINDOW_HEIGHT);
        void zoom(float factor);
        void setCenter(float x,float y);
        void pan(float pixelDeltaX, float pixelDeltaY);
        sf::Vector2f toScreenCoords(double bodyX_AU, double bodyY_AU);
        void setWindowSize(unsigned int w, unsigned int h);
};