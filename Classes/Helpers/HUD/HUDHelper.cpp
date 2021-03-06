//
//  HUDHelper.cpp
//  UniLife
//
//  Created by csci321ga2a on 22/09/2014.
//
//

#include "HUDHelper.h"
#include "DormScene.h"
#include "PauseMenu.h"
#include "PhoneLayer.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "PopUpLayer.h"
#include <ctime>

// SOME GLOBALS FOR AUTOSAVE
/////////////////////////////
time_t start;
int gametime;
bool firstTick;
PlayerModel player;
cocos2d::Scene* activeScene;
bool running = false;
std::vector<int> used;
////////////////////////////

// this method is used to create the HUD for each scene
void HUDLayer::createHUD(cocos2d::Scene* scene)
{
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    
    // set the active scene for the HUD
    activeScene = scene;
    
    cocos2d::ui::Text* engText = cocos2d::ui::Text::create("Energy ", "Verdana", 20);
    cocos2d::Sprite* engSprite = cocos2d::Sprite::create("HUD_energy_bar.png");
    cocos2d::ui::Text* streText = cocos2d::ui::Text::create("Stress ", "Verdana", 20);
    cocos2d::Sprite* streSprite = cocos2d::Sprite::create("HUD_stress_bar.png");
    cocos2d::ProgressTimer* pg = cocos2d::ProgressTimer::create(engSprite);
    cocos2d::ProgressTimer* pg2 = cocos2d::ProgressTimer::create(streSprite);
    // set up the timer
    cocos2d::Label* timer = cocos2d::Label::createWithSystemFont("", "Verdana", 64);
    timer->setPosition(cocos2d::Vec2(visibleSize.width * 0.52, visibleSize.height * 0.95));
    timer->setName("Timer");
    
    cocos2d::Vector<cocos2d::MenuItem*> pMenuItems;
    
    // animate the menu button to spin
    auto pauseButton = cocos2d::Sprite::create("cog-110.png");
    
    pauseButton->setPosition(cocos2d::Vec2(visibleSize.width * .95, visibleSize.height * .10));
    
    auto rotate = cocos2d::RotateBy::create(5.0f, 360);
    
    // run this forever so it keeps on spinning
    auto action = cocos2d::RepeatForever::create(rotate);
    
    pauseButton->runAction(action);
    
    auto pauseListener = cocos2d::EventListenerTouchOneByOne::create();

    pauseListener->setSwallowTouches(true);
    
    pauseListener->onTouchBegan = [](cocos2d::Touch* touch, cocos2d::Event* event){
        
        auto target = static_cast<cocos2d::Sprite*>(event->getCurrentTarget());
        
        //Get the position of the current point relative to the button
        cocos2d::Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        cocos2d::Size s = target->getContentSize();
        cocos2d::Rect rect = cocos2d::Rect(0, 0, s.width, s.height);
        
        //Check the click area
        if (rect.containsPoint(locationInNode))
        {
            // activate the pause overlay
            HUDLayer::PausedPressed(event->getCurrentTarget()->getScene());
            return true;
        }
        return false;
    };
    
    scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pauseListener, pauseButton);
    
    auto phoneButton = cocos2d::Sprite::create("phone_button.png");
    
    phoneButton->setPosition(cocos2d::Vec2(visibleSize.width * 0.95, visibleSize.height * .90));
    
    auto phoneListener = cocos2d::EventListenerTouchOneByOne::create();
    
    phoneListener->onTouchBegan = [](cocos2d::Touch* touch, cocos2d::Event* event){
        
        auto target = static_cast<cocos2d::Sprite*>(event->getCurrentTarget());
        
        //Get the position of the current point relative to the button
        cocos2d::Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        cocos2d::Size s = target->getContentSize();
        cocos2d::Rect rect = cocos2d::Rect(0, 0, s.width, s.height);
        
        //Check the click area
        if (rect.containsPoint(locationInNode))
        {
            // activate the pause overlay
            HUDLayer::PhonePressed(event->getCurrentTarget()->getScene());
            return true;
        }
        return false;
    };
    
    scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(phoneListener, phoneButton);
    
    engText->setContentSize(cocos2d::Size(400, 40));
    engText->setPosition(cocos2d::Vec2(visibleSize.width * 0.28, visibleSize.height * 0.96));
    engText->setColor(cocos2d::Color3B(255,255,255));
    
    engSprite->setPosition(cocos2d::Vec2(visibleSize.width * 0.1, visibleSize.height * 0.95));
    engSprite->setAnchorPoint(cocos2d::Vec2(0.f,0.5f));
    engSprite->setScale(0.5 , 0.5);
    engSprite->setName("EnergyHUD");
    
    streText->setContentSize(cocos2d::Size(400, 40));
    streText->setPosition(cocos2d::Vec2(visibleSize.width * 0.28, visibleSize.height * 0.91));
    streText->setColor(cocos2d::Color3B(255,255,255));
    
    streSprite->setPosition(cocos2d::Vec2(visibleSize.width * 0.1, visibleSize.height * 0.90));
    streSprite->setAnchorPoint(cocos2d::Vec2(0.f,0.5f));
    streSprite->setScale(0.5 , 0.5);
    streSprite->setName("StressHUD");
    
    pg->setBarChangeRate(cocos2d::Vec2(1, 0));
    pg->setAnchorPoint(cocos2d::Vec2(0.f,0.5f));
    pg->setTag(98);
    pg2->setTag(99);
    pg2->setBarChangeRate(cocos2d::Vec2(1, 0));
    pg2->setAnchorPoint(cocos2d::Vec2(0.f,0.5f));
    
    pg->setScaleX(player.getStats().getEnergy()/100.0);
    pg2->setScaleX(player.getStats().getStress()/100.0);
    pg->setPercentage(player.getStats().getEnergy()/100.0);
    pg2->setPercentage(player.getStats().getStress()/100.0);
    
    auto hudFace = cocos2d::Sprite::create("hud-pic.png");
    
    hudFace->setPosition(cocos2d::Vec2(visibleSize.width * 0.02, visibleSize.height * 0.90));

    activeScene->addChild(engText, 1);
    activeScene->addChild(engSprite);
    activeScene->addChild(pg);
    activeScene->addChild(streText, 1);
    activeScene->addChild(streSprite);
    activeScene->addChild(pg2);
    activeScene->addChild(pauseButton);
    activeScene->addChild(phoneButton);
    activeScene->addChild(timer);
    activeScene->addChild(hudFace);
    
    running = false;
    
    if(!running)
    {
        scene->schedule(schedule_selector(HUDLayer::updateGameTime),1.0f);
        running = true;
    }
    
    firstTick = false;
    
}

