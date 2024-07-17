#pragma once
#include "db.h"

using namespace std;

class JsFetchDB: public DB {
public:
  int fetchFncPtr;
  
  string currentGetKey;
  string currentGetValue;

  string get_data_from_js(string key);

  string GetCurrentGetKey();
  void SetCurrentGetValue(string value);

  JsFetchDB(int ptr);

  ~JsFetchDB();
  vector<uint8_t> Get(vector<uint8_t> key);
  // may add string address later to know which address to fetch data
};

