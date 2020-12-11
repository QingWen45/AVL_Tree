#pragma once
#include <iostream>

class AVLNode {
public:
	int key;
	int height;
	AVLNode* left, * right;
	AVLNode(int val, AVLNode* l, AVLNode* r) :
		key(val), height(0), left(l), right(r) {}
};

class AVLTree
{
private:
	AVLNode* root = nullptr;
public:
	int getHeight();

	AVLNode* search(int key);
	int minimum();
	int maximum();

	void insert(int key);
	void remove(int key);
	void destroy();
	void print();
private:
	int getHeight(AVLNode* tree);
	int max(int a, int b);

	AVLNode* search(AVLNode* tree, int key) const;
	AVLNode* minimum(AVLNode* tree);
	AVLNode* maximum(AVLNode* tree);

	AVLNode* left_leftRotation(AVLNode* n);
	AVLNode* right_rightRotation(AVLNode* n);
	AVLNode* left_rightRotation(AVLNode* p);
	AVLNode* right_leftRotation(AVLNode* p);

	AVLNode* insert(AVLNode*& tree, int key);
	AVLNode* remove(AVLNode*& tree, AVLNode* z);
	void destroy(AVLNode*& tree);
	void print(AVLNode* tree, int d);
};

