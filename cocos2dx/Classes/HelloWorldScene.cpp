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

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "ParallaxNodeExtras.h"

using namespace cocos2d;
using namespace CocosDenshion;

Scene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    
    if ( !Layer::init() )
    {
        return false;
    }
    
    _batchNode = SpriteBatchNode::create("Sprites.pvr.ccz");
    this->addChild(_batchNode);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Sprites.plist");
    
    _ship = Sprite::createWithSpriteFrameName("SpaceFlier_sm_1.png");
    auto winSize = Director::getInstance()->getWinSize();
    _ship->setPosition(Vec2(winSize.width * 0.1, winSize.height * 0.5));
    _batchNode->addChild(_ship, 1);
    
    // 1) Create the ParallaxNode
    _backgroundNode = ParallaxNodeExtras::node();
    this->addChild(_backgroundNode, -1) ;
    
    // 2) Create the sprites will be added to the ParallaxNode
    _spacedust1 = Sprite::create("bg_front_spacedust.png");
    _spacedust2 = Sprite::create("bg_front_spacedust.png");
    _planetsunrise = Sprite::create("bg_planetsunrise.png");
    _galaxy = Sprite::create("bg_galaxy.png");
    _spacialanomaly = Sprite::create("bg_spacialanomaly.png");
    _spacialanomaly2 = Sprite::create("bg_spacialanomaly2.png");
    
    // 3) Determine relative movement speeds for space dust and background
    auto dustSpeed = Vec2(0.1, 0.1);
    auto bgSpeed = Vec2(0.05, 0.05);
    
    // 4) Add children to ParallaxNode
    _backgroundNode->addChild(_spacedust1, 0, dustSpeed , Vec2(0,winSize.height/2)); // 2
    _backgroundNode->addChild(_spacedust2, 0, dustSpeed , Vec2( _spacedust1->getContentSize().width,winSize.height/2));
    _backgroundNode->addChild(_galaxy, -1, bgSpeed, Vec2(0,winSize.height * 0.7));
    _backgroundNode->addChild(_planetsunrise, -1 , bgSpeed, Vec2(600, winSize.height * 0));
    _backgroundNode->addChild(_spacialanomaly, -1, bgSpeed, Vec2(900, winSize.height * 0.3));
    _backgroundNode->addChild(_spacialanomaly2, -1, bgSpeed, Vec2(1500, winSize.height * 0.9));
    
    this->scheduleUpdate();
    
    HelloWorld::addChild(ParticleSystemQuad::create("Stars1.plist"));
    HelloWorld::addChild(ParticleSystemQuad::create("Stars2.plist"));
    HelloWorld::addChild(ParticleSystemQuad::create("Stars3.plist"));
    
    Device::setAccelerometerEnabled(true);
    
#define KNUMASTEROIDS 15
    _asteroids = __Array::createWithCapacity(KNUMASTEROIDS);
    _asteroids->retain();
    for(int i = 0; i < KNUMASTEROIDS; ++i) {
        Sprite *asteroid = Sprite::createWithSpriteFrameName("asteroid.png");
        asteroid->setVisible(false);
        _batchNode->addChild(asteroid);
        _asteroids->addObject(asteroid);
    }
    
