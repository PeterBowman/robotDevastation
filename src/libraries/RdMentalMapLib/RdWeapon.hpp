// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __RD_WEAPON_HPP__
#define __RD_WEAPON_HPP__

#include <string>
#include "RdUtils.hpp"
#include "RdTarget.hpp"
#include "RdPlayer.hpp"
#include "RdAudioManager.hpp"

namespace rd {

class RdWeapon
{
public:
    RdWeapon();
    RdWeapon(std::string name, int damage, int max_ammo);

    bool shoot(RdTarget& target);
    bool reload();

    std::string getName();
    int getDamage();
    int getCurrentAmmo();
    bool setCurrentAmmo(int current_ammo);
    int getMaxAmmo();

    static const int SCOPE_X;
    static const int SCOPE_Y;

private:


    std::string name;
    int damage;
    int current_ammo;
    int max_ammo;
};

}
#endif //__RD_WEAPON_HPP__