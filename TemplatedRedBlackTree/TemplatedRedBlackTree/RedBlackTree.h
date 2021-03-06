#include "RedBlackNode.h"
#include <iostream>
#include <string>
#include <list>

using namespace std;

template <class T> class RedBlackTree
{
private:
	RedBlackNode<T>* root;
	int nodes = 0;
	bool searchComplete = false;

	void display(RedBlackNode <T>* root){
		if (root != NULL){
			cout << root->getValue() << " ";
			if (root->getLeft() != NULL){
				display(root->getLeft());
			}
			if (root->getRight() != NULL){
				display(root->getRight());
			}
		}
	}

	void insert(RedBlackNode<T> *root, T data)
	{
		RedBlackNode<T>* insertedNode = NULL;
		if (root->getValue() == data)
		{
			//skip
		}
		else if (root->getValue() > data)
		{
			if (root->getLeft() == NULL)
			{
				insertedNode = new RedBlackNode<T>(data);
				root->setLeft(insertedNode);
			}
			else
			{
				this->insert(root->getLeft(), data);
			}
		}
		else
		{
			if (root->getRight() == NULL)
			{
				insertedNode = new RedBlackNode<T>(data);
				root->setRight(insertedNode);
			}
			else
			{
				this->insert(root->getRight(), data);
			}
		}
		//restore uniform black height
		if (insertedNode == NULL) return;
		this->solveDoubleRedProblem(root);
		insertedNode = NULL;
	}

	//ballancing functionalities: double red problem and insertion
	void solveDoubleRedProblem(RedBlackNode<T> *root)
	{
		//exception black child
		//if (root->getLeft() != NULL && !root->getLeft()->isRed()
		//	&& root->getRight() != NULL && !root->getRight()->isRed()) return;
		//if no double red problem
		if (root->isRed() == false) return;
		//right rotate
		if (root == root->getParent()->getLeft())
		{
			if (root->getParent()->getRight() == NULL || !root->getParent()->getRight()->isRed()) this->rightRotate(root);
			else
			{
				root->changeColor();
				root->getParent()->getRight()->changeColor();
				root->getParent()->changeColor();
				//case real root is reached
				if (root->getParent()->getParent() == NULL)
				{
					root->getParent()->changeColor();
					return;
				}
				//root is now black so check one level up
				solveDoubleRedProblem(root->getParent()->getParent());
			}
		}
		//left rotate
		else
		{
			if (root->getParent()->getLeft() == NULL || !root->getParent()->getLeft()->isRed()) this->leftRotate(root);
			else
			{
				root->changeColor();
				root->getParent()->getLeft()->changeColor();
				root->getParent()->changeColor();
				//case real root is reached
				if (root->getParent()->getParent() == NULL)
				{
					root->getParent()->changeColor();
					return;
				}
				//root is now black so check one level up
				solveDoubleRedProblem(root->getParent()->getParent());
			}
		}
	}
	void leftRotate(RedBlackNode<T> *root)
	{
		RedBlackNode<T> *parent = root->getParent();
		//avl similar case 2 for left rotation - double rotation
		if (root->getLeft() != NULL && root->getLeft()->isRed())
		{
			RedBlackNode<T> *badChild = root->getLeft();
			root->setLeft(badChild->getRight());
			badChild->setRight(root);
			parent->setRight(badChild);
			root = badChild;
		}
		root->changeColor();
		parent->changeColor();
		//parent's right -> root's left
		parent->setRight(root->getLeft());
		//root -> parent
		if (parent->getParent() != NULL)
		{
			//bind root to rest of the tree
			if (parent->getParent()->getLeft() == parent) parent->getParent()->setLeft(root);
			else parent->getParent()->setRight(root);
		}
		else
		{
			//root is real root
			this->root = root;
			this->root->clearParent();
			root = this->root;
		}
		//root's left -> parent
		root->setLeft(parent);
	}
	void rightRotate(RedBlackNode<T> *root)
	{
		RedBlackNode<T> *parent = root->getParent();
		//avl similar case 2 for right rotation - double rotation
		if (root->getRight() != NULL && root->getRight()->isRed())
		{
			RedBlackNode<T> *badChild = root->getRight();
			root->setRight(badChild->getLeft());
			badChild->setLeft(root);
			parent->setLeft(badChild);
			root = badChild;
		}
		root->changeColor();
		parent->changeColor();
		//parent's left -> root's right
		parent->setLeft(root->getRight());
		//root -> parent
		if (parent->getParent() != NULL)
		{
			//bind root to rest of the tree
			if (parent->getParent()->getLeft() == parent) parent->getParent()->setLeft(root);
			else parent->getParent()->setRight(root);
		}
		else
		{
			//root is real root
			this->root = root;
			this->root->clearParent();
			root = this->root;
		}
		//root's right -> parent
		root->setRight(parent);
	}
	//ballancing functionalities: reduced height problem and deletion
	void restoreReducedHeight(RedBlackNode<T> *root)
	{
		RedBlackNode<T>* parent = root->getParent();
		if (parent == NULL) return;
		//double cases because of symmetries
		if (root == parent->getLeft())
		{
			if (parent->isRed())
			{
				//first two cases
				if ((parent->getRight()->getLeft() != NULL && parent->getRight()->getLeft()->isRed())
					|| (parent->getRight()->getRight() != NULL && parent->getRight()->getRight()->isRed()))
				{
					//case 1.1L
					firstLRotate(parent->getRight());
				}
				else
				{
					//case 1.2L
					parent->getRight()->changeColor();
					parent->changeColor();
				}
			}
			else
			{
				if (parent->getRight()->isRed())
				{
					//middle two cases
					if ((parent->getRight()->getLeft()->getRight() != NULL && parent->getRight()->getLeft()->getRight()->isRed())
						|| (parent->getRight()->getLeft()->getLeft() != NULL && parent->getRight()->getLeft()->getLeft()->isRed()))
					{
						//case 2.1.1L
						secondLRotate(parent->getRight());
					}
					else
					{
						//case 2.1.2L
						thirdLRotate(parent->getRight());
					}
				}
				else
				{
					//last two cases
					if ((parent->getRight()->getLeft() != NULL && parent->getRight()->getLeft()->isRed())
						|| (parent->getRight()->getRight() != NULL && parent->getRight()->getRight()->isRed()))
					{
						//case 2.2.1L
						forthLRotate(parent->getRight());
					}
					else
					{
						//case 2.2.2L
						parent->getRight()->changeColor();
						if (parent->getParent() != NULL) restoreReducedHeight(parent);
						//otherwise overall black height reduced by 1
					}
				}
			}
		}
		else
		{
			if (parent->isRed())
			{
				//first two cases
				if ((parent->getLeft()->getLeft() != NULL && parent->getLeft()->getLeft()->isRed())
					|| (parent->getLeft()->getRight() != NULL && parent->getLeft()->getRight()->isRed()))
				{
					//case 1.1R
					firstRRotate(parent->getLeft());
				}
				else
				{
					//case 1.2R
					parent->getLeft()->changeColor();
					parent->changeColor();
				}
			}
			else
			{
				if (parent->getLeft()->isRed())
				{
					//middle two cases
					if ((parent->getLeft()->getRight()->getRight() != NULL && parent->getLeft()->getRight()->getRight()->isRed())
						|| (parent->getLeft()->getRight()->getLeft() != NULL && parent->getLeft()->getRight()->getLeft()->isRed()))
					{
						//case 2.1.1R
						secondRRotate(parent->getLeft());
					}
					else
					{
						//case 2.1.2R
						thirdRRotate(parent->getLeft());
					}
				}
				else
				{
					//last two cases
					if ((parent->getLeft()->getLeft() != NULL && parent->getLeft()->getLeft()->isRed())
						|| (parent->getLeft()->getRight() != NULL && parent->getLeft()->getRight()->isRed()))
					{
						//case 2.2.1R
						forthRRotate(parent->getLeft());
					}
					else
					{
						//case 2.2.2R
						parent->getLeft()->changeColor();
						if (parent->getParent() != NULL) restoreReducedHeight(parent);
						//otherwise overall black height reduced by 1
					}
				}
			}
		}
	}
	void firstLRotate(RedBlackNode<T> *root)
	{
		RedBlackNode<T> *parent = root->getParent();
		//avl similar case 2 for left rotation - double rotation
		if (root->getLeft() != NULL && root->getLeft()->isRed())
		{
			RedBlackNode<T> *badChild = root->getLeft();
			root->setLeft(badChild->getRight());
			badChild->setRight(root);
			parent->setRight(badChild);
			root = badChild;
			parent->changeColor();
		}
		else
		{
			root->getRight()->changeColor();
			root->changeColor();
			parent->changeColor();
		}
		parent->setRight(root->getLeft());
		if (parent->getParent() != NULL)
		{
			//bind root to rest of the tree
			if (parent->getParent()->getLeft() == parent) parent->getParent()->setLeft(root);
			else parent->getParent()->setRight(root);
		}
		else
		{
			//root is real root
			this->root = root;
			this->root->clearParent();
			root = this->root;
		}
		root->setLeft(parent);
	}
	void secondLRotate(RedBlackNode<T> *root)
	{
		RedBlackNode<T>* parent = root->getParent();
		RedBlackNode<T>* grandParent = parent->getParent();
		//make red child always on the right
		if (root->getLeft()->getLeft() != NULL && root->getLeft()->getLeft()->isRed())
		{
			RedBlackNode<T> *badChild = root->getLeft()->getLeft();
			root->getLeft()->setLeft(badChild->getRight());
			badChild->setRight(root->getLeft());
			root->setLeft(badChild);
			badChild->getRight()->changeColor();
			badChild->changeColor();
		}
		parent->setRight(root->getLeft()->getLeft());
		root->getLeft()->setLeft(parent);
		root->setLeft(root->getLeft()->getRight());
		root->getLeft()->changeColor();
		parent->getParent()->setRight(root);
		if (grandParent != NULL)
		{
			//bind root to rest of the tree
			if (grandParent->getLeft() == parent) grandParent->setLeft(parent->getParent());
			else grandParent->setRight(parent->getParent());
		}
		else
		{
			//parent is real root
			this->root = parent->getParent();
			this->root->clearParent();
		}
	}
	void thirdLRotate(RedBlackNode<T> *root)
	{
		RedBlackNode<T>* parent = root->getParent();
		root->getLeft()->changeColor();
		parent->setRight(root->getLeft());
		root->changeColor();
		if (parent->getParent() != NULL)
		{
			//bind root to rest of the tree
			if (parent->getParent()->getLeft() == parent) parent->getParent()->setLeft(root);
			else parent->getParent()->setRight(root);
		}
		else
		{
			//parent is real root
			this->root = root;
			this->root->clearParent();
		}
		root->setLeft(parent);
	}
	void forthLRotate(RedBlackNode<T> *root)
	{
		RedBlackNode<T> *parent = root->getParent();
		//avl similar case 2 for left rotation - double rotation
		if (root->getLeft() != NULL && root->getLeft()->isRed())
		{
			RedBlackNode<T> *badChild = root->getLeft();
			root->setLeft(badChild->getRight());
			badChild->setRight(root);
			parent->setRight(badChild);
			root = badChild;
			root->changeColor();
		}
		else
		{
			root->getRight()->changeColor();
		}
		parent->setRight(root->getLeft());
		if (parent->getParent() != NULL)
		{
			//bind root to rest of the tree
			if (parent->getParent()->getLeft() == parent) parent->getParent()->setLeft(root);
			else parent->getParent()->setRight(root);
		}
		else
		{
			//root is real root
			this->root = root;
			this->root->clearParent();
			root = this->root;
		}
		root->setLeft(parent);
	}
	void firstRRotate(RedBlackNode<T> *root)
	{
		RedBlackNode<T> *parent = root->getParent();
		//avl similar case 2 for left rotation - double rotation
		if (root->getRight() != NULL && root->getRight()->isRed())
		{
			RedBlackNode<T> *badChild = root->getRight();
			root->setRight(badChild->getLeft());
			badChild->setLeft(root);
			parent->setLeft(badChild);
			root = badChild;
			parent->changeColor();
		}
		else
		{
			root->getLeft()->changeColor();
			root->changeColor();
			parent->changeColor();
		}
		parent->setLeft(root->getRight());
		if (parent->getParent() != NULL)
		{
			//bind root to rest of the tree
			if (parent->getParent()->getLeft() == parent) parent->getParent()->setLeft(root);
			else parent->getParent()->setRight(root);
		}
		else
		{
			//root is real root
			this->root = root;
			this->root->clearParent();
			root = this->root;
		}
		root->setRight(parent);
	}
	void secondRRotate(RedBlackNode<T> *root)
	{
		RedBlackNode<T>* parent = root->getParent();
		RedBlackNode<T>* grandParent = parent->getParent();
		//make red child always on the right
		if (root->getRight()->getRight() != NULL && root->getRight()->getRight()->isRed())
		{
			RedBlackNode<T> *badChild = root->getRight()->getRight();
			root->getRight()->setRight(badChild->getLeft());
			badChild->setLeft(root->getRight());
			root->setRight(badChild);
			badChild->getLeft()->changeColor();
			badChild->changeColor();
		}
		parent->setLeft(root->getRight()->getRight());
		root->getRight()->setRight(parent);
		root->setRight(root->getRight()->getLeft());
		root->getRight()->changeColor();
		parent->getParent()->setLeft(root);
		if (grandParent != NULL)
		{
			//bind root to rest of the tree
			if (grandParent->getLeft() == parent) grandParent->setLeft(parent->getParent());
			else grandParent->setRight(parent->getParent());
		}
		else
		{
			//parent is real root
			this->root = parent->getParent();
			this->root->clearParent();
		}
	}
	void thirdRRotate(RedBlackNode<T> *root)
	{
		RedBlackNode<T>* parent = root->getParent();
		root->getRight()->changeColor();
		parent->setLeft(root->getRight());
		root->changeColor();
		if (parent->getParent() != NULL)
		{
			//bind root to rest of the tree
			if (parent->getParent()->getLeft() == parent) parent->getParent()->setLeft(root);
			else parent->getParent()->setRight(root);
		}
		else
		{
			//parent is real root
			this->root = root;
			this->root->clearParent();
		}
		root->setRight(parent);
	}
	void forthRRotate(RedBlackNode<T> *root)
	{
		RedBlackNode<T> *parent = root->getParent();
		//avl similar case 2 for left rotation - double rotation
		if (root->getRight() != NULL && root->getRight()->isRed())
		{
			RedBlackNode<T> *badChild = root->getRight();
			root->setRight(badChild->getLeft());
			badChild->setLeft(root);
			parent->setLeft(badChild);
			root = badChild;
			root->changeColor();
		}
		else
		{
			root->getLeft()->changeColor();
		}
		parent->setLeft(root->getRight());
		if (parent->getParent() != NULL)
		{
			//bind root to rest of the tree
			if (parent->getParent()->getLeft() == parent) parent->getParent()->setLeft(root);
			else parent->getParent()->setRight(root);
		}
		else
		{
			//root is real root
			this->root = root;
			this->root->clearParent();
			root = this->root;
		}
		root->setRight(parent);
	}
	int getNodes(RedBlackNode <T>* root){
		int words = 0;
		if (root != NULL){
			words++;
			if (root->getLeft() != NULL){
				words += getNodes(root->getLeft());
			}
			if (root->getRight() != NULL){
				words += getNodes(root->getRight());
			}
		}
		return words;
	}

	int getHeight(RedBlackNode<T>* root)
	{
		if (root == NULL)
		{
			return 0;
		}

		int left = getHeight(root->getLeft());
		int right = getHeight(root->getRight());

		if (left > right)
			return 1 + left;
		else
			return 1 + right;
	}

	void search(T data, RedBlackNode <T>* root){
		if (root != NULL){
			nodes++;
			if (root->getValue() == data){
				searchComplete = true;
			}
			else{
				searchComplete = false;
				if (data <= root->getValue()){
					search(data, root->getLeft());
				}
				else{
					search(data, root->getRight());
				}
			}
		}
	}

	int checkLevelFull(RedBlackNode<T>* root){
		if (root == NULL){
			return 0;
		}
		if (root->getLeft() != NULL && root->getRight() != NULL){
			return (checkLevelFull(root->getLeft()) + 1 + checkLevelFull(root->getRight()));
		}
		else return 0;
	}

public:
	RedBlackTree()
	{
		this->root = NULL;
	}

	friend ostream& operator<<(ostream &os, RedBlackTree<T> tree){
		cout << "________________________________________________________________________________" << endl;
		tree.display();
		cout << "\n________________________________________________________________________________" << endl << endl;
		cout << "Tree details:" << endl << endl;
		cout << "Number of nodes: " << tree.getNodes() << endl;
		cout << "Height of tree: " << tree.getHeight() << endl;
		cout << "Level at which tree is full: " << tree.checkLevelFull() << endl;
		return os;
	}

	int checkLevelFull(){
		return checkLevelFull(root);
	}

	int getNodes(){
		return getNodes(root);
	}

	int getHeight(){
		return getHeight(root);
	}

	bool IsEmpty()
	{
		return root == NULL;
	}

	void display(){
		display(root);
	}

	void insert(T data)
	{
		if (this->IsEmpty())
		{
			this->root = new RedBlackNode<T>(data);
			this->root->changeColor();
		}
		else this->insert(this->root, data);
	}

	void search(T data){
		searchComplete = false;
		search(data, root);
		if (searchComplete == true){
			cout << "\"" << data << "\"" << " was found after examining " << nodes << " nodes." << endl;
		}
		else{
			cout << "\"" << data << "\"" << " was not found. Searched " << nodes << " nodes." << endl;
		}
		nodes = 0;
	}
};