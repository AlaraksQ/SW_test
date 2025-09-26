#pragma once

#include "Modifier.h"
#include <memory>
#include <random>
#include <vector>


class ModifierFactory
{
public:
    static std::mt19937& rng();

    // multipliable is true for factors meant to be multiplied on stat.
    // multipliable is false for factors meant to be added to stat.
    static float GetRandomFactor(float min, float max, bool multipliable = true);

    static std::shared_ptr<Modifier> getRandomCharacterModifier();
    static std::shared_ptr<Modifier> getRandomWeaponModifier();

    static std::vector<std::shared_ptr<Modifier>> getUniqueCharacterModifiers(int count);
    static std::vector<std::shared_ptr<Modifier>> getUniqueWeaponModifiers(int count);
};
