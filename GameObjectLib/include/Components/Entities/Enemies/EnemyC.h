#include "Components/Entities/EnemyAbstract.h"
#include "Components/SpriteRenderer.h"

class EnemyC : public EnemyAbstract {
public:
	EnemyC();
private:
	Sprite sprite;
};