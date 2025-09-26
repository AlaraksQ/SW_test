#pragma once

#include "Descriptors/WeaponDescriptor.h"
#include "cocos2d.h"
#include <string>
#include <vector>
#include <memory>

class Character;
class Weapon : public std::enable_shared_from_this<Weapon>
{
public:
	Weapon(const WeaponDescriptor& descriptor, cocos2d::Sprite3D* owner, cocos2d::Node* root);

	WeaponDescriptor descriptor;

	bool hasAmmo() const noexcept;
	bool isReady() const noexcept;

	void reload();
	void update(float deltaTime);
	void fire(std::shared_ptr<Character> character, bool hit);

	void addModifierDescription(std::string desc);
	std::string getModifiersDescription() const;

private:
	int _ammo;
	bool _ready;
	float _time;
	cocos2d::Sprite3D* _owner;
	cocos2d::Node* _root;

	std::vector<std::string> modifiersDesc;
};
