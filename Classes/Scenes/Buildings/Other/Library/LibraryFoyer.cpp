//
//  Library-Foyer.cpp
//  UniLife
//
//  Created by csci321ga2a on 8/09/2014.
//
//

#include "LibraryFoyer.h"
#include "PlayerModel.h"
#include "SqlHelper.h"
#include "cocos2d.h"
#include "MenuOptionScene.h"
#include <CCTransition.h>
#include <string>
#include <vector>
#include "MapScene.h"
#include "LibraryRooms.h"
#include "LibraryFoyerController.h"
#include "HUDHelper.h"
#include "Movement.h"

USING_NS_CC;
extern PlayerModel pm;

Scene* LibraryFoyer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LibraryFoyer::create();
    layer->setName("libraryfoyer");
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    layer->setHUDScene(scene);
    
    // create the HUD
    HUDLayer::createHUD(scene);
    
    // load the sprite into the scene
    Movement::loadSpriteFrames(scene);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LibraryFoyer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    // get the size of the screen that is visible
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // create the main menu
    LibraryFoyerController::CreateMainMenu(this, visibleSize, origin);
    
    HUDLayer::resumeTimer();
    
    return true;
}

void LibraryFoyer::ToMap(Ref* pSender)
{
    HUDLayer::pauseTimer();
    
    auto scene = MapScene::createScene(pm);
    TransitionPageTurn *crosssfade = TransitionPageTurn::create(1,scene, true);
    Director::getInstance()->replaceScene(crosssfade);
    
}

void LibraryFoyer::ToMeetingRoom(Ref* pSender)
{
    HUDLayer::pauseTimer();
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("dorm-door-opening.wav");
    
    auto scene = LibraryRooms::createScene();
    TransitionPageTurn *crosssfade = TransitionPageTurn::create(1,scene, true);
    Director::getInstance()->replaceScene(crosssfade);
    
}

void LibraryFoyer::staffTouched(Ref* pSender)
{
    // get the character and staff positions
    auto character = this->getScene()->getChildByName<SpriteBatchNode*>("test")->getChildByName<Sprite*>("bill");
    auto staff = this->getScene()->getChildByName<LibraryFoyer*>("libraryfoyer")->getChildByName("menu")->getChildByName<cocos2d::Sprite*>("staff");
    
    float destination = staff->getPositionX();
    
    // get the character's sprite position
    float start = character->getPositionX();
    
    // move the character there
    Movement::moveCharacter(this->getScene(), start, destination);
    
}

