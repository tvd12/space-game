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
    bool shouldReconnect(event::EzyDisconnectionEvent* event) override {
        return true;
    }
    void postHandle(event::EzyDisconnectionEvent* event) override {
        SocketClientProxy::getInstance()->emitDisconnected();
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
    void postHandle(entity::EzyApp* app, entity::EzyArray* data) override {
        auto request = new entity::EzyObject();
        request->setString("gameName", GAME_NAME);
        app->send("reconnect", request);
    }
};
 
class ReconnectResponseHandler : public handler::EzyAbstractAppDataHandler<entity::EzyObject> {
protected:
    void process(entity::EzyApp* app, entity::EzyObject* data) override {
        SocketClientProxy::getInstance()->emitReconnected(data);
    }
};

class GetGameIdResponseHandler : public handler::EzyAbstractAppDataHandler<entity::EzyObject> {
protected:
    void process(entity::EzyApp* app, entity::EzyObject* data) override {
        SocketClientProxy::getInstance()->emitGameIdReceived(data);
    }
};

class StartGameResponseHandler : public handler::EzyAbstractAppDataHandler<entity::EzyObject> {
protected:
    void process(entity::EzyApp* app, entity::EzyObject* data) override {
        SocketClientProxy::getInstance()->emitStartGame(data);
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
    appSetup->addDataHandler("reconnect", new ReconnectResponseHandler());
    appSetup->addDataHandler("getGameId", new GetGameIdResponseHandler());
    appSetup->addDataHandler("startGame", new StartGameResponseHandler());
    mAppAccessed = false;
}

void SocketClientProxy::setCredential(const std::string username,
                                      const std::string password) {
    this->mUsername = username;
    this->mPassword = password;
}

void SocketClientProxy::connectToServer() {
    if(!isConnected()) {
        mSocketClient->connect("127.0.0.1", 3005);
    }
}

void SocketClientProxy::processEvents() {
    mSocketClient->processEvents();
}

bool SocketClientProxy::isConnected() {
    return mSocketClient->isConnected() && mSocketClient->isUdpConnected() && mAppAccessed;
}

void SocketClientProxy::emitReconnected(entity::EzyObject *data) {
    mAppAccessed = true;
    mReconnectedCallback(data);
}

void SocketClientProxy::onReconnected(const objectCallback &callback) {
    mReconnectedCallback = callback;
}

void SocketClientProxy::emitGameIdReceived(entity::EzyObject *data) {
    mGameIdReceivedCallback(data);
}

void SocketClientProxy::onGameIdReceived(const objectCallback &callback) {
    mGameIdReceivedCallback = callback;
}

void SocketClientProxy::emitStartGame(entity::EzyObject *data) {
    mStartGameCallback(data);
}

void SocketClientProxy::onStartGame(const objectCallback &callback) {
    mStartGameCallback = callback;
}

void SocketClientProxy::emitDisconnected() {
    mAppAccessed = false;
    mDisconnectedCallback();
}

void SocketClientProxy::onDisconnected(const callback0 &callback) {
    mDisconnectedCallback = callback;
}

void SocketClientProxy::getGameId() {
    auto request = new entity::EzyObject();
    request->setString("gameName", GAME_NAME);
    mSocketClient->getApp()->send("getGameId", request);
}

void SocketClientProxy::startGame(long gameId) {
    auto request = new entity::EzyObject();
    request->setString("gameName", GAME_NAME);
    request->setInt("gameId", gameId);
    mSocketClient->getApp()->send("startGame", request);
}

void SocketClientProxy::syncScore(long gameId, long score) {
    auto request = new entity::EzyObject();
    request->setString("gameName", GAME_NAME);
    request->setInt("gameId", gameId);
    request->setInt("score", score);
    mSocketClient->getApp()->send("updateScore", request);
}

void SocketClientProxy::syncPosition(long gameId,
                                     std::string objectName,
                                     int objectId,
                                     bool visible,
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
    request->setInt("gameId", gameId);
    request->setInt("objectId", objectId);
    request->setString("objectName", objectName);
    request->setBool("visible", visible);
    request->setObject("position", position);
    auto app = mSocketClient->getApp();
    if(app) {
        app->udpSend("syncPosition", request);
    }
}
