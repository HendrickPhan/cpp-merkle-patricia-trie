#include "node.h"
#include "merkle_patricia_trie.pb.h"
#include "short_node.h"
#include "full_node.h"
#include "hash_node.h"
#include "value_node.h"
#include "logger.h"
#include "utils.h"

Node* DecodeNode(vector<uint8_t> hash, vector<uint8_t> data) {
  Logger::LogDebug("Decoding node with hash: " + bytesToHexString(hash));
  merkle_patricia_trie::MPTNode protoNode;
  protoNode.ParseFromString(string(data.begin(), data.end()));
  Logger::LogDebug("Decoding node type: " + std::to_string(protoNode.type()));
  vector<uint8_t> nodeData = vector<uint8_t>(protoNode.data().begin(), protoNode.data().end()); 
  switch (protoNode.type()) {
    case merkle_patricia_trie::FULL:{
      FullNode* fullNode = new FullNode();
      fullNode->Unmarshal(hash, nodeData);
      return fullNode;
    }
    case merkle_patricia_trie::SHORT:{
      ShortNode* shortNode = new ShortNode();
      shortNode->Unmarshal(hash, nodeData);
      return shortNode;
    }
    default:{
      return nullptr;
    }
  }  
};
