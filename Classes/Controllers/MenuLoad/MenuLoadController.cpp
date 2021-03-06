//
//  MenuLoadController.cpp
//  UniLife
//
//  Created by csci321ga2a on 8/12/14.
//
//

#include "MenuLoadController.h"
#include "MenuLoadScene.h"
#include "cocos2d.h"

USING_NS_CC;

// create the buttons for the main menu
cocos2d::Vector<cocos2d::MenuItem*> MenuLoadController::CreateMenuButtons(MenuLoadScene *that, Size visibleSize, Vec2 origin)
{
    
    // create the a vector to hold the menu items
    cocos2d::Vector<cocos2d::MenuItem*> pMenuItems;
    
    // create the back button
    auto backButton = MenuItemImage::create("options-back.png", "options-back.png", CC_CALLBACK_1(MenuLoadScene::backButtonCallback, that));
    backButton->setPosition(Vec2(origin.x + visibleSize.width / 2 - 500, visibleSize.height / 2 + 250));
    backButton->setName("BackButton");
    pMenuItems.pushBack(backButton);
    
    return pMenuItems;
    
}

// call this method in the main menu scene to create the main menu
void MenuLoadController::CreateMainMenu(MenuLoadScene *that, Size visibleSize, Vec2 origin)
{
    // create the a vector to hold the menu items
    cocos2d::Vector<cocos2d::MenuItem*> pMenuItems = CreateMenuButtons(that, visibleSize, origin);
    
    // create menu, it's an autorelease object
    auto menu = Menu::createWithArray(pMenuItems);
    menu->setPosition(Vec2::ZERO);
    that->addChild(menu, 1);
    
    // add "MenuScene" splash screen"
    auto sprite = Sprite::create("background.png");
    
    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // add the sprite as a child to this layer
    that->addChild(sprite, 0);
    
    auto label = Label::createWithSystemFont("Load Game", "Helvetica", 74);

    label->setPosition(Vec2(origin.x + visibleSize.width / 2, visibleSize.height / 2 + 250));
    
    label->setColor(Color3B(0, 0, 0));
    
    that->addChild(label, 0);
    
    
}