#include "Components/Input.h"
#include "WindowManager.h"
#include "EventManager.h"

Input::Input()
{
    isEnteringText = false;
	this->window = WindowManager::GetWindow();
}

void Input::Update(sf::Time _delta)
{
	if (isEnteringText) {
        sf::String inputString = text.getString();

		Component::Update(_delta);
        for (int i = sf::Keyboard::A; i <= sf::Keyboard::Z; ++i) {
            if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i))) {
                    // Ajouter le caractère à la chaîne de texte si la saisie est activée
                    char newChar = 'A' + (i - sf::Keyboard::A);
                    inputString += newChar;
                    text.setString(inputString);
                

                // Attendre un court instant pour éviter la répétition rapide des touches
                sf::sleep(sf::milliseconds(100));
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
            // Supprimer le dernier caractère si la touche de retour arrière est enfoncée
            if (isEnteringText && inputString.getSize() > 0) {
                inputString.erase(inputString.getSize() - 1);
                text.setString(inputString);
            }

            // Attendre un court instant pour éviter la répétition rapide de la touche
            sf::sleep(sf::milliseconds(100));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
            // Commencer/arrêter la saisie lorsque la touche Entrée est enfoncée
            isEnteringText = !isEnteringText;

            // Attendre un court instant pour éviter la répétition rapide de la touche
            sf::sleep(sf::milliseconds(100));
        }
	}
	
}

void Input::Render(sf::RenderWindow* _window)
{
	Component::Render(_window);

    _window->draw(rectangle);
    _window->draw(text);
}

void Input::SetInput(unsigned int fontSize)
{
    sf::Font font;
    if (!font.loadFromFile("../Fonts/Roboto-Medium.ttf")) {
        std::cout << "Font introuvable" << std::endl;
    }
    text = sf::Text("", font, fontSize);
    rectangle.setSize(sf::Vector2f(width, height));
    rectangle.setFillColor(sf::Color::White);
}
void Input::SetOrigin()
{
	rectangle.setOrigin(width / 2, height / 2);
	text.setOrigin(width / 2, height / 2);
}
void Input::SetSize(float _width, float _height)
{
	this->width = _width;
	this->height = _height;
}

void Input::SetPosition(float _x, float _y)
{
	rectangle.setPosition(_x, _y);
	text.setPosition(_x - width / 2, _y);
}

bool Input::IsClicked()
{
	return rectangle.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window))) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isEnteringText;
}

Input::~Input()
{

}