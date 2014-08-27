//
//  Inside_EIS_Controller.cpp
//  UniLife
//
//  Created by csci321ga2a on 28/08/2014.
//
//

#include "Inside_EIS_Controller.h"
#include "ExtensionMacros.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::extension;


USING_NS_CC;

// create the buttons for the main menu
cocos2d::Vector<cocos2d::MenuItem*> Inside_EIS_Controller::CreateMenuButtons(Inside_EIS *that, Size visibleSize, Vec2 origin)
{
    
    // create the a vector to hold the menu items
    cocos2d::Vector<cocos2d::MenuItem*> pMenuItems;
    
    
    auto LowerEnergy = MenuItemImage::create("load_game_on.png", "load_game_off.png", CC_CALLBACK_1(Inside_EIS::MinusEnergy, that));
    LowerEnergy->setPosition(Vec2(origin.x + visibleSize.width / 2 - 200, visibleSize.height / 2));
    LowerEnergy->setScale(0.5,0.5);
    LowerEnergy->setAnchorPoint(Vec2(1,0));
    pMenuItems.pushBack(LowerEnergy);

    auto RaiseEnergy = MenuItemImage::create("new_game_on.png", "new_game_off.png", CC_CALLBACK_1(Inside_EIS::PlusEnergy, that));
    RaiseEnergy->setPosition(Vec2(origin.x + visibleSize.width / 2 + 200, visibleSize.height / 2));
    RaiseEnergy->setScale(0.5,0.5);
    RaiseEnergy->setAnchorPoint(Vec2(1,0));
    pMenuItems.pushBack(RaiseEnergy);


    
    return pMenuItems;
    
}

// call this method in the main menu scene to create the main menu
void Inside_EIS_Controller::CreateMainMenu(Inside_EIS *that, Size visibleSize, Vec2 origin)
{
    log("The New Game Menu Was Loaded");
    
    // create the a vector to hold the menu items
    cocos2d::Vector<cocos2d::MenuItem*> pMenuItems = CreateMenuButtons(that, visibleSize, origin);
    
    // create menu, it's an autorelease object
    auto menu = Menu::createWithArray(pMenuItems);
    menu->setPosition(Vec2::ZERO);
    that->addChild(menu, 1);
    
    // add "MenuScene" splash screen"
    auto sprite = Sprite::create("New-Game-background.png");
    
    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // add the sprite as a child to this layer
    that->addChild(sprite, 0);
    
    
    
    
    
    //Energy HUD
    cocos2d::ui::Text* engText = cocos2d::ui::Text::create("Energy ", "Verdana", 20);
    engText->setContentSize(Size(400, 40));
    engText->setPosition(Vec2(origin.x + visibleSize.width / 2 - 360, visibleSize.height / 2 + 310));
    engText->setColor(Color3B(0,0,0));
    that->addChild(engText, 1);
    
    Sprite* engSprite = Sprite::create("HUD_energy_bar.png");
    engSprite->setPosition(Vec2(origin.x + visibleSize.width / 2 - 400, origin.y + visibleSize.height / 2 + 300));
    ProgressTimer* pg = ProgressTimer::create(engSprite);
    engSprite->setScale(0.5 , 0.5);
    engSprite->setTag(1);
    pg->setBarChangeRate(Vec2(1, 0));
    pg->setMidpoint(Vec2(0, 1));
    that->addChild(engSprite);
    that->addChild(pg);
    
    
    //Stress HUD
    cocos2d::ui::Text* strText = cocos2d::ui::Text::create("Stress ", "Verdana", 20);
    strText->setContentSize(Size(400, 40));
    strText->setPosition(Vec2(origin.x + visibleSize.width / 2 - 360, visibleSize.height / 2 + 275));
    strText->setColor(Color3B(0,0,0));
    that->addChild(strText, 1);
    
    Sprite* streSprite = Sprite::create("HUD_stress_bar.png");
    streSprite->setPosition(Vec2(origin.x + visibleSize.width / 2 - 400, origin.y + visibleSize.height / 2 + 265));
    ProgressTimer* pg2 = ProgressTimer::create(streSprite);
    streSprite->setScale(0.5 , 0.5);
    streSprite->setTag(2);
    pg2->setBarChangeRate(Vec2(1, 0));
    pg2->setMidpoint(Vec2(0, 1));
    that->addChild(streSprite);
    that->addChild(pg2);
    
    
    
    
    
    
}

