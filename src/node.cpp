#include "node.h"
#include "merkle_patricia_trie.pb.h"
#include "short_node.h"
#include "full_node.h"
#include "hash_node.h"
#include "value_node.h"

Node* DecodeNode(vector<uint8_t> hash, vector<uint8_t> data) {
  merkle_patricia_trie::MPTNode protoNode;
  protoNode.ParseFromString(string(data.begin(), data.end()));
  switch (protoNode.type()) {
    case merkle_patricia_trie::FULL:{
      FullNode* fullNode = new FullNode();
      fullNode->Unmarshal(hash, data);
      return fullNode;
    }
    case merkle_patricia_trie::SHORT:{
      ShortNode* shortNode = new ShortNode();
      shortNode->Unmarshal(hash, data);
      return shortNode;
    }
    default:{
      return nullptr;
    }
  }  
};
