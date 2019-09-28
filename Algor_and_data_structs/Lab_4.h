#pragma once

void swap(int* a, int* b)		//total = 1
{
	int t = *a;					//c = 1
	*a = *b;					//c = 1
	*b = t;						//c = 1
}

int partition(int arr[], int low, int high)		//total = n
{
	int pivot = arr[high];						//c = 1
	int i = (low - 1);							//c = 1

	for (int j = low; j <= high - 1; j++)		//c = n
	{
		if (arr[j] <= pivot)					//c = 1
		{
			i++;								//c = 1
			swap(&arr[i], &arr[j]);				//c = 1
		}
	}
	swap(&arr[i + 1], &arr[high]);				//c = 1
	return (i + 1);								//c = 1
}

void quickSort(int arr[], int low, int high)	//total = n
{
	if (low < high)
	{
		int pi = partition(arr, low, high);

		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

void printArray(int arr[], int size)		//total = n
{
	for (int i = 0; i < size; i++)			//c = n
		std::cout << arr[i] << " ";			//c = 1
	std::cout << std::endl;					//c = 1
}

void inputArray(int arr[], int size)		//total = n
{
	for (int i = 0; i < size; i++)			//c = n
		std::cin >> arr[i];					//c = 1
}

int binarySearch(int* arr,int start, int end, int key)		//total = n
{
	int midd = 0;											//c = 1
	while (1)												//c = n
	{
		midd = (start + end) / 2;							//c = 3

		if (key < arr[midd])								//c = 1
			end = midd - 1;									//c = 2
		else if (key > arr[midd])							//c = 1
			start = midd + 1;								//c = 2
		else
			return midd;									//c = 1

		if (start > end)									//c = 1
			return -1;										//c = 1
	}
}

int* arraySearch(int* arr1, int size1, int* arr2, int size2)	//total = 
{
	int* res = new int[size2];									//c = 1
	for (int i = 0; i < size2; i++)								//c = n
	{
		res[i] = binarySearch(arr1, 0, size1, arr2[i]);			//c = 1
	}
	return res;													//c = 1
}

void useLab4()
{
	while (true)
	{
		int size1;
		std::cout << "Enter size of first array: ";
		std::cin >> size1;
		int *arr1 = new int[size1];
		std::cout << "Input first array: ";
		inputArray(arr1, size1);
		quickSort(arr1, 0, size1 - 1);
		printf("Sorted array: ");
		printArray(arr1, size1);
		int size2;
		std::cout << "Enter size of array with elements to binary search: ";
		std::cin >> size2;
		int *arr2 = new int[size2];
		std::cout << "Input second array: ";
		inputArray(arr2, size2);
		int * res = arraySearch(arr1, size1, arr2, size2);
		printArray(res, size2);
		std::cout << std::endl;
	}
	system("pause");
}