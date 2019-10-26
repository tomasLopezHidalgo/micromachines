//
// Created by leobellaera on 15/10/19.
//

#ifndef MICROMACHINES_MATCH_H
#define MICROMACHINES_MATCH_H


#include <ProtectedQueue.h>
#include <atomic>
#include <map>
#include <string>
#include "Thread.h"
#include "Client.h"
#include "Car.h"
#include "World.h"

class Match : public Thread {
private:
    World world;
    std::atomic<bool> matchStarted;
    std::atomic<bool> matchFinished;
    ProtectedQueue<std::string> eventsQueue;
    std::map<std::string, Car*> cars;
    int playersAmount;
    int raceLaps;
public:
    Match(std::string& mapName, int playersAmount, int raceLaps, std::map<std::string, float> &config);
    void addPlayer(std::string nickname, Client* client);
    bool hasStarted();
    bool nicknameIsAvailable(std::string nickname);
    ProtectedQueue<std::string>& getEventsQueue();
    void run() override;
    void stop();
    ~Match();
};

#endif //MICROMACHINES_MATCH_H