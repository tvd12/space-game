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

typedef std::function<void()> callback0;
typedef std::function<void(const entity::EzyObject*)> objectCallback;

class SocketClientProxy {
private:
    bool mAppAccessed;
    EzyClient* mSocketClient;
private:
    EZY_SINGLETON_GET_INSTANCE(SocketClientProxy);
protected:
    EZY_SYNTHESIZE_READONLY(std::string, Username);
    EZY_SYNTHESIZE_READONLY(std::string, Password);
    EZY_SYNTHESIZE_READONLY(callback0, AppAccessedCallback);
    EZY_SYNTHESIZE_READONLY(objectCallback, ReconnectCallback);
public:
    void setCredential(const std::string username = "dungtv",
                       const std::string password = "123456");
    void connectToServer();
    void processEvents();
    bool isConnected();
public:
    void emitAppAccessed();
    void emitReconnect(const entity::EzyObject* data);
    void onAppAccessed(const callback0& callback);
    void onResponseReceived(const objectCallback& callback);
public:
    void syncPosition(const std::string objectName, int objectIndex, double x, double y);
};

#endif /* SocketClientProxy_h */
