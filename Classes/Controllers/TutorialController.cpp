//
//  TutorialController.cpp
//  UniLife
//
//  Created by csci321ga2a on 14/10/2014.
//
//

#include "TutorialController.h"
#include "MenuNewGameController.h"
#include "MenuNewGame.h"
#include "ExtensionMacros.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::extension;

USING_NS_CC;

// create the buttons for the main menu
cocos2d::Vector<cocos2d::MenuItem*> TutorialController::CreateMenuButtons(TutorialScene *that, Size visibleSize, Vec2 origin)
{
    
    // create the a vector to hold the menu items
    cocos2d::Vector<cocos2d::MenuItem*> pMenuItems;
    
    
    return pMenuItems;
    
}

// call this method in the main menu scene to create the main menu
void TutorialController::CreateMainMenu(TutorialScene *that, Size visibleSize, Vec2 origin)
{
    log("The Tutorial Was Loaded");
    
    // create the a vector to hold the menu items
    cocos2d::Vector<cocos2d::MenuItem*> pMenuItems = CreateMenuButtons(that, visibleSize, origin);
    
    // create menu, it's an autorelease object
    auto menu = Menu::createWithArray(pMenuItems);
    menu->setPosition(Vec2::ZERO);
    that->addChild(menu, 2);
    
    // add "MenuScene" splash screen"
    auto sprite = Sprite::create("New-Game-background.png");
    
    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    sprite->setName("mapBG");
    // add the sprite as a child to this layer
    that->addChild(sprite, 0);

    
    auto legoface = Sprite::create("legoDude.png");
    legoface->setPosition(Vec2(visibleSize.width/2 + origin.x - 425, visibleSize.height/2 + origin.y - 200));
    legoface->setScale(0.6);
    legoface->setName("legodude");
    that->addChild(legoface, 1);
    
    
    auto sBubble = Sprite::create("speech_big.png");
    sBubble->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y -100 ));
    sBubble->setScaleX(1.8);
    sBubble->setName("sBubble");
    that->addChild(sBubble, 1);

    
    auto introText = ui::Text::create("Welcome to The University Of Wollongong", "Arial", 30);
    introText->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y -50 ));
    introText->setColor(Color3B::BLACK);
    introText->setName("IntroText");
    that->addChild(introText, 2);
    
    
    auto otherText = ui::Text::create("Tap Screen To Continue", "Arial", 20);
    otherText->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y -150 ));
    otherText->setColor(Color3B::BLACK);
    otherText->setName("OtherText");
    that->addChild(otherText, 2);

    
    auto phoneButton = cocos2d::Sprite::create("phone_button.png");
    phoneButton->setPosition(cocos2d::Vec2(visibleSize.width * .90, visibleSize.height * .85));
    phoneButton->setName("phonebutton");
    phoneButton->setVisible(false);
    that->addChild(phoneButton,4);
    
    auto highlighter = Sprite::create();
    highlighter->setColor(Color3B::BLUE);
    highlighter->setOpacity(90);
    Rect newRect = Rect(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y, phoneButton->getContentSize().width + 25, phoneButton->getContentSize().height + 25);
    highlighter->setTextureRect(newRect);
    highlighter->setVisible(false);
    highlighter->setPosition(Vec2(cocos2d::Vec2(visibleSize.width * .90, visibleSize.height * .85)));
    highlighter->setName("highlighter");
    that->addChild(highlighter, 3);

    auto mapButton = cocos2d::Sprite::create("Map-marker.png");
    mapButton->setPosition(cocos2d::Vec2(visibleSize.width * .75, visibleSize.height * .85));
    mapButton->setScale(0.8);
    mapButton->setName("mapbutton");
    mapButton->setVisible(false);
    that->addChild(mapButton,4);
    
}


//Set code for going into faculty building
//GoToSciMed->addTouchEventListener(CC_CALLBACK_2(TutorialController::FacultyPressed, that));

