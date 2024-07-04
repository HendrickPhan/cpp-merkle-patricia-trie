#include "encoding.h"
#include <iostream>
#include <vector>

using namespace std;

void decodeNibbles(vector<uint8_t> nibbles, vector<uint8_t>& bytes){
  int bi = 0;
  for (int ni = 0; ni < nibbles.size(); ni+=2){
    bytes[bi] = (nibbles[ni] << 4) | nibbles[ni + 1];
    bi++;
  }
};

vector<uint8_t> HexToCompact(vector<uint8_t> hex){
  uint8_t terminator = 0;
  if (HasTerm(hex)){
    terminator = 1;
    hex.pop_back();
  }
  vector<uint8_t> buf(hex.size() / 2 + 1); 
  buf[0] = terminator << 5;
  if ((hex.size()&1) == 1){
    buf[0] |= 1 << 4;
    buf[1] = hex[0];
  } 
  // create sub vector from buf[1] to the end
  vector<uint8_t> subvector(buf.begin() + 1, buf.end());
  decodeNibbles(hex, subvector);
  // copy the subvector to the buf
  copy(subvector.begin(), subvector.end(), buf.begin() + 1); 
  return buf;
};

vector<uint8_t> CompactToHex(vector<uint8_t> compact) {
    if (compact.size() == 0) {
        cout << "Compact string must have at least one character" << endl;
        return vector<uint8_t>(); // Return an empty vector instead of null
    }

    vector<uint8_t> base = KeyBytesToHex(compact);
    if (base[0] < 2) {
        base.pop_back(); // Removing the last element if the condition is met
    }

    int chop = 2 - (base[0] & 1);

    // Creating a subvector from base[chop] to the end
    vector<uint8_t> result(base.begin() + chop, base.end());
    return result;
}

vector<uint8_t> KeyBytesToHex(vector<uint8_t> input){
  int l = input.size() * 2+ 1;
  vector<uint8_t> nibbles(l);
  for (int i = 0; i < input.size(); i++){
    nibbles[i * 2] = input[i] >> 4;
    nibbles[i * 2 + 1] = input[i] & 0xf;
  }
  nibbles[l - 1] = 16;
  return nibbles;
};

vector<uint8_t> HexToKeyBytes(vector<uint8_t> hex){
  if(HasTerm(hex)){
    hex.pop_back();
  }
  if ((hex.size()&1) != 0){
    cout << "Hex string must have an even number of characters" << endl;
    return vector<uint8_t>();
  }
  vector<uint8_t> key(hex.size() / 2);
  decodeNibbles(hex, key);
  return key;
};


// prefixLen returns the length of the common prefix of a and b.
int PrefixLen(vector<uint8_t> a, vector<uint8_t> b){
  int i = 0;
  int length = a.size();
  if (b.size() < length){
    length = b.size();
  }
  while (i < a.size() && i < b.size() && a[i] == b[i]){
    i++;
  }
  return i;
};

bool HasTerm(vector<uint8_t> b){
  return b.size() > 0 && b[b.size() - 1] == 16;
};


