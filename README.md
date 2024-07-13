# Description
This project is a C++ implementation of a Merkle Patricia Trie. It is a trie data structure that stores key-value pairs.
It is a modified version that use Protobuf to encode data instead of RLP like Ethereum. 
The Merkle Patricia Trie is used in the Ethereum blockchain to store account information and transaction data.  
This project also includes a WebAssembly iteration of the Merkle Patricia Trie that can be used in a web browser. 

# Build and Run
## Build c++
```bash
make
```

## Run c++
```bash
./cpp_merkle_partricia_trie
```

## Build web assembly
```bash
cd web_assembly
make
```

## Run sample web assembly
```bash
cd web_assembly
node index.js
```

## Clean
```bash
make clean
```
> **_NOTE:_**
>> Using protobuf ver v3.12.4 because newer use bazel and it's not easy to use in this project.
