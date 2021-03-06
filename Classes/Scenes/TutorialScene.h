//
//  TutorialScene.h
//  UniLife
//
//  Created by csci321ga2a on 14/10/2014.
//
//

#ifndef __UniLife__TutorialScene__
#define __UniLife__TutorialScene__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "PlayerModel.h"

using namespace cocos2d::extension;




class TutorialScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // overloaded createScene to pass in player
    static cocos2d::Scene* createScene(PlayerModel player);
    
    // overloaded create method to take player data
    static TutorialScene* create(PlayerModel player);
    
    // new game callback method
   
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    bool nextPage(cocos2d::Touch* touch, cocos2d::Event* event);
    bool nextPageOnMap(cocos2d::Touch* touch, cocos2d::Event* event);
    void compassPress(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    void buildingPress(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    void receptPress(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    void phonePress(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    void dormPress(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    // implement the "static create()" method manually
    CREATE_FUNC(TutorialScene);
    
    // set current player
    void setPlayer(PlayerModel player);
    
    PlayerModel getPlayer();
    
private:
    int whichpage = 0;
    int whichbuild = 0;
    bool lock = false;
    
    PlayerModel playerModel;
};





#endif /* defined(__UniLife__TutorialScene__) */
