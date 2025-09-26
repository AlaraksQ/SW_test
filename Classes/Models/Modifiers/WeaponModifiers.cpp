#include "WeaponModifiers.h"


// -- Accuracy --
void WeaponAccuracyModifier::apply(WeaponDescriptor& wd)
{
    wd.accuracy *= factor;
}

std::string WeaponAccuracyModifier::getDescription() const
{
    if (almostEqual(factor, 1.0f))
    {
        return "";
    }

    std::string prefix = factor > 1 ? "Weapon Accuracy boosted by " : "Weapon Accuracy decreased by ";
    return prefix + std::to_string(factor);
}


// -- Fire Rate --
void FireRateModifier::apply(WeaponDescriptor& wd) 
{
    wd.fireRate *= factor;
}

std::string FireRateModifier::getDescription() const
{
    if (almostEqual(factor, 1.0f))
    {
        return "";
    }

    std::string prefix = factor > 1 ? "Fire Rate boosted by " : "Fire Rate decreased by ";
    return prefix + std::to_string(factor);
}


// -- Clip Size --
void ClipSizeModifier::apply(WeaponDescriptor& wd)
{
    wd.clipSize += bonus;
}

std::string ClipSizeModifier::getDescription() const
{
    if (bonus == 0)
    {
        return "";
    }

    std::string sign = bonus > 0 ? "+" : "";
    return "Clip Size + " + sign + std::to_string(bonus);
}


// -- Damage --
void DamageModifier::apply(WeaponDescriptor& wd)
{
    wd.damage *= factor;
}

std::string DamageModifier::getDescription() const
{
    if (almostEqual(factor, 1.0f))
    {
        return "";
    }

    std::string prefix = factor > 1 ? "Damage boosted by " : "Damage decreased by ";
    return prefix + std::to_string(factor);
}


// -- Muzzle Velocity --
void MuzzleVelocityModifier::apply(WeaponDescriptor& wd)
{
    wd.muzzleVelocity *= factor;
}

std::string MuzzleVelocityModifier::getDescription() const
{
    if (almostEqual(factor, 1.0f))
    {
        return "";
    }

    std::string prefix = factor < 1 ? "Muzzle Velocity boosted by " : "Muzzle Velocity increased by ";
    return prefix + std::to_string(factor);
}


// -- Reload Time --
void ReloadTimeModifier::apply(WeaponDescriptor& wd)
{
    wd.reloadTime *= factor;
}

std::string ReloadTimeModifier::getDescription() const
{
    if (almostEqual(factor, 1.0f))
    {
        return "";
    }

    std::string prefix = factor < 1 ? "Reload Time decreased by " : "Reload Time increased by ";
    return prefix + std::to_string(factor);
}
