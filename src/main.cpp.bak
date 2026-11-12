#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(HackAIMenu, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        auto label = CCLabelBMFont::create(
            "HACK AI",
            "bigFont.fnt"
        );

        auto button = CCMenuItemSpriteExtra::create(
            label,
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
