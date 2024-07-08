#include "value_node.h"
#include "hash_node.h"
#include "merkle_patricia_trie.pb.h"
#include <iostream>
#include "encoding.h"
#include "full_node.h" 
#include <vector>
#include <tuple>
#include "utils.h" 

using namespace std;

// Constructor
FullNode::FullNode() {
  for (int i = 0; i < TOTAL_CHILD_NODE; ++i) {
    children[i] = nullptr;
  }
}
// Destructor
FullNode::~FullNode() {
}

void FullNode::Unmarshal(vector<uint8_t> hash, vector<uint8_t> data) {
//
  merkle_patricia_trie::MPTFullNode proto;
  // convert data to 
  proto.ParseFromString(string(data.begin(), data.end()));
  for (int i = 0; i < TOTAL_CHILD_NODE; i++) {
    // check if children is empty bytes or 32 zero bytes
    vector<uint8_t> hash = vector<uint8_t>(proto.nodes(i).begin(), proto.nodes(i).end());
    string hexHash = bytesToHexString(hash);
    if (hexHash == "" || hexHash == "0000000000000000000000000000000000000000000000000000000000000000" ){
      continue; 
    }
    children[i] = new HashNode(hash);
  }
  flag.hash = hash;
}

vector<uint8_t> FullNode::Marshal(){
  merkle_patricia_trie::MPTFullNode protoFullNode;
  for (int i = 0; i < TOTAL_CHILD_NODE; i++) {
    if (children[i]) {
      vector<uint8_t> childData = children[i]->Marshal(); 
      protoFullNode.add_nodes(string(childData.begin(), childData.end()));
    } else {
      vector<uint8_t> emptyHash(32, 0);
      protoFullNode.add_nodes(string(emptyHash.begin(), emptyHash.end()));
    }
  }
  merkle_patricia_trie::MPTNode protoNode;
  protoNode.set_data(protoFullNode.SerializeAsString());
  protoNode.set_type(merkle_patricia_trie::FULL);
  string rs = protoNode.SerializeAsString();
  return vector<uint8_t>(rs.begin(), rs.end());
}


tuple<vector<uint8_t>, bool> FullNode::Cache(){
  return make_tuple(flag.hash, flag.dirty);
}

Node* FullNode::Copy(){
  FullNode* copy = new FullNode();
  for (int i = 0; i < TOTAL_CHILD_NODE; i++) {
    if (children[i]) {
      copy->children[i] = children[i]->Copy();
    }
  }
  copy->flag = flag;
  return copy;
}
