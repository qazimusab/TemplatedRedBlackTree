template <class T> class RedBlackNode
{
private:
	bool isNodeRed;
	T date;
	RedBlackNode<T> *left, *right, *parent;
public:
	//Node()
	//{
	//	left = NULL;
	//	right = NULL;
	//}
	RedBlackNode(T date)
	{
		this->isNodeRed = true;
		this->date = date;
		left = NULL;
		right = NULL;
		parent = NULL;
	}
	void recolor()
	{
		if (this->isNodeRed)
			this->isNodeRed = false;
		else
			this->isNodeRed = true;
	}
	bool isRed()
	{
		return isNodeRed;
	}
	T getValue()
	{
		return this->date;
	}
	RedBlackNode* getLeft()
	{
		return this->left;
	}
	RedBlackNode* getRight()
	{
		return this->right;
	}
	RedBlackNode* getParent()
	{
		return this->parent;
	}
	void clearParent()
	{
		this->parent = NULL;
	}
	void setLeft(RedBlackNode* left)
	{
		this->left = left;
		if (left != NULL) left->parent = this;
	}
	void setRight(RedBlackNode* right)
	{
		this->right = right;
		if (right != NULL) right->parent = this;
	}
};

