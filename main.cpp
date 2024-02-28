#include <iostream>
#include <functional> //описание классов функторов для программ
#include <algorithm>
#include <vector>

//1
int Summ(int a, int b)
{
	return a + b;
}
int Multiply(int a, int c)
{
	return a * c;
}

//2. как бы выглядела функция принимающая в себя другую функцию

using FunctionName = int (*)(int, int); //переопределение типа данных функции
typedef int (*NewName)(int, int); //или можно сделать так, тело взяли из мейн



void PrintOperation(int Jane, int Jacob, FunctionName Alg) //заполнили ее Alg
{
	std::cout << "Our operation take params: \n" << 
		"\tJane - " << Jane << '\n' << 
		"\tJacob - " << Jacob << '\n' << 
		"With result " << Alg(Jane, Jacob);
}
//3
class Functor
{
public:
	Functor(int val) :num(val) {}

	void operator() (int& val) 
	{
		val = num;
	}
private:
	int num;
};

//алгоритм обработки массивов
void OperateArray(int* arr, int length, std::function<void(int&)> Alg) //не возвращает ничего, принимает ссылки на инты
{
	for (int i = 0; i < length; i++)
	{
		Alg(arr[i]);
	}
}

void Fo2(int& j)
{
	j = 9;
}

int mainEx() {
	setlocale(LC_ALL, "Russian");
	int n; 
	//1
	int a{ 5 }, b{ 9 };
	std::cout << Summ << " with " << a << " " << b << " args - " << Summ(a,b) << '\n';
	std::cout << Multiply << " with " << a << " " << b << " args - " << Multiply(a, b) << "\n\n";
	
	auto pFunc = Summ; //выводит тип данных 
	int (*pFunc2)(int, int) { Summ }; // что делает auto
	pFunc = Multiply;
	pFunc2 = Summ;

	//2
	PrintOperation(2, 4, Multiply);
	std::cout << "\n";
	PrintOperation(a, b, pFunc2); //можем использовать все что угодно
	std::cout << "\n\n";

	//3
	int* arr = new int[6] {};
	OperateArray(arr, 6, Fo2);
	for (int i = 0; i < 6; i++)
	{
		std::cout << arr[i];
	}
	std::cout << std::endl;
	Functor funtic(4);
	OperateArray(arr, 6, funtic);
	for (int i = 0; i < 6; i++)
	{
		std::cout << arr[i];
	}

	return 0;
}






#include <random>

bool More(int a, int b) //чтобы было задом наперед
{
	return a > b;
}

struct Runner
{
	int id;
	double result;
	std::string Name;
};

int main() {
	setlocale(LC_ALL, "Russian");

	//создали коллекцию
	std::vector<int> arr; 
	for (int i = 0; i < 20; i++)
	{
		arr.push_back(i + 1);
	}
	//перемешиваем
	std::shuffle(arr.begin(), arr.end(), std::random_device()); //шафл перемешивает элементы коллекции в произвольном порядке с помощью методов коллекции, те что в скобочках
	for (auto& j : arr)
	{
		std::cout << j << ", ";
	}
	std::cout << "\b\b \n";

	//мортирует коллекцию по возрастанию если знает как сравнить соседние элементы на меньше. В остальных случаях требуется передать правила сравнения
	std::sort(arr.begin(), arr.end(), More); //море чтобы сортировка была от большего к меньшему
	for (auto& j : arr)
	{
		std::cout << j << ", ";
	}
	std::cout << "\b\b \n" << "\n";

	//сортировка пацанов по параметрам
	std::vector<Runner> lBoard
	{
		{1,123.4, "Joe"},
		{2,122.6, "Ken"},
		{4,115.3, "Tomas"},
		{6,145.7,"Alex"},
		{7,115.1,"Gregory"}
	};
	std::cout << "сортировка по именам\n";
	for (const auto& j : lBoard)
	{
		std::cout << "ID: " << j.id << ' ';
		std::cout << "Name: " << j.Name << ' ';
		std::cout << "Result: " << j.result << '\n';
	}
	std::cout << "\n";


	//анонимные функции - лямбда выражения
	auto funk = [](int a) ->bool
		{
			if (a % 2)
			{
				return a % 2;
			}
			else
			{
				return false;
			}
		};
	std::cout << funk(4) << "\n\n";

	//сортировка лямбдой
	std::sort(lBoard.begin(), lBoard.end(), 
		[](const Runner& a, const Runner& b)->bool
		{
			return a.result < b.result;
		});
	std::cout << "сортировка по числам\n";
	for (const auto& j : lBoard)
	{
		std::cout << "ID: " << j.id << ' ';
		std::cout << "Name: " << j.Name << ' ';
		std::cout << "Result: " << j.result << '\n';
	};


	return 0;
}