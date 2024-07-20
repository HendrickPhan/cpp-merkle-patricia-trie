#include "trie.h"
#include "utils.h" 
#include "short_node.h"
#include "hasher.h"
#include "full_node.h"
#include "hash_node.h"
#include "value_node.h"
#include "encoding.h"
#include "db.h"
#include "logger.h"
#include <iostream>
#include <emscripten/emscripten.h>

using namespace std;

Trie::Trie(void) {
  root = nullptr;
  commited = false;
}

Trie::Trie(Node *_root, DB* db) {
  root = _root;
  reader = TrieReader(db);
  commited = false;
}

Trie::~Trie(void) {
}

vector<uint8_t> Trie::Get(vector<uint8_t> key) {
  vector<uint8_t> hashedKey = keccak256(key);
  if (commited) {
    Logger::LogDebug("Trie::GET Commited\n");
    return vector<uint8_t>();
  }
  vector<uint8_t> k = KeyBytesToHex(hashedKey);
  tuple<vector<uint8_t>, Node*, bool> result = get(root, k, 0);
  if (std::get<2>(result)) {
    root = std::get<1>(result);
  }
  return std::get<0>(result); 
}


tuple<vector<uint8_t>, Node*, bool>Trie::get(
  Node* originNode,
  vector<uint8_t> key,
  uint32_t pos
) {
  Logger::LogDebug("Trie::get key " + bytesToHexString(key));
  if(originNode->Type() == NodeType::VALUE){
    return make_tuple(
      ((ValueNode*)originNode)->data, 
      originNode, 
      false
    );
  }
  if(originNode->Type() == NodeType::SHORT){
    if(
      key.size() - pos < ((ShortNode*)originNode)->key.size() || 
      !equal(
        key.begin() + pos, 
        key.begin() + pos + ((ShortNode*)originNode)->key.size(), 
        ((ShortNode*)originNode)->key.begin()
      )
    ){
      return make_tuple(
        vector<uint8_t>(), 
        originNode, 
        false
      );
    }
    tuple<vector<uint8_t>, Node*, bool> result = get(
      ((ShortNode*)originNode)->value, 
      key, 
      pos + ((ShortNode*)originNode)->key.size()
    );
    if(std::get<2>(result)){
      originNode = originNode->Copy();
      ((ShortNode*)originNode)->value = std::get<1>(result);
    }
    return make_tuple(
      std::get<0>(result), 
      originNode, 
      std::get<2>(result)
    );
  }
  if(originNode->Type() == NodeType::FULL){
    tuple<vector<uint8_t>, Node*, bool> result = get(
      ((FullNode*)originNode)->children[key[pos]], 
      key, 
      pos + 1
    );
    if(std::get<2>(result)){
      originNode = originNode->Copy();
      ((FullNode*)originNode)->children[key[pos]] = std::get<1>(result);
    }
    return make_tuple(
      std::get<0>(result), 
      originNode, 
      std::get<2>(result)
    );
    
  }
  if(originNode->Type() == NodeType::HASH){
    Node* child = resolveAndTrack(originNode, vector<uint8_t>(key.begin(), key.begin() + pos));
    tuple<vector<uint8_t>, Node*, bool> result = get(
      child, 
      key, 
      pos
    );
    return make_tuple(
      std::get<0>(result), 
      std::get<1>(result), 
      true
    ); 
  }
  throw "Invalid node";
}

void Trie::Update(vector<uint8_t> key, vector<uint8_t> value){
  if(commited){
    throw "Already commited";
  }
  vector<uint8_t> hashedKey = keccak256(key);
  return update(hashedKey, value);
};

EM_JS(int, complete_resolve, (const char* value), {
  GLOBAL.resolve(UTF8ToString(value));
  return 1
});

string Trie::GetHex(string hkey) {
  vector<uint8_t> key = hexStringToBytes(hkey);
  vector<uint8_t> value = Get(key);
  Logger::Log("Trie::GetHex key " + hkey + " value " + bytesToHexString(value));
  string rs = bytesToHexString(value);
  Logger::Log("return " + rs);
  complete_resolve(rs.c_str());
  return rs; 
}

void Trie::UpdateHex(string hkey, string hvalue){
  if(commited){
    throw "Already commited";
  }
  vector<uint8_t> key = hexStringToBytes(hkey);
  vector<uint8_t> value = hexStringToBytes(hvalue);
  vector<uint8_t> hashedKey = keccak256(key);
  return update(hashedKey, value);
};

string Trie::HashHex(){
  vector<uint8_t> hash = Hash();
  return bytesToHexString(hash);
};

void Trie::update(vector<uint8_t> key, vector<uint8_t> value){
  vector<uint8_t> k = KeyBytesToHex(key);
  if (value.size() != 0) {
    tuple<bool, Node*> result = insert(root, vector<uint8_t>(), k, new ValueNode(value));
    if(std::get<0>(result)){
      root = std::get<1>(result);
    }
  } else {
    // TODO
    // tuple<bool, Node*> result = delete(root, vector<uint8_t>(), k);
    // if(std::get<0>(result)){
    //   root = std::get<1>(result);
    // }
  }
}

vector<uint8_t>Trie::Hash(){
  // TODO
  tuple<Node*, Node*> result = hashRoot();
  root = std::get<1>(result);
  return ((HashNode*)std::get<0>(result))->hash;
};

// tuple<vector<uint8_t>, vector<NodeWrapper>> Trie::Commit(){
//   // TODO
//   return make_tuple(vector<uint8_t>(), vector<NodeWrapper>());
// };

