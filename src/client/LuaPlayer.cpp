#include <unistd.h>
#include "LuaPlayer.h"

LuaPlayer::LuaPlayer(ProtectedQueue<Event> &q, ProtectedModel &model,
        std::string playerId, std::string scriptFile) :
    q(q),
    model(model),
    alive(true),
    script(playerId, scriptFile) {}

void LuaPlayer::run() {
    script.createMap(model.getMap());

    std::cout << "LOG - Corriendo lua player\n";

    SDL_Event e;
    while (alive) {

        if (SDL_PollEvent(&e)) {
            if (e.key.keysym.sym == SDLK_q)
                alive = false;
        }

        usleep(10000);
        script.setEntities(model.getEntitiesPos());
        std::vector<int> state = std::move(model.getActualState());
        Event e(std::move(script.getEvent(state[0], state[1], state[2])));
        q.push(std::move(e));
    }
}

void LuaPlayer::stop() {
    this->alive = false;
}
