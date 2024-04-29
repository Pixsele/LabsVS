#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<vector>
#include<cstring>

using namespace std;


enum AState { S, A, B, E, FE, F }; //состояния
enum Symbols{Digit, Alpfa, Space, Other}; //возможные варианты

bool isalpfa(char c) { //проверка на букву
		if ((c >= 'А' && c <= 'я') || c == 'ё' || c == 'Ё') {
			return true;
		}
	return false;
}

bool isspace(char c) { //проверка на пробел
	if (c == '\t' || c == ' ' || c == '\n') {
		return true;
	}
	return false;

}
Symbols check(char c) { //функция для опредения, какой сейчас вариант
	if (isdigit(c)) return Digit;
	if (isalpfa(c)) return Alpfa;
	if (isspace(c)) return Space;
	return Other;
}
//       
//		  S | A | B | E | FE | F
// 0...9  A   A   A   E
// a...Я  E   B   B   E
//   -	  S   F   FE  FE
// other  E   E   E   E
//                    

const AState state_table[4][4] = { //таблица состояний

	{A, A, A, E},
	{E, B, B, E},
	{S, F ,FE, FE},
	{E, E, E, E}
};



vector<char*> LexAnalysis(char* str) {//фукнция для обрабтки строки автоматом

	vector<char*> result;//вектор с результатом
	int pos = 0;//текущая позиция в строке
	AState state = AState::S;//текущее состояние
	char* lexema;//массив для лексемы
	int firstpos;//начало лексемы


	while (str[pos] != '\0') {


		char curChar = str[pos];

		//проверка на начало лексемы
		if (state == AState::S && curChar != ' ' && curChar != '\n' && curChar != '\t') {
			firstpos = pos;
		}

		//переход по матрице состояний
		state = state_table[check(curChar)][state];

		//если лексема не подходит, то не запоминаем её и сбасываем состояние до начала
		if (state == AState::FE) {
			state = AState::S;
		}

		//если лексема подходит, то запонимаем её и сбрасываем состояние до начала
		if (state == AState::F) {
			int lenght = pos - firstpos;//считаем длину лексемы
			lexema = new char[lenght + 1];//выделяем память под лексему
			strncpy(&lexema[0], &str[0] + firstpos, lenght);//записываем всё в lexema
			lexema[lenght] = '\0';
			result.push_back(lexema);//добаляем в вектор с результами

			state = AState::S;
		}
		pos++;
	}
	//проверяем последнею лексему, тк строка может кончиться не пробелом
	if (state == AState::A) {
		int lenght = pos - firstpos; //считаем длину лексемы
		lexema = new char[lenght + 1]; //выделяем память под лексему
		strncpy(&lexema[0], &str[0] + firstpos, lenght); //записываем всё в lexema
		lexema[lenght] = '\0';
		result.push_back(lexema); //добаляем в вектор с результами

	}
	return result;
}

int main() {
	setlocale(LC_ALL, "Russian");

	//отрытие файлов для чтения и записи
	ifstream in("input.txt");
	ofstream out("output.txt");

	//узанем размер файла
	in.seekg(0, ios::end); //перемещаем в конец файла указатель
	streampos filesize = in.tellg(); //узнаем текущую позицию указателя - размер файла
	in.seekg(0, ios::beg);//перемещаем в начало файла указатель

	int size = filesize;

	//память под строку
	char* str = new char[size + 1];

	//считываем строку
	in.read(str, size);

	str[size] = '\0';

	//запускаем функцию с автоматом
	vector<char*> ans = LexAnalysis(str);

	//выводим каждый элемент вектора и очищаем память
	for (size_t i = 0; i < ans.size(); i++) {
		cout << ans[i] << ' ';
		out << ans[i] << ' ';

		delete[] ans[i];
	}

	//очищаем память строки
	delete[] str;

	//закрытие файлов
	in.close();
	out.close();
}