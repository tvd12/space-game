//
//  CustomParallaxNode.cpp
//  space-game-mobile
//
//  Created by Dung Ta Van on 3/9/21.
//

#include "CustomParallaxNode.h"

USING_NS_CC;

class CPointObject : public IPointObject
{
public:
    static CPointObject * create(Vec2 ratio, Vec2 offset)
    {
        CPointObject *ret = new (std::nothrow) CPointObject();
        ret->initWithPoint(ratio, offset);
        ret->autorelease();
        return ret;
    }
    
    bool initWithPoint(Vec2 ratio, Vec2 offset)
    {
        _ratio = ratio;
        _offset = offset;
        _child = nullptr;
        return true;
    }
    
    const Vec2& getRatio() const { return _ratio; }
    void setRatio(const Vec2& ratio) { _ratio = ratio; }
    
    const Vec2& getOffset() const { return _offset; }
    void setOffset(const Vec2& offset) override { _offset = offset; }
    
    Node* getChild() const override { return _child; }
    void setChild(Node* child) { _child = child; }
    
private:
    Vec2 _ratio;
    Vec2 _offset;
    Node *_child; // weak ref
};

CustomParallaxNode::CustomParallaxNode()
{
    _parallaxArray = ccArrayNew(5);
    _lastPosition.set(-100.0f, -100.0f);
}

CustomParallaxNode::~CustomParallaxNode()
{
    if( _parallaxArray )
    {
        ccArrayFree(_parallaxArray);
        _parallaxArray = nullptr;
    }
}

CustomParallaxNode* CustomParallaxNode::create()
{
    CustomParallaxNode *ret = new (std::nothrow) CustomParallaxNode();
    ret->autorelease();
    return ret;
}

void CustomParallaxNode::addChild(Node *child, int z, const Vec2& ratio, const Vec2& offset)
{
    CCASSERT( child != nullptr, "Argument must be non-nil");
    CPointObject *obj = CPointObject::create(ratio, offset);
    obj->setChild(child);
    ccArrayAppendObjectWithResize(_parallaxArray, (Ref*)obj);
    
    Vec2 pos = this->absolutePosition();
    pos.x = -pos.x + pos.x * ratio.x + offset.x;
    pos.y = -pos.y + pos.y * ratio.y + offset.y;
    child->setPosition(pos);
    
    Node::addChild(child, z, child->getName());
}

void CustomParallaxNode::removeChild(Node* child, bool cleanup)
{
    for( int i=0;i < _parallaxArray->num;i++)
    {
        CPointObject *point = (CPointObject*)_parallaxArray->arr[i];
        if (point->getChild() == child)
        {
            ccArrayRemoveObjectAtIndex(_parallaxArray, i, true);
            break;
        }
    }
    Node::removeChild(child, cleanup);
}

void CustomParallaxNode::removeAllChildrenWithCleanup(bool cleanup)
{
    ccArrayRemoveAllObjects(_parallaxArray);
    Node::removeAllChildrenWithCleanup(cleanup);
}

Vec2 CustomParallaxNode::absolutePosition()
{
    Vec2 ret = _position;
    Node *cn = this;
    while (cn->getParent() != nullptr)
    {
        cn = cn->getParent();
        ret = ret + cn->getPosition();
    }
    return ret;
}

/*
 The positions are updated at visit because:
 - using a timer is not guaranteed that it will called after all the positions were updated
 - overriding "draw" will only precise if the children have a z > 0
 */
void CustomParallaxNode::visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
    //    Vec2 pos = position_;
    //    Vec2    pos = [self convertToWorldSpace:Vec2::ZERO];
    Vec2 pos = this->absolutePosition();
    if( ! pos.equals(_lastPosition) )
    {
        for( int i=0; i < _parallaxArray->num; i++ )
        {
            CPointObject *point = (CPointObject*)_parallaxArray->arr[i];
            float x = -pos.x + pos.x * point->getRatio().x + point->getOffset().x;
            float y = -pos.y + pos.y * point->getRatio().y + point->getOffset().y;
            point->getChild()->setPosition(x,y);
        }
        _lastPosition = pos;
    }
    Node::visit(renderer, parentTransform, parentFlags);
}
