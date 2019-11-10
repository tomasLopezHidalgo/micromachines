//
// Created by eliana on 27/10/19.
//

#ifndef MICROMACHINES_DECREASESPEED_CPP
#define MICROMACHINES_DECREASESPEED_CPP

#include "entities/Car.h"
#include "World.h"
#include "Plugin.h"

#define NEWFORDWARDSPEED 70
#define SEVERAL_DAMAGED_POINTS 50

class DecreaseSpeed : public Plugin {
public:
    void updateModel(World* world, std::vector<Car*> cars) override;
};


#endif //MICROMACHINES_DECREASESPEED_CPP
