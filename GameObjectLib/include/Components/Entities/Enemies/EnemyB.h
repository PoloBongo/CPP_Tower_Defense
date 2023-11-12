#include "Components/Entities/EnemyAbstract.h"
#include "Components/SpriteRenderer.h"

class EnemyB : public EnemyAbstract {
public:
	EnemyB();
private:
	Sprite sprite;
};