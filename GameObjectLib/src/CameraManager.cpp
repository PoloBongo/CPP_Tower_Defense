#include "CameraManager.h"
#include <iostream>

sf::RenderWindow* CameraManager::window;
sf::View CameraManager::view;
sf::Vector2i CameraManager::lastMousePos;
bool CameraManager::isDragging = false;
float CameraManager::zoom = 1;
float CameraManager::minZoom = 1.f;
float CameraManager::maxZoom = 3.f;
int CameraManager::initialX = 0;
int CameraManager::initialY = 0;


void CameraManager::SetWindow(sf::RenderWindow* _window) {
	CameraManager::window = _window;
	CameraManager::view = CameraManager::window->getDefaultView();
}

void CameraManager::Event(sf::Event& event) {
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		CameraManager::isDragging = true;
		CameraManager::lastMousePos = sf::Mouse::getPosition(*window);
	}

	if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
	{
		isDragging = false;
	}

	if (event.type == sf::Event::MouseWheelScrolled)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
		sf::Vector2f worldPos = window->mapPixelToCoords(mousePos, view);
		if (event.mouseWheelScroll.delta > 0 && zoom < maxZoom)
		{
			zoom *= 1.05f;
		}
		else if (event.mouseWheelScroll.delta < 0 && zoom > 1.0f)
		{
			zoom /= 1.05f;
		}
		if (zoom < maxZoom && zoom > 1.0f) {
			view.setCenter(worldPos);
			view.setSize(window->getDefaultView().getSize() / zoom);

			if (view.getSize().x > window->getSize().x) {
				view.setSize(window->getSize().x, view.getSize().y);
			}
			if (view.getSize().y > window->getSize().y) {
				view.setSize(view.getSize().x, window->getSize().y);
			}
			if (view.getCenter().x - view.getSize().x / 2 < 0.f) {
				view.setCenter(view.getSize().x / 2, view.getCenter().y);
			}
			if (view.getCenter().y - view.getSize().y / 2 < 0.f) {
				view.setCenter(view.getCenter().x, view.getSize().y / 2);
			}
			if (view.getCenter().x + view.getSize().x / 2 > 1920) {
				view.setCenter(1920 - view.getSize().x / 2, view.getCenter().y);
			}
			if (view.getCenter().y + view.getSize().y / 2 > 1080) {
				view.setCenter(view.getCenter().x, 1080 - view.getSize().y / 2);
			}
		}


		CameraManager::window->setView(view);
	}
}

void CameraManager::Update(sf::Time _delta) {
	if (CameraManager::isDragging)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(*CameraManager::window);
		sf::Vector2f offset = sf::Vector2f(lastMousePos - mousePos);

		// D�placez temporairement la vue pour calculer la nouvelle position
		sf::View tempView = CameraManager::GetView();


		// R�cup�rez les dimensions de la fen�tre
		sf::Vector2u windowSize = CameraManager::window->getSize();
		tempView.move(offset);
		// V�rifiez les limites pour emp�cher la sortie de l'�cran
		if (view.getCenter().x - view.getSize().x / 2 < 0.0f)
		{
			tempView.setCenter(tempView.getSize().x / 2.0f, tempView.getCenter().y);
		}
		if (view.getCenter().y - view.getSize().y / 2 < 0.f)
		{
			tempView.setCenter(tempView.getCenter().x, tempView.getSize().y / 2.0f);
		}
		if (view.getCenter().x + view.getSize().x / 2 > windowSize.x)
		{
			tempView.setCenter(windowSize.x - tempView.getSize().x / 2.0f, tempView.getCenter().y);
		}
		if (view.getCenter().y + view.getSize().y / 2 > windowSize.y)
		{
			tempView.setCenter(tempView.getCenter().x, windowSize.y - tempView.getSize().y / 2.0f);
		}

		// Appliquez la vue temporaire � la cam�ra
		CameraManager::view = tempView;
		window->setView(CameraManager::GetView());
		lastMousePos = mousePos;

	}
}

void CameraManager::Move(float offsetX, float offsetY) {
	// D�placez temporairement la vue pour calculer la nouvelle position
	sf::View tempView = CameraManager::GetView();
	// R�cup�rez les dimensions de la fen�tre
	sf::Vector2u windowSize = CameraManager::window->getSize();
	tempView.move(offsetX, offsetY);
	// V�rifiez les limites pour emp�cher la sortie de l'�cran
	if (view.getCenter().x - view.getSize().x / 2 < 0.0f)
	{
		tempView.setCenter(tempView.getSize().x / 2.0f, tempView.getCenter().y);
	}
	if (view.getCenter().y - view.getSize().y / 2 < 0.f)
	{
		tempView.setCenter(tempView.getCenter().x, tempView.getSize().y / 2.0f);
	}
	if (view.getCenter().x + view.getSize().x / 2 > windowSize.x)
	{
		tempView.setCenter(windowSize.x - tempView.getSize().x / 2.0f, tempView.getCenter().y);
	}
	if (view.getCenter().y + view.getSize().y / 2 > windowSize.y)
	{
		tempView.setCenter(tempView.getCenter().x, windowSize.y - tempView.getSize().y / 2.0f);
	}

	// Appliquez la vue temporaire � la cam�ra
	CameraManager::view = tempView;
	window->setView(CameraManager::GetView());
}

void CameraManager::SetCenter(float x, float y) {
	CameraManager::initialX = x;
	CameraManager::initialY = y;
	CameraManager::view.setCenter(x, y);
}

void CameraManager::Zoom(float factor) {
	view.setSize(CameraManager::window->getDefaultView().getSize() / CameraManager::zoom);
}

void CameraManager::SetZoom(float _zoom) {
	if (CameraManager::zoom * _zoom < CameraManager::minZoom)
	{
		CameraManager::zoom = CameraManager::minZoom;
	}
	else if (CameraManager::zoom * _zoom > CameraManager::maxZoom)
	{
		CameraManager::zoom = CameraManager::maxZoom;
	}
	else
	{
		CameraManager::zoom *= _zoom;
	}
	CameraManager::Zoom(CameraManager::zoom);

}