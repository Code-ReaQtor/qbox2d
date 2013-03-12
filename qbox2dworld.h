/*
Copyright (c) 2013, Ronie P. Martinez <ronmarti18@gmail.com>
All rights reserved.

Permission to use, copy, modify, and/or distribute this software for any purpose
with or without fee is hereby granted, provided that the above copyright notice
and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT,
OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA
OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#ifndef QBOX2DWORLD_H
#define QBOX2DWORLD_H

#include <QGraphicsScene>
#include <QTimerEvent>
#include <QGraphicsPolygonItem>
#include <QGraphicsEllipseItem>
#include <QHash>

#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/Joints/b2Joint.h>
#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include <Box2D/Collision/Shapes/b2Shape.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Collision/Shapes/b2EdgeShape.h>
#include <Box2D/Collision/Shapes/b2ChainShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/b2ContactManager.h>
#include "qbox2dcommon.h"


static float32 timeStep = 1.0f / 60.0f;
static int32 velocityIterations = 6;
static int32 positionIterations = 2;

class QBox2DWorld : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit QBox2DWorld(const b2Vec2 &gravity, QObject *parent = 0);
    ~QBox2DWorld() {
        delete q_b2World;
    }
    void start() {
        q_timerId = startTimer(timeStep*1000);
    }
    b2Body* createBody(const b2BodyDef *qb2BodyDef);
    void destroyBody(b2Body *qb2Body) {
        q_b2World->DestroyBody(qb2Body);
    }
    b2Joint* createJoint (const b2JointDef *def) {
        return q_b2World->CreateJoint(def);
    }
    void destroyJoint (b2Joint *joint) {
        q_b2World->DestroyJoint(joint);
    }
    b2Vec2 getGravity() {
        return q_b2World->GetGravity();
    }
    void setGravity(const b2Vec2 &qGravity) {
        q_b2World->SetGravity(qGravity);
    }
    bool isLocked() const {
        return q_b2World->IsLocked();
    }
    bool getAutoClearForces() const {
        return q_b2World->GetAutoClearForces();
    }
    void setAutoClearForces(bool flag) {
        q_b2World->SetAutoClearForces(flag);
    }
    void clearForces() {
        q_b2World->ClearForces();
    }
    void dump() {
        q_b2World->Dump();
    }
    QList<b2Body*> getBodyList();
    QList<b2Joint*> getJointList();
    QList<b2Contact*> getContactList();
    void setAllowSleeping(bool flag) {
        q_b2World->SetAllowSleeping(flag);
    }
    bool getAllowSleeping() const {
        return q_b2World->GetAllowSleeping();
    }
    void setWarmStarting(bool flag) {
        q_b2World->SetWarmStarting(flag);
    }
    bool getWarmStarting() const {
        return q_b2World->GetWarmStarting();
    }
    void setContinuousPhysics(bool flag) {
        q_b2World->SetContinuousPhysics(flag);
    }
    bool getContinuousPhysics() const {
        return q_b2World->GetContinuousPhysics();
    }
    void setSubStepping(bool flag) {
        q_b2World->SetSubStepping(flag);
    }
    bool getSubStepping() const {
        return q_b2World->GetSubStepping();
    }
    const b2ContactManager& getContactManager () const {
        return q_b2World->GetContactManager();
    }
    const b2Profile& getProfile () const {
        return q_b2World->GetProfile();
    }
    void setDestructionListener (b2DestructionListener *qListener) {
        q_b2World->SetDestructionListener(qListener);
    }
    void setContactFilter (b2ContactFilter *qFilter) {
        q_b2World->SetContactFilter(qFilter);
    }
    void setContactListener (b2ContactListener *qListener) {
        q_b2World->SetContactListener(qListener);
    }
    void setDebugDraw (b2Draw *qDebugDraw) {
        q_b2World->SetDebugDraw(qDebugDraw);
    }
    void drawDebugData() {
        q_b2World->DrawDebugData();
    }
    void queryAABB(b2QueryCallback *qCallback, const b2AABB &qAABB) const {
        q_b2World->QueryAABB(qCallback, qAABB);
    }
    void rayCast(b2RayCastCallback *qCallback, const b2Vec2 &qPoint1, const b2Vec2 &qPoint2) const {
        q_b2World->RayCast(qCallback, qPoint1, qPoint2);
    }
    int getProxyCount() const {
        return q_b2World->GetProxyCount();
    }
    int getBodyCount() const {
        return q_b2World->GetBodyCount();
    }
    int getJointCount() const {
        return q_b2World->GetJointCount();
    }
    int getContactCount() const {
        return q_b2World->GetContactCount();
    }
    int getTreeHeight() const {
        return q_b2World->GetTreeHeight();
    }
    int getTreeBalance() const {
        return q_b2World->GetTreeBalance();
    }
    float getTreeQuality() const {
        return q_b2World->GetTreeQuality();
    }

signals:

public slots:

protected:
    void timerEvent(QTimerEvent *event);

private:
    b2World *q_b2World;
    int q_timerId;
    QHash<b2Body*, QGraphicsItem*> bodyManager;
    
};

#endif // QBOX2DWORLD_H