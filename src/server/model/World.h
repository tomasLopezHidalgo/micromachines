#ifndef TESTING_WORLD_H
#define TESTING_WORLD_H

#include "Box2D/Box2D.h"
#include <map>
#include <vector>
#include "Projectile.h"
#include "Grass.h"
#include "Car.h"
#include "HealthBooster.h"
#include "CollisionsProcessor.h"
#include "Stone.h"
#include "Oil.h"
#include "SpeedBooster.h"
#include "Track.h"
#include "Identifiers.h"
#include "Checkpoint.h"
#include "TimedEvent.h"
#include "Mud.h"

class World {
private:
    b2World* world;
    CollisionsProcessor collisionsProcessor;
    float height;
    float width;
    float timeStep;
    std::map<std::string, float> &config;
    std::vector<TimedEvent>& timedEvents;

    b2Body* addBody(b2Vec2 pos, bool dynamic, float angle = 0);

    b2Body* addBoxBody(b2Vec2 pos, b2Vec2 size, bool dynamic, bool sensor, float angle = 0);

    b2Body* addCircleBody(b2Vec2 pos, float radius, bool dynamic, bool sensor);

    b2Body* addFloorBody(b2Vec2 pos, b2Vec2 size);

    b2Body* createTireBody(b2Vec2 chassisPosition, b2Vec2 tirePos);

    b2RevoluteJoint* joinTireToChassis(b2RevoluteJointDef* jointDef,
            b2Body* tireBody, b2Vec2& pos);

public:
    World(float height, float width, std::map<std::string, float> &config, std::vector<TimedEvent>& timedEvents);

    World(World&& other);

    Car* addCar(std::string id, float x_pos, float y_pos);

    b2Body* getGrandstandBody(float x_pos, float y_pos, bool horizontalDisposal);

    Projectile* addProjectile(EntityIdentifier entityIdentifier, float x_pos, float y_pos, bool horizontalTrajectory);

    Checkpoint* addCheckpoint(float x_pos, float y_pos,
            bool horizontalDisposal, int checkpointOrder, RaceJudge& raceJudge);

    HealthBooster* addHealthBooster(float x_pos, float y_pos);

    Stone* addStone(float x_pos, float y_pos);

    SpeedBooster* addSpeedBooster(float x_pos, float y_pos);

    Oil* addOil(float x_pos, float y_pos);

    Mud* addMud(float x_pos, float y_pos);

    Track* addTrack(float x_pos, float y_pos, int floorId, float friction);

    Grass* addGrass(float x_pos, float y_pos, float friction);

    void step();

    ~World();
};

#endif //TESTING_WORLD_H
