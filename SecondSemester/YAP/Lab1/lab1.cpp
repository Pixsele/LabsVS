#include<iostream>
#include<fstream>

using namespace std;

//функция для считывания текста из файла
double* text_from_file(ifstream& in, int& count) {

	//узанем размер файла
	in.seekg(0, ios::end); //перемещаем в конец файла указатель
	streampos filesize = in.tellg(); //узнаем текущую позицию указателя - размер файла
	in.seekg(0, ios::beg);//перемещаем в начало файла указатель

	int size = filesize;

	//массив для текста 
	char* res = new char[size];
	res[size - 1] = 0;

	//переменная для флага пробела
	bool is_space = true;

	//посимвольно считываем текст из файла
	for (int i = 0; i < size; i++) {
		char c = in.get();
		res[i] = c;
		//если встретился пробел и символ рядом то к количество чисел прибавляем +1
		if (c == ' ') {
			is_space = true;
		}
		else if (is_space) {
			count += 1;
			is_space = false;
		}
	}

	//выделяем память для массива чисел
	double* m = new double[count];

	//позиция в массиве m
	int now_count = 0;

	char* digs = new char[size]; //выделяем память для наших чисел
	int cur = 0; //текущая позиция в digs
	for (int i = 0; i < size; i++) {
		digs[cur] = res[i];//добавляем новый символ в массив
		if (digs[cur] == ' ' || digs[cur] == '\t' || digs[cur] == '\n') { //проверка на конец числа
			if ((isdigit(digs[0]) || digs[0] == '-')) {
				digs[cur] = 0; //заканчиваем массив числа
				m[now_count++] = atof(digs); //переводим в double и добавляем в массив чисел
				cur = 0; //обнуляем позицию
				delete[] digs;//очищяем память
				digs = new char[size];//выдялем память для следующего числа
			}
			else {
				cur = 0; //иначе обнуляем позицию в digs
			}
		}
		else { //если не конец, то увеличиваем позицию в digs
			cur++;
		}
	}
	//проверяем последние слово
	if (cur > 0) {
		digs[cur] = 0;//заканчиваем массив числа
		m[now_count] = atof(digs);//переводим в double и добавляем в массив чисел
	}

	delete[] digs; //очищаем память для последнего digs

	delete[] res; // очищаем память для массива с текстом

	return m;
}


double summator(double* m, int count) {

	double res = 0;
	double d = m[0];// по условию задания b

	for (int i = 1; i < count; i++) { 
		if (m[i] < 0 && m[i] <= d) {//проверка на условие задания
			res += m[i] * m[i];//добавляем квадрат числа к ответу
		}
	}

	return res;
}


int main() {

	//отрытие файлов для чтения и записи
	ifstream in("input.txt");
	ofstream out("output.txt");



	//cчитываем текст из файла
	int count = 0;
	//объевляем и инициализируем массив с числами
	double* mass = text_from_file(in, count);
	//считаем ответ
	double result = summator(mass, count);

	delete[] mass;//очищаем память для массива чисел

	long long diff = result;
	//проверяем является ли числом int для корректного вывода 
	if (result == diff) {
		cout << diff;
		out << diff;
	}
	else {
		cout << result;
		out << result;
	}

}