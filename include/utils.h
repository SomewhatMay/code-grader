#pragma once

#include <iostream>

int _count_value = 0;
void debug_count() {
  std::cout << "Counter: " << _count_value << "\n";
  _count_value++;
}