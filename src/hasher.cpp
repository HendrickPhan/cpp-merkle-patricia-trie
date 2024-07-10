#include "hasher.h"
#include "utils.h"
#include "encoding.h"
#include "hash_node.h"
#include "value_node.h"
#include "logger.h"
#include <iostream>

using namespace std;

tuple<Node*, Node*> hashNode(Node* node){
  vector<uint8_t> cacheHash; 
  bool cacheDirty;
  tie(cacheHash, cacheDirty) = node->Cache();
  if (cacheHash.size() > 0) {
    return make_tuple(new HashNode(cacheHash), node);
  }
  if (node->Type() == NodeType::SHORT) {
    Node* collapsed;
    Node* cached;
    tie(collapsed, cached) = hashShortNodeChildren((ShortNode*)node);
    Node* hashed = shortNodeToHash((ShortNode*)collapsed);
    ((ShortNode*)cached)->flag.hash = ((HashNode*)hashed)->hash;
    return make_tuple(hashed, (ShortNode*)cached);
  } else if (node->Type() == NodeType::FULL) {
    Node* collapsed;
    Node* cached;
    tie(collapsed, cached) = hashFullNodeChildren((FullNode*)node);
    Node* hashed = fullNodeToHash((FullNode*)collapsed);
    ((FullNode*)cached)->flag.hash = ((HashNode*)hashed)->hash;
    return make_tuple(hashed, (FullNode*)cached);
  } else {
    return make_tuple(node, node);
  }
};

tuple<Node*, Node*> hashShortNodeChildren(ShortNode* n) {
  Node* collapsed = n->Copy();
  Node* cached = n->Copy();
  Logger::LogInfo("hashShortNodeChildren type origin (): " + to_string(n->value->Type())
    + "cached type: " + to_string(((ShortNode*)cached)->value->Type())
  );
  ((ShortNode*)collapsed)->key = HexToCompact(n->key);
  if (((ShortNode*)n)->value->Type() == FULL || ((ShortNode*)n)->value->Type() == SHORT) {
    tie(
      ((ShortNode*)collapsed)->value, 
      ((ShortNode*)cached)->value
    ) = hashNode(((ShortNode*)n)->value);
  }

  Logger::LogInfo("hashShortNodeChildren 2 type origin (): " + to_string(n->value->Type())
    + "cached type: " + to_string(((ShortNode*)cached)->value->Type())
  );
  return make_tuple(collapsed, cached);
}

tuple<Node*, Node*> hashFullNodeChildren(FullNode* n){
  Node* collapsed = n->Copy();
  Node* cached = n->Copy();
  for (int i = 0; i < 16 ; i++) {
    if (n->children[i]) {
      Node* collapsedChild;
      Node* cachedChild;
      tie(collapsedChild, cachedChild) = hashNode(n->children[i]);
      ((FullNode*)collapsed)->children[i] = collapsedChild;
      ((FullNode*)cached)->children[i] = cachedChild;
      vector<uint8_t> hash = get<0>(cachedChild->Cache());
      Logger::LogInfo(
        "cached type " + to_string(i) +": " + bytesToHexString(hash) + "\n"
      );
    } else {
      ((FullNode*)collapsed)->children[i] = new ValueNode(vector<uint8_t>{});
    }
  }
  return make_tuple(collapsed, cached);
};

Node* shortNodeToHash(ShortNode* node){
  vector<uint8_t> data = node->Marshal();
  Logger::LogDebug("shortNodeToHash short node data: " + bytesToHexString(data));
  return hashData(data);
};

Node* fullNodeToHash(FullNode* node) {
  vector<uint8_t> data = node->Marshal();
  Logger::LogDebug("fullNodeToHash full node data: " + bytesToHexString(data));
  return hashData(data);
};

Node* hashData(vector<uint8_t> data) {
  vector<uint8_t> hash = keccak256(data);
  return new HashNode(hash);
}

