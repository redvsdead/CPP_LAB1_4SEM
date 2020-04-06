
#include "pch.h" 
#include <iostream>
#include "main_utils.h"

//задача B_8
//B - std::deque
//8 - прибавить к каждому элементу первое нечетное по модулю число
//до - сокращенно двусторонняя очередь
//шаблон до и вспомогательные методы описаны в мейн_утилс

//мейн меню
void menu()
{
	cout << "The main task is to add the first odd number to each deque element" << endl;
	cout << endl;
	cout << endl;
	cout << "If you want to:" << endl;
	cout << " - fill the file with the numbers - press 1" << endl; 
	cout << " - full the queue using the textfile - press 2" << endl;
	cout << " - fulfill the main task - press 3" << endl;
	cout << " - fulfill the main task (for the queue section) - press 4" << endl;
	cout << " - fulfill the main task (using _transform_) - press 5" << endl;
	cout << " - fulfill the main task (using _for_each_) - press 6" << endl;
	cout << " - clear the queue - press 7" << endl;
	cout << " - quit - press 0" << endl;
	cout << endl;
	cout << endl;
}

//главная программа
int main()
{
	setlocale(LC_ALL, "Russian");
	bool quit = false;
	char c;
	MyDeque<int> IntDQ;
	fstream f;
	f.open("testfile.txt");
	while (!quit)
	{
		menu();
		cout << "Your choice is: ";
		cin >> c;
		cin.get();
		switch (c)
		{
		case '0':
			quit = true;
			break;
		case '1':
			cout << "If you want to use _generate_ - press 1" << endl;
			cout << "If you want the numbers to be generated randomly - press 2" << endl;
			cout << endl;
			cout << endl;
			char c1;
			cout << "Your choice is: ";
			cin >> c1;
			cin.get();
			switch (c1)
			{
			case '1':
				f = MyDeque<int>::FillFile("testfile.txt", 9, 15);
				cout << "The file was filled with random numbers." << endl;
				cout << endl;
				cout << endl;
				break;
			case '2':
				f = MyDeque<int>::FillFile2("testfile.txt", 9, 15);
				cout << "The file was filled with random numbers." << endl;
				cout << endl;
				cout << endl;
				break;
			}
			break;

		case '2':
			IntDQ.DQ = MyDeque<int>::FillContainer(f);
			cout << "The queue was filled with the numbers from the file:" << endl;
			IntDQ.Show();
			cout << endl;
			cout << endl;
			break;

		case '3':			
			IntDQ.DQ = MyDeque<int>::modify(IntDQ.DQ);
			cout << "The queue was modifyed:" << endl;
			IntDQ.Show();
			cout << endl;
			cout << endl;
			break;

		case '4':			
			IntDQ.DQ = MyDeque<int>::modify(IntDQ.DQ.begin() + 1, IntDQ.DQ.begin() + 3, IntDQ.DQ);
			cout << "The queue was modifyed:" << endl;
			IntDQ.Show();
			cout << endl;
			cout << endl;
			break;

		case '5':			
			IntDQ.Func_transform();
			cout << "The queue was modifyed:" << endl;
			IntDQ.Show();
			cout << endl;
			cout << endl;
			break;

		case '6':			
			IntDQ.Foreach();
			cout << "The queue was modifyed:" << endl;
			IntDQ.Show();
			cout << endl;
			cout << endl;
			break;

		case '7':
			IntDQ.Clear();
			cout << "The queue is clear now" << endl;
			cout << endl;
			cout << endl;
			break;
		default:
			cout << "Warning: you entered the number which is out of [0 ; 9] range. Try again." << endl;
		}
	}
}