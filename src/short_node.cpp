#include "short_node.h"
#include "value_node.h"
#include "hash_node.h"
#include "merkle_patricia_trie.pb.h"
#include <iostream>
#include "encoding.h"

using namespace std;

// Constructor
ShortNode::ShortNode() {
  
}
// Destructor
ShortNode::~ShortNode() {
}

void ShortNode::Unmarshal(vector<uint8_t> hash, vector<uint8_t> data) {
//
  merkle_patricia_trie::MPTShortNode proto;
  // convert data to 
  proto.ParseFromString(string(data.begin(), data.end()));
  key = vector<uint8_t>(proto.key().begin(), proto.key().end());
  if (HasTerm(key)) {
    this->value = new ValueNode(vector<uint8_t>(proto.value().begin(), proto.value().end()));
  }
  // else {
  //   this->value = new HashNode(vector<uint8_t>(proto.value().begin(), proto.value().end()));
  // }
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
  return vector<uint8_t>(protoNode.data().begin(), protoNode.data().end());
}


tuple<vector<uint8_t>, bool> ShortNode::Cache(){
  return make_tuple(flag.hash, flag.dirty);
}

