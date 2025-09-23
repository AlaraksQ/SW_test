#include "GameUI.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

bool GameUI::init()
{
    if (!Node::init())
        return false;

    auto winSize = Director::getInstance()->getWinSize();

    _continueButton = ui::Button::create("ui/TEX_button_continue.png");
    _continueButton->setPosition({ winSize.width / 2, winSize.height / 2 });
    _continueButton->addClickEventListener([this](Ref*)
    {
        if (onContinue) onContinue();
    });
    this->addChild(_continueButton);

    _restartButton = ui::Button::create("ui/TEX_button_replay.png");
    _restartButton->setPosition({ winSize.width / 2, winSize.height / 2 });
    _restartButton->setVisible(false);
    _restartButton->addClickEventListener([this](Ref*)
    {
        if (onRestart) onRestart();
    });
    this->addChild(_restartButton);

    showContinue();

    return true;
}

void GameUI::showContinue()
{
    _continueButton->setVisible(true);
    _restartButton->setVisible(false);
}

void GameUI::showRestart()
{
    _continueButton->setVisible(false);
    _restartButton->setVisible(true);
}
