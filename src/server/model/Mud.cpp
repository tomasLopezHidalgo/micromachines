#include "Mud.h"

Mud::Mud(b2Body *body, std::vector<TimedEvent> &timedEvents) :
    Entity(MUD, body),
    timedEvents(timedEvents),
    used(false) {}

void Mud::beginCollision(Entity* entity) {
    if (entity->getIdentifier() == CAR && !isDead() && !used) {
        Car* car = dynamic_cast<Car*>(entity);
        reduceVision(car);
    }
}

void Mud::reduceVision(Car* car) {
    used = true;
    car->reduceVision();
    timedEvents.emplace_back(TimedEvent(car, &Car::recoverTotalVision, 3));
    timedEvents.emplace_back(TimedEvent(this, &Entity::die, 0.5f));
}

void Mud::endCollision(Entity* entity) {}

Mud::~Mud() {}
