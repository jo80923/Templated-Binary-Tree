#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include "binary_tree.hpp"

int main(int argc, char* argv[]){
	if(argc != 2){
		std::cerr<<"ERROR: must include desired size of randomly generated binary tree"<<std::endl;
		return -1;
	}
	int numElements = std::stoi(argv[1]);
	//initialize random seed
	srand(time(nullptr));
	
	BinaryTree<int> btree;

	for(int i = 0; i < numElements; ++i){
		btree.insert(rand()%100);
	}
	btree.print(btree.root,1);
	std::cout<<btree.difference(btree.root)<<std::endl;
	return 0;
}
