#pragma once

#include "Modifier.h"


class WeaponAccuracyModifier : public Modifier
{
public:
    WeaponAccuracyModifier(float f) : factor(f) {};

    void apply(WeaponDescriptor& wd) override;
    std::string getDescription() const override;

private:
    float factor;
};


class FireRateModifier : public Modifier 
{
public:
    FireRateModifier(float f) : factor(f) {};

    void apply(WeaponDescriptor& wd) override;
    std::string getDescription() const override;

private:
    float factor;
};


class ClipSizeModifier : public Modifier
{
public:
    ClipSizeModifier(int b) : bonus(b) {};
    void apply(WeaponDescriptor& wd) override;
    std::string getDescription() const override;

private:
    int bonus;
};


class DamageModifier : public Modifier
{
public:
    DamageModifier(float f) : factor(f) {};
    void apply(WeaponDescriptor& wd) override;
    std::string getDescription() const override;

private:
    float factor;
};


class MuzzleVelocityModifier : public Modifier
{
public:
    MuzzleVelocityModifier(float f) : factor(f) {};
    void apply(WeaponDescriptor& wd) override;
    std::string getDescription() const override;

private:
    float factor;
};


class ReloadTimeModifier : public Modifier
{
public:
    ReloadTimeModifier(float f) : factor(f) {};
    void apply(WeaponDescriptor& wd) override;
    std::string getDescription() const override;

private:
    float factor;
};
