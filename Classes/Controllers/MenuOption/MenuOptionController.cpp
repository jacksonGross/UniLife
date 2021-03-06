//
//  MenuOptionController.cpp
//  UniLife
//
//  Created by csci321ga2a on 8/12/14.
//
//

#include "MenuOptionController.h"
#include "MenuScene.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace cocos2d::extension;

// create the buttons for the main menu
cocos2d::Vector<cocos2d::MenuItem*> MenuOptionController::CreateMenuButtons(MenuOptionScene *that, Size visibleSize, Vec2 origin)
{
    
    // create the a vector to hold the menu items
    cocos2d::Vector<cocos2d::MenuItem*> pMenuItems;
    
    // create the back button 
    auto backButton = MenuItemImage::create("options-back.png", "options-back.png", CC_CALLBACK_1(MenuOptionScene::backButtonCallback, that));
    
    backButton->setPosition(Vec2(origin.x + backButton->getContentSize().width, 490 + backButton->getContentSize().height));
    
    pMenuItems.pushBack(backButton);
    
    /*
    auto debugButton = MenuItemImage::create("speech_small.png", "speech_small.png", CC_CALLBACK_1(MenuOptionScene::debugButtonCallback, that));
       debugButton->setScale(0.75);
       debugButton->setPosition(Vec2(visibleSize.width / 2 + 365, visibleSize.height / 2 - 150));
    
        pMenuItems.pushBack(debugButton);
    */
    
    return pMenuItems;
    
}

// call this method in the main menu scene to create the main menu
void MenuOptionController::CreateMainMenu(MenuOptionScene *that, Size visibleSize, Vec2 origin)
{
    // create the a vector to hold the menu items
    cocos2d::Vector<cocos2d::MenuItem*> pMenuItems = CreateMenuButtons(that, visibleSize, origin);
    
    // create menu, it's an autorelease object
    auto menu = Menu::createWithArray(pMenuItems);
    menu->setPosition(Vec2::ZERO);
    that->addChild(menu, 1);
    
    // add "MenuScene" splash screen"
    auto sprite = Sprite::create("options-bg.png");
    
    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // add the sprite as a child to this layer
    that->addChild(sprite, 0);
    
    // add the title sprite to the menu
    sprite = Sprite::create("options-title.png");
    sprite->setPosition(Vec2(origin.x + visibleSize.width / 2, visibleSize.height / 2 + 250));
    
    that->addChild(sprite, 0);
    
    // add the border to the layer
    
    sprite = Sprite::create("options-border.png");
    sprite->setPosition(Vec2(origin.x + visibleSize.width / 2, visibleSize.height / 2 - 30));
    
    that->addChild(sprite, 0);
    
    cocos2d::ui::Text* backgroundLabel = cocos2d::ui::Text::create("Music", "Verdana", 30);
    backgroundLabel->setContentSize(Size(300, 50));
    backgroundLabel->setPosition(Vec2(origin.x + visibleSize.width / 2 - 270 , visibleSize.height / 2 + 120));
    backgroundLabel->setTextHorizontalAlignment(TextHAlignment::RIGHT);
    backgroundLabel->setColor(Color3B::BLACK);
    that->addChild(backgroundLabel, 2);
    
    cocos2d::ui::Slider* backgroundSlider = cocos2d::ui::Slider::create();
    backgroundSlider->loadBarTexture("sliderTrack2.png");
    backgroundSlider->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", "");
    backgroundSlider->loadProgressBarTexture("slider_bar_active_9patch.png");
    backgroundSlider->setScale9Enabled(true);
    backgroundSlider->setCapInsets(Rect(0, 0, 0, 0));
    backgroundSlider->setContentSize(Size(250.0f, 19));
    backgroundSlider->setPercent(100);
    backgroundSlider->setPosition(Vec2(origin.x + visibleSize.width / 2 - 20, origin.y + visibleSize.height / 2 + 110));
    backgroundSlider->setScale(2.0);
    backgroundSlider->addEventListener(CC_CALLBACK_2(MenuOptionScene::backgroundMusicSliderChange, that));
    backgroundSlider->setTag(2);
    that->addChild(backgroundSlider, 3);
    
    
    
    cocos2d::ui::Text* soundEffectLabel = cocos2d::ui::Text::create("Effects", "Verdana", 30);
    soundEffectLabel->setContentSize(Size(300, 50));
    soundEffectLabel->setPosition(Vec2(origin.x + visibleSize.width / 2 - 270 , visibleSize.height / 2 ));
    soundEffectLabel->setTextHorizontalAlignment(TextHAlignment::RIGHT);
    soundEffectLabel->setColor(Color3B::BLACK);
    that->addChild(soundEffectLabel, 2);
    
    cocos2d::ui::Slider* soundEffectSlider = cocos2d::ui::Slider::create();
    soundEffectSlider->loadBarTexture("sliderTrack2.png");
    soundEffectSlider->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", "");
    soundEffectSlider->loadProgressBarTexture("slider_bar_active_9patch.png");
    soundEffectSlider->setScale9Enabled(true);
    soundEffectSlider->setCapInsets(Rect(0, 0, 0, 0));
    soundEffectSlider->setContentSize(Size(250.0f, 19));
    soundEffectSlider->setPercent(100);
    soundEffectSlider->setPosition(Vec2(origin.x + visibleSize.width / 2 - 20, origin.y + visibleSize.height / 2 -10));
    soundEffectSlider->setScale(2.0);
    soundEffectSlider->addEventListener(CC_CALLBACK_2(MenuOptionScene::soundEffectsSliderChange, that));
    soundEffectSlider->setTag(3);
    that->addChild(soundEffectSlider, 3);
    
    
}