#include "hash_node.h"
#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

  // Constructor
HashNode::HashNode(vector<uint8_t> _hash){
  hash = _hash;
}

HashNode::HashNode(){
  hash = vector<uint8_t>(32, 0);
}

  // Destructor
HashNode::~HashNode(void){
}
  
void HashNode::Unmarshal(vector<uint8_t> _hash, vector<uint8_t> data) {
  return;
}

vector<uint8_t> HashNode::Marshal() {
  return hash;
}

tuple<vector<uint8_t>, bool> HashNode::Cache() {
  return make_tuple(hash, true);
}

Node* HashNode::Copy() {
  return new HashNode(vector<uint8_t>(this->hash.begin(), this->hash.end()));
}
