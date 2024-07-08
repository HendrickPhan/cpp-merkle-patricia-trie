#include "hasher.h"
#include "utils.h"
#include "encoding.h"
#include "hash_node.h"

using namespace std;

tuple<Node*, Node*> hashNode(Node* node){
  vector<uint8_t> cacheHash; 
  bool cacheDirty;
  tie(cacheHash, cacheDirty) = node->Cache();
  if (cacheHash.size() > 0) {
    return make_tuple(new HashNode(cacheHash), new HashNode(cacheHash));
  }
  if (node->Type() == SHORT) {
    Node* collapsed;
    Node* cached;
    tie(collapsed, cached) = hashShortNodeChildren((ShortNode*)node);
    Node* hashed = shortNodeToHash((ShortNode*)collapsed);
    ((ShortNode*)cached)->flag.hash = ((HashNode*)hashed)->hash;
    return make_tuple(hashed, cached);
  } else if (node->Type() == FULL) {
    Node* collapsed;
    Node* cached;
    tie(collapsed, cached) = hashFullNodeChildren((FullNode*)node);
    Node* hashed = fullNodeToHash((FullNode*)collapsed);
    ((FullNode*)cached)->flag.hash = ((HashNode*)hashed)->hash;
    return make_tuple(hashed, cached);
  } else {
    return make_tuple(node, node);
  }
};

tuple<Node*, Node*> hashShortNodeChildren(ShortNode* n) {
  Node* collapsed = n->Copy();
  Node* cached = n->Copy();
  ((ShortNode*)collapsed)->key = HexToCompact(n->key);
  if (n->Type() == FULL || n->Type() == SHORT) {
    tie(
      ((ShortNode*)collapsed)->value, 
      ((ShortNode*)cached)->value
    ) = hashNode(((ShortNode*)n)->value);
  }
  return make_tuple(collapsed, cached);
}

tuple<Node*, Node*> hashFullNodeChildren(FullNode* n){
  Node* collapsed = n->Copy();
  Node* cached = n->Copy();
  for (int i = 0; i < TOTAL_CHILD_NODE; i++) {
    if (n->children[i]) {
      Node* collapsedChild;
      Node* cachedChild;
      tie(collapsedChild, cachedChild) = hashNode(n->children[i]);
      ((FullNode*)collapsed)->children[i] = collapsedChild;
      ((FullNode*)cached)->children[i] = cachedChild;
    } else {
      ((FullNode*)collapsed)->children[i] = nullptr;
      ((FullNode*)collapsed)->children[i] = nullptr;
    }
  }
  return make_tuple(collapsed, cached);
};

Node* shortNodeToHash(ShortNode* node){
  vector<uint8_t> data = node->Marshal();
  return hashData(data);
};

Node* fullNodeToHash(FullNode* node) {
  vector<uint8_t> data = node->Marshal();
  return hashData(data);
};

Node* hashData(vector<uint8_t> data) {
  vector<uint8_t> hash = keccak256(data);
  return new HashNode(hash);
}

