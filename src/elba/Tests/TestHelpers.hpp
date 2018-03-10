#pragma once

#include <iostream>
#include <thread>

inline void PrintTestHeader(const char* testName)
{
  std::cout << "*************************************" << std::endl;
  std::cout << "Test: " << testName << std::endl;
  std::cout << "*************************************" << std::endl;

  std::this_thread::sleep_for(std::chrono::seconds(2));
}

inline void PrintTestFooter()
{
  std::cout << "/////////////////////////////////////" << std::endl;
  std::cout << std::endl;
}