// this method is used to update the HUD bars
void HUDLayer::updateHUD(PlayerModel &pm)
{
    pm = player;
    
    auto pgTimer = (cocos2d::ProgressTimer*)activeScene->getChildByName("EnergyHUD");
    
    pgTimer->setScaleX(player.getStats().getEnergy()/100.0);
    pgTimer->setAnchorPoint(cocos2d::Vec2(0.f,0.5f));
    
    auto pgTimer2 = (cocos2d::ProgressTimer*)activeScene->getChildByName("StressHUD");
    
    pgTimer2->setScaleX(player.getStats().getStress()/100.0);
    pgTimer2->setAnchorPoint(cocos2d::Vec2(0.f,0.5f));
    
}

void HUDLayer::PausedPressed(cocos2d::Scene* scene)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("select.wav");
    
    cocos2d::Director::getInstance()->pause();
    cocos2d::log("Pausing the game");
    
    auto *p = PauseMenu::createScene();
    
    scene->addChild(p, 10);
}

void HUDLayer::PhonePressed(cocos2d::Scene* scene)
{
    cocos2d::log("Showing the Phone screen game");
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("select.wav");
    
    auto *p = PhoneLayer::createScene(player);
    
    scene->addChild(p, 10);
}

void HUDLayer::setPlayer(PlayerModel pm)
{
    player = pm;
    
    // start the timers for this player
    start = time(0);
    gametime = 0;
}

