#include <zconf.h>
#include "Dispatcher.h"
#include "../common/Proxy.h"
#include "../common/Event.h"

Dispatcher::Dispatcher(ProtectedQueue<Event> &q, Proxy& proxy) :
    q(q), alive(true), proxy(proxy) {}

void Dispatcher::run() {
    while (alive) {
        Event action(std::move(q.pop()));
        std::string dumpedAction(std::move(action.serialize()));
       	if (dumpedAction.find("81") == std::string::npos){
			// Si entra acá es porque el msj es válido
			proxy.sendMessage(dumpedAction);
        }
        dumpedAction.clear();
    }
}

void Dispatcher::stop() {
    this->alive = false;
}
