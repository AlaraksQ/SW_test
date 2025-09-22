#include "Models/Character/Character.h"

class BulletView : public cocos2d::Node
{
public:
	bool init(std::weak_ptr<Weapon> weapon, std::shared_ptr<Character> target, bool hit);
	void update(float deltaTime);

	static BulletView* create(std::weak_ptr<Weapon> weapon, std::shared_ptr<Character> target, bool hit)
	{
		BulletView* pRet = new (std::nothrow) BulletView();
		if (pRet && pRet->init(weapon, target, hit))
		{
			pRet->autorelease();
			return pRet;
		}
		else
		{
			delete pRet;
			pRet = nullptr;
			return nullptr;
		}
	}

private:
	std::weak_ptr<Weapon> _weapon;
	std::weak_ptr<Character> _target;
	bool _hit;
};