// update stats for a player
void HUDLayer::updateStats(int intelligence, int stamina, int social, int energy, int stress)
{
    PlayerStatsModel stats = player.getStats();
    
    // set the stat changes for each stat
    stats.setIntelligence(stats.getIntelligence() + intelligence);
    stats.setStamina(stats.getStamina() + stamina);
    stats.setSocial(stats.getSocial() + social);
    stats.setEnergy(stats.getEnergy() + energy);
    stats.setStress(stats.getStress() + stress);
    
    if(stats.getIntelligence() > 20)
    {
        stats.setIntelligence(20);
    }
    else if(stats.getIntelligence() < 0)
    {
        stats.setIntelligence(0);
    }
    
    if(stats.getStamina() > 20)
    {
        stats.setStamina(20);
    }
    else if(stats.getStamina() < 0)
    {
        stats.setStamina(0);
    }
    
    if(stats.getSocial() > 20)
    {
        stats.setSocial(20);
    }
    else if(stats.getSocial() < 0)
    {
        stats.setSocial(0);
    }
    
    if(stats.getEnergy() > 100)
    {
        stats.setEnergy(100);
    }
    else if(stats.getEnergy() < 0)
    {
        stats.setEnergy(0);
    }
    
    if(stats.getStress() > 100)
    {
        stats.setStress(100);
    }
    else if(stats.getStress() < 0)
    {
        stats.setStress(0);
    }
    
    // update the stats
    player.setStats(stats);
    
    // update the HUD bars
    HUDLayer::updateHUD(player);
    
}

PlayerModel HUDLayer::getCurrentPlayer()
{
    return player;
}

void HUDLayer::updateTime(double hoursminutes)
{
    TimeModel tm = player.getGameTime();
    tm.setHoursMinutes(tm.getHoursMinutes() + hoursminutes);
    
    player.setGameTime(tm);
}

void HUDLayer::updateGameTime(float t)
{
    double seconds_since_start = difftime( time(0), start);
    
    gametime = (int) seconds_since_start;
    
    // if the game has been played for 5 minute intervals
    if(gametime % 300 == 0)
    {
        cocos2d::log("TIME TO AUTOSAVE");
        cocos2d::log("Player: %d", player.getId());
        
        if(player.getId() > 0)
        {
            SqlHelper::autosave(player);
        }
        else
        {
            cocos2d::log("First time saving game!");
            SqlHelper::serialize(player);
        }
    }
    
    if(firstTick == false)
    {
        HUDLayer::updateTimer();
        firstTick = true;
    }

    // update the in-game time every 5 seconds
    if(gametime % 5 == 0)
    {
        HUDLayer::updateTimer();
    }
}

void HUDLayer::updateTimer()
{
    std::string ampm;
    std::ostringstream stringStream;
    
    TimeModel th = player.getGameTime();
    
    // set some local variables for manipulation
    double hour = th.getHoursMinutes() + 0.5;
    int day = th.getDay();
    int week = th.getWeek();
    int semester = th.getSemester();
    
    if( hour > 11.5) // roll over to afternoon
    {
        ampm = "pm";
    }
    else
    {
        ampm = "am";
    }
    
    if(hour > 23.5) // roll over to new day
    {
        hour = 0;
        ampm = "am";
        
        if(day ==  7) // roll over to new week
        {
            day = 1;
            
            if(week == 16) // roll over to new semester
            {
                week = 1;
                
                if(semester == 3) // game over
                {
                    cocos2d::log("...GAME OVER...");
                }
                
                else semester++;
            }
            
            else week++;
        }
        
        else day++;
    }
    
    stringStream << (int)hour << ":";
    
    if((hour + 0.5) == ceil(hour))
    {
        stringStream << "30" << ampm;
    }
    else
    {
        stringStream << "00" << ampm;
    }
    
    // update the timer with the new time
    auto timer = (cocos2d::Label*)activeScene->getChildByName("Timer");
    timer->setString(stringStream.str());
    
    // persist stat changes
    th.setHoursMinutes(hour);
    th.setDay(day);
    th.setWeek(week);
    th.setSemester(semester);
    
    // persist changes to player object
    player.setGameTime(th);
    
    //Added an update for the HUD Stress & Energy Bars
    HUDLayer::updateHUD(player);
    
    checkForEvents();
    
}

