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
    mGameObjectById = std::map<int, Node*>();
    mGameObjectPositions = std::map<Node*, Vec2>();
}

void GameManager::addGameObject(Node *gameObject) {
    mGameObjectById[gameObject->getTag()] = gameObject;
    mGameObjectPositions[gameObject] = Vec2::ZERO;
}

Node* GameManager::getGameObject(int id) {
    return mGameObjectById[id];
}

void GameManager::syncGameObjectPositions() {
    auto socketClientProxy = SocketClientProxy::getInstance();
    EZY_FOREACH_MAP(mGameObjectPositions) {
        auto obj = it->first;
        auto position = obj->getPosition();
        if(position != it->second) {
            it->second = position;
            socketClientProxy->syncPosition(mGameId,
                                            obj->getName(),
                                            obj->getTag(),
                                            obj->isVisible(),
                                            position.x,
                                            position.y);
        }
    }
}

void GameManager::clear() {
    mGameObjectById.clear();
    mGameObjectPositions.clear();
}
