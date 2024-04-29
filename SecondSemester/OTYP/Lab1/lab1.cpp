#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

//функция для обработки текста
vector<char*> processText(char* text, int size) {
	vector<char*> list; //вектор для слов
	char* word = new char[size]; //массив для слова
	int cur = 0; //переменная для текущей позиции в слове
	for (int i = 0; i < size; i++) {
		//добавляем новый элемент в слово
		word[cur] = text[i];
		//если найдем пробел, значит слово закончилось, иначе продолжаем увеличиваем указатель
		if (word[cur] == ' ' || word[cur] == '\t' || word[cur] == '\n') {
			// проверка на то, что слово начинается и заканчивается на цифру
			if (isdigit(word[0]) && isdigit(word[cur - 1])) {
				//заканчиваем слово
				word[cur] = 0;
				//добавляем слово в список
				list.push_back(word);
				cur = 0;
				word = new char[size];
			}
			else {
				cur = 0;
			}
		}
		else {
			cur++;
		}
	}
	//проверяем последнее слово в файле
	if (isdigit(word[0]) && isdigit(word[cur - 1])) {
		word[cur] = 0;

		list.push_back(word);

	}
	else {
		//если слово не подходит по условию, то очищаем память
		delete[] word;
	}
	return list;

}
//функция для считывания текста из файла
char* text_from_file(ifstream& input,int size) {
	char* res = new char[size];
	res[size - 1] = 0;
	//посимвольно читаем файл
	for (int i = 0; i < size;i++) {
		char c = input.get();
		res[i] = c;
	}
	return res;
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
	//cчитываем текст из файла
	char* text = text_from_file(in, size);
	//обрабатываем текст
	vector<char*> list = processText(text, size);
	int size_list = list.size();
	//вывод в файл и на консоль результата
	for (int i = 0; i < size_list; ++i) {
		cout << list[i] << ' ';
		out << list[i] << ' ';
	}
	//очистка памяти слов
	for (int i = 0; i < size_list; ++i) {
		delete[] list[i];
	}
	//очистка памяти для текста
	delete[] text;

	//закрываем файлы
	in.close();
	out.close();
}