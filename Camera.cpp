#include "Camera.hpp"

Camera::Camera(unsigned int WINDOW_WIDTH,unsigned int WINDOW_HEIGHT)
{
    this->WINDOW_HEIGHT = WINDOW_HEIGHT;
    this->WINDOW_WIDTH = WINDOW_WIDTH;
}

void Camera::zoom(float factor) 
{
        pixelsPerAU *= factor;  
}

void Camera::pan(float pixelDeltaX, float pixelDeltaY) 
{
        // Convert pixel movement back to AU
        centerX_AU -= pixelDeltaX / pixelsPerAU;
        centerY_AU -= pixelDeltaY / pixelsPerAU;
}

sf::Vector2f Camera::toScreenCoords(double bodyX_AU, double bodyY_AU) 
{
        float screenX = (bodyX_AU - centerX_AU) * pixelsPerAU + WINDOW_WIDTH / 2;
        float screenY = (bodyY_AU - centerY_AU) * pixelsPerAU + WINDOW_HEIGHT / 2;
        return {screenX, screenY};
}