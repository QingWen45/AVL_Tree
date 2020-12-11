#include "AVLTree.h"

int AVLTree::getHeight(AVLNode* tree) {
	if (tree != nullptr)
		return tree->height;
	return 0;
}

int AVLTree::getHeight() {
	return getHeight(root);
};

int AVLTree::max(int a, int b) {
	return a > b ? a : b;
}

AVLNode* AVLTree::minimum(AVLNode* tree) {
	if (tree == nullptr)
		return nullptr;
	while (tree->left != nullptr)
		tree = tree->left;
	return tree;
}

int AVLTree::minimum() {
	AVLNode* p = minimum(root);
	if (p != nullptr)
		return p->key;
	return NULL;
}

AVLNode* AVLTree::maximum(AVLNode* tree) {
	if (tree == nullptr)
		return nullptr;
	while (tree->right != nullptr)
		tree = tree->right;
	return tree;
}

int AVLTree::maximum() {
	AVLNode* p = maximum(root);
	if (p != nullptr)
		return p->key;
	return NULL;
}

AVLNode* AVLTree::left_leftRotation(AVLNode* n) {
	AVLNode* m;
	m = n->left;
	n->left = m->right;
	m->right = n;

	n->height = max(getHeight(n->left), getHeight(n->right)) + 1;
	m->height = max(getHeight(m->left), n->height) + 1;

	return m;
}

AVLNode* AVLTree::right_rightRotation(AVLNode* n) {
	AVLNode* m;
	m = n->right;
	n->right = m->left;
	m->left = n;

	n->height = max(getHeight(n->left), getHeight(n->right)) + 1;
	m->height = max(getHeight(m->right), n->height) + 1;

	return m;
}

AVLNode* AVLTree::left_rightRotation(AVLNode* p) {
	p->left = right_rightRotation(p->left);
	return left_leftRotation(p);
}

AVLNode* AVLTree::right_leftRotation(AVLNode* p) {
	p->right = left_leftRotation(p->right);
	return right_rightRotation(p);
}

AVLNode* AVLTree::insert(AVLNode*& tree, int key) {
	if (tree == nullptr)
		tree = new AVLNode(key, nullptr, nullptr);
	else if (key < tree->key) {
		tree->left = insert(tree->left, key);
		if (getHeight(tree->left) - getHeight(tree->right) == 2) {
			if (key < tree->left->key)
				tree = left_leftRotation(tree);
			else
				tree = left_rightRotation(tree);
		}
	}
	else if (key > tree->key) {
		tree->right = insert(tree->right, key);
		if (getHeight(tree->right) - getHeight(tree->left) == 2) {
			if (key > tree->right->key)
				tree = right_rightRotation(tree);
			else
				tree = right_leftRotation(tree);
		}
	}
	else
		std::cout << "Key doubled!";
	tree->height = max(getHeight(tree->left), getHeight(tree->right)) + 1;

	return tree;
}

void AVLTree::insert(int key) {
	insert(root, key);
}

AVLNode* AVLTree::remove(AVLNode*& tree, AVLNode* z) {
	if (tree == nullptr || z == nullptr)
		return nullptr;
	if (z->key < tree->key) {
		tree->left = remove(tree->left, z);
		if (getHeight(tree->right) - getHeight(tree->left) == 2) {
			AVLNode* r = tree->right;
			if (getHeight(r->left) > getHeight(r->right))
				tree = right_leftRotation(tree);
			else
				tree = right_rightRotation(tree);
		}
	}
	else if (z->key > tree->key) {
		tree->right = remove(tree->right, z);
		if (getHeight(tree->left) - getHeight(tree->right) == 2) {
			AVLNode* l = tree->left;
			if (getHeight(l->right) > getHeight(l->left))
				tree = left_rightRotation(tree);
			else
				tree = left_leftRotation(tree);
		}
	}
	else {
		if ((tree->left != nullptr) && (tree->right != nullptr)) {
			if (getHeight(tree->left) > getHeight(tree->right)) {
				AVLNode* max = maximum(tree->left);
				tree->key = max->key;
				tree->left = remove(tree->left, max);
			}
			else {
				AVLNode* min = minimum(tree->right);
				tree->key = min->key;
				tree->right = remove(tree->right, min);
			}
		}
		else {
			AVLNode* tmp = tree;
			tree = (tree->left != nullptr) ? tree->left : tree->right;
			delete tmp;
		}
	}
	if (tree != nullptr)
		tree->height = max(getHeight(tree->left), getHeight(tree->right)) + 1;
	return tree;
}

void AVLTree::remove(int key) {
	AVLNode* z = search(root, key);
	if (z != nullptr)
		root = remove(root, z);
	
}

AVLNode* AVLTree::search(AVLNode* x, int key) const
{
	if (x == nullptr || x->key == key)
		return x;

	if (key < x->key)
		return search(x->left, key);
	else
		return search(x->right, key);
}

AVLNode* AVLTree::search(int key) {
	return search(root, key);
}

void AVLTree::destroy(AVLNode*& tree) {
	if (tree == nullptr)
		return;
	if (tree->left != nullptr)
		destroy(tree->left);
	if (tree->right != nullptr)
		destroy(tree->right);
	delete tree;
}

void AVLTree::destroy() {
	destroy(root);
}

void AVLTree::print(AVLNode* tree, int d)
{
	using namespace std;
	if (tree != nullptr) {
		print(tree->right, d + 1);

		for (int i = 0; i < d; i++)
		{
			cout << "    ";
		}
		cout << tree->key;
		cout << "---|" << endl;

		print(tree->left, d + 1);
	}
}

void AVLTree::print()
{
	if (root != NULL)
		print(root, 0);
	std::cout << std::endl;
}