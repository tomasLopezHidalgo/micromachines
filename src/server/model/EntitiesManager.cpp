#include "EntitiesManager.h"
#include "Constants.h"
#include "Mud.h"

EntitiesManager::EntitiesManager(World& stageWorld) :
    entitiesCounter(0),
    world(stageWorld) {}

void EntitiesManager::addProjectile(EntityIdentifier entityIdentifier,
        float x_pos, float y_pos, b2Vec2 force, bool horizontalTrajectory) {

    if (projectiles.size() >= MAX_PROJECTILES_NUMBER || entities.size() >= MAX_ENTITIES_NUMBER) {
        return;
    }

    Projectile* projectile = world.addProjectile(entityIdentifier, x_pos, y_pos, horizontalTrajectory);
    projectile->applyForce(force);

    projectiles.emplace(entitiesCounter, projectile);
    entities.emplace(entitiesCounter, projectile);
    entitiesCounter++;
}

void EntitiesManager::addEntity(EntityIdentifier entityIdentifier, float x_pos, float y_pos) {
    if (entityIdentifier == SPEEDBOOSTER) {
        SpeedBooster* speedBooster = world.addSpeedBooster(x_pos, y_pos);
        entities.emplace(entitiesCounter, speedBooster);

    } else if (entityIdentifier == HEALTHBOOSTER) {
        HealthBooster* healthBooster = world.addHealthBooster(x_pos, y_pos);
        entities.emplace(entitiesCounter, healthBooster);

    } else if (entityIdentifier == OIL) {
        Oil* oil = world.addOil(x_pos, y_pos);
        entities.emplace(entitiesCounter, oil);

    } else if (entityIdentifier == MUD) {
        Mud* mud = world.addMud(x_pos, y_pos);
        entities.emplace(entitiesCounter, mud);

    } else if (entityIdentifier == STONE) {
        Stone* stone = world.addStone(x_pos, y_pos);
        entities.emplace(entitiesCounter, stone);

    }

    entitiesCounter++;

}

void EntitiesManager::deleteEntity(int entityId) {
    entities.find(entityId)->second->die();
}

void EntitiesManager::deleteDeadEntities() {
    auto it = entities.begin();
    while (it != entities.end()) {
        if (it->second->isDead()) {
            delete it->second;
            it = entities.erase(it);
        } else {
            it++;
        }
    }
}

void EntitiesManager::updateProjectilesStatus() {
    auto it = projectiles.begin();

    while (it != projectiles.end()) {

        if (it->second->isStill()) {

            EntityIdentifier identifier = it->second->getIdentifier();
            b2Vec2 pos = it->second->getPosition();
            int projectileId = it->first;
            delete it->second;
            it = projectiles.erase(it);

            if (identifier == HEALTHBOOSTER) {
                HealthBooster* healthBooster = world.addHealthBooster(pos.x, pos.y);
                entities.find(projectileId)->second = healthBooster;

            } else if (identifier == STONE) {
                Stone* stone = world.addStone(pos.x, pos.y);
                entities.find(projectileId)->second = stone;

            } else if (identifier == OIL) {
                Oil* oil = world.addOil(pos.x, pos.y);
                entities.find(projectileId)->second = oil;

            } else if (identifier == SPEEDBOOSTER) {
                SpeedBooster* speedBooster = world.addSpeedBooster(pos.x, pos.y);
                entities.find(projectileId)->second = speedBooster;

            } else if (identifier == MUD) {
                Mud* mud = world.addMud(pos.x, pos.y);
                entities.find(projectileId)->second = mud;

            }

        } else {
            it++;
        }
    }
}

void EntitiesManager::updateProjectilesFriction() {
    auto it = projectiles.begin();
    while (it != projectiles.end()) {
        it->second->updateFriction();
        it++;
    }
}

std::unordered_map<int, Entity*>& EntitiesManager::getEntities() {
    return entities;
}

EntitiesManager::~EntitiesManager() {
    for (auto & entity : entities) {
        projectiles.erase(entity.first);
        delete (entity.second);
    }

    for (auto & projectile : projectiles) {
        delete (projectile.second);
    }
}
