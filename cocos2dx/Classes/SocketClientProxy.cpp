//
//  SocketClientProxy.cpp
//  space-game-mobile
//
//  Created by Dzung on 14/03/2021.
//

#include "SocketClientProxy.h"

const auto GAME_NAME = "space-game";
const auto ZONE_NAME = "space-game";
const auto APP_NAME = "space-game";

class DisconnectionHandler : public handler::EzyDisconnectionHandler {
protected:
    bool shouldReconnect(event::EzyDisconnectionEvent* event) {
        return true;
    }
};
 
class HandshakeHandler : public handler::EzyHandshakeHandler {
protected:
    request::EzyRequest* getLoginRequest() {
        auto request = request::EzyLoginRequest::create();
        request->setZoneName(ZONE_NAME);
        request->setUsername(SocketClientProxy::getInstance()->getUsername());
        request->setPassword(SocketClientProxy::getInstance()->getUsername());
        return request;
    };
};
 
class LoginSuccessHandler : public handler::EzyLoginSuccessHandler {
protected:
    void handleLoginSuccess(entity::EzyValue* responseData) {
        mClient->udpConnect(2611);
    }
};
 
class UdpHandshakeHandler : public handler::EzyUdpHandshakeHandler {
protected:
    void onAuthenticated(entity::EzyArray *data) override {
        auto request = request::EzyAppAccessRequest::create();
        request->setAppName(APP_NAME);
        request->setData(new entity::EzyArray());
        mClient->send(request);
    }
};

class AppAccessHandler : public handler::EzyAppAccessHandler {
protected:
    void postHandle(entity::EzyApp* app, entity::EzyArray* data) {
        SocketClientProxy::getInstance()->emitAppAccessed();
    }
};
 
class StartGameResponseHandler : public handler::EzyAbstractAppDataHandler<entity::EzyValue> {
protected:
    void process(entity::EzyApp* app, entity::EzyValue* data) {
        logger::log("recived message: ");
#ifdef EZY_DEBUG
        data->printDebug();
#endif
    }
};

SocketClientProxy::SocketClientProxy() {
    auto config = config::EzyClientConfig::create();
    config->setClientName(ZONE_NAME);
    mSocketClient = EzyUTClient::create(config);
    EzyClients::getInstance()->addClient(mSocketClient);
    auto setup = mSocketClient->setup();
    setup->addEventHandler(event::ConnectionSuccess, new handler::EzyConnectionSuccessHandler());
    setup->addEventHandler(event::ConnectionFailure, new handler::EzyConnectionFailureHandler());
    setup->addEventHandler(event::Disconnection, new DisconnectionHandler());
    setup->addDataHandler(constant::Handshake, new HandshakeHandler());
    setup->addDataHandler(constant::Login, new LoginSuccessHandler());
    setup->addDataHandler(constant::LoginError, new handler::EzyLoginErrorHandler());
    setup->addDataHandler(constant::AppAccess, new AppAccessHandler());
    setup->addDataHandler(constant::UdpHandshake, new UdpHandshakeHandler());
    auto appSetup = setup->setupApp(APP_NAME);
    appSetup->addDataHandler("startGame", new StartGameResponseHandler());
    mAppAccessed = false;
}

void SocketClientProxy::setCredential(const std::string username,
                                      const std::string password) {
    this->mUsername = username;
    this->mPassword = password;
}

void SocketClientProxy::connectToServer() {
    mSocketClient->connect("127.0.0.1", 3005);
}

void SocketClientProxy::processEvents() {
    mSocketClient->processEvents();
}

bool SocketClientProxy::isConnected() {
    return mSocketClient->isConnected() && mSocketClient->isUdpConnected();
}

void SocketClientProxy::emitAppAccessed() {
    mAppAccessed = true;
    mAppAccessedCallback();
}

void SocketClientProxy::emitReconnect(const entity::EzyObject *data) {
    mReconnectCallback(data);
}

void SocketClientProxy::onAppAccessed(const callback0 &callback) {
    mAppAccessedCallback = callback;
}

void SocketClientProxy::onResponseReceived(const objectCallback &callback) {
    mReconnectCallback = callback;
}

void SocketClientProxy::syncPosition(const std::string objectName,
                                     int objectIndex,
                                     double x,
                                     double y) {
    if(!mAppAccessed) {
        return;
    }
    auto position = new entity::EzyObject();
    position->setDouble("x", x);
    position->setDouble("y", y);
    position->setDouble("z", 0);
    auto request = new entity::EzyObject();
    request->setString("gameName", GAME_NAME);
    request->setString("objectName", objectName);
    request->setInt("objectIndex", objectIndex);
    request->setObject("position", position);
    mSocketClient->getApp()->udpSend("syncPosition", request);
}
