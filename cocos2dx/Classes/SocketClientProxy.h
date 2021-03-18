//
//  SocketClientProxy.h
//  space-game-mobile
//
//  Created by Dzung on 14/03/2021.
//

#ifndef SocketClientProxy_h
#define SocketClientProxy_h

#include "EzyHeaders.h"

using namespace EZY_NAMESPACE;

typedef std::function<void(void)> callback0;
typedef std::function<void(entity::EzyObject*)> objectCallback;

class SocketClientProxy {
private:
    bool mAppAccessed;
    EzyClient* mSocketClient;
private:
    EZY_SINGLETON_GET_INSTANCE(SocketClientProxy);
protected:
    EZY_SYNTHESIZE_BOOL(FirstLogin);
    EZY_SYNTHESIZE_READONLY(std::string, Username);
    EZY_SYNTHESIZE_READONLY(std::string, Password);
    EZY_SYNTHESIZE_READONLY(objectCallback, ReconnectedCallback);
    EZY_SYNTHESIZE_READONLY(objectCallback, GameIdReceivedCallback);
    EZY_SYNTHESIZE_READONLY(objectCallback, StartGameCallback);
    EZY_SYNTHESIZE_READONLY(callback0, DisconnectedCallback);
public:
    void setCredential(const std::string username = "dungtv",
                       const std::string password = "123456");
    void connectToServer();
    void processEvents();
    bool isConnected();
public:
    void emitReconnected(entity::EzyObject* data);
    void onReconnected(const objectCallback& callback);
    
    void emitGameIdReceived(entity::EzyObject* data);
    void onGameIdReceived(const objectCallback& callback);
    
    void emitStartGame(entity::EzyObject* data);
    void onStartGame(const objectCallback& callback);
    
    void emitDisconnected();
    void onDisconnected(const callback0& callback);
public:
    void getGameId();
    void startGame(long gameId);
    void syncScore(long gameId, long score);
    void syncPosition(long gameId,
                      std::string objectName,
                      int objectIndex,
                      bool visible,
                      double x,
                      double y);
};

#endif /* SocketClientProxy_h */
