// LW6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <exception>
#include <string>
#include <vector>

class GeomProgress_Except :public std::invalid_argument {
private:
	double first_element;
	double step;
	double *p;
	int n;
public:
	GeomProgress_Except(std::string name_of_except, double f_e, double s, double* parr, int num) :std::invalid_argument(name_of_except) {
		first_element = f_e;
		step = s;
		p = parr;
		n = num;
	}
	void print() {
		double *p1 = p;
		std::cout << "Exception: " << what() << std::endl << "Data: " << std::endl << first_element << std::endl << step << std::endl << n << std::endl;
		for (int i = 0; i < n; i++) { std::cout << *p1 << "; "; p1++; }
		std::cout << std::endl;
	}
};

class Array_GeomProgress 
{
private:
	double first_element;
	double step;
	int n;
	double *p;
public:
	Array_GeomProgress() {
		first_element = step = n = 0;
	}
	Array_GeomProgress(double f_e, double s, int num, double *parr) {
		first_element = f_e;
		step = s;
		n = num;
		p = parr;
		for (int i = 0; i < (n-1); i++) {
			double *p1 = parr; double *p2 = ++parr;
			if (*p2 != (*p1 * step)) {
				throw GeomProgress_Except("Invalid data set", first_element, step, p, n);
			}
		}
	}
};

int main()
{
	std::cout << "First exapmle:" << std::endl;
	try {
		double p[]={ 1, 1.5, 2.25, 1 };
		Array_GeomProgress Arr = Array_GeomProgress(1., 1.5, 4, &p[0]);
		std::cout << "All correct";
	}
	catch (GeomProgress_Except ex) {
		ex.print();
	}
	std::cout << "Second exapmle:" << std::endl;
	try {
		double p[] = { 1, 1.5, 2.25 };
		Array_GeomProgress Arr = Array_GeomProgress(1., 1.5, 3, &p[0]);
		std::cout << "All correct";
	}
	catch (GeomProgress_Except ex) {
		ex.print();
	}
	return 0;
}