tuple<bool, Node*> Trie::insert(Node* node, vector<uint8_t> prefix, vector<uint8_t> key, Node* value){
  Logger::LogDebug("Trie::insert key " + bytesToHexString(key) + " prefix " + bytesToHexString(prefix));
  if(key.size() == 0){
    if(node != nullptr && node->Type() == NodeType::VALUE){
      return make_tuple(
        !equal(
          ((ValueNode*)node)->data.begin(), 
          ((ValueNode*)node)->data.end(), 
          ((ValueNode*)value)->data.begin()
        ), 
        value
      );
    }
    return make_tuple(true, value);
  }
  if(node == nullptr){
    Logger::LogDebug("Trie::insert node == nullptr value: " + bytesToHexString(
      ((ValueNode*)value)->data
    ));
    return make_tuple(true, new ShortNode(key, value, NewFlag()));
  }
  Logger::LogDebug("Trie::insert node type " + to_string(node->Type()) + "\n");
  switch (node->Type()) {
    case SHORT:{
      Logger::LogDebug("Trie::insert SHORT\n");
      int matchLen = PrefixLen(key, ((ShortNode*)node)->key);
	 	  // If the whole key matches, keep this short node as is
	 	  // and only update the value.
      if(matchLen == ((ShortNode*)node)->key.size()){
        Logger::LogDebug("Trie::insert SHORT matchLen == ((ShortNode*)node)->key.size()\n");
        vector<uint8_t> newPrefix = vector<uint8_t>(prefix.begin(), prefix.end());
        newPrefix.insert(newPrefix.end(), key.begin(), key.begin() + matchLen);
        tuple<bool, Node*> result = insert(
          ((ShortNode*)node)->value, 
          newPrefix,
          vector<uint8_t>(key.begin() + matchLen, key.end()), 
          value
        );
        if(std::get<0>(result)){
          return make_tuple(
            true, 
            new ShortNode(
              ((ShortNode*)node)->key, 
              std::get<1>(result),
              NewFlag()
            )
          );
        }
        return make_tuple(false, node);
      }
      Logger::LogDebug("Trie::insert SHORT matchLen != ((ShortNode*)node)->key.size()\n");
		  // Otherwise branch out at the index where they differ.
      FullNode* branch = new FullNode();
      vector<uint8_t> newPrefix = vector<uint8_t>(prefix.begin(), prefix.end());
      newPrefix.insert(newPrefix.end(), ((ShortNode*)node)->key.begin(), ((ShortNode*)node)->key.begin() + matchLen + 1);
      Logger::LogDebug("Trie::insert SHORT key" + bytesToHexString(((ShortNode*)node)->key) + "\n");
      vector<uint8_t> newKey = vector<uint8_t>(((ShortNode*)node)->key.begin() + matchLen + 1, ((ShortNode*)node)->key.end());
      Logger::LogDebug("Trie::insert SHORT newKey" + bytesToHexString(newKey) + "\n");
      tuple<bool, Node*> result1 = insert(
        nullptr, 
        newPrefix,
        newKey,
        (((ShortNode*)node)->value)
      );
      branch->children[((ShortNode*)node)->key[matchLen]] = std::get<1>(result1);

      vector<uint8_t> newPrefix2 = vector<uint8_t>(prefix.begin(), prefix.end());
      newPrefix2.insert(newPrefix2.end(), key.begin(), key.begin() + matchLen + 1);
      vector<uint8_t> newKey2 = vector<uint8_t>(key.begin() + matchLen + 1, key.end());
      tuple<bool, Node*> result2 = insert(
        nullptr, 
        newPrefix2,
        newKey2,
        value
      );
      branch->children[key[matchLen]] = std::get<1>(result2);
      if (matchLen == 0) {
        return make_tuple(true, branch);
      }

      Node* newNode = new ShortNode(
        vector<uint8_t>(key.begin(), key.begin() + matchLen),
        branch,
        NewFlag()
      );
      return make_tuple(true, newNode);
    }
    case FULL: {
      vector<uint8_t> newPrefixf = vector<uint8_t>(prefix.begin(), prefix.end());
      newPrefixf.push_back(key[0]);
      Logger::LogDebug("Trie::insert FULL\n" + to_string(key[0]) + "\n");
      tuple<bool, Node*> result = insert(
        ((FullNode*)node)->children[key[0]], 
        newPrefixf,
        vector<uint8_t>(key.begin() + 1, key.end()), 
        value
      );
      if(!std::get<0>(result)){
        return make_tuple(false, node);
      }
      Node* cpNode = node->Copy();
      ((FullNode*)cpNode)->flag = NewFlag();
      ((FullNode*)cpNode)->children[key[0]] = std::get<1>(result);
      return make_tuple(true, cpNode);
    }
    case HASH:{
      Node* rn = resolveAndTrack(node, prefix);
      tuple<bool, Node*> resulth = insert(
        rn, 
        prefix, 
        key, 
        value
      );
      if(!std::get<0>(resulth)){
        return make_tuple(false, rn);
      }
      return make_tuple(true, std::get<1>(resulth));
    }
    case VALUE:{
      throw "Invalid node";
    }
  }
  throw "Invalid node";
};

Node* Trie::resolveAndTrack(Node* n, vector<uint8_t> prefix){
  // TODO
  vector<uint8_t> hash = ((HashNode*)n)->hash;
	vector<uint8_t> blob = reader.node(prefix, hash);
	return DecodeNode(hash, blob);
};

Node* Trie::resolve(Node* node, vector<uint8_t> prefix){
  if(node->Type() == NodeType::HASH){
    return resolveAndTrack(node, prefix);
  }
  return node;
};

tuple<Node*, Node*>Trie::hashRoot(){
  // TODO
  if (root == nullptr) {
    return make_tuple(
      new HashNode(
       hexStringToBytes(EMPTY_ROOT_HASH_HEX)
      ),
      nullptr
    );
  }
  return hashNode(root);
};

