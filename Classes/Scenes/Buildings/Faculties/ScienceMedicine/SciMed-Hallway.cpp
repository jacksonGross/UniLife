//
//  SciMed-Hallway.cpp
//  UniLife
//
//  Created by csci321ga2a on 8/09/2014.
//
//

#include "SciMed-Hallway.h"
#include "SciMed-Foyer-Controller.h"
#include "PlayerModel.h"
#include "SqlHelper.h"
#include "cocos2d.h"
#include "SciMed-Hallway-Controller.h"
#include "MenuOptionScene.h"
#include <CCTransition.h>
#include <string>
#include <vector>
#include "MapScene.h"
#include "HUDHelper.h"
#include "Movement.h"
#include "EventScene.h"

USING_NS_CC;
extern PlayerModel pm;

Scene* SciMedHallway::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SciMedHallway::create();
    layer->setName("scimedhallway");
    
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
bool SciMedHallway::init()
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
    SciMedHallwayController::CreateMainMenu(this, visibleSize, origin);
    
    return true;
}

void SciMedHallway::ToFoyer(Ref* pSender)
{
    log("Going To SciMed Foyer!");
    
    auto scene = SciMedFoyer::createScene();
    TransitionPageTurn *crosssfade = TransitionPageTurn::create(1,scene, true);
    Director::getInstance()->replaceScene(crosssfade);
    
}


void SciMedHallway::ToLecture(Ref* pSender){
    log("Going To SciMed Lecture!");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("dorm-door-opening.wav");
    

    // get the character and door positions
    auto character = this->getScene()->getChildByName<SpriteBatchNode*>("test")->getChildByName<Sprite*>("bill");
    auto staff = this->getScene()->getChildByName<SciMedHallway*>("scimedhallway")->getChildByName("menu")->getChildByName<cocos2d::Sprite*>("lectdoor");
    
    float destination = staff->getPositionX();
    
    // get the character's sprite position
    float start = character->getPositionX();
    
    // move the character there
    auto moveCallback = CallFunc::create([this, start, destination](){
        Movement::moveCharacter(this->getScene(), start, destination);
    });
    
    // run the event screen
    auto eventCallback = CallFunc::create([](){
        
        auto event = EventScene::createScene("events/science_medicine_lecture.png");
        
        TransitionCrossFade *crossfade = TransitionCrossFade::create(0.5, event);
        Director::getInstance()->pushScene(crossfade);
    });
    
    this->runAction(Sequence::createWithTwoActions(moveCallback, eventCallback));
    
    // check whether the player is due for a lecture
    
    std::vector<timeTableClassModel> timetable = pm.getTimeTable();
    TimeModel tm = HUDLayer::getCurrentPlayer().getGameTime();
    
    std::vector<subjectBlockClassModel> classes = timetable[tm.getSemester() - 1].getClassQueue();
    
    float attendance = 0;
    
    for(int i = 0; i < classes.size(); i++)
    {
        
        double start = classes[i].getStartTime();
        
        if(start < 9)
        {
            start += 12.0;
        }
        
        double end = classes[i].getTotalTimeInt() + start;
        
        if(tm.getDay() == classes[i].getDay())
        {
            // calculate a buffer for attendance
            
            double bufferMin = start - 0.5;
            double bufferMax = start + 1;
            
            if(bufferMin == tm.getHoursMinutes() || start == tm.getHoursMinutes())
            {
                attendance = 1;
            }
            // if you enter the class after the start time and before the end
            else if(tm.getHoursMinutes() > bufferMax
                    && tm.getHoursMinutes() <= end)
            {
                attendance = 0.5;
            }
        }
    }
    
    if(attendance == 1)
    {
        HUDLayer::updateStats(0, 0, 0, -5, 10);
    }
    else if(attendance == 0.5)
    {
        HUDLayer::updateStats(0, 0, 0, -5, 15);
    }
    
    
}


void SciMedHallway::ToTutorial(Ref* pSender){
    log("Going To SciMed Tutorial!");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("dorm-door-opening.wav");

    // get the character and door positions
    auto character = this->getScene()->getChildByName<SpriteBatchNode*>("test")->getChildByName<Sprite*>("bill");
    auto staff = this->getScene()->getChildByName<SciMedHallway*>("scimedhallway")->getChildByName("menu")->getChildByName<cocos2d::Sprite*>("tutdoor");
    
    float destination = staff->getPositionX();
    
    // get the character's sprite position
    float start = character->getPositionX();
    
    // move the character there
    auto moveCallback = CallFunc::create([this, start, destination](){
        Movement::moveCharacter(this->getScene(), start, destination);
    });
    
    // run the event screen
    auto eventCallback = CallFunc::create([](){
        
        auto event = EventScene::createScene("events/science_medicine_tutorial.png");
        
        TransitionCrossFade *crossfade = TransitionCrossFade::create(0.5, event);
        Director::getInstance()->pushScene(crossfade);
    });
    
    this->runAction(Sequence::createWithTwoActions(moveCallback, eventCallback));
    
    // check whether the player is due for a tutorial
    
    std::vector<timeTableClassModel> timetable = pm.getTimeTable();
    TimeModel tm = HUDLayer::getCurrentPlayer().getGameTime();
    
    std::vector<subjectBlockClassModel> classes = timetable[tm.getSemester() - 1].getClassQueue();
    
    float attendance = 0;
    
    for(int i = 0; i < classes.size(); i++)
    {
        
        double start = classes[i].getStartTime();
        
        if(start < 9)
        {
            start += 12.0;
        }
        
        double end = classes[i].getTotalTimeInt() + start;
        
        if(tm.getDay() == classes[i].getDay())
        {
            // calculate a buffer for attendance
            
            double bufferMin = start - 0.5;
            double bufferMax = start + 1;
            
            if(bufferMin == tm.getHoursMinutes() || start == tm.getHoursMinutes())
            {
                attendance = 1;
            }
            // if you enter the class after the start time and before the end
            else if(tm.getHoursMinutes() > bufferMax
                    && tm.getHoursMinutes() <= end)
            {
                attendance = 0.5;
            }
        }
    }
    
    if(attendance == 1)
    {
        HUDLayer::updateStats(0, 0, 0, -5, 10);
    }
    else if(attendance == 0.5)
    {
        HUDLayer::updateStats(0, 0, 0, -5, 15);
    }
    
    
}


