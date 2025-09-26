#include "Weapon.h"
#include "Models/Character/Character.h"
#include "Views/Bullet/BulletView.h"
#include "cocos2d.h"

USING_NS_CC;

Weapon::Weapon(const WeaponDescriptor& descriptor, cocos2d::Sprite3D* owner, cocos2d::Node* root) 
	: descriptor(descriptor), _owner(owner), _root(root), _ammo(descriptor.clipSize)
{
	_ready = true;
	_time = 0.0f;
}

bool Weapon::hasAmmo() const noexcept
{
	return _ammo > 0;
}

bool Weapon::isReady() const noexcept
{
	return _ready;
}

void Weapon::reload()
{
	_ammo = descriptor.clipSize;
}

void Weapon::update(float deltaTime)
{
	if (!_ready)
	{
		if (_time > 0)
		{
			_time -= deltaTime;
		}
		else
		{
			_ready = true;
		}
	}
}

void Weapon::fire(std::shared_ptr<Character> character, bool hit)
{
	if (_ammo > 0)
	{
		_ammo -= 1;
		_time = 1.0f / descriptor.fireRate;
		_ready = false;

		Skeleton3D* skeleton = _owner->getSkeleton();
		Bone3D* rightHandBone = skeleton->getBoneByName("RightHand");
		Mat4 worldMat = rightHandBone->getWorldMat();
		cocos2d::Vec3 worldPosition;
		worldMat.transformPoint(&worldPosition);
		Vec3 position = _owner->getPosition3D() + worldPosition * _owner->getScale();
		Sprite3D* view = Sprite3D::create("objects/bullet.c3b", "objects/bullet.png");
		BulletView* bullet = BulletView::create(shared_from_this(), character, hit);

		bullet->addChild(view);
		bullet->setPosition3D(position);
		view->setScale(1);
		view->setPosition3D(cocos2d::Vec3(0, 0, 0));

		_root->addChild(bullet);
	}
}

void Weapon::addModifierDescription(std::string desc)
{
	modifiersDesc.push_back(desc);
}

std::string Weapon::getModifiersDescription() const
{
	std::string result;
	for (const auto& desc : modifiersDesc)
	{
		result += desc + "\n";
	}
	return result;
}
