//
//  TavernFoyer.h
//  UniLife
//
//  Created by csci321ga2a on 1/09/2014.
//
//

#ifndef __UniLife__TavernFoyer__
#define __UniLife__TavernFoyer__

#include <iostream>
#include "PlayerModel.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

class TavernFoyer : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    void ToTavernRoom(Ref* pSender);
    void ToMap(Ref* pSender);
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(TavernFoyer);
    
    cocos2d::Scene* getHUDScene(){return this->HUDScene;};
    
    void setHUDScene(cocos2d::Scene* HUDScene){this->HUDScene = HUDScene;};
    void ShowSpeech(Ref *pSender);
    
private:
    cocos2d::Scene* HUDScene;
};

#endif /* defined(__UniLife__TavernFoyer__) */
