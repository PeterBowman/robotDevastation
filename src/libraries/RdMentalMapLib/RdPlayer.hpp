// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __RD_PLAYER_HPP__
#define __RD_PLAYER_HPP__

#include <string>
#include <sstream>

namespace rd{

class RdPlayer
{
public:
    RdPlayer();
    RdPlayer( int id, std::string name, int health, int max_health, int team_id, int score);

    int getId() const;
    void setId(int value);

    std::string getName() const;
    void setName(const std::string &value);

    int getHealth() const;
    void setHealth(int value);

    int getMaxHealth() const;
    void setMaxHealth(int value);

    int getTeamId() const;
    void setTeamId(int value);

    int getScore() const;
    void setScore(int value);

    std::string str();

private:
    std::string name;
    int id;
    int health;
    int max_health;
    int team_id;
    int score;

};
}

#endif //__RD_PLAYER_HPP__
