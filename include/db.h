/*
 *   Copyright (c) 2024 hieuphanuit
 *   All rights reserved.
 */
#pragma once
using namespace std;

class DB {
public:
  virtual vector<uint8_t> Get(vector<uint8_t> key);
}; 

