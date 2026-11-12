#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

namespace {
    bool g_noclipEnabled = false;
    CCLabelBMFont* g_noclipLabel = nullptr;
}

class $modify(HackAIMenu, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        auto menu = this->getChildByID("bottom-menu");
        if (!menu) {
            return true;
        }

        auto label = CCLabelBMFont::create("HACK AI", "bigFont.fnt");
        auto button = CCMenuItemSpriteExtra::create(
            label, this, menu_selector(HackAIMenu::onHackAI)
        );

        menu->addChild(button);
        button->setID("hack-ai-button"_spr);

        g_noclipLabel = CCLabelBMFont::create(
            "NOCLIP: OFF", "bigFont.fnt"
        );

        auto noclipButton = CCMenuItemSpriteExtra::create(
            g_noclipLabel, this, menu_selector(HackAIMenu::onNoclip)
        );

        menu->addChild(noclipButton);
        noclipButton->setID("hack-ai-noclip"_spr);
        menu->updateLayout();

        return true;
    }

    void onHackAI(CCObject*) {
        FLAlertLayer::create(
            "HACK AI",
            "Welcome to HACK AI!",
            "OK"
        )->show();
    }

    void onNoclip(CCObject*) {
        g_noclipEnabled = !g_noclipEnabled;

        g_noclipLabel->setString(
            g_noclipEnabled ? "NOCLIP: ON" : "NOCLIP: OFF"
        );
    }
};

class $modify(HackAIPlayLayer, PlayLayer) {
    void destroyPlayer(PlayerObject* player, GameObject* object) {
        if (g_noclipEnabled) {
            return;
        }

        PlayLayer::destroyPlayer(player, object);
    }
};
