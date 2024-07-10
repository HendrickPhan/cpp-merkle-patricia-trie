/*
 *   Copyright (c) 2024 hieuphanuit
 *   All rights reserved.
 */
#pragma once

#include<vector>
#include<tuple>
#include "trie_reader.h"
#include "db.h"

class TrieReader {
public:
  TrieReader(DB* _db);
  TrieReader(void);
  ~TrieReader(void);

  vector<uint8_t> node(vector<uint8_t> path, vector<uint8_t> hash);
  void setDB(DB* _db);
private:
  DB* db;
};

