#pragma once

typedef enum { RED, BLACK } nodeColor;

class RBNode
{
public:
	RBNode *left, *right, *parent;
	int value;
	nodeColor color;

	RBNode(int value = 0, nodeColor color = BLACK)
	{
		this->value = value;
		this->color = color;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	}

	void setValue(int value)
	{
		this->value = value;
	}
};

class RBTree
{
private:
	
	RBNode *root;
	RBNode* min;
	RBNode* max;
	RBNode* nil;

public:
	class MaxSuccessor
	{
	public:
		MaxSuccessor() {};
	};

	class MinPredecessor
	{
	public:
		MinPredecessor() {};
	};

	int getMin()
	{
		return min->value;
	}
	std::string getColor() 
	{
		if (min->color == RED)
			return "red";
		return "black";
	}

	RBTree()
	{
		nil = new RBNode;
		root = nil;
		min = nullptr;
		max = nullptr;
	}

	void leftRotate(RBNode *x)
	{
		RBNode *y = x->right;
		x->right = y->left;
		if (y->left != nil)
			y->left->parent = x;
		y->parent = x->parent;
		if (x->parent = nil)
			root = y;
		else if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
		y->left = x;
		x->parent = y;
	}

	void rightRotate(RBNode *y)
	{ 
		RBNode *x = y->left;
		y->left = x->right;
		if (x->right != nil)
			x->right->parent = y;
		x->parent = y->parent;
		if (x->parent == nil)
			root = x;
		else if (y == y->parent->left)
			y->parent->left = x;
		else
			y->parent->right = x;
		x->right = y;
		y->parent = x;
	}

	void fixup(RBNode *z)
	{
		RBNode *y;
		while (z->parent->color == RED)
		{
			if (z->parent == z->parent->parent->left)
			{
				y = z->parent->parent->right;
				if (y->color == RED)
				{
					z->parent->color = BLACK;
					y->color = BLACK;
					z->parent->parent->color = RED;
					z = z->parent->parent;
				}
				else
				{
					if (z == z->parent->right)
					{
						z = z->parent;
						leftRotate(z);
					}
					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					rightRotate(z->parent->parent);
				}
			}
			else
			{
				y = z->parent->parent->left;
				if (y->color == RED)
				{
					z->parent->color == BLACK;
					y->color = BLACK;
					z->parent->parent->color = RED;
					z = z->parent->parent;
				}
				else
				{
					if (z == z->parent->left)
					{
						z = z->parent;
						rightRotate(z);
					}
					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					leftRotate(z->parent->parent);
				}
			}
		}
		root->color = BLACK;
	}

	RBNode* minimum(RBNode* nd)
	{
		while (nd->left != nil)
		{
			nd = nd->left;
		}
		return nd;
	}

	RBNode* maximum(RBNode* nd)
	{
		while (nd->right != nil)
		{
			nd = nd->right;
		}
		return nd;
	}

	RBNode * successor(RBNode * x)
	{
		if (x == max)		//try max
			throw RBTree::MaxSuccessor();
		if (x->right != nil)
			return minimum(x->right);
		RBNode* y = x->parent;
		while (y != nil && x == y->right)
		{
			x = y;
			y = y->parent;
		}
		return y;
	}

	RBNode * predecessor(RBNode * x)
	{
		if (x == min)	//try min
			throw RBTree::MinPredecessor();
		if (x->left != nil)
			return maximum(x->left);
		RBNode* y = x->parent;
		while (y != nil && x == y->left)
		{
			x = y;
			y = y->parent;
		}
		return y;
	}

	void insert(RBNode* z)
	{
		RBNode *x = root;
		RBNode *y = nil;
		while (x != nil)
		{
			y = x;
			if (z->value < x->value)
				x = x->left;
			else if(z->value >= x->value)
				x = x->right;
		}
		z->parent = y;
		if (y == nil)
		{
			min = z;
			max = z;
			root = z;
		}
		else if (z->value < y->value)
			y->left = z;
		else if(z->value >= y->value)
			y->right = z;
		z->left = nil;
		z->right = nil;
		z->color = RED;
		if (z->value < min->value)
			min = z;
		if (z->value > max->value)
			max = z;
		fixup(z);
	}

	int findMin()
	{
		RBNode *x = root;		
		while (x->right != nullptr)
			x = x->right;
		return x->value;
	} 
};

void useLab3()
{
	RBTree tree;
	int num, amount;
	std::cout << "Enter amount of elements in your tree: ";
	std::cin >> amount;
	RBNode *nodes = new RBNode[amount];
	for (int i = 0; i < amount; i++)
	{
		std::cout << "Enter element #" << i << ": ";
		std::cin >> num;
		nodes[i].setValue(num);
		tree.insert(&nodes[i]);
		std::cout << std::endl << "The minimum element is " << tree.getMin() << " and its' color is " << tree.getColor() << std::endl;;
	}

	try
	{
		std::cout << "Enter number of element for predecessor: ";
		std::cin >> num;
		if (num >= amount)
			throw 21;
		std::cout << "The predecessor of value " << nodes[num].value
			<< " is " << tree.predecessor(&nodes[num])->value
			<< " and color is ";
		if (tree.predecessor(&nodes[num])->color == RED)
			std::cout << "red" << std::endl;
		else
			std::cout << "black" << std::endl;
	}
	catch (RBTree::MinPredecessor)
	{
		std::cout << "This element is minimum in this tree!!!" << std::endl;
	}
	catch (int i)
	{
		std::cout << "To big index!!!" << std::endl;
	}
	system("pause");
}


///////successor
//try
//{
//	std::cout << "Enter number of element for successor: ";
//	std::cin >> num;
//	if (num >= amount)
//		throw 21;
//	std::cout << "The successor of value " << nodes[num].value
//		<< " is " << tree.successor(&nodes[num])->value
//		<< " and color is ";
//	if (tree.successor(&nodes[num])->color == RED)
//		std::cout << "red" << std::endl;
//	else
//		std::cout << "black" << std::endl;
//}
//catch (RBTree::MaxSuccessor)
//{
//	std::cout << "This element is maximum in this tree!!!" << std::endl;
//}
//catch (int i)
//{
//	std::cout << "To big index!!!" << std::endl;
//}