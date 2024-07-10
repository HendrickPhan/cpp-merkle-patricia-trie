/*
 *   Copyright (c) 2024 hieuphanuit
 *   All rights reserved.
 */
#pragma once
#include <vector>
#include <tuple>
#include "node.h"
#include "trie_reader.h"

using namespace std;

const string EMPTY_ROOT_HASH_HEX = "56e81f171bcc55a6ff8345e692c0f86e5b48e01b996cadc001622fb5e363b421";

struct NodeWrapper {
  vector<uint8_t> hash;
  vector<uint8_t> value;
};

class Trie {
public:
  Trie(void);
  ~Trie(void);

  vector<uint8_t> Get(vector<uint8_t> key);
  void Update(vector<uint8_t> key, vector<uint8_t> value);
  vector<uint8_t>Hash();
  // tuple<vector<uint8_t>, vector<NodeWrapper>, vector<vector<uint8_t>>> Commit();
  
private:
  Node* root;
  TrieReader reader;
  bool commited;

  tuple<vector<uint8_t>, Node*, bool>get(
    Node* origNode,
    vector<uint8_t> key,
    uint32_t pos
  );
  void update(vector<uint8_t> key, vector<uint8_t> value);
  tuple<bool, Node*> insert(Node* node, vector<uint8_t> prefix, vector<uint8_t> key, Node* value);
  // tuple<bool, Node*> delete(Node* node, vector<uint8_t> prefix, vector<uint8_t> key);
  Node* resolveAndTrack(Node* node, vector<uint8_t> prefix);
  Node* resolve(Node* node, vector<uint8_t> prefix);
  tuple<Node*, Node*>hashRoot();
};
