#pragma once
#include <deque>
#include <fstream>
#include <algorithm>
#include <iterator>

using namespace std;

template <typename T> class MyDeque
{
public:
	deque<T>  DQ; //шаблон двусторонней очереди


	MyDeque(int size) :DQ(size)
	{

	}

	MyDeque() :DQ() {}


	//вывод до на экран
	void Show()
	{
		int i = 0;
		int N = DQ.size();
		cout << "The queue is: ";
		while (i < N)
		{
			cout << DQ[i];
			if (i != N - 1)
				cout << ",  ";
			++i;
		}
		cout << endl;
	}

	//добавление элементов через пробел и вывод получившейся до
	void Add()
	{
		cout << "Enter the dequeue elements separating them with spaces :   ";
		T tmp;
		int i = 0;
		while ((cin.peek() != '\n') && (cin >> tmp))
		{
			DQ.push_back(tmp);
			++i;
		}
		cout << endl;
		Show();
	}

	//проверка до на пустоту
	bool IsEmpty()
	{
		return DQ.size() == 0;
	}


	//очистка до
	void Clear()
	{
		DQ.clear();
	}

	//функциональный объект генерации
	class Gen
	{
		const char *FileName; //текстовый файл, куда будут сохранять
		int M; //модуль диапазона

	public:

		Gen(const char *_FileName, int _M)
		{
			FileName = _FileName;
			M = _M;
		}

		int operator()() //перегрузка () аналогично gen_one_number
		{
			fstream f(FileName, ios_base::app);
			int plusOrMinus;
			int result;
			result = (rand() % (M + 1));
			plusOrMinus = rand() % 2;
			if (plusOrMinus == 1)
				result = result * (-1);
			f << result;
			f << " ";
			f.close();
			return result;
		}
	};

	//запускает generate для данной до
	static fstream  FillFile(const char *FileName, int N, int M)
	{
		deque<int> A(N);
		generate(A.begin(), A.begin() + N, Gen(FileName, M));
		return fstream(FileName);
	}

	//вспомогательный метод - генерация одного рандомного числа в пределах -м..м и его запись в файл
	static void Gen_one_number(const char *FileName, int M)
	{
		fstream f(FileName, ios_base::app);
		int plusOrMinus;
		int result;
		plusOrMinus = rand() % 2;  //генерирует знак числа
		result = rand() % (M + 1);	//генерирует модульное значение
		if (plusOrMinus == 1)
			result = result * (-1);
		f << result;
		f << " ";
		f.close();
	}

	//заполнение до n случайных чисел и ее запись в файл (пункт 1 задания)
	static fstream FillFile2(const char *FileName, int N, int M)
	{
		for (int i = 0; i < N; ++i)
			Gen_one_number(FileName, M);
		return fstream(FileName);
	}

	//заполнение до числами из файла (пункт 2 задания), возвращает измененный контейнер до
	static deque<T> FillContainer(fstream &f)
	{
		deque<T> DQ;
		T tmp;
		int i = 0;
		bool range_control = true;
		while (!f.eof() && range_control)
		{

			f >> tmp;
			DQ.push_back(tmp);
			++i;
		}
		return DQ;
	}

	//основная задача (вспомогательное): поик первого нечетного в заданных пределах
	static int search_odd(deque<int>::iterator a, deque<int>::iterator b, deque<T> DQ)
	{
		bool range_control = true;
		deque<int>::iterator i = a;
		while (range_control && abs(*i) % 2 == 0)
		{
			++i;
			if (i == b + 1)
				range_control = false;
		}
		if (!range_control)
		{
			cout << "Warning: the queue doesn't contain odd numbers." << endl;
			return 0;
		}
		return *i;
	}

	//основное задание: прибавляет ко всем элементам первое нечетное число, если оно есть
	static deque<T> modify(deque<T> DQ)
	{
		deque<int>::iterator a = DQ.begin();
		deque<int>::iterator b = DQ.end() - 1;
		int odd = search_odd(a, b, DQ);
		deque<int>::iterator i = DQ.begin();
		if (odd != 0) {
			while (i != DQ.end())
			{
				*i += odd;
				++i;
			}
		}
		return DQ;
	}

	//перегруженный модифай: прибавляет число к элементам в заданном итераторами отрезке
	static deque<T> modify(deque<int>::iterator a, deque<int>::iterator b, deque<T> &_DQ)
	{
		int odd = search_odd(a, b, _DQ);
		deque<int>::iterator i = a;
		while (i != b + 1)
		{
			*i += odd;
			++i;
		}
		return _DQ;
	}

	//функциональный оператор для transform
	class Transform
	{
		int odd;

	public:

		Transform(deque<T> DQ)
		{
			odd = search_odd(DQ.begin(), DQ.end() - 1, DQ);
		}

		int operator()(int &x) //перегрузка () для transform, аналогичная modify
		{
			return x += odd;
		}


	};

	//запускает transform для данной очереди
	void Func_transform()
	{
		transform(DQ.begin(), DQ.end(), DQ.begin(), Transform(DQ));
	}

	//функциональный оператор для for_each
	class Foreach_
	{
		int odd;

	public:

		Foreach_(deque<T> DQ)
		{
			odd = search_odd(DQ.begin(), DQ.end() - 1, DQ);
		}

		int operator()(int &x)  //перегрузка () для for_each, аналогичная modify
		{
			return x += odd;
		}

	};

	//этот метод просто запускает for_each для данной очереди
	void Foreach()
	{
		for_each(DQ.begin(), DQ.end(), Foreach_(DQ));
	}
};

