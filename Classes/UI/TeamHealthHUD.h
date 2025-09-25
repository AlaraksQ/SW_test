#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Models/Character/Character.h"

class TeamHealthHUD : public cocos2d::Node
{
public:
    CREATE_FUNC(TeamHealthHUD);

    bool init() override;

    void setTeams(const std::vector<std::shared_ptr<Character>>& allies,
        const std::vector<std::shared_ptr<Character>>& enemies);

    void updateHUD();

private:
    struct CharacterBars
    {
        cocos2d::LayerColor* healthBar = nullptr;
        cocos2d::LayerColor* armorBar = nullptr;
        cocos2d::Sprite* healthBg;
        cocos2d::Sprite* armorBg;
        std::weak_ptr<Character> character;
    };

    std::vector<CharacterBars> _allyBars;
    std::vector<CharacterBars> _enemyBars;

    CharacterBars createHealthBars(const cocos2d::Vec2& pos,
        const cocos2d::Color3B& healthColor,
        const cocos2d::Color3B& armorColor
    );
};