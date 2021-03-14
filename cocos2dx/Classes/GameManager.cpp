//
//  GameManager.cpp
//  space-game-mobile
//
//  Created by Dzung on 14/03/2021.
//

#include "GameManager.h"
#include "SocketClientProxy.h"

using namespace cocos2d;

using namespace EZY_NAMESPACE;

GameManager::GameManager() {
    mGameObjects = std::map<Node*, Vec2>();
}

void GameManager::addGameObject(Node *gameObject) {
    mGameObjects[gameObject] = Vec2::ZERO;
}

void GameManager::syncGameObjectPositions() {
    auto socketClientProxy = SocketClientProxy::getInstance();
    EZY_FOREACH_MAP(mGameObjects) {
        auto obj = it->first;
        auto position = obj->getPosition();
        if(position != it->second) {
            it->second = position;
            socketClientProxy->syncPosition(obj->getName(),
                                            obj->getTag(),
                                            position.x,
                                            position.y);
        }
    }
}

void GameManager::clear() {
    mGameObjects.clear();
}
