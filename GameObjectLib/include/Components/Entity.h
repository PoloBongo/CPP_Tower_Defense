#pragma once
#include "Component.h"
class Entity : public Component
{
public:
    Entity();
    Entity(int _hp, int _damage, int _lane, float _speed , float _attackSpeed, float _range);

    int GetHealthPoint() const { return healthPoint; }
    int GetMaxHealthPoint() const { return maxHealthPoint; }
    int GetDamage() const { return damage; }
    float GetSpeed() const { return speed; }
    float GetAttackSpeed() const { return attackSpeed; }
    float GetRange() const { return range; }

    void SetHealthPoint(const int _hp)  { healthPoint = _hp;}
    void SetMaxHealthPoint(const int _maxHp)  { maxHealthPoint = _maxHp;}
    void SetDamage(const int _damage)  { damage = _damage; }
    void SetSpeed(const float _speed)  {  speed = _speed; }
    void SetAttackSpeed(const float _attackspeed) { attackSpeed = _attackspeed; }
    void SetRange(const float _range) { range = _range; }

    void MoveToPoint(Maths::Vector2i point, float speed);
    void SetCurrPathPoint(int newPathPoint);
    int GetCurrPathPoint() { return currPathPoint; }
    
    void SetLane(int newLane) { lane = newLane; }
    int GetLane() { return lane; }

    void IncrementCount() { count++; }
    void ResetCount() { count = 0; }
    int GetCount() { return count; }

    void TakeDamage(int damage);
    virtual void Die();
    void Update(sf::Time _delta) override;

protected:
    int currPathPoint = 0;
    int count = 0;

    int healthPoint;
    int maxHealthPoint;
    int damage;
    int lane;
    float speed;
    float attackSpeed;
    float range;
};
