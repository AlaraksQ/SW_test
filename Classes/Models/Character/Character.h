#pragma once

#include "Descriptors/CharacterDescriptor.h"
#include "Models/Battlefield/Battlefield.h"
#include "Models/Battlefield/TargetLocator.h"
#include "Models/Weapon/Weapon.h"
#include "cocos2d.h"
#include <string>
#include <vector>
#include <memory>

class Character : public std::enable_shared_from_this<Character>
{
public:
	Character(
		cocos2d::Sprite3D* view,
		const CharacterDescriptor& descriptor,
		std::shared_ptr<Weapon> weapon,
		TargetLocator* targetLocator);

	enum class State
	{
		Idle,
		Aiming,
		Shooting,
		Reloading
	};

	std::string _currentAnimation;
	cocos2d::Sprite3D* Sprite3d;
	CharacterDescriptor descriptor;
	float health;
	float armor;

	std::function<void()> onDeath;
	std::function<void()> onTakeDamage;

	cocos2d::Sprite3D* getSprite3D() const noexcept;
	bool isAlive() const;
	void update(float deltaTime);
	void runAnimation(const std::string& name, bool repeat, bool force = false);
	cocos2d::Vec3 getPosition() const;

	void addModifierDescription(std::string desc);
	std::string getModifiersDescription() const;
	void updateCharacterHealthAndArmor();

private:
	std::shared_ptr<Weapon> _weapon;
	std::weak_ptr<Character> _currentTarget;
	TargetLocator* _targetLocator;

	std::vector<std::string> modifiersDesc;

	std::unordered_map<std::string, cocos2d::RefPtr<cocos2d::Animate3D>> _animationCache;

	State _state;
	float _time;
};