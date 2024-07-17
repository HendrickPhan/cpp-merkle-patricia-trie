#include <iostream>
#include <vector>
#include "utils.h"
#include "short_node.h"
#include "full_node.h"
#include "hash_node.h"
#include "encoding.h"
#include "hasher.h"
#include "trie.h"
#include "logger.h"
#include "js_fetch_db.h"
#include "db.h"
#include <emscripten/emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>

using namespace std;

Trie NewTrieWithJsFetchDB(string rootHash, JsFetchDB* jsFetchDB) {
  Node *root = nullptr;
  if(rootHash != ""){
    root = new HashNode(hexStringToBytes(rootHash));
  }
  return Trie(root, jsFetchDB);
}

// Export the function so it can be called from JavaScript
extern "C" {
 EMSCRIPTEN_BINDINGS(mpt_module) {
        // emscripten::function("main", &main);
  //
        emscripten::class_<Trie>("Trie")
            .constructor<>()
            .function("GetHex", &Trie::GetHex)
            .function("UpdateHex", &Trie::UpdateHex)
            .function("HashHex", &Trie::HashHex);

        emscripten::class_<JsFetchDB>("JsFetchDB")
          .constructor<int>()
          .function("GetCurrentGetKey", &JsFetchDB::GetCurrentGetKey)
          .function("SetCurrentGetValue", &JsFetchDB::SetCurrentGetValue);

        emscripten::function("NewTrieWithJsFetchDB", &NewTrieWithJsFetchDB, emscripten::allow_raw_pointers());
    }
}

