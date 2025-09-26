#include "TeamHealthHUD.h"

USING_NS_CC;

bool TeamHealthHUD::init()
{
    if (!Node::init())
        return false;

    setContentSize(Director::getInstance()->getWinSize());

    return true;
}

void TeamHealthHUD::setTeams(const std::vector<std::shared_ptr<Character>>& allies,
    const std::vector<std::shared_ptr<Character>>& enemies)
{
    _allyBars.clear();
    _enemyBars.clear();

    Size winSize = Director::getInstance()->getWinSize();

    float startX = 50;
    float startY = winSize.height - 50;
    float offsetY = 40;

    for (size_t i = 0; i < allies.size(); ++i)
    {
        CharacterBars bars;
        bars.character = allies[i];
        createHealthBars(bars,Vec2(startX, startY - i * offsetY),
            Color3B::GREEN, Color3B::YELLOW);
        _allyBars.push_back(bars);
    }

    startX = winSize.width - 200;

    for (size_t i = 0; i < enemies.size(); ++i)
    {
        CharacterBars bars;
        bars.character = enemies[i];
       createHealthBars(bars, Vec2(startX, startY - i * offsetY),
            Color3B::RED, Color3B::YELLOW);
        _enemyBars.push_back(bars);
    }
}

void TeamHealthHUD::createHealthBars(
    CharacterBars& bars,
    const Vec2& pos,
    const Color3B& healthColor,
    const Color3B& armorColor)
{
    const auto character = bars.character.lock();
    if (!character)
    {
        CCLOGWARN("Can't create Health and Armor bars for character. Character not set.");
        return;
    }

    const float hpHeight = 10.0f;
    const float armorHeight = 5.0f;
    const float spacing = 2.0f;
    const float healthPerDivision = 5.0f;

    auto container = Node::create();
    container->setPosition(pos);
    this->addChild(container);

    // --- HP ---
    const auto maxHp = character->descriptor.maxHealth;
    auto width = maxHp;
    auto hpFill = LayerColor::create(Color4B(healthColor), width, hpHeight);
    hpFill->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    hpFill->setPosition(Vec2(0, 0));
    container->addChild(hpFill);
    bars.healthBar = hpFill;

    // --- HP border ---
    auto hpBorder = DrawNode::create();
    Vec2 hpRect[4] = {
        Vec2(0, 0),
        Vec2(width, 0),
        Vec2(width, hpHeight),
        Vec2(0, hpHeight)
    };
    hpBorder->drawPoly(hpRect, 4, true, Color4F::BLACK);

    if (maxHp > 0)
    {
        for (float x = healthPerDivision; x < width; x += healthPerDivision)
        {
            hpBorder->drawLine(Vec2(x, 0), Vec2(x, hpHeight), Color4F::BLACK);
        }
    }

    container->addChild(hpBorder, 1);

    // --- Armor ---
    width = character->descriptor.maxArmor;
    auto armorFill = LayerColor::create(Color4B(armorColor), width, armorHeight);
    armorFill->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    armorFill->setPosition(Vec2(0, hpHeight + spacing));
    container->addChild(armorFill);
    bars.armorBar = armorFill;

    // --- Armor border ---
    auto armorBorder = DrawNode::create();
    Vec2 armorRect[4] = {
        Vec2(0, hpHeight + spacing),
        Vec2(width, hpHeight + spacing),
        Vec2(width, hpHeight + spacing + armorHeight),
        Vec2(0, hpHeight + spacing + armorHeight)
    };
    armorBorder->drawPoly(armorRect, 4, true, Color4F::BLACK);
    container->addChild(armorBorder, 1);

    bars.container = container;
}

void TeamHealthHUD::updateHUD()
{
    auto updateBars = [](std::vector<CharacterBars>& barsList)
    {
        for (auto& bars : barsList)
        {
            if (auto character = bars.character.lock())
            {
                if (character->isAlive())
                {
                    bars.healthBar->setScaleX(character->health / character->descriptor.maxHealth);
                    bars.armorBar->setScaleX(character->armor / character->descriptor.maxArmor);
                    bars.healthBar->setVisible(true);
                    bars.armorBar->setVisible(true);
                }
                else
                {
                    bars.container->setVisible(false);
                }
            }
        }
    };

    updateBars(_allyBars);
    updateBars(_enemyBars);
}

void TeamHealthHUD::resetHUD()
{
    auto resetBars = [](std::vector<CharacterBars>& barsList)
    {
        for (auto& bars : barsList)
        {
            if (bars.container)
            {
                bars.container->removeFromParent();
                bars.container = nullptr;
                bars.healthBar = nullptr;
                bars.armorBar = nullptr;
            }
        }
    };

    resetBars(_allyBars);
    resetBars(_enemyBars);
}