#define KNUMLASERS 5
    _shipLasers = __Array::createWithCapacity(KNUMLASERS);
    _shipLasers->retain();
    for(int i = 0; i < KNUMLASERS; ++i) {
        Sprite *shipLaser = Sprite::createWithSpriteFrameName("laserbeam_blue.png");
        shipLaser->setVisible(false);
        _batchNode->addChild(shipLaser);
        _shipLasers->addObject(shipLaser);
    }
    this->setTouchEnabled(true);
    
    _lives = 3;
    auto curTime = getTimeTick();
    _gameOverTime = curTime + 60000;
    
    SimpleAudioEngine::getInstance()->playBackgroundMusic("SpaceGame.wav",true);
    SimpleAudioEngine::getInstance()->preloadEffect("explosion_large.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("laser_ship.wav");
    
    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::update(float dt) {
    auto backgroundScrollVert = Vec2(-1000,0);
    _backgroundNode->setPosition(_backgroundNode->getPosition() + backgroundScrollVert * dt);
    
    auto spaceDusts = std::vector<Node*>(2);
    spaceDusts[0] = _spacedust1;
    spaceDusts[1] = _spacedust2;
    for (int ii = 0; ii <spaceDusts.size(); ii++) {
        auto spaceDust = (Sprite *)(spaceDusts[ii]);
        float xPosition = _backgroundNode->convertToWorldSpace(spaceDust->getPosition()).x ;
        float size = spaceDust->getContentSize().width;
        if ( xPosition < -size/2 ) {
            _backgroundNode->incrementOffset(Vec2(spaceDust->getContentSize().width * 2,0), spaceDust);
        }
    }
    
    auto backGrounds = std::vector<Node*>(4);
    backGrounds[0] = _galaxy;
    backGrounds[1] = _planetsunrise;
    backGrounds[2] = _spacialanomaly;
    backGrounds[3] = _spacialanomaly2;
    for (int ii = 0; ii < backGrounds.size(); ii++) {
        auto background = (Sprite *)(backGrounds[ii]);
        float xPosition = _backgroundNode->convertToWorldSpace(background->getPosition()).x;
        float size = background->getContentSize().width;
        if (xPosition < -size) {
            _backgroundNode->incrementOffset(Vec2(2000, 0), background);
        }
    }
    
    auto winSize = Director::getInstance()->getWinSize();
    auto maxY = winSize.height - _ship->getContentSize().height/2;
    auto minY = _ship->getContentSize().height/2;
    
    auto diff = (_shipPointsPerSecY * dt);
    auto newY = _ship->getPosition().y + diff;
    newY = MIN(MAX(newY, minY), maxY);
    _ship->setPosition(Vec2(_ship->getPosition().x, newY));
    
    auto curTimeMillis = getTimeTick();
    if(curTimeMillis > _nextAsteroidSpawn) {
        
        auto randMillisecs = randomValueBetween(0.20,1.0) * 1000;
        _nextAsteroidSpawn = randMillisecs + curTimeMillis;
        
        auto randY = randomValueBetween(0.0,winSize.height);
        auto randDuration = randomValueBetween(2.0,10.0);
        
        auto asteroid = (Sprite *)_asteroids->getObjectAtIndex(_nextAsteroid);
        _nextAsteroid++;
        
        if (_nextAsteroid >= _asteroids->count())
            _nextAsteroid = 0;
        
        asteroid->stopAllActions();
        asteroid->setPosition( Vec2(winSize.width+asteroid->getContentSize().width/2, randY));
        asteroid->setVisible(true);
        asteroid->runAction(Sequence::create(MoveBy::create(randDuration, Vec2(-winSize.width-asteroid->getContentSize().width, 0)), CallFuncN::create(CC_CALLBACK_1(HelloWorld::setInvisible, this)), NULL)); // DO NOT FORGET TO TERMINATE WITH NULL (unexpected in C++)
    }
    
    // Asteroids
    auto asteroid = (Ref*)NULL;
    auto shipLaser = (Ref*)NULL;
    CCARRAY_FOREACH(_asteroids, asteroid){
        if (!((Sprite *) asteroid)->isVisible() )
            continue;
        CCARRAY_FOREACH(_shipLasers, shipLaser){
            if (!((Sprite *) shipLaser)->isVisible())
                continue;
            if (((Sprite *) shipLaser)->getBoundingBox().intersectsRect(((Sprite *)asteroid)->getBoundingBox()) ) {
                SimpleAudioEngine::getInstance()->playEffect("explosion_large.wav");
                ((Sprite *)shipLaser)->setVisible(false);
                ((Sprite *)asteroid)->setVisible(false);
                continue;
            }
        }
        if (_ship->getBoundingBox().intersectsRect(((Sprite *)asteroid)->getBoundingBox()) ) {
            ((Sprite *)asteroid)->setVisible(false);
            _ship->runAction( Blink::create(1.0, 9));
            _lives--;
        }
    }
    
    if (_lives <= 0) {
        _ship->stopAllActions();
        _ship->setVisible(false);
        this->endScene(KENDREASONLOSE);
    } else if (curTimeMillis >= _gameOverTime) {
        this->endScene(KENDREASONWIN);
    }
}

void HelloWorld::onAcceleration(Acceleration* pAccelerationValue) {
#define KFILTERINGFACTOR 0.1
#define KRESTACCELX -0.6
#define KSHIPMAXPOINTSPERSEC (winSize.height*0.5)
#define KMAXDIFFX 0.2
    
    double rollingX;
    
    // Cocos2DX inverts X and Y accelerometer depending on device orientation
    // in landscape mode right x=-y and y=x !!! (Strange and confusing choice)
    pAccelerationValue->x = pAccelerationValue->y;
    rollingX = (pAccelerationValue->x * KFILTERINGFACTOR) + (rollingX * (1.0 - KFILTERINGFACTOR));
    auto accelX = pAccelerationValue->x - rollingX;
    auto winSize = Director::getInstance()->getWinSize();
    auto accelDiff = accelX - KRESTACCELX;
    auto accelFraction = accelDiff / KMAXDIFFX;
    _shipPointsPerSecY = KSHIPMAXPOINTSPERSEC * accelFraction;
}

float HelloWorld::randomValueBetween(float low, float high) {
    return (((float) arc4random() / 0xFFFFFFFFu) * (high - low)) + low;
}

double HelloWorld::getTimeTick() {
    timeval time;
    gettimeofday(&time, NULL);
    auto millisecs = (time.tv_sec * 1000) + (time.tv_usec/1000);
    return (float) millisecs;
}

void HelloWorld::setInvisible(Node * node) {
    node->setVisible(false);
}

void HelloWorld::setTouchEnabled(bool enabled) {
    _touchListener = EventListenerTouchAllAtOnce::create();
    _touchListener->onTouchesBegan = CC_CALLBACK_2(HelloWorld::onTouchesBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);
}

void HelloWorld::onTouchesBegan(const std::vector<Touch*>& touches, Event* event) {
    SimpleAudioEngine::getInstance()->playEffect("laser_ship.wav");
    
    auto winSize = Director::getInstance()->getWinSize();
    
    auto shipLaser = (Sprite *)_shipLasers->getObjectAtIndex(_nextShipLaser++);
    if ( _nextShipLaser >= _shipLasers->count() )
        _nextShipLaser = 0;
    shipLaser->setPosition(_ship->getPosition() + Vec2(shipLaser->getContentSize().width/2, 0));
    shipLaser->setVisible(true);
    shipLaser->stopAllActions();
    shipLaser->runAction(Sequence::create(MoveBy::create(0.5,Vec2(winSize.width, 0)), CallFuncN::create(CC_CALLBACK_1(HelloWorld::setInvisible, this)), NULL)); // DO NOT FORGET TO TERMINATE WITH NULL
    auto touchPosition = touches[0]->getLocation();
    auto newPosition = Vec2(_ship->getPosition().x, touchPosition.y);
    _ship->runAction(MoveTo::create(0.25, newPosition));
}

void HelloWorld::restartTapped() {
    Director::getInstance()->replaceScene
    (TransitionZoomFlipX::create(0.5, this->scene()));
    // reschedule
    this->scheduleUpdate();
}

void HelloWorld::endScene( EndReason endReason ) {
    if (_gameOver)
        return;
    _gameOver = true;
    
    auto winSize = Director::getInstance()->getWinSize();
    char message[10] = "You Win";
    if ( endReason == KENDREASONLOSE)
        strcpy(message,"You Lose");

    auto label = Label::createWithBMFont("Arial.fnt", message);
    label->setScale(0.1);
    label->setPosition(Vec2(winSize.width/2 , winSize.height*0.6));
    this->addChild(label);
    
    strcpy(message,"Restart");
    auto restartLabel = Label::createWithBMFont("Arial.fnt", message);
    auto restartItem = MenuItemLabel::create(restartLabel, CC_CALLBACK_0(HelloWorld::restartTapped, this));
    restartItem->setScale(0.1);
    restartItem->setPosition( Vec2(winSize.width/2, winSize.height*0.4));
    
    auto menu = Menu::create(restartItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    
    // clear label and menu
    restartItem->runAction(ScaleTo::create(0.5, 1.0));
    label ->runAction(ScaleTo::create(0.5, 1.0));
    // Terminate update callback
    this->unscheduleUpdate();
}
