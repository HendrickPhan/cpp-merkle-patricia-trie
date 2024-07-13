/*
 *   Copyright (c) 2024 hieuphanuit
 *   All rights reserved.
 */
#pragma once
#include<vector>

class DB {
public:
  virtual std::vector<uint8_t> Get(std::vector<uint8_t> key) = 0;
}; 

