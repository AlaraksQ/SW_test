#include "Character.h"

#include "Models/Battlefield/TargetLocator.h"
#include "Models/Weapon/Weapon.h"
#include "cocos2d.h"

USING_NS_CC;

Character::Character(
	cocos2d::Sprite3D* view,
	const CharacterDescriptor& character,
	std::shared_ptr<Weapon> weapon,
	TargetLocator* targetLocator)
		: descriptor(character), _time(0.0f)
{
	_weapon = weapon;
	_targetLocator = targetLocator;
	_state = State::Idle;

	Sprite3d = view;
	health = descriptor.maxHealth;
	armor = descriptor.maxArmor;
}

bool Character::isAlive() const
{
	return health > 0 || armor > 0;
}

cocos2d::Vec3 Character::getPosition() const
{
	return Sprite3d->getPosition3D();
}

//TODO make if (_time > 0) _time -= deltaTime; and remove according code in every case
void Character::update(float deltaTime)
{
	if (!isAlive())
		return;

	auto target = _currentTarget.lock();

	switch (_state)
	{
		case State::Idle:
			runAnimation("objects/Idle.c3b", true);

			_currentTarget = _targetLocator->getNearestAliveTarget(shared_from_this());
			target = _currentTarget.lock();
			if (!_currentTarget.expired())
			{
				_state = State::Aiming;
				_time = descriptor.aimTime;

				cocos2d::Vec3 direction = target->getPosition() - this->getPosition();
				direction.normalize();
				float rotationY = CC_RADIANS_TO_DEGREES(atan2(direction.x, direction.z));
				cocos2d::Vec3 rotation = cocos2d::Vec3(0, rotationY, 0);
				Sprite3d->setRotation3D(rotation);
			}
			break;
		case State::Aiming:
			runAnimation("objects/Aiming.c3b", true);	
			if (target && target->isAlive())
			{
				if (_time > 0)
				{
					_time -= deltaTime;
				}
				else
				{
					_state = State::Shooting;
					_time = 0;
				}
			}
			else
			{
				_state = State::Idle;
				_time = 0;
			}
			break;
		case State::Shooting:
			if (target != nullptr && target->isAlive())
			{
				if (_weapon->hasAmmo())
				{
					if (_weapon->isReady())
					{
						float random = CCRANDOM_0_1();
						bool hit = random <= descriptor.accuracy
								   && random <= _weapon->descriptor.accuracy
								   && random >= target->descriptor.dexterity;
						_weapon->fire(target, hit);
						runAnimation("objects/Shooting.c3b", false, true);
					}
					else
					{
						_weapon->update(deltaTime);
					}
				}
				else
				{
					_state = State::Reloading;
					_time = _weapon->descriptor.reloadTime;
				}
			}
			else
			{
				_state = State::Idle;
			}
			break;
		case State::Reloading:
			runAnimation("objects/Reloading.c3b", false);

			if (_time > 0)
			{
				_time -= deltaTime;
			}
			else
			{
				if (target && target->isAlive())
				{
					_state = State::Shooting;
				}
				else
				{
					_state = State::Idle;
				}

				_weapon->reload();
				_time = 0;
			}
			break;
		default:
			_state = State::Idle;
			break;
	}
}

// Note! Check properly animations. Revert animations cache if something wrong
void Character::runAnimation(const std::string& name, bool repeat, bool force)
{
	if (_currentAnimation == name && !force)
	{
		return;
	}

	Sprite3d->stopAllActions();

	cocos2d::RefPtr<Animate3D> animate;

	auto it = _animationCache.find(name);
	if (it != _animationCache.end())
	{
		animate = it->second;
	}
	else
	{
		Animation3D* animation = Animation3D::create(name);

		if (!animation)
		{
			CCLOG("Animation3D not found: %s", name.c_str());
			return;
		}

		Animate3D* rawAnimate = Animate3D::create(animation);
		if (!rawAnimate)
		{
			CCLOG("Animate3D creation failed: %s", name.c_str());
			return;
		}

		animate = cocos2d::RefPtr<Animate3D>(rawAnimate);
		_animationCache[name] = animate;
	}

	if (!animate)
	{
		CCLOG("Animate3D is nullptr for %s", name.c_str());
		return;
	}

	if (repeat)
	{
		Sprite3d->runAction(RepeatForever::create(animate));
	}
	else
	{
		Sprite3d->runAction(animate);
	}

	_currentAnimation = name;
}
