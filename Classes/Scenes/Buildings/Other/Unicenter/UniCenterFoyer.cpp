//
//  UniCenterFoyer.cpp
//  UniLife
//
//  Created by csci321ga2a on 8/09/2014.
//
//
#include "UniCenterFoyer.h"
#include "UniCenterGym.h"
#include "PlayerModel.h"
#include "SqlHelper.h"
#include "cocos2d.h"
#include <CCTransition.h>
#include <string>
#include <vector>
#include "MapScene.h"
#include "HUDHelper.h"
#include "Movement.h"

USING_NS_CC;
extern PlayerModel pm;

Scene* UniCenterFoyer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = UniCenterFoyer::create();
    
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
bool UniCenterFoyer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    HUDLayer::resumeTimer();
    
    // get the size of the screen that is visible
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // create the unicenter screen
    auto bg = Sprite::create("unicenter/uni_centre_foyer.png");
    bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    
    // create the a vector to hold the menu items
    cocos2d::Vector<cocos2d::MenuItem*> pMenuItems;
   
    auto ToMap = MenuItemImage::create("Map-marker.png","Map-marker.png" , CC_CALLBACK_1(UniCenterFoyer::toMap, this));
    ToMap->setPosition(Vec2(visibleSize.width * 0.8, visibleSize.height * 0.9 ));
    ToMap->setScale(0.85);
    pMenuItems.pushBack(ToMap);
    
    auto ToUniCentreGym = MenuItemImage::create("Go_Left_Arrow.png","Go_Left_Arrow.png" , CC_CALLBACK_1(UniCenterFoyer::ToGym, this));
    ToUniCentreGym->setPosition(Vec2(origin.x + visibleSize.width / 2 + 450 , origin.y + (visibleSize.height / 2 )));
    ToUniCentreGym->setScale(0.25);
    ToUniCentreGym->setRotation(180.0);
    pMenuItems.pushBack(ToUniCentreGym);
    
    // create menu, it's an autorelease object
    auto menu = Menu::createWithArray(pMenuItems);
    menu->setPosition(Vec2::ZERO);
    menu->setName("menu");
    this->addChild(menu, 1);
    
    this->addChild(bg);
    
    return true;
}

void UniCenterFoyer::ToGym(Ref* pSender)
{
    HUDLayer::pauseTimer();
    
    auto scene = UniCenterGym::createScene();
    TransitionPageTurn *crosssfade = TransitionPageTurn::create(1,scene, true);
    Director::getInstance()->replaceScene(crosssfade);
    
}

void UniCenterFoyer::toMap(cocos2d::Ref *pSender)
{
    HUDLayer::pauseTimer();
    
    auto scene = MapScene::createScene();
    TransitionCrossFade *crosssfade = TransitionCrossFade::create(.5,scene);
    Director::getInstance()->replaceScene(crosssfade);
}
