#pragma once

#include "Elba/Core/Component.hpp"

namespace Elba
{

struct Triangle
{
  float a;
  float b;
  float c;
  float d;
};

struct Trapezoid
{
  float p[4];
};

class Antecedent
{
public:
  Antecedent();

private:


};

class Consequence
{
public:
  Consequence();

private:


};

class FuzzyController : public Component
{
public:
  FuzzyController(Object* parent);

private:

};
}

