/**
* \file TestHelpers.hpp
* \author Nicholas Ammann
* \date 3/10/2018
* \brief Helper functions for running tests.
*/

#pragma once

#include <iostream>
#include <thread>

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

inline void PrintTestHeader(const char* testName)
{
  std::cout << "*************************************" << std::endl;
  std::cout << "Test: " << testName << std::endl;
  std::cout << "*************************************" << std::endl;

  //std::this_thread::sleep_for(std::chrono::seconds(2));
}

inline void PrintTestFooter()
{
  std::cout << "/////////////////////////////////////" << std::endl;
  std::cout << std::endl;
}

inline void PrintVector(const glm::vec3& vector)
{
  std::cout << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
}

inline void PrintQuaternion(const glm::quat& quat)
{
  std::cout << "(" << quat.x << ", " << quat.y << ", " << quat.z << ", " << quat.w << ")";
}

