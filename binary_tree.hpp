#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>

template<typename K>
class Node{
	public:
                K key;
		unsigned int occurance;
                Node<K>* l;
                Node<K>* r;

		Node();
		Node(K key, Node<K>* l = nullptr, Node<K>* r = nullptr, unsigned int occurance = 1);
		~Node();
};

/*
 * NODE COMPARATORS
 */

template<typename K>
class BinaryTree{
	public:
		Node<K>* root;

		BinaryTree(Node<K>* root = nullptr);
		BinaryTree(K root_key);
		~BinaryTree();

		int height(Node<K>* n = nullptr);
		int difference(Node<K>* n = nullptr);

		void insert(K k);
		void insert(Node<K>* n);
		

		Node<K>* rr_rot(Node<K>* n);
		Node<K>* ll_rot(Node<K>* n);
		Node<K>* lr_rot(Node<K>* n);
		Node<K>* rl_rot(Node<K>* n);
		void balance(Node<K>* n);


		void print(Node<K>* n, int l);
};


/*
 * BINARY TREE NODE METHODS
 */

template<typename K>
Node<K>::Node(){
	this->key = K();
	this->occurance = 0;
	this->l = nullptr;
	this->r = nullptr;
}
template<typename K>
Node<K>::Node(K key, Node* l, Node* r, unsigned int occurance): key(key),l(l),r(r),occurance(occurance){}
template<typename K>
Node<K>::~Node(){
	if(this->l != nullptr) delete this->l;
	if(this->r != nullptr) delete this->r;
}

/*
 * NODE COMPARATORS
 */

template<typename K>
bool operator==(const Node<K> &l, const Node<K> &r){
        return l.key == r.key;
}
template<typename K>
bool operator!=(const Node<K> &l, const Node<K> &r){
        return l.key != r.key;
}
template<typename K>
bool operator<(const Node<K> &l, const Node<K> &r){
        return l.key < r.key;
}
template<typename K>
bool operator<=(const Node<K> &l, const Node<K> &r){
        return (l < r) || (l == r);
}
template<typename K>
bool operator>(const Node<K> &l, const Node<K> &r){
        return l.key > r.key;
}
template<typename K>
bool operator>=(const Node<K> &l, const Node<K> &r){
        return (l > r) || (l == r);
}


/*
 * BINARY TREE METHODS
 */

template<typename K>
BinaryTree<K>::BinaryTree(Node<K>* root) : root(root){}
template<typename K>
BinaryTree<K>::BinaryTree(K root_key){
	this->root = Node<K>(root_key);
	this->height = 1;
	this->width = 1;
}
template<typename K>
BinaryTree<K>::~BinaryTree(){
	delete this->root;
}

template<typename K>
int BinaryTree<K>::height(Node<K>* n){
	if(n == nullptr) n = this->root;
	int lh = (n->l == nullptr) ? 0 : this->height(n->l);
	int rh = (n->r == nullptr) ? 0 : this->height(n->r);
	if(lh > rh) return lh + 1;
	else return rh + 1;
}
template<typename K>
int BinaryTree<K>::difference(Node<K>* n){
	if(n == nullptr) n = this->root;
	if(this->root == nullptr){
		std::cerr<<"ERROR: cannot calculate difference of an empty tree"<<std::endl;
		exit(-1);
	}
	int lh = this->height(n->l);
	int rh = this->height(n->r);
	return lh - rh;
}

template<typename K>
void BinaryTree<K>::insert(K k){
	this->insert(new Node<K>(k));
}
template<typename K>
void BinaryTree<K>::insert(Node<K>* n){
	if(n == nullptr){
		std::cerr<<"ERROR: cannot add node == nullptr"<<std::endl;
		exit(-1);
	}
	if(this->root == nullptr){
		this->root = n;
		return;
	}
	Node<K>* current = this->root;
	while(1){
		if(*n == *current){
			current->occurance++;
			break;
		}
		else if(*n < *current){
			if(current->l == nullptr){
				current->l = n;
				break;
			}
			else current = current->l;
		}
		else if(*n > *current){
			if(current->r == nullptr){
				current->r = n;
				break;
			}
			else current = current->r;
		}
	}
	this->balance(this->root);
}

template<typename K>
Node<K>* BinaryTree<K>::rr_rot(Node<K>* n){
	if(n == nullptr) return n;
	Node<K>* t = n->r;
	n->r = t->l;
	t->l = n;
	return t;
}
template<typename K>
Node<K>* BinaryTree<K>::ll_rot(Node<K>* n){
	if(n == nullptr) return n;
	Node<K>* t = n->l;
	n->l = t->r;
	t->r = n;
	return t;
}
template<typename K>
Node<K>* BinaryTree<K>::lr_rot(Node<K>* n){
	if(n == nullptr) return n;
	Node<K>* t = n->l;
	n->l = this->rr_rot(t);
	return this->ll_rot(n);
}
template<typename K>
Node<K>* BinaryTree<K>::rl_rot(Node<K>* n){
	if(n == nullptr) return n;
	Node<K>* t = n->r;
	n->r = this->ll_rot(t);
	return this->rr_rot(n);
}
template<typename K>
void BinaryTree<K>::balance(Node<K>* n){
	int bal = this->difference(this->root);
	if(bal > 1){
		if(difference(n->l) > 0) n = this->ll_rot(n);
		else n = this->lr_rot(n);
	}
	else if(bal < -1){
		if(difference(n->r) > 0) n = this->rr_rot(n);
		else n = this->rl_rot(n);
	}
	this->root = n;
}

template<typename K>
void BinaryTree<K>::print(Node<K>* n, int l){
	if(n == nullptr) return;
	std::cout<<"[ ";
	print(n->l,l+1);
	if(n == this->root){
		std::cout<<"Root->";
	}
	std::cout<<n->key;
	print(n->r,l+1);
	std::cout<<" ]";
	if(n == this->root) std::cout<<std::endl;
}


#endif /* BINARY_TREE_HPP */
