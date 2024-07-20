#pragma once
#include "db.h"
#include <future>
#include <functional>

using namespace std;

class JsFetchDB: public DB {
public:
  
  string currentGetKey;
  string currentValue;
  bool valueSet = false;

  string GetCurrentGetKey();
  void SetCurrentGetValue(string value);

  JsFetchDB();

  ~JsFetchDB();
  vector<uint8_t> Get(vector<uint8_t> key);
  // may add string address later to know which address to fetch data
};

