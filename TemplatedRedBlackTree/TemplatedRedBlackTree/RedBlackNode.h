template <class T> 
class RedBlackNode
{
private:
	bool isNodeRed;
	T data;
	RedBlackNode<T> *left;
	RedBlackNode<T> *right;
	RedBlackNode<T> *parent;
public:
	RedBlackNode(T data)
	{
		this->isNodeRed = true;
		this->data = data;
		left = NULL;
		right = NULL;
		parent = NULL;
	}
	void changeColor()
	{
		isNodeRed = !isNodeRed;
	}
	bool isRed()
	{
		return isNodeRed;
	}
	T getValue()
	{
		return this->data;
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
		if (left != NULL) {
			left->parent = this;
		}
	}
	void setRight(RedBlackNode* right)
	{
		this->right = right;
		if (right != NULL) {
			right->parent = this;
		}
	}
};

