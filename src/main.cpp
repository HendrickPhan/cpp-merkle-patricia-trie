#include <iostream>
#include <vector>
#include "utils.h"
#include "short_node.h"
#include "encoding.h"

using namespace std;

void testEncodingFunc() {
  // Keccak256 and hex to string, string to hex test
  string testHexString = "ffff";
  vector<uint8_t> testBytes = hexStringToBytes(testHexString);
  vector<uint8_t> testOutput = keccak256(testBytes);
  string wantedHashRs = "06d41322d79dfed27126569cb9a80eb0967335bf2f3316359d2a93c779fcd38a";
  cout << "Hash result: " << bytesToHexString(testOutput) << ", valid: " << (bytesToHexString(testOutput) == wantedHashRs) << endl;
  
  // KeyBytesToHex, HexToKeyBytes test
  string strKeyBytes = "1111";
  string wantedHexBytes = "0101010110";
  vector<uint8_t> hexBytes = KeyBytesToHex(hexStringToBytes(strKeyBytes));
  vector<uint8_t> keyBytes = HexToKeyBytes(hexBytes);

  cout << "hex bytes: " << bytesToHexString(hexBytes) << ", valid: " << (bytesToHexString(hexBytes) == wantedHexBytes) << endl;
  cout << "key bytes: " << bytesToHexString(keyBytes) << ", valid: " << (bytesToHexString(keyBytes) == strKeyBytes) << endl;
  
  // Test prefix len
  int prefixLen = PrefixLen(hexStringToBytes("0101010203"), hexStringToBytes("0101010303"));
  cout << "key bytes" << ", valid: " << (prefixLen == 3) << endl;
}

int main() {
  testEncodingFunc();
  return 0;
}
