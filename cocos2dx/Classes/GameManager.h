//
//  GameManager.h
//  space-game-mobile
//
//  Created by Dzung on 14/03/2021.
//

#ifndef GameManager_h
#define GameManager_h

#include "cocos2d.h"
#include "EzyHeaders.h"

class GameManager {
private:
    std::map<int, cocos2d::Node*> mGameObjectById;
    std::map<cocos2d::Node*, cocos2d::Vec2> mGameObjectPositions;
private:
    EZY_SINGLETON_GET_INSTANCE(GameManager);
protected:
    EZY_SYNTHESIZE(long, GameId);
public:
    cocos2d::Node* getGameObject(int id);
    void getNewGameId();
    void finishGame();
    void startGame();
    void addGameObject(cocos2d::Node* gameObject);
    void syncGameObjectPositions();
    void syncScore(long score);
    void clear();
};

#endif /* GameManager_h */
