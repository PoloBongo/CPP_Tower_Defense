#pragma once

#include "Command.h"

class PauseCommand : public Command
{
public:
	PauseCommand();
	void Execute(sf::Time _delta) override;
};


class ZoomCommand : public Command
{
public:
	ZoomCommand();
	void Execute(sf::Time _delta) override;
};


class DezoomCommand : public Command
{
public:
	DezoomCommand();
	void Execute(sf::Time _delta) override;
};

class LeftCommand : public Command
{
public:
	LeftCommand();
	void Execute(sf::Time _delta) override;
};


class RightCommand : public Command
{
public:
	RightCommand();
	void Execute(sf::Time _delta) override;
};


class UpCommand : public Command
{
public:
	UpCommand();
	void Execute(sf::Time _delta) override;
};

class DownCommand : public Command
{
public:
	DownCommand();
	void Execute(sf::Time _delta) override;
};