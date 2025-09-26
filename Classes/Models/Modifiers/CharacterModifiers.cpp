#include "CharacterModifiers.h"


// -- Accuracy --
void CharacterAccuracyModifier::apply(CharacterDescriptor& cd)
{
    cd.accuracy *= factor;
}

std::string CharacterAccuracyModifier::getDescription() const
{
    if (almostEqual(factor, 1.0f))
    {
        return "";
    }

    std::string prefix = factor > 1 ? "Character Accuracy boosted by " : "Character Accuracy decreased by ";
    return prefix + std::to_string(factor);
}


// -- Dexterity --
void DexterityModifier::apply(CharacterDescriptor& cd)
{
    cd.dexterity *= factor;
}

std::string DexterityModifier::getDescription() const
{
    if (almostEqual(factor, 1.0f))
    {
        return "";
    }

    std::string prefix = factor > 1 ? "Dexterity boosted by " : "Dexterity decreased by ";
    return prefix + std::to_string(factor);
}


// -- Max Health --
void MaxHealthModifier::apply(CharacterDescriptor& cd)
{
    cd.maxHealth += amount;
}

std::string MaxHealthModifier::getDescription() const
{
    std::string sign = amount > 0 ? "+" : "";
    return "Max Health " + sign + std::to_string(amount);
}


// -- Max Armor --
void MaxArmorModifier::apply(CharacterDescriptor& cd)
{
    cd.maxArmor += amount;
}

std::string MaxArmorModifier::getDescription() const
{
    std::string sign = amount > 0 ? "+" : "";
    return "Max Armor " + sign + std::to_string(amount);
}


// -- Aim Time --
void AimTimeModifier::apply(CharacterDescriptor& cd)
{
    cd.aimTime *= factor;
}

std::string AimTimeModifier::getDescription() const
{
    if (almostEqual(factor, 1.0f))
    {
        return "";
    }

    std::string prefix = factor < 1 ? "Aim Time reduced by " : "Aim Time increased by ";
    return prefix + std::to_string(factor);
}
