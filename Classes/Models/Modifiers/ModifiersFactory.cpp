#include "ModifiersFactory.h"
#include "CharacterModifiers.h"
#include "WeaponModifiers.h"
#include <random>


std::mt19937& ModifierFactory::rng()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return gen;
}

float ModifierFactory::GetRandomFactor(float min, float max, bool multipliable)
{
    std::uniform_real_distribution<float> dist(min, max);
    float val = dist(rng());

    return multipliable ? (1.0f + val) : val;
}

std::shared_ptr<Modifier> ModifierFactory::getRandomCharacterModifier()
{
    std::uniform_int_distribution<int> dist(0, 4);
    switch (dist(rng()))
    {
    case 0: return std::make_shared<CharacterAccuracyModifier>(GetRandomFactor(-0.2f, 0.2f));
    case 1: return std::make_shared<DexterityModifier>(GetRandomFactor(0.2f, 0.4f));
    case 2: return std::make_shared<MaxHealthModifier>(GetRandomFactor(-20.0f, 20.0f, false));
    case 3: return std::make_shared<MaxArmorModifier>(GetRandomFactor(-10.0f, 10.0f, false));
    case 4: return std::make_shared<AimTimeModifier>(GetRandomFactor(-0.2f, 0.0f));
    }
    return nullptr;
}

std::shared_ptr<Modifier> ModifierFactory::getRandomWeaponModifier()
{
    std::uniform_int_distribution<int> dist(0, 5);
    switch (dist(rng()))
    {
    case 0: return std::make_shared<WeaponAccuracyModifier>(GetRandomFactor(-0.1f, 0.1f));
    case 1: return std::make_shared<FireRateModifier>(GetRandomFactor(0.0f, 0.2f));
    case 2: return std::make_shared<ClipSizeModifier>(3);
    case 3: return std::make_shared<MuzzleVelocityModifier>(GetRandomFactor(-0.15f, 0.15f));
    case 4: return std::make_shared<ReloadTimeModifier>(GetRandomFactor(-0.3f, 0.0f));
    case 5: return std::make_shared<DamageModifier>(GetRandomFactor(-0.2f, 0.2f));
    }
    return nullptr;
}

std::vector<std::shared_ptr<Modifier>> ModifierFactory::getUniqueCharacterModifiers(int count)
{
    std::vector<int> indices = { 0, 1, 2, 3, 4 };
    std::shuffle(indices.begin(), indices.end(), ModifierFactory::rng());
    std::vector<std::shared_ptr<Modifier>> result;
    for (int i = 0; i < count && i < indices.size(); ++i)
    {
        switch (indices[i])
        {
        case 0: result.push_back(std::make_shared<CharacterAccuracyModifier>(ModifierFactory::GetRandomFactor(-0.2f, 0.2f))); break;
        case 1: result.push_back(std::make_shared<DexterityModifier>(ModifierFactory::GetRandomFactor(0.2f, 0.4f))); break;
        case 2: result.push_back(std::make_shared<MaxHealthModifier>(ModifierFactory::GetRandomFactor(-20.0f, 20.0f, false))); break;
        case 3: result.push_back(std::make_shared<MaxArmorModifier>(ModifierFactory::GetRandomFactor(-15.0f, 15.0f, false))); break;
        case 4: result.push_back(std::make_shared<AimTimeModifier>(ModifierFactory::GetRandomFactor(-0.2f, 0.0f))); break;
        }
    }
    return result;
}

std::vector<std::shared_ptr<Modifier>> ModifierFactory::getUniqueWeaponModifiers(int count)
{
    std::vector<int> indices = { 0, 1, 2, 3, 4, 5 };
    std::shuffle(indices.begin(), indices.end(), rng());
    std::vector<std::shared_ptr<Modifier>> result;
    for (int i = 0; i < count && i < indices.size(); ++i)
    {
        switch (indices[i])
        {
        case 0: result.push_back(std::make_shared<WeaponAccuracyModifier>(GetRandomFactor(-0.1f, 0.1f))); break;
        case 1: result.push_back(std::make_shared<FireRateModifier>(GetRandomFactor(0.0f, 0.2f))); break;
        case 2: result.push_back(std::make_shared<ClipSizeModifier>(3)); break;
        case 3: result.push_back(std::make_shared<MuzzleVelocityModifier>(GetRandomFactor(-0.15f, 0.15f))); break;
        case 4: result.push_back(std::make_shared<ReloadTimeModifier>(GetRandomFactor(-0.3f, 0.0f))); break;
        case 5: result.push_back(std::make_shared<DamageModifier>(GetRandomFactor(-0.2f, 0.2f))); break;
        }
    }
    return result;
}
