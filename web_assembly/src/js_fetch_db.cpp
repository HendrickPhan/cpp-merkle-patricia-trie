#include "js_fetch_db.h"
#include "utils.h"
#include "logger.h"
#include <emscripten/emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>

using namespace std;

#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN
#endif

// Define a C++ function that will call JavaScript to fetch data
std::string JsFetchDB::get_data_from_js(std::string key) {
  currentGetKey = key;
  currentValue = "";

  void (*jsFetchFnc)() = reinterpret_cast<void (*)()>(fetchFncPtr);
  jsFetchFnc();
  while(1){
    if(currentValue != ""){
      break;
    }
    emscripten_sleep(10);
  }
  return currentValue;
}

// Constructor
JsFetchDB::JsFetchDB(int ptr) {
  fetchFncPtr = ptr;
}

// Destructor
JsFetchDB::~JsFetchDB() {
}

vector<uint8_t> JsFetchDB::Get(vector<uint8_t> key){
  string hexKey = bytesToHexString(key);
  string hexData = get_data_from_js(hexKey);
  Logger::Log("Got data from JS: " + hexData);
  return hexStringToBytes(hexData);
};


string JsFetchDB::GetCurrentGetKey(){
  return currentGetKey;
};

void JsFetchDB::SetCurrentGetValue(string value){
  currentValue = value;
};
