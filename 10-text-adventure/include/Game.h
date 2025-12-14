#pragma once
#include "Player.h"
#include "Room.h"
#include <vector>

class Game
{
private:
    Player player;
    std::vector<Room> rooms;
    int currentRoomIndex;

public:
    Game(const std::string &playerName);
    void run();
};