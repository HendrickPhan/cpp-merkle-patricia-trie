#include "short_node.h"
#include "value_node.h"
#include "hash_node.h"
#include "merkle_patricia_trie.pb.h"
#include <iostream>
#include "encoding.h"
#include "logger.h"
#include "utils.h"

using namespace std;

// Constructor
ShortNode::ShortNode() {
  
}

ShortNode::ShortNode(vector<uint8_t> key, Node* value, NodeFlag flag) {
  this->key = key;
  this->value = value;
  this->flag = flag;
}
// Destructor
ShortNode::~ShortNode() {
}

void ShortNode::Unmarshal(vector<uint8_t> hash, vector<uint8_t> data) {
//
  merkle_patricia_trie::MPTShortNode proto;
  // convert data to 
  proto.ParseFromString(string(data.begin(), data.end()));
  key = CompactToHex(vector<uint8_t>(proto.key().begin(), proto.key().end()));
  if (HasTerm(key)) {
    Logger::LogDebug("ShortNode::Unmarshal key has term: " + bytesToHexString(key));
    this->value = new ValueNode(vector<uint8_t>(proto.value().begin(), proto.value().end()));
  }
  else {
    Logger::LogDebug("ShortNode::Unmarshal key doesn't have term: " + bytesToHexString(key));
    this->value = new HashNode(vector<uint8_t>(proto.value().begin(), proto.value().end()));
  }
  flag.hash = hash; 
}

vector<uint8_t> ShortNode::Marshal(){
  merkle_patricia_trie::MPTShortNode protoShortNode;
  protoShortNode.set_key(string(key.begin(), key.end()));
  vector<uint8_t> vv= this->value->Marshal(); 
  protoShortNode.set_value(string(vv.begin(), vv.end()));
  merkle_patricia_trie::MPTNode protoNode;
  protoNode.set_data(protoShortNode.SerializeAsString());
  protoNode.set_type(merkle_patricia_trie::SHORT);
  string b = protoNode.SerializeAsString();
  return vector<uint8_t>(b.begin(), b.end());
}


tuple<vector<uint8_t>, bool> ShortNode::Cache(){
  return make_tuple(flag.hash, flag.dirty);
}

Node* ShortNode::Copy(){
  ShortNode* newNode = new ShortNode();
  newNode->key = key;
  newNode->value = value->Copy();
  newNode->flag = flag;
  return newNode;
}
