/*
 *   Copyright (c) 2024 hieuphanuit
 *   All rights reserved.
 */
#pragma once
#include<vector>
#include<map>
#include "db.h"

using namespace std;

class MemoryDB: public DB{
  std::map<string, string> data;
public:
  MemoryDB(
    const vector<string>& keys, const vector<string>& values
  );
  std::vector<uint8_t> Get(std::vector<uint8_t> key);
}; 

