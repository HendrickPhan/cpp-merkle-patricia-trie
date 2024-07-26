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

// Constructor
JsFetchDB::JsFetchDB() {
}

// Destructor
JsFetchDB::~JsFetchDB() {
}


EM_ASYNC_JS(int, get_data_from_js, (), {
  await GLOBAL.GetTrieValue();
  return 1
});


// EM_ASYNC_JS(char*, getAccountStateCodeJs, (const char *address), {
//   // call API to get data
//   var rs = await GLOBAL.getAccountStateCodeJs(UTF8ToString(address));          
//   console.log("getAccountStateCodeJs", rs);
//   return stringToNewUTF8(rs);
// });

vector<uint8_t> JsFetchDB::Get(vector<uint8_t> key){
  string hexKey = bytesToHexString(key);
  currentGetKey = hexKey;
  valueSet = false;
  get_data_from_js();
  while(!valueSet){
    emscripten_sleep(10);
  }
  Logger::Log("Got data from JS: " + currentValue);
  return hexStringToBytes(currentValue);
};


string JsFetchDB::GetCurrentGetKey(){
  return currentGetKey;
};

void JsFetchDB::SetCurrentGetValue(string value){
  currentValue = value;
  valueSet = true;
};

