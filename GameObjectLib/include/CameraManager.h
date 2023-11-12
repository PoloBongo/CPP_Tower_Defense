#pragma once
#include <SFML/Graphics.hpp>


class CameraManager
{
public:

    static void SetWindow(sf::RenderWindow* _window);
    static sf::View GetView() { return view; }

    static void Update(sf::Time _delta);
    static void Event(sf::Event& event);

    static void Move(float offsetX, float offsetY);

    static void SetCenter(float x, float y);

    static void Zoom(float factor);

    static void SetZoom(float _zoom);

private:
    static sf::RenderWindow* window;
    static sf::View view;
    static float minZoom, zoom, maxZoom;
    static int initialX, initialY;
    static bool isDragging;
    static sf::Vector2i lastMousePos;
};

