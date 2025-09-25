#pragma once

#include "BulletView.h"

#include <cocos2d.h>

bool BulletView::init(std::weak_ptr<Weapon> weapon, std::shared_ptr<Character> target, bool hit)
{
	_weapon = weapon;
	_target = target;
	_hit = hit;

	this->scheduleUpdate();

	return true;
}

void BulletView::update(float deltaTime)
{
	auto weaponShared = _weapon.lock();
    if (!weaponShared)
    {
		CCLOG("BulletView::update. Pointer to weapon is nullptr.");
        this->removeFromParentAndCleanup(true);
        return;
    }

	const WeaponDescriptor& weaponDescriptor = weaponShared->descriptor;
	if (auto targetShared = _target.lock())
	{
		cocos2d::Vec3 targetPosition = targetShared->getPosition() + cocos2d::Vec3(0, 2, 0);
		cocos2d::Vec3 direction = targetPosition - this->getPosition3D();
		direction.normalize();
		cocos2d::Vec3 newPosition = this->getPosition3D() + direction * weaponDescriptor.muzzleVelocity * deltaTime * 10;
		this->setPosition3D(newPosition);
		float distance = targetPosition.distance(this->getPosition3D());
		if (distance < 10)
		{
			if (_hit)
			{
				float damage = weaponDescriptor.damage;
				if (targetShared->armor > 0)
				{
					targetShared->armor = std::max(0.0f, targetShared->armor - damage);
				}
				else if (targetShared->health > 0)
				{
					targetShared->health -= damage;
				}

				if (targetShared->onTakeDamage)
				{
					targetShared->onTakeDamage();
				}

				if (!targetShared->isAlive())
				{
					targetShared->runAnimation("objects/Death.c3b", false);
					if (targetShared->onDeath)
					{
						targetShared->onDeath();
					}
				}
			}

			this->removeFromParentAndCleanup(true);
		}
	}
	else
	{
		CCLOG("BulletView::update. _target is expired.");
	}
}
