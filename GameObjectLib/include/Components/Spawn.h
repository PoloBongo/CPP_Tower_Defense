#pragma once
#include "Component.h"

class Spawn : public Component
{

public:
	void SetSpawnAvailable(bool _available) { available = _available; }
	bool IsSpawnAvailable() { return available; }

private:
	bool available = true;

};