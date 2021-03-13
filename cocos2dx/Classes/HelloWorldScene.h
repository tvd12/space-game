/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class ParallaxNodeExtras;

typedef enum {
    KENDREASONWIN,
    KENDREASONLOSE
} EndReason;

class HelloWorld : public cocos2d::Layer {
private:
    cocos2d::SpriteBatchNode * _batchNode;
    cocos2d::Sprite * _ship;
    
    ParallaxNodeExtras *_backgroundNode;
    cocos2d::Sprite *_spacedust1;
    cocos2d::Sprite *_spacedust2;
    cocos2d::Sprite *_planetsunrise;
    cocos2d::Sprite *_galaxy;
    cocos2d::Sprite *_spacialanomaly;
    cocos2d::Sprite *_spacialanomaly2;
    
    cocos2d::EventListenerTouchAllAtOnce *_touchListener;
    
    float _shipPointsPerSecY;
    
    cocos2d::__Array* _asteroids;
    int _nextAsteroid;
    double _nextAsteroidSpawn;
    
    cocos2d::__Array* _shipLasers;
    int _nextShipLaser;
    
    int _lives;
    
    double _gameOverTime;
    bool _gameOver;
    
    // scheduled Update
    void update(float dt);
    
    void endScene(EndReason endReason);
    void restartTapped();
    
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::Scene* scene();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
    
    virtual void onAcceleration(cocos2d::Acceleration* pAccelerationValue);
    
    float randomValueBetween(float low, float high);
    void setInvisible(cocos2d::Node * node);
    double getTimeTick();
    
    virtual void setTouchEnabled(bool enable);
    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
};

#endif // __HELLOWORLD_SCENE_H__
