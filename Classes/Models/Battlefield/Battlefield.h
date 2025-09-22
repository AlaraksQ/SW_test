#pragma once

#include "Models/Character/Character.h"
#include "TargetLocator.h"
#include "Views/Character/CharacterView.h"
#include "math/Vec3.h"
#include <map>
#include <vector>

class Battlefield : public TargetLocator
{
public:
	Battlefield(cocos2d::Node* root, std::unordered_map<int, std::vector<cocos2d::Vec3>> map);

	void update(float delta);
	void start(std::vector<CharacterView> characters);

private:
	bool _paused;
	cocos2d::Node* _root;
	std::unordered_map<int, std::vector<cocos2d::Vec3>> _spawnPositionsByTeam;
	std::map<int, std::vector<std::shared_ptr<Character>>> _charactersByTeam;

	std::shared_ptr<Character> getNearestAliveTarget(const std::shared_ptr<Character>& character) override;
	int getTeam(const Character* target);
	std::shared_ptr<Character> createCharacterAt(
		const CharacterView& prefab,
		Battlefield& battlefield,
		const cocos2d::Vec3& position);
};