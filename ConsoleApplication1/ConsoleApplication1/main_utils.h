#pragma once
#include <deque>
#include <fstream>
#include <algorithm>
#include <iterator>

using namespace std;

template <typename T> class MyDeque
{
public:
	deque<T>  DQ; //������ ������������ �������


	MyDeque(int size) :DQ(size)
	{

	}

	MyDeque() :DQ() {}


	//����� �� �� �����
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

	//���������� ��������� ����� ������ � ����� ������������ ��
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

	//�������� �� �� �������
	bool IsEmpty()
	{
		return DQ.size() == 0;
	}


	//������� ��
	void Clear()
	{
		DQ.clear();
	}

	//�������������� ������ ���������
	class Gen
	{
		const char *FileName; //��������� ����, ���� ����� ���������
		int M; //������ ���������

	public:

		Gen(const char *_FileName, int _M)
		{
			FileName = _FileName;
			M = _M;
		}

		int operator()() //���������� () ���������� gen_one_number
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

	//��������� generate ��� ������ ��
	static fstream  FillFile(const char *FileName, int N, int M)
	{
		deque<int> A(N);
		generate(A.begin(), A.begin() + N, Gen(FileName, M));
		return fstream(FileName);
	}

	//��������������� ����� - ��������� ������ ���������� ����� � �������� -�..� � ��� ������ � ����
	static void Gen_one_number(const char *FileName, int M)
	{
		fstream f(FileName, ios_base::app);
		int plusOrMinus;
		int result;
		plusOrMinus = rand() % 2;  //���������� ���� �����
		result = rand() % (M + 1);	//���������� ��������� ��������
		if (plusOrMinus == 1)
			result = result * (-1);
		f << result;
		f << " ";
		f.close();
	}

	//���������� �� n ��������� ����� � �� ������ � ���� (����� 1 �������)
	static fstream FillFile2(const char *FileName, int N, int M)
	{
		for (int i = 0; i < N; ++i)
			Gen_one_number(FileName, M);
		return fstream(FileName);
	}

	//���������� �� ������� �� ����� (����� 2 �������), ���������� ���������� ��������� ��
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

	//�������� ������ (���������������): ���� ������� ��������� � �������� ��������
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

	//�������� �������: ���������� �� ���� ��������� ������ �������� �����, ���� ��� ����
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

	//������������� �������: ���������� ����� � ��������� � �������� ����������� �������
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

	//�������������� �������� ��� transform
	class Transform
	{
		int odd;

	public:

		Transform(deque<T> DQ)
		{
			odd = search_odd(DQ.begin(), DQ.end() - 1, DQ);
		}

		int operator()(int &x) //���������� () ��� transform, ����������� modify
		{
			return x += odd;
		}


	};

	//��������� transform ��� ������ �������
	void Func_transform()
	{
		transform(DQ.begin(), DQ.end(), DQ.begin(), Transform(DQ));
	}

	//�������������� �������� ��� for_each
	class Foreach_
	{
		int odd;

	public:

		Foreach_(deque<T> DQ)
		{
			odd = search_odd(DQ.begin(), DQ.end() - 1, DQ);
		}

		int operator()(int &x)  //���������� () ��� for_each, ����������� modify
		{
			return x += odd;
		}

	};

	//���� ����� ������ ��������� for_each ��� ������ �������
	void Foreach()
	{
		for_each(DQ.begin(), DQ.end(), Foreach_(DQ));
	}
};

