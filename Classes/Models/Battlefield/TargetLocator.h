#pragma once

#include "Models/Character/Character.h"
#include "cocos2d.h"

class Character;
class TargetLocator
{
public:
	virtual std::shared_ptr<Character> getNearestAliveTarget(const std::shared_ptr<Character>& character) = 0;
};