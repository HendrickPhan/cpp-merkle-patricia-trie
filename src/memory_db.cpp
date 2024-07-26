#include "memory_db.h"
#include "utils.h"

using namespace std;

// Constructor
 MemoryDB::MemoryDB(const vector<string>& keys, const vector<string>& values) {
        for (size_t i = 0; i < keys.size(); i++) {
            if (i < values.size()) {
                data[keys[i]] = values[i];
            } else {
                data[keys[i]] = "";
            }
        }
    }

std::vector<uint8_t> MemoryDB::Get(std::vector<uint8_t> key) {
  string keyStr = bytesToHexString(key);
  string value = data[keyStr];
  return hexStringToBytes(value);
}

