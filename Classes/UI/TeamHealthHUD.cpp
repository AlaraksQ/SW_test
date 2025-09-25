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
        auto bars = createHealthBars(Vec2(startX, startY - i * offsetY),
            Color3B::GREEN, Color3B::YELLOW);
        bars.character = allies[i];
        _allyBars.push_back(bars);
    }

    startX = winSize.width - 200;

    for (size_t i = 0; i < enemies.size(); ++i)
    {
        auto bars = createHealthBars(Vec2(startX, startY - i * offsetY),
            Color3B::RED, Color3B::YELLOW);
        bars.character = enemies[i];
        _enemyBars.push_back(bars);
    }
}

TeamHealthHUD::CharacterBars TeamHealthHUD::createHealthBars(
    const Vec2& pos,
    const Color3B& healthColor,
    const Color3B& armorColor)
{
    CharacterBars bars;
    float borderSize = 1.0f;

    auto hpBg = Sprite::create("ui/TEX_health_bar.png");
    hpBg->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    hpBg->setPosition(pos);
    this->addChild(hpBg);

    // Получаем точный размер и origin фона
    Rect hpRect = hpBg->getBoundingBox();

    auto hpFill = LayerColor::create(Color4B(healthColor), hpRect.size.width - 2 * borderSize, hpRect.size.height - 2 * borderSize);
    hpFill->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    hpFill->setPosition(hpRect.origin + Vec2(borderSize, borderSize)); // выравниваем по верхнему левому углу спрайта
    this->addChild(hpFill);
    bars.healthBar = hpFill;
    bars.healthBg = hpBg;

    // Armor аналогично
    Vec2 armorPos = pos + Vec2(0, hpRect.size.height);
    auto armorBg = Sprite::create("ui/TEX_armor_bar.png");
    armorBg->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    armorBg->setPosition(armorPos);
    this->addChild(armorBg);

    Rect armorRect = armorBg->getBoundingBox();
    auto armorFill = LayerColor::create(Color4B(armorColor), armorRect.size.width - 2, armorRect.size.height - 2);
    armorFill->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    armorFill->setPosition(armorRect.origin + Vec2(borderSize, borderSize));
    this->addChild(armorFill);
    bars.armorBar = armorFill;
    bars.armorBg = armorBg;

    return bars;
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
                    bars.healthBar->setVisible(false);
                    bars.healthBg->setVisible(false);
                    bars.armorBar->setVisible(false);
                    bars.armorBg->setVisible(false);
                }
            }
        }
    };

    updateBars(_allyBars);
    updateBars(_enemyBars);
}
