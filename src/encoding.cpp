#include "encoding.h"
#include <iostream>
#include <vector>

using namespace std;

vector<uint8_t> HexToCompact(vector<uint8_t> input){

};

vector<uint8_t> CompactToHex(vector<uint8_t> compact){
  if(compact.size() == 0){
    cout << "Compact string must have at least one character" << endl;
    return null;
  }
  vector<uint8_t> hex(compact.size() * 2 + 1);


};

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
  if len(hex) % 2 == 1{
    cout << "Hex string must have an even number of characters" << endl;
    return null;
  }
  vector<uint8_t> key(hex.size() / 2);
  decodeNibbles(hex, key);
};

void decodeNibbles(vector<uint8_t> nibbles, vector<uint8_t> bytes){
  int bi = 0;
  for (int ni = 0; ni < nibbles.size(); i+=2){
    bytes[bi] = (nibbles[ni] << 4) | nibbles[ni + 1];
    bi++;
  }
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

