#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <algorithm>
#include <ctime>
#include <fstream>

#include "Menu.h"
#include "Tools.h"
#include "Lab_1.h"
#include "Lab_2.h"
#include "Lab_3.h"
#include "Lab_4.h"
#include "Lab_5.h"
#include "Lab_6.h"
#include "Lab_7.h"

int main()
{
	while (true)
	{
		system("cls");
		std::cout << "Select your lab:" << std::endl;
		std::vector<std::string> labs = { "Lab 1", "Lab 2", "Lab 3",
			"Lab 4", "Lab 5", "Lab 6", "Lab 7", "Lab 8",  "Lab 9"
		, "Lab 10" , "Lab 11"};
		switch (Menu::getInstance().menuOrgan(labs))
		{
		case -1:
			return 0;
		case 0:
		{
			useLab1();
		}break;
		case 1:
		{
			useLab2();
		}break;
		case 2:
		{
			useLab3();
		}break;
		case 3:
		{
			useLab4();
		}break;
		case 4:
		{
			useLab5();
		}break;
		case 5:
		{
			useLab6();
		}
		case 6:
		{
			useLab7();
		}
		}
	}
}