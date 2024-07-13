#pragma once
#include "db.h"

using namespace std;

class JsFetchDB: public DB {
public:
  string address;

  JsFetchDB(string _address);
  ~JsFetchDB();
  vector<uint8_t> Get(vector<uint8_t> key);
  // may add string address later to know which address to fetch data
};

