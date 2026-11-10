
#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(HackAIMenu, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        auto button = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName(
                "GJ_likeBtn_001.png"
            ),
            this,
            menu_selector(HackAIMenu::onHackAI)
        );

        auto menu = this->getChildByID("bottom-menu");

        if (menu && button) {
            menu->addChild(button);
            button->setID("hack-ai-button"_spr);
            menu->updateLayout();
        }

        return true;
    }

    void onHackAI(CCObject*) {
        FLAlertLayer::create(
            "HACK AI",
            "Welcome to HACK AI!",
            "OK"
        )->show();
    }
};
