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
std::string get_data_from_js(std::string address, std::string key) {
  char *str = (char*)EM_ASM_PTR({
    // this is sample js code to fetch data from a map
    // later can update it to get data from other sources
    var testDict = new Map([
      ["86afc4f91e36db7fe36feee987472f4ac8f0a354144f5e47984e2c35167ead67","12c2040a2000000000000000000000000000000000000000000000000000000000000000000a2000000000000000000000000000000000000000000000000000000000000000000a2000000000000000000000000000000000000000000000000000000000000000000a2000000000000000000000000000000000000000000000000000000000000000000a2000000000000000000000000000000000000000000000000000000000000000000a2000000000000000000000000000000000000000000000000000000000000000000a207a83a13dbf772fe7f98931ece18f07762ed0ad34304ebd877df60d8fde5de0090a2000000000000000000000000000000000000000000000000000000000000000000a2000000000000000000000000000000000000000000000000000000000000000000a2000000000000000000000000000000000000000000000000000000000000000000a2000000000000000000000000000000000000000000000000000000000000000000a2000000000000000000000000000000000000000000000000000000000000000000a2000000000000000000000000000000000000000000000000000000000000000000a2000000000000000000000000000000000000000000000000000000000000000000a2000000000000000000000000000000000000000000000000000000000000000000a20b801a4a522d1efe0f663e44b0c786877d03284be93688ac55be10f9cb5ace7330a200000000000000000000000000000000000000000000000000000000000000000"],
      ["9578d0afde64e5faedfbfbd27459315d037f14ca4eb7db11130171c4373eedc6","12c2040a2000000000000000000000000000000000000000000000000000000000000000000a2000000000000000000000000000000000000000000000000000000000000000000a2000000000000000000000000000000000000000000000000000000000000000000a2000000000000000000000000000000000000000000000000000000000000000000a2000000000000000000000000000000000000000000000000000000000000000000a2000000000000000000000000000000000000000000000000000000000000000000a2000000000000000000000000000000000000000000000000000000000000000000a2000000000000000000000000000000000000000000000000000000000000000000a2000000000000000000000000000000000000000000000000000000000000000000a2000000000000000000000000000000000000000000000000000000000000000000a2000000000000000000000000000000000000000000000000000000000000000000a204b13679b81b4ad513ccc587c32b5fa157a64e4062c9b81a2dadbc2b5600ac2850a2000000000000000000000000000000000000000000000000000000000000000000a2000000000000000000000000000000000000000000000000000000000000000000a2000000000000000000000000000000000000000000000000000000000000000000a202d8b584c66b60ae1c5e16328ec90724c27b7cd1852f6c168df88d0240af763a30a200000000000000000000000000000000000000000000000000000000000000000"],
      ["5798e775f80f1a24b84615383b78c3417934481a3e368a646d8fb6fd2e5b09d8","0801122a0a20306274471e2da8cd055691fab80001a5d2c592080ecd4deffd876239cbf68cb4120676616c756536"],
      ["5c0fcec323e68821800e4773299d5a6cca67ddd028e701d55ffbef9bf8c35a4d","12c2040a20519887d423d94a49bb29c72fdc3a0786b1d9781fdb6c5f8ec02c6c7930c931c40a2000000000000000000000000000000000000000000000000000000000000000000a2000000000000000000000000000000000000000000000000000000000000000000a2000000000000000000000000000000000000000000000000000000000000000000a200170b80009573e674c0502f0d4dbeaf4819414e0b52f87d38b89a4e87ad42a130a2086afc4f91e36db7fe36feee987472f4ac8f0a354144f5e47984e2c35167ead670a209578d0afde64e5faedfbfbd27459315d037f14ca4eb7db11130171c4373eedc60a2000000000000000000000000000000000000000000000000000000000000000000a2000000000000000000000000000000000000000000000000000000000000000000a205798e775f80f1a24b84615383b78c3417934481a3e368a646d8fb6fd2e5b09d80a2000000000000000000000000000000000000000000000000000000000000000000a205b6481613a87206eeb72b81c9c6c6b892558dfff45505b4cf70b2410bdbf927c0a20e651dfcb37db994feba3f011f4860c6f1871ceaf375eb4f27711cb184998557f0a203cfaf450ccd6b7786bb6f3596fa4e23801e15e0dcafed560a56d085afad019c70a2000000000000000000000000000000000000000000000000000000000000000000a2000000000000000000000000000000000000000000000000000000000000000000a200000000000000000000000000000000000000000000000000000000000000000"],
      ["7a83a13dbf772fe7f98931ece18f07762ed0ad34304ebd877df60d8fde5de009","0801122a0a202061f1fd0e3bcfda2dc423bced32c1a25e24581ed9c3440a946bb1cb0db24e07120676616c756537"],
      ["b801a4a522d1efe0f663e44b0c786877d03284be93688ac55be10f9cb5ace733","0801122a0a20201b94249f60809342da726cec530c7133a77dcbed72667722d5d994959bd275120676616c756532"],
      ["4b13679b81b4ad513ccc587c32b5fa157a64e4062c9b81a2dadbc2b5600ac285","0801122a0a2020f9df112a9e0c022482022d3ba5cc7e19ded8ea3a7307932d679b5a6aa68760120676616c756534"],
      ["2d8b584c66b60ae1c5e16328ec90724c27b7cd1852f6c168df88d0240af763a3","0801122a0a202068e18db5269b4325f851855066f0815eee031fc55c050e6e62cca3d1b3c574120676616c756538"],
      ["5b6481613a87206eeb72b81c9c6c6b892558dfff45505b4cf70b2410bdbf927c","0801122a0a2036c3c71e68c9c05bd409cd1810145107fcd5493a3f14871d4f6841f5bbee4f6f120676616c756530"],
      ["e651dfcb37db994feba3f011f4860c6f1871ceaf375eb4f27711cb184998557f","0801122a0a203775035f74a58828f4597f2e262e5afdb2ac70a26515d12ffda581858eba0322120676616c756533"],
      ["3cfaf450ccd6b7786bb6f3596fa4e23801e15e0dcafed560a56d085afad019c7","0801122a0a203ef5955cf732bfbbe31fa5cf40b44d249c6f5661087a95d843e67d939d0d014d120676616c756535"],
      ["519887d423d94a49bb29c72fdc3a0786b1d9781fdb6c5f8ec02c6c7930c931c4","0801122a0a203e42f327ee3cfa7ccfc084a0bb68d05eb627610303012a67afbf1ecd9b0d32fa120676616c756531"],
      ["0170b80009573e674c0502f0d4dbeaf4819414e0b52f87d38b89a4e87ad42a13","0801122a0a203a8dd1bcd84a59dd7e440bcaa3b3fadf511be78f661a70fdbbd82b23450fd7fe120676616c756539"]
    ]);
    var address = UTF8ToString($0);
    var jsString = testDict.get(address);
    var lengthBytes = lengthBytesUTF8(jsString)+1;
    return stringToNewUTF8(jsString);
    // return stringToNewUTF8("a");
  }, key.c_str());
  return string(str);
}

// Constructor
JsFetchDB::JsFetchDB(string _address) {
  address = _address;
}

// Destructor
JsFetchDB::~JsFetchDB() {
}

vector<uint8_t> JsFetchDB::Get(vector<uint8_t> key){
  string hexKey = bytesToHexString(key);
  string hexData = get_data_from_js(address, hexKey);
  Logger::Log("Got data from JS: " + hexData);
  return hexStringToBytes(hexData);
};
