const load_module = require('./merkle_patricia_trie.js')

async function main() {
  const mpt2 = await load_module()
  await mpt2.main()
  console.log("Done")

  // const result = mainc();
  // console.log(result);
}

main();
