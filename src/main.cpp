#include <iostream>
#include <vector>
#include "utils.h"
#include "short_node.h"
#include "full_node.h"
#include "hash_node.h"
#include "encoding.h"
#include "hasher.h"
#include "trie.h"
#include "logger.h"
#include <emscripten/emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>

using namespace std;

void testEncodingFunc() {
  // Keccak256 and hex to string, string to hex test
  string testHexString = "ffff";
  vector<uint8_t> testBytes = hexStringToBytes(testHexString);
  vector<uint8_t> testOutput = keccak256(testBytes);
  string wantedHashRs = "06d41322d79dfed27126569cb9a80eb0967335bf2f3316359d2a93c779fcd38a";
  Logger::LogInfo("Hash result: " + bytesToHexString(testOutput) + ", valid: " + ((bytesToHexString(testOutput) == wantedHashRs) ? "true" : "false"));
  
  // KeyBytesToHex, HexToKeyBytes test
  string strKeyBytes = "1111";
  string wantedHexBytes = "0101010110";
  vector<uint8_t> hexBytes = KeyBytesToHex(hexStringToBytes(strKeyBytes));
  vector<uint8_t> keyBytes = HexToKeyBytes(hexBytes);

  Logger::LogInfo("hex bytes: " + bytesToHexString(hexBytes) + ", valid: " + ((bytesToHexString(hexBytes) == wantedHexBytes) ? "true" : "false"));
  Logger::LogInfo("key bytes: " + bytesToHexString(keyBytes) + ", valid: " + ((bytesToHexString(keyBytes) == strKeyBytes) ? "true" : "false"));
  // Test prefix len
  int prefixLen = PrefixLen(hexStringToBytes("0101010203"), hexStringToBytes("0101010303"));
  Logger::LogInfo("prefix len: " + to_string(prefixLen) + ", valid: " + ((prefixLen == 3) ? "true" : "false"));
  // Test hash with hasher
  HashNode* hn = (HashNode*)hashData(hexStringToBytes(strKeyBytes));
  Logger::LogInfo("hash node: " + bytesToHexString(hn->hash));
  
  // Test encoding
  FullNode fn = FullNode();
  Logger::LogInfo("empty full node data: " + bytesToHexString(fn.Marshal()));
  Logger::LogInfo("hash empty full node data: " + bytesToHexString(keccak256(fn.Marshal())));
}

void testTrie() {
  Trie trie = Trie();
  vector<uint8_t> rootHash = trie.Hash();
  Logger::LogInfo("Empty Root hash: " + bytesToHexString(rootHash));

  string key0 = "doe";
  string value0 = "reindeer";
  trie.Update(
    vector<uint8_t>(key0.begin(), key0.end()),
    vector<uint8_t>(value0.begin(), value0.end())
  );
  string root1 = bytesToHexString(trie.Hash());
  Logger::LogInfo("Root 1: " + root1);

  string key1 = "dog";
  string value1 = "puppy";
  trie.Update(
    vector<uint8_t>(key1.begin(), key1.end()),
    vector<uint8_t>(value1.begin(), value1.end())
  );
  string root2 =  bytesToHexString(trie.Hash());

  Logger::LogInfo("Root 2: " + root2);

  string key2 = "dogglesworth";
  string value2 = "cat";
  trie.Update(
    vector<uint8_t>(key2.begin(), key2.end()),
    vector<uint8_t>(value2.begin(), value2.end())
  );

  string root3 =  bytesToHexString(trie.Hash());
  Logger::LogInfo("Root 3: " + root3);

  vector<uint8_t> gettedValue= trie.Get(
    vector<uint8_t>(key1.begin(), key1.end())
  );
  string rs = string(gettedValue.begin(), gettedValue.end()); 
  Logger::LogInfo("Get value: " + rs);
  string wantedRoot = "f479ba810f41c9ec2845d3ab6c8e2f4f1802114dea7c4d499991ea600f99156a";
  Logger::LogInfo("Root 3: " + root3 + ", valid: " + ((root3 == wantedRoot) ? "true" : "false"));
}

void test10KInsertTrie() {
  Trie trie = Trie();
  for (int i = 0; i < 1000; i++) {
    string key = "key" + to_string(i);
    string value = "value" + to_string(i);
    trie.Update(
      vector<uint8_t>(key.begin(), key.end()),
      vector<uint8_t>(value.begin(), value.end())
    );
  }
  string root = bytesToHexString(trie.Hash());
  Logger::LogInfo(", root: " + root );
}

int main() {
  Logger::level = 1;
  // testEncodingFunc();
  // testTrie();
  test10KInsertTrie();
  return 0;
}

// Export the function so it can be called from JavaScript
extern "C" {

EMSCRIPTEN_BINDINGS(mpt_module){
  emscripten::function("main", &main);
}
}

