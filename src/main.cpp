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
        if (!Popup::init(320.f, 300.f))
            return false;

        auto bg = CCLayerColor::create(
            ccc4(0, 10, 4, 255), 280, 260
        );
        bg->setPosition({20, 20});
        this->addChild(bg);

        auto border = CCLayerColor::create(
            ccc4(0, 255, 80, 255), 280, 3
        );
        border->setPosition({20, 277});
        this->addChild(border);

        auto robot = CCLabelBMFont::create(
            "[ AI ROBOT ]", "bigFont.fnt"
        );
        robot->setColor(ccc3(0, 255, 80));
        robot->setScale(0.75f);
        robot->setPosition({160, 255});
        this->addChild(robot);

        auto title = CCLabelBMFont::create(
            "HACK AI CONTROL", "bigFont.fnt"
        );
        title->setColor(ccc3(0, 255, 80));
        title->setScale(0.55f);
        title->setPosition({160, 225});
        this->addChild(title);

        auto menu = CCMenu::create();
        menu->setPosition({0, 0});
        this->addChild(menu);

        m_noclipLabel = CCLabelBMFont::create(
            g_noclipEnabled ? "NOCLIP: ON" : "NOCLIP: OFF",
            "bigFont.fnt"
        );
        m_noclipLabel->setColor(ccc3(0, 255, 80));
        m_noclipLabel->setScale(0.55f);

        auto noclip = CCMenuItemSpriteExtra::create(
            m_noclipLabel,
            this,
            menu_selector(HackAIPopup::onNoclip)
        );
        noclip->setPosition({90, 190});
        menu->addChild(noclip);

        const char* features[] = {
            "AI SOLVER: SOON",
            "AUTO CLICK: SOON",
            "FLY: SOON",
            "MAP EDITOR: SOON",
            "MENU CUSTOMIZER: SOON",
            "ALWAYS DIE: SOON",
            "HITBOXES: SOON",
            "INSTANT COMPLETE: SOON"
        };

        float positions[][2] = {
            {230, 190},
            {90, 150},
            {230, 150},
            {90, 110},
            {230, 110},
            {90, 70},
            {230, 70},
            {160, 40}
        };

        for (int i = 0; i < 8; i++) {
            auto label = CCLabelBMFont::create(
                features[i], "bigFont.fnt"
            );
            label->setColor(ccc3(0, 190, 65));
            label->setScale(0.38f);
            label->setPosition({
                positions[i][0], positions[i][1]
            });
            this->addChild(label);
        }

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
            "[AI] HACK AI", "bigFont.fnt"
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
