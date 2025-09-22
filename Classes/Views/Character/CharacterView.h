#pragma once

#include "Descriptors/CharacterDescriptor.h"
#include "Descriptors/WeaponDescriptor.h"
#include <string>


struct CharacterView
{
    std::string model;
    std::string texture;
    CharacterDescriptor characterDescriptor;
    WeaponDescriptor weaponDescriptor;
};
