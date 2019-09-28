#pragma once

class List
{
public:
	List();
	~List();

	void push_back(int data);

	void clear();

	int GetSize() { return Size; }

	int& operator[](const int index);

	double findAv();

	int getMin();

	int getMax();

	int beforeMin();

private:


	class Node
	{
	public:
		Node * pNext;
		int data;

		Node(int data = NULL, Node *pNext = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
		}
	};
	int Size;
	Node *head;
};


List::List()
{
	Size = 0;
	head = nullptr;
}


List::~List()
{
	clear();
}

void List::push_back(int data)
{
	if (head == nullptr)
	{
		head = new Node(data);
	}
	else
	{
		Node *current = this->head;

		while (current->pNext != nullptr)
		{
			current = current->pNext;
		}
		current->pNext = new Node(data);

	}

	Size++;
}

void List::clear()
{
	while (Size)
	{
		Node *temp = head;

		head = head->pNext;

		delete temp;

		Size--;
	}
}

int & List::operator[](const int index)
{
	int counter = 0;

	Node *current = this->head;

	while (current != nullptr)
	{
		if (counter == index)
		{
			return current->data;
		}
		current = current->pNext;
		counter++;
	}
}

std::ostream& operator<< (std::ostream &out, List &t)
{
	for (int i = 0; i < t.GetSize(); i++)
	{
		out << t[i] << std::endl;
	}
	return out;
}

double List::findAv()
{
	double sum = 0;
	Node *node = this->head;
	for (int i = 0; i < Size; i++)
	{
		sum += node->data;
		node = node->pNext;
	}
	return sum / Size;
}

int List::getMin()
{
	Node *node = this->head;
	int min = node->data;
	for (int i = 0; i < Size; i++)
	{
		if (node->data < min)
			min = node->data;
		node = node->pNext;
	}
	return min;
}

int List::getMax()
{
	Node *node = this->head;
	int max = node->data;
	for (int i = 0; i < Size; i++)
	{
		if (node->data > max)
			max = node->data;
		node = node->pNext;
	}
	return max;
}

int List::beforeMin()
{
	Node *node = this->head;
	int min = node->data;
	int beforeMin = NULL;
	int prev = NULL;
	for (int i = 0; i < Size; i++)
	{
		if (node->data < min)
		{
			min = node->data;
			beforeMin = prev;
		}
		prev = node->data;
		node = node->pNext;
	}
	return beforeMin;

}

void useLab1()
{
	List lst;

	int *amount = new int;
	input("Enter amount of elements: ", *amount);
	for (int i = 0; i < *amount; i++)
	{
		int temp;
		input("Enter element: ", temp);
		lst.push_back(temp);
	}
	delete amount;

	std::cout << std::endl << "--------------------------" << std::endl;

	std::cout << "Size: " << lst.GetSize() << std::endl;
	std::cout << "Average: " << lst.findAv() << std::endl;
	std::cout << "Minimum element: " << lst.getMin() << std::endl;
	std::cout << "Maximum element: " << lst.getMax() << std::endl;
	std::cout << "Fourth element: " << lst[3] << std::endl;
	std::cout << "Element that is before minimum: " << lst.beforeMin() << std::endl;
	system("pause");
}