void HUDLayer::checkForEvents()
{
    TimeModel tm = player.getGameTime();
    
    // 1 to 7 days
    int day = rand() % 7 + 1;
    int currDay = tm.getDay();
    
    if(used.size() == 7)
    {
        for(int i = 0; i < used.size(); i++)
        {
            used.pop_back();
        }
    }
    else
    {
        for(int i = 0; i < used.size(); i++)
        {
            if(used[i] == day)
                return;
        }
    }
    
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    
    if(tm.getHoursMinutes() > 10)
    {
    
        switch (day)
        {
            case 1:
            {
                if(currDay == day)
                {
                    cocos2d::log("monday");
                    
                    used.push_back(1);
                    
                    cocos2d::Rect a = cocos2d::Rect(visibleSize.width / 2, visibleSize.height / 2 , 600, 300);
                    std::string msg = "Wanna play a game?";
                    
                    auto *p = PopUpLayer::createScene(a, msg, 1);
                    
                    Director::getInstance()->pause();
                    
                    activeScene->addChild(p, 10);
                }
                
                break;
            }
                
            case 2:
            {
                if(currDay == day)
                {
                    cocos2d::log("tuesday");
                    
                    used.push_back(2);
                    
                    cocos2d::Rect a = cocos2d::Rect(visibleSize.width / 2, visibleSize.height / 2 , 600, 300);
                    std::string msg = "Relieve some stress?";
                    
                    auto *p = PopUpLayer::createScene(a, msg, 2);
                    
                    Director::getInstance()->pause();
                    
                    activeScene->addChild(p, 10);
                }
                
                break;
            }
                
            case 3:
            {
                if(currDay == day)
                {
                    cocos2d::log("wednesday");
                    
                    used.push_back(3);
                    
                    cocos2d::Rect a = cocos2d::Rect(visibleSize.width / 2, visibleSize.height / 2 , 600, 300);
                    std::string msg = "Wanna study?";
                    
                    auto *p = PopUpLayer::createScene(a, msg, 3);
                    
                    Director::getInstance()->pause();
                    
                    activeScene->addChild(p, 10);
                    
                }
                
                break;
            }
                
            case 4:
            {
                if(currDay == day)
                {
                    cocos2d::log("thursday");
                    
                    used.push_back(4);
                    
                    cocos2d::Rect a = cocos2d::Rect(visibleSize.width / 2, visibleSize.height / 2 , 600, 300);
                    std::string msg = "Feeling tired?";
                    
                    auto *p = PopUpLayer::createScene(a, msg, 4);
                    
                    Director::getInstance()->pause();
                    
                    activeScene->addChild(p, 10);
                }
                
                break;
            }
                
            case 5:
            {
                if(currDay == day)
                {
                    cocos2d::log("friday");
                    
                    used.push_back(5);
                    
                    cocos2d::Rect a = cocos2d::Rect(visibleSize.width / 2, visibleSize.height / 2 , 600, 300);
                    std::string msg = "Seen your friends lately?";
                    
                    auto *p = PopUpLayer::createScene(a, msg, 5);
                    
                    Director::getInstance()->pause();
                    
                    activeScene->addChild(p, 10);
                }
                
                break;
            }
                
            case 6:
            {
                if(currDay == day)
                {
                    cocos2d::log("saturday");
                    
                    used.push_back(6);
                    
                    cocos2d::Rect a = cocos2d::Rect(visibleSize.width / 2, visibleSize.height / 2 , 600, 300);
                    std::string msg = "Have a drink?";
                    
                    auto *p = PopUpLayer::createScene(a, msg, 6);
                    
                    Director::getInstance()->pause();
                    
                    activeScene->addChild(p, 10);
                }
                
                break;
            }
                
            case 7:
            {
                if(currDay == day)
                {
                    cocos2d::log("sunday");
                    
                    used.push_back(7);
                    
                    cocos2d::Rect a = cocos2d::Rect(visibleSize.width / 2, visibleSize.height / 2 , 600, 300);
                    std::string msg = "Think you're smart?";
                    
                    auto *p = PopUpLayer::createScene(a, msg, 7);
                    
                    Director::getInstance()->pause();
                    
                    activeScene->addChild(p, 10);
                }
                
                break;
            }
                
        }
    }
    
}

void HUDLayer::pauseTimer()
{
    if(running)
    {
        activeScene->unschedule(schedule_selector(HUDLayer::updateGameTime));
        running = false;
    }
}

void HUDLayer::resumeTimer()
{
    if(!running && activeScene != NULL)
    {
        activeScene->schedule(schedule_selector(HUDLayer::updateGameTime),1.0f);
        running = true;
    }
}
                                              