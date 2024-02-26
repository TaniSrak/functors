#include <iostream>
#include <functional> //описание классов функторов для программ
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

int main() {
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