void TutorialController::loadMap(TutorialScene *that, Size visibleSize, Vec2 origin, int buildingID, int whichone)
{
    Rect newRect;
    auto highlighter = (Sprite*)that->getChildByName("highlighter");
    auto action = RepeatForever::create(Sequence::create(Blink::create(10, 20),Blink::create(10, 20),nullptr));
    
    if(buildingID == 1){
        Vec2 newLoc = Vec2(origin.x + visibleSize.width / 2 -240, origin.y + visibleSize.height / 2 - 185);
        auto GoToArt = ui::Button::create("map-art.png");
        //GoToArt->addTouchEventListener(CC_CALLBACK_2(TutorialController::FacultyPressed, that));
        GoToArt->setPosition(newLoc);
        GoToArt->setScale(0.8);
        that->addChild(GoToArt,4);
        
        if(whichone == 1) {
            newRect = Rect(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y, GoToArt->getContentSize().width + 20, GoToArt->getContentSize().height + 20);
            highlighter->setTextureRect(newRect);
            highlighter->setVisible(true);
            highlighter->setScale(0.8);
            highlighter->setPosition(newLoc);
            highlighter->runAction(action);
        }
        
    }else if(buildingID == 2){
        Vec2 newLoc = Vec2(origin.x + visibleSize.width / 2 - 400, origin.y + visibleSize.height / 2 - 60);
        auto GoToSocSci = ui::Button::create("map-social_science.png");
        GoToSocSci->setPosition(newLoc);
        GoToSocSci->setScale(0.8);
        that->addChild(GoToSocSci,4);
        
        if(whichone == 2) {
            newRect = Rect(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y, GoToSocSci->getContentSize().width + 20, GoToSocSci->getContentSize().height + 20);
            highlighter->setTextureRect(newRect);
            highlighter->setVisible(true);
            highlighter->setScale(0.8);
            highlighter->setPosition(newLoc);
            highlighter->runAction(action);
        }
    }else if(buildingID == 3){
        Vec2 newLoc = Vec2(origin.x + visibleSize.width / 2 - 400, origin.y + visibleSize.height / 2 + 105);
        auto GoToBus = ui::Button::create("map-business.png");
        GoToBus->setPosition(newLoc);
        GoToBus->setScale(0.8);
        that->addChild(GoToBus,4);
        
        if(whichone == 3) {
            newRect = Rect(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y, GoToBus->getContentSize().width + 20, GoToBus->getContentSize().height + 20);
            highlighter->setTextureRect(newRect);
            highlighter->setVisible(true);
            highlighter->setScale(0.8);
            highlighter->setPosition(newLoc);
            highlighter->runAction(action);
        }
    }else if(buildingID == 4){
        Vec2 newLoc = Vec2(origin.x + visibleSize.width / 2 - 20, origin.y + visibleSize.height / 2 + 180);
        auto GoToSciMed = ui::Button::create("map-science_medicine.png");
        GoToSciMed->setPosition(newLoc);
        GoToSciMed->setScale(0.8);
        that->addChild(GoToSciMed,4);
        
        if(whichone == 4) {
            newRect = Rect(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y, GoToSciMed->getContentSize().width + 20, GoToSciMed->getContentSize().height + 20);
            highlighter->setTextureRect(newRect);
            highlighter->setVisible(true);
            highlighter->setScale(0.8);
            highlighter->setPosition(newLoc);
            highlighter->runAction(action);
        }
        
    }else if(buildingID == 5){
        Vec2 newLoc = Vec2(origin.x + visibleSize.width / 2 + 325, origin.y + visibleSize.height / 2 + 75);
        auto GoToEIS = ui::Button::create("map-computing_engineering.png");
        GoToEIS->setPosition(newLoc);
        GoToEIS->setScale(0.8);
        that->addChild(GoToEIS,4);
        
        if(whichone == 5) {
            newRect = Rect(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y, GoToEIS->getContentSize().width + 20, GoToEIS->getContentSize().height + 20);
            highlighter->setTextureRect(newRect);
            highlighter->setVisible(true);
            highlighter->setScale(0.8);
            highlighter->setPosition(newLoc);
            highlighter->runAction(action);
        }
        
    }else{
        log("Invalid Faculty");
    }
    
}

void TutorialController::FacultyPressed(cocos2d::Ref *pSender, ui::Widget::TouchEventType eEventType)
{
    log("faculty building pressed");
    //change sound effect for faculty press
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("dorm-door-opening.wav");
    log("you have touched the fac building!");
    
    // transition to the menu game scene test
    // need to change to specific faculty building player has selected
    auto scene = MenuScene::createScene();
    TransitionPageTurn *crosssfade = TransitionPageTurn::create(1,scene, true);
    Director::getInstance()->replaceScene(crosssfade);
    
}