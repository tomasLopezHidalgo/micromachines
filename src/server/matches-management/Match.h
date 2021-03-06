#ifndef MICROMACHINES_MATCH_H
#define MICROMACHINES_MATCH_H

#include "ProtectedQueue.h"
#include "Event.h"
#include <atomic>
#include <unordered_map>
#include <string>
#include <nlohmann/json.hpp>
#include <StageBuilder.h>
#include "Thread.h"
#include "Client.h"
#include "../model/Car.h"
#include "World.h"
#include "RaceManager.h"

class Match : public Thread {
private:
    
    RaceManager raceManager;
    std::atomic<bool> dead;
    std::atomic<bool> matchStarted;
    std::string mapName;
    int playersAmount;
    int raceLaps;
    long timeStep;
    ProtectedQueue<Event> eventsQueue;
    std::unordered_map<std::string, Client*> clients;
    
    void sendMatchDataToClients();
    void startCountdown();
    void startClientsThread();
    void sendMessageToClients(std::string& message);
    
public:
    
    Match(std::string& mapName, int playersAmount,
            int raceLaps, std::map<std::string, float> &config);
    
    void showIfAvailable(nlohmann::json& availableMatches, std::string& matchName);
    
    void addClient(std::string nickname, Client* client);
    
    bool hasStarted();
    
    bool finished();
    
    bool nicknameIsAvailable(std::string& nickname);
    
    ProtectedQueue<Event>& getEventsQueue();
    
    void run() override;
    
    void stop();
    
    ~Match();

};

#endif //MICROMACHINES_MATCH_H
