#pragma once

#include "Descriptors/CharacterDescriptor.h"
#include "Descriptors/WeaponDescriptor.h"
#include <string>
#include <cmath>

class Modifier 
{
public:
    virtual ~Modifier() = default;
    virtual void apply(CharacterDescriptor& cd) {};
    virtual void apply(WeaponDescriptor& wd) {};
    virtual std::string getDescription() const = 0;

protected:
    static bool almostEqual(float a, float b, float epsilon = 0.0001f)
    {
        return std::fabs(a - b) < epsilon;
    }
};
