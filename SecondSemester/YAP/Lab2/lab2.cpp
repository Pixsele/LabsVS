#include<iostream>
#include<fstream>

using namespace std;

double** inizialization_m(ifstream& in, int size_1, int size_2) {

	//объявляем двумерный динимаческий массив
	double** m = new double* [size_1];

	for (int i = 0; i < size_1; i++) {
		m[i] = new double[size_2];
	}

	//проходим по каждому элементу двумерного массива
	for (int i = 0; i < size_1; i++) {
		for (int j = 0; j < size_2; j++) {
			//считываем из файла значения и инициализурем элементы массива
			in >> m[i][j];
		}
	}

	//возвращаем массив
	return m;
}

void cut_elements(double**& m, int size_1, int size_2, int b, int d) {

	//проходим по каждому элементу двумерного массива
	for (int i = 0; i < size_1; i++) {
		for (int j = 0; j < size_2; j++) {
			//если элемент меньше нижней границы, то обрезаем его до нижней границы
			if (m[i][j] < b) {
				m[i][j] = b;
			}
			//если элемент больше верхней границы, то обрезаем его до верней границы
			else if (m[i][j] > d) {
				m[i][j] = d;
			}

		}
	}
}


int main() {
	//открываем файлы для считывания и записи
	ifstream input("input.txt");
	ofstream output("output.txt");

	//объявляем и считываем из файла размеры матрицы
	int size_1, size_2;
	input >> size_1 >> size_2;
	
	//объявляем матрицу и инициализируем при помощи функции
	double** m = inizialization_m(input, size_1, size_2);

	//объявление и считываем из файла допустимые границы для элементов массива
	int b, d;
	input >> b >> d;

	//функция для обрезания элементов определенных границах
	cut_elements(m, size_1, size_2, b, d);

	//проходим по каждому элементу двумерного массива
	for (int i = 0; i < size_1; i++) {
		for (int j = 0; j < size_2; j++) {
			//выводим элемент в файл и консоль
			output << m[i][j] << ' ';
			cout << m[i][j] << ' ';

		}
	}
	//удаление двумерног массива
	for (int i = 0; i < size_1; i++) {

		delete[] m[i];
	}
	delete[] m;

	//закрываем файлы
	input.close();
	output.close();
}