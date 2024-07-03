all:
	rm -rf build
	mkdir build
	cd build && cmake .. && make && cp cpp_merkle_patricia_trie ../
clean:
	rm -rf build
	rm cpp_merkle_patricia_trie
