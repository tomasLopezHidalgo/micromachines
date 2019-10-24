#ifndef MICROMACHINES_DISPATCHER_H
#define MICROMACHINES_DISPATCHER_H

#include <../common/Action.h>
#include "../common/Thread.h"
#include "../common/Socket.h"
#include "../common/ProtectedQueue.h"

class Dispatcher: public Thread {
    private:
        ProtectedQueue<Action> actions;

    public:
        Dispatcher(ProtectedQueue<Action>& q);
        void start();


};
#endif
