#pragma once

class RandArray
{
private:
	int size;
	double* arr;
	std::string* strArr;
public:
	RandArray(int size)						//total = 1
	{
		this->size = size;					//c = 1
		arr = new double[size];				//c = 1
		strArr = new std::string[size];		//c = 1
	}

	void generate(int a, int b)								//total = n
	{
		srand(time(0));										//c = 1
		for (int i = 0; i < std::max(a, b); i++)			//c = n
		{
			arr[i] = 0.01 * (0 + rand() % 100);				//c = 4
		}
		for (int i = std::max(a, b); i < size; i++)			//c = n
		{
			arr[i] = arr[i - a] - arr[i - b];				//c = 2
			if (arr[i] < 0)									//c = 1
				arr[i]++;									//c = 1
		}
	}

	std::string transform(double num)						//total = n
	{
		std::string str;									//c = 1
		unsigned int rest = num;							//c = 1
		while (rest)										//c = n
		{
			str = ((rest & 1) ? "1" : "0") + str;			//c = 4
			rest >>= 1;										//c = 2
		}

		if (str.empty())									//c = 1
		{
			str = "0";										//c = 1
		}

		return str;											//c = 1
	}

	void fillStrArr()										//total = n^2
	{
		for (int i = 0; i < size; i++)						//c = n
		{
			strArr[i] = transform(arr[i]*100);				//c = n + 1
		}
	}

	bool test()												//total = n^2
	{
		fillStrArr();										//c = n^2
		int sum = 0;										//c = 1
		int n = 0;											//c = 1
		for (int i = 0; i < size; i++)						//c = n
		{
			for (int j = 0; j < strArr[i].size(); j++)		//c = n
			{
				n++;
				int bit = 0;								//c = 1
				if (strArr[i][j] == '1')					//c = 1
					bit = 1;								//c = 1
				sum += (2 * bit) - 1;						//c = 3
			}
		}
		double Sobs = abs(sum) / sqrt(n);					//c = 2

		double result = erfc(Sobs / sqrt(2));				//c = 2
		if (result < 0.01)									//c = 1
			return true;									//c = 1
		else
			return false;									//c = 1
	}

	void gist()												//total = n^2
	{
		std::ofstream fout;									//c = 1
		fout.open("Gist.txt");								//c = 1
		for (int i = 0; i < 100; i++)						//c = n
		{
			int counter = 0;								//c = 1
			for (int j = 0; j < size; j++)					//c = n
			{
				if ((int)(arr[j] * 100) == i)				//c = 2
					counter++;								//c = 1
			}
			if (counter != 0)								//c = 1
			{
				fout << (double)i/100 << std::endl;			//c = 2
				for (int i = 0; i < counter; i++)			//c = n
				{
					fout << "|";							//c = 1
				}
				fout << std::endl;							//c = 1
			}
		}
		fout.close();										//c = 1
	}

	friend std::ostream& operator<< (std::ostream& out, const RandArray& obj);
};

std::ostream& operator<< (std::ostream& out, const RandArray& obj)		//total = n
{
	for (int i = 0; i < obj.size; i++)									//c = n
	{
		out << obj.arr[i] << ' ';										//c = 1
	}
	return out;															//c = 1
}

void useLab5()												//total = n^2
{
	int size;												//c = 1
	std::cout << "Enter size of array: ";					//c = 1
	std::cin >> size;										//c = 1
	RandArray arr(size);									//c = 1
	int a, b;												//c = 2
	std::cout << "Enter lags A and B: ";					//c = 1
	std::cin >> a >> b;										//c = 2
	arr.generate(a, b);										//c = n
	std::cout << arr << std::endl;							//c = 2
	if (arr.test() == true)									//c = 1
		std::cout << "Test is successfull!!!";				//c = 1
	else
		std::cout << "Test failed";							//c = 1
	std::cout << std::endl;									//c = 1
	arr.gist();												//c = n^2
	system("pause");										//c = 1
}