#ifndef MICROMACHINES_ENTITIESMANAGER_H
#define MICROMACHINES_ENTITIESMANAGER_H

#include "Entity.h"
#include "Projectile.h"
#include <unordered_map>
#include "World.h"

class EntitiesManager {
private:
    World& world;
    std::unordered_map<int, Projectile*> projectiles;
    std::unordered_map<int, Entity*> entities;
    int entitiesCounter;
public:
    EntitiesManager(World& stageWorld);

    void addProjectile(EntityIdentifier entityIdentifier,
            float x_pos, float y_pos, b2Vec2 force, bool horizontalTrajectory);

    void addEntity(EntityIdentifier entityIdentifier, float x_pos, float y_pos);

    void deleteEntity(int entityId);

    void deleteDeadEntities();

    void updateProjectilesStatus();

    void updateProjectilesFriction();

    std::unordered_map<int, Entity*>& getEntities();

    ~EntitiesManager();

};

#endif //MICROMACHINES_ENTITIESMANAGER_H
