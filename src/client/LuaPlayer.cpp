#include <unistd.h>
#include "LuaPlayer.h"

LuaPlayer::LuaPlayer(ProtectedQueue<Event> &q, ProtectedModel &model, std::string playerId) :
q(q),
model(model),
alive(true),
script(playerId) { }

void LuaPlayer::run() {

    script.createMap(model.getMap());

    while (alive) {
        usleep(2000);
        script.setEntities(model.getEntitiesPos());
        std::vector<int> state = std::move(model.getActualState());
        Event e(std::move(script.getEvent(state[0], state[1], state[2])));
        q.push(std::move(e));
    }
}

void LuaPlayer::stop() {
    this->alive = false;
}