#include <vector>
#include <tuple>
#include "trie_reader.h"
#include <iostream>

using namespace std;

TrieReader::TrieReader(DB* _db) {
  db = _db;
}

TrieReader::TrieReader(void) {
  db = nullptr;
}

TrieReader::~TrieReader(void) {
}

void TrieReader::setDB(DB* _db) {
  db = _db;
}

vector<uint8_t> TrieReader::node(vector<uint8_t> path, vector<uint8_t> hash) {
  vector<uint8_t> blob = db->Get(hash);
  return blob;
}
