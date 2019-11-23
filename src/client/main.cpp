#include "../common/Event.h"
#include "EventListener.h"
#include <iostream>
#include <zconf.h>
#include "ProtectedQueue.h"
#include "Camera.h"
#include <vector>
#include "Drawer.h"
#include "ProtectedModel.h"
#include "Receiver.h"
#include "Proxy.h"
#include "Dispatcher.h"
#include <nlohmann/json.hpp>
#include <QApplication>
#include "mainwindow.h"
#include "ffmpeg/Recorder.h"
#include "LuaPlayer.h"
#include "Audio.h"
#include "ffmpeg/RecorderHandle.h"

#define LUA_PLAYER "player.lua"
using json = nlohmann::json;

int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_EVERYTHING);
    Audio audio;
    Music ambient_music("../media/sounds/ambience_music.wav");
    ambient_music.play(-1);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    a.exec();

    Proxy* proxy = w.getProxy();

    if (!w.isValidUser()){
        SDL_Quit();
        a.quit();
        delete proxy;
        return 1;
    }

    Window *main = NULL;
    Thread *event_handler = NULL;

    try {

        if (w.isFullScreen())
            main = new Window("Micromachines");
        else
            main = new Window("Micromachines", w.getWidthSelected(), w.getHeightSelected());

        Camera cam(*main, main->createTextureFrom("../media/sprites/mud_screen_sprite.png"));
        ProtectedModel model(*main, cam, w.getPlayerID());
        ProtectedQueue<Event> q;
        ProtectedVector pv;
        av_register_all();

        std::string fileName = std::string(GAME_NAME) + std::string(".mp4");
        //Recorder recorder(main->getWidth(), main->getHeight(), pv, fileName);

        RecorderHandle recorderHandle(pv);
        
        Drawer drawer(*main, model, pv);
        Receiver receiver(model, *proxy);
        Dispatcher dispatcher(q, *proxy);

        if (w.isLuaPlayer())
            event_handler = new LuaPlayer(q, model, w.getPlayerID(), LUA_PLAYER);
        else
            event_handler = new EventListener(w.getPlayerID(), q);

        drawer.start();
        receiver.start();
        dispatcher.start();

        event_handler->run();
        
        //recorder.stop();
        drawer.stop();
        dispatcher.stop();
        receiver.stop();
 
    } catch(std::runtime_error &e) {
        // Avisar al server que catchee esta exception
        std::cout << "ocurrio una excepcion :( " << e.what() << std::endl;
        return 1;
    }

    delete event_handler;
    delete main;

    return 0;
}
