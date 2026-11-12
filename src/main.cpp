#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

namespace {
    bool g_noclipEnabled = false;
}

class HackAIPopup : public Popup {
protected:
    CCLabelBMFont* m_noclipLabel = nullptr;

    bool init() {
        if (!Popup::init(300.f, 220.f))
            return false;

        auto bg = CCLayerColor::create(
            ccc4(0, 12, 5, 255), 260, 180
        );
        bg->setPosition({20, 20});
        this->addChild(bg, 0);

        auto topBar = CCLayerColor::create(
            ccc4(0, 255, 80, 255), 260, 3
        );
        topBar->setPosition({20, 197});
        this->addChild(topBar, 1);

        auto bottomBar = CCLayerColor::create(
            ccc4(0, 255, 80, 255), 260, 3
        );
        bottomBar->setPosition({20, 20});
        this->addChild(bottomBar, 1);

        auto title = CCLabelBMFont::create(
            "HACK AI", "bigFont.fnt"
        );
        title->setColor(ccc3(0, 255, 80));
        title->setScale(0.8f);
        title->setPosition({150, 180});
        this->addChild(title, 2);

        m_noclipLabel = CCLabelBMFont::create(
            g_noclipEnabled ? "NOCLIP: ON" : "NOCLIP: OFF",
            "bigFont.fnt"
        );
        m_noclipLabel->setColor(ccc3(0, 255, 80));

        auto noclipButton = CCMenuItemSpriteExtra::create(
            m_noclipLabel,
            this,
            menu_selector(HackAIPopup::onNoclip)
        );
        noclipButton->setPosition({150, 125});

        auto menu = CCMenu::create();
        menu->setPosition({0, 0});
        menu->addChild(noclipButton);
        this->addChild(menu, 3);

        auto comingSoon = CCLabelBMFont::create(
            "AI SOLVER - SOON", "bigFont.fnt"
        );
        comingSoon->setColor(ccc3(0, 180, 65));
        comingSoon->setScale(0.55f);
        comingSoon->setPosition({150, 80});
        this->addChild(comingSoon, 2);

        auto footer = CCLabelBMFont::create(
            "HACK AI v0.2", "bigFont.fnt"
        );
        footer->setColor(ccc3(0, 255, 80));
        footer->setScale(0.5f);
        footer->setPosition({150, 42});
        this->addChild(footer, 2);

        return true;
    }

    void onNoclip(CCObject*) {
        g_noclipEnabled = !g_noclipEnabled;

        m_noclipLabel->setString(
            g_noclipEnabled ? "NOCLIP: ON" : "NOCLIP: OFF"
        );
    }

public:
    static HackAIPopup* create() {
        auto ret = new HackAIPopup();

        if (ret && ret->init()) {
            ret->autorelease();
            return ret;
        }

        delete ret;
        return nullptr;
    }
};

class $modify(HackAIMenu, MenuLayer) {
    bool init() {
        if (!MenuLayer::init())
            return false;

        auto menu = this->getChildByID("bottom-menu");
        if (!menu)
            return true;

        auto label = CCLabelBMFont::create(
            "HACK AI", "bigFont.fnt"
        );
        label->setColor(ccc3(0, 255, 80));

        auto button = CCMenuItemSpriteExtra::create(
            label,
            this,
            menu_selector(HackAIMenu::onHackAI)
        );

        menu->addChild(button);
        button->setID("hack-ai-button"_spr);
        menu->updateLayout();

        return true;
    }

    void onHackAI(CCObject*) {
        HackAIPopup::create()->show();
    }
};

class $modify(HackAIPlayLayer, PlayLayer) {
    void destroyPlayer(PlayerObject* player, GameObject* object) {
        if (g_noclipEnabled)
            return;

        PlayLayer::destroyPlayer(player, object);
    }
};
