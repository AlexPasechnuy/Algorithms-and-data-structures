#pragma once
#pragma once

#include <iostream>
#include <algorithm>

class Chain
{
private:
	class Point
	{
	public:
		int x;
		int y;
	};

	class Segment
	{
	public:
		Point p1, p2;
		int intersections = 0;
	};
	Point* points;
	Segment* arr;
	int pAmount;
	bool seg_inter(Segment s1, Segment s2)																		//total = 1
	{
		int d1 = direction(s2.p1, s2.p2, s1.p1);																//c = 1
		int d2 = direction(s2.p1, s2.p2, s1.p2);																//c = 1
		int d3 = direction(s1.p1, s1.p2, s2.p1);																//c = 1
		int d4 = direction(s1.p1, s1.p2, s2.p2);																//c = 1
		if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)))			//c = 8
			return true;																						//c = 1
		else if (d1 == 0 && on_segment(s2.p1, s2.p2, s1.p1))													//c = 1
			return true;																						//c = 1
		else if (d2 == 0 && on_segment(s2.p1, s2.p2, s1.p2))													//c = 1
			return true;																						//c = 1
		else if (d3 == 0 && on_segment(s1.p1, s1.p2, s2.p1))													//c = 1
			return true;																						//c = 1
		else if (d4 == 0 && on_segment(s1.p1, s1.p2, s2.p2))													//c = 1
			return true;																						//c = 1
		else
			return false;																						//c = 1
	}

	int direction(Point i, Point j, Point k)								//total = 1
	{
		return (((k.x - i.x)*(j.y - i.y)) - ((j.x - i.x)*(k.y - i.y)));		//c = 7
	}

	bool on_segment(Point i, Point j, Point k)								//total = 1
	{
		if ((std::min(i.x, j.x) < k.x && k.x < std::max(i.x, j.x))			//c = 8
			&& (std::min(i.y, j.y) < k.y && k.y <
				std::max(i.y, j.y)))
			return true;													//c = 1
		else
			return false;													//c = 1
	}
public:
	Chain(int a)															//total = 1
	{
		pAmount = a;														//c = 1
		arr = new Segment[a - 1];											//c = 1
		points = new Point[a];												//c = 1
	}

	void input()															//total = n
	{
		std::cin >> points[0].x >> points[0].y;								//c = 2
		for (int i = 1; i < pAmount; i++)									//c = n
		{
			std::cin >> points[i].x >> points[i].y;							//c = 1
			arr[i - 1].p1 = points[i - 1];									//c = 1
			arr[i - 1].p2 = points[i];										//c = 1
		}
	}

	void find_inter()														//total = n^2
	{
		for (int i = 0; i < (pAmount - 1); i++)								//c = n
		{
			for (int j = i - 1; j >= 0; j--)								//c = n
			{
				if (seg_inter(arr[i], arr[j]) == true)						//c = 1
					arr[i].intersections++;									//c = 1
			}
		}
	}

	void show_inter()																															//total = n^2
	{
		find_inter();																															//c = n^2
		for (int i = 0; i < (pAmount - 1); i++)																									//c = n
		{
			std::cout << "Segment " << i + 1 << ": " << arr[i].intersections << " intersections with previous elements" << std::endl;			//c = 1
		}
	}

	void output()																																//total = n
	{
		for (int i = 0; i < (pAmount - 1); i++)																									//c = n
		{
			std::cout << i << ": (" << arr[i].p1.x << ", " << arr[i].p1.y << ") - (" << arr[i].p2.x << ", " << arr[i].p2.y << ")\n";			//c = 1
		}
	}
};

void useLab7()													//total = n^2
{
		int amount;												//c = 1
		std::cout << "Enter amount of pairs: ";					//c = 1
		std::cin >> amount;										//c = 1
		Chain ch(amount);										//c = 1
		ch.input();												//c = n
		ch.show_inter();										//c = n^2
		system("pause");										//c = n
}