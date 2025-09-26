#pragma once

#include "Modifier.h"


class CharacterAccuracyModifier : public Modifier
{
public:
    CharacterAccuracyModifier(float f) : factor(f) {};
    void apply(CharacterDescriptor& cd) override;
    std::string getDescription() const override;

private:
    float factor;
};


class DexterityModifier : public Modifier
{
public:
    DexterityModifier(float f) : factor(f) {};
    void apply(CharacterDescriptor& cd) override;
    std::string getDescription() const override;

private:
    float factor;
};


class MaxHealthModifier : public Modifier 
{
public:
    MaxHealthModifier(float f) : amount(f) {};
    void apply(CharacterDescriptor& cd) override;
    std::string getDescription() const override;

private:
    float amount;
};


class MaxArmorModifier : public Modifier
{
public:
    MaxArmorModifier(float f) : amount(f) {};
    void apply(CharacterDescriptor& cd) override;
    std::string getDescription() const override;

private:
    float amount;
};


class AimTimeModifier : public Modifier
{
public:
    AimTimeModifier(float f) : factor(f) {};
    void apply(CharacterDescriptor& cd) override;
    std::string getDescription() const override;

private:
    float factor;
};
