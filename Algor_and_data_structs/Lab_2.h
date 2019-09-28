#pragma once

class HashTable
{
private:
	std::vector<std::string> **arr;
	int size;
public:
	HashTable(int size)
	{
		this->size = size;
		arr = new std::vector<std::string>*[size];
		for (int i = 0; i < size; i++)
		{
			arr[i] = new std::vector<std::string>;
		}
	}

	int hash(int key)
	{
		double A = 0.618033;
		int h = size * fmod(key*A, 1);
		return h;
	}

	void insert(int key, std::string value)
	{
		std::vector<std::string> our = *arr[hash(key)];
		our.push_back(value);
		*arr[hash(key)] = our;
	}

	/*void del() 
	{

	}*/

	std::vector<std::string>& operator[](int index)
	{
		return *arr[index];
	}

	friend std::istream& operator>>(std::istream& in, std::vector<std::string> &res);
};

std::istream& operator>>(std::istream& in, HashTable &obj)
{
	int key;
	std::string str;
	in >> key >> str;
	obj.insert(key, str);
	return in;
}

void useLab2()
{
	int a, b;
	std::cin >> a >> b;
	HashTable tbl(a);
	for (int i = 0; i < a; i++)
	{
		std::cin >> tbl;
	}
	std::vector<int> vec;
	for (int i = 0; i < b; i++)
	{
		int temp;
		std::cin >> temp;
		vec.push_back(temp);
	}

	for (int i = 0; i < vec.size(); i++)
	{
		int index = tbl.hash(vec[i]);
		std::vector<std::string> res =  tbl[index];
		for(int i = 0; i < res.size(); i++)
		{
			std::cout << res[i] << ' ';
		}
		std::cout << std::endl;
	}
	system("pause");
}