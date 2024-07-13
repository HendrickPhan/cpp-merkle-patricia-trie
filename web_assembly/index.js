const load_module = require('./merkle_patricia_trie.js')

function getValue(address, key) {
  console.log("xxxx", address, key)
  // Simulate an API call (replace with actual fetch call)
}

async function main() {
  const mpt = await load_module()

  var Trie = mpt.Trie;
  var trie = new Trie();

   // Insert key-value pairs into the trie
   // for (let i = 0; i < 1000; i++) {
    let key = "1010" 
    let value = "1011" 
    console.log(key, value);
    trie.UpdateHex(key, value);
   // }

  // Get the root hash of the trie
  let rootHash = trie.HashHex()
  let testGet = trie.GetHex("1010")
  console.log(testGet);

  var trie2 = mpt.NewTrieWithJsFetchDB("01", "5c0fcec323e68821800e4773299d5a6cca67ddd028e701d55ffbef9bf8c35a4d")
  let testGet2 = trie2.GetHex("6b657938")
  console.log("get2Value", testGet2);
}

main();
