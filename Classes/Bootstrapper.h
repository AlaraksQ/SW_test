#pragma once

#include "Models/Battlefield/Battlefield.h"
#include "Views/Character/CharacterView.h"
#include "cocos2d.h"
#include <vector>


class Bootstrapper : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void update(float delta) override;

	CREATE_FUNC(Bootstrapper);

private:
	std::unique_ptr<Battlefield> _battlefield;
	cocos2d::Camera* _camera;

	int getTeam(const std::string& name);
	std::unordered_map<int, std::vector<cocos2d::Vec3>> getTeamSpawnPoints(cocos2d::Node* node);
	std::vector<CharacterView> getCharacterViews();

	// For cam unlock rotation
	/*bool _dragging = false;
	cocos2d::Vec2 _prevCursor;
	float _camYaw = 0.0f;
	float _camPitch = 20.0f;
	float _camDistance = 600.0f;*/
};
