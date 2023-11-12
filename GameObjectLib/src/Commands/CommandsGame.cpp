#include "SceneManager.h"
#include "CameraManager.h"

PauseCommand::PauseCommand() {

}

void PauseCommand::Execute(sf::Time _delta) {
	SceneManager::GetActiveGameScene()->SetIsActive(!SceneManager::GetActiveGameScene()->GetIsActive());
}

ZoomCommand::ZoomCommand() {

}

void ZoomCommand::Execute(sf::Time _delta) {
	CameraManager::Zoom(0.95f);
}

DezoomCommand::DezoomCommand() {
}

void DezoomCommand::Execute(sf::Time _delta) {
	CameraManager::Zoom(1.05f);
}


LeftCommand::LeftCommand() {}
void LeftCommand::Execute(sf::Time _delta) {
	CameraManager::Move(-500.f * _delta.asSeconds(), 0);
}

RightCommand::RightCommand() {}
void RightCommand::Execute(sf::Time _delta) {
	CameraManager::Move(500.f * _delta.asSeconds(), 0);
}


UpCommand::UpCommand() {}
void UpCommand::Execute(sf::Time _delta) {
	CameraManager::Move(0.f,-500.f * _delta.asSeconds());
}

DownCommand::DownCommand() {}
void DownCommand::Execute(sf::Time _delta) {
	CameraManager::Move(0.f, +500.f * _delta.asSeconds());
}
