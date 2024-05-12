#include<iostream>
#include<fstream>
#include<cmath>

using namespace std;

class RGB {
private:
	//Данные о цвете в формате RGB(red,green,blue)
	double red;
	double green;
	double blue;

	//Функция перехода
	double transfer_function(double color) {
		//Нормализуем данные от 0 до 1
		color = color / 255;
		//Вычисляем новый цвет по формуле
		if (color > 0.04045) {
			color = pow((color + 0.055) / 1.055, 2.4);
		}
		else {
			color = color / 12.92;
		}
		return color;
	}
public:

	//конструктор по умолчанию(по умолчанию белый цвет)
	RGB() {
		this->red = 255;
		this->green = 255;
		this->blue = 255;
	}
	//конструктор инициализации объекта, принимает параметры для каждого цвета
	RGB(double r, double g, double b) {
		this->red = r;
		this->green = g;
		this->blue = b;
	}
	//конструктор копирования, копирует каждый цвет
	RGB(const RGB& other) {
		this->red = other.red;
		this->green = other.green;
		this->blue = other.blue;
	}
	//деструктор
	~RGB() {};

	//перегрузка операции сложения
	RGB operator+(const RGB& other) {
		//складывает каждый цвет
		double red = this->red + other.red;
		double green = this->green + other.green;
		double blue = this->blue + other.blue;
		//объявляем и инициализурем новый объект с полученными данными, данные нормализируем в диапазоне(0 <= x <= 255)
		RGB result(255*(red>255) + (red<=255) * red, 255 * (green > 255) + (green <= 255) * green, 255 * (blue > 255) + (blue <= 255) * blue);
		return result;
	}
	//перегрузка операции вычитания
	RGB operator-(const RGB& other) {
		//вычитаем каждый цвет
		double red = this->red - other.red;
		double green = this->green - other.green;
		double blue = this->blue - other.blue;
		//объявляем и инициализурем новый объект с полученными данными, данные нормализируем в диапазоне(0 <= x <= 255)
		RGB result((red > 0) * red + 0, (green > 0) * green + 0, (blue > 0) * blue + 0);
		return result;
	}
	//перегрузка операции присваивания
	RGB& operator=(RGB& other) {
		//копируем каждый цвет
		this->red = other.red;
		this->green = other.green;
		this->blue = other.blue;
		//возвращаем ссылку на текущий объект
		return *this;
	}
	//перегрузки операции сравниния на основе яркости цвета(red + green + blue)/3
	//Перегрузка операции >
	bool operator>(const RGB& other) {
		return(this->red + this->green + this->blue) / 3 > (other.red + other.green + other.blue) / 3;
	}
	//Перегрузка операции <
	bool operator<(const RGB& other) {
		return (this->red + this->green + this->blue) / 3 < (other.red + other.green + other.blue) / 3;
	}
	//Перегрузка операции >=
	bool operator>=(const RGB& other) {
		return (this->red + this->green + this->blue) / 3 >= (other.red + other.green + other.blue) / 3;
	}
	//Перегрузка операции <=
	bool operator<=(const RGB& other) {
		return (this->red + this->green + this->blue) / 3 <= (other.red + other.green + other.blue) / 3;
	}
	//Перегрузка операции ==
	bool operator==(const RGB& other) {
		return (this->red + this->green + this->blue) / 3 == (other.red + other.green + other.blue) / 3;
	}
	//Перегрузка операции !=
	bool operator!=(const RGB& other) {
		return !(*this == other);
	}
	//Переход из одного цветого пространства в другое
	//Из RGB в sRGB
	RGB convert_to_sRGB() {
		//Преобразуем данные при помощи переходной функции
		double S_red = transfer_function(this->red);
		double S_green = transfer_function(this->green);
		double S_blue = transfer_function(this->blue);
		//Создаем новый объект и переводи данные в формат от 0 до 255
		RGB result(S_red * 255, S_green * 255, S_blue * 255);
		return result;
	}
	//Перегрузка оператора ввода из консоли
	friend istream& operator>>(istream& in, RGB& CurColor) {
		in >> CurColor.red >> CurColor.green >> CurColor.blue;
		return in;
	}
	//Перегрузка оператора вывода в консоль
	friend ostream& operator<<(ostream& out, RGB& CurColor) {
		//Вывод в красивом формате
		out << "Color (" << CurColor.red << "," << CurColor.green << "," << CurColor.blue << ")" << endl;
		return out;
	};
	//Перегрузка оператора ввода из файла
	friend ifstream& operator>>(ifstream& in, RGB& CurColor) {
		in >> CurColor.red >> CurColor.green >> CurColor.blue;
		return in;
	}
	//Перегрузка оператора вывода в файл
	friend ofstream& operator<<(ofstream& out, RGB& CurColor) {
		//Вывод в красивом формате
		out << "Color (" << CurColor.red << "," << CurColor.green << "," << CurColor.blue << ")" << endl;
		return out;
	};
};

int main() {
	//Открытие файлов
	ifstream in("input.txt");
	ofstream out("output.txt");

	//Проверка на открытие
	if (in) {
		//Считывем ключ
		int key;
		in >> key;

		//1 - конструктор по умолчанию
		//2 - конструктор инициалиазации
		//3 - конструктор копирования
		//4 - Сложение цветов
		//5 - Вычитание цветов
		//6 - Присваивание
		//7 - Операция >
		//8 - Переход в другое цветовое пространство
		
		//Переход по нужному ключу
		switch (key) {
		case 1: 
		{
			RGB color;
			out << color;
			cout << color;
			break;
		}
		case 2: 
		{
			double r, g, b;
			in >> r >> g >> b;
			RGB color(r, g, b);
			out << color;
			cout << color;
			break; 
		}
		case 3: 
		{
			RGB color;
			in >> color;
			RGB color2(color);
			out << color;
			cout << color;
			out << color2;
			cout << color2;
			break; 
		}
		case 4: 
		{
			RGB color;
			RGB color1;
			in >> color >> color1;
			cout << color << color1;
			out << color << color1;
			RGB result = color + color1;
			cout << result;
			out << result;
			break;
		}
		case 5:
		{
			RGB color;
			RGB color1;
			in >> color >> color1;
			cout << color << color1;
			out << color << color1;
			RGB result = color - color1;
			cout << result;
			out << result;
			break;
		}
		case 6: 
		{
			RGB color;
			in >> color;
			cout << color;
			out << color;
			RGB result = color;
			cout << result;
			out << result;
			break;
		}
		case 7: 
		{
			RGB color, color1;
			in >> color >> color1;
			bool result = color > color1;
			if (result) {
				cout << color << "is greater than" << endl << color1;
				out << color << "is greater than" << endl << color1;
			}
			else {
				cout << color << "is less than or equal to"<< endl << color1;
				out << color << "is less than or equal to" << endl << color1;
			}
			break;
		}
		case 8: 
		{
			RGB color;
			in >> color;
			RGB result = color.convert_to_sRGB();
			cout << result;
			out << result;
			break;
		}
		}
	}
	//Закрытие файлов
	in.close();
	out.close();
}