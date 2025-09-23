#include "Models/Character/Character.h"

namespace cocos2d 
{
    namespace ui 
    {
        class Button;
    }
}

class GameUI : public cocos2d::Node
{
public:
    CREATE_FUNC(GameUI);

    virtual bool init() override;

    void showContinue();
    void showRestart();

    std::function<void()> onContinue;
    std::function<void()> onRestart;

private:
    cocos2d::ui::Button* _continueButton = nullptr;
    cocos2d::ui::Button* _restartButton = nullptr;
};
