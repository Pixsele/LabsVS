#include<iostream>
#include<fstream>


using namespace std;

//класс для элементов списка
class Node {
public:
	//значени элемента и указатели на следующий и предыдуший элемент
	double value = 0;
	Node* next = nullptr;
	Node* prev = nullptr;
	//конструктор по умолчанию
	Node() {};
	//конструктор со значением
	Node(double value) {
		this->value = value;
	}
};
//класс для двусвязного нециклического списка
class List {
public:
	//указатели на начало и конец списка
	Node* current = nullptr;
	Node* tail = nullptr;
	int size = 0; //размер списка
	//деконструктор
	~List() {
		while (tail) {
			Node* temp = tail->prev;
			delete tail;
			tail = temp;
			if (tail != nullptr) {
				tail->next = nullptr;
			}
		}
	}
	//конструктор
	List(){};
	//функция для добавления нода в конец списка
	void push_back(Node* newNode) {
		//если список пустой
		if (current == nullptr) {
			current = newNode;
			tail = newNode;
		}//если не пустой
		else {
			newNode->prev = tail;
			tail->next = newNode;

			tail = newNode;
		}
		//увеличиваем размер списка
		size++;
	}
	//метод для получения нода по индексу
	Node* get_node(int n) {
		Node* head = current;
		while (n--) {
			head = head->next;
		}
		return head;
	}
};

 void print(ostream& os, const List& list) {
	Node* head = list.current;
	os << list.size << " ";
	while (head) {
		os << head->value << " ";
		head = head->next;
	}
}

//функция для свапа элементов
void swap(List& list, Node* a, Node* b) {

	//если одинаковые то на выход
	if (a == b) {
		return;
	}

	//меняем хвосты списка если один из элементов хвост
	if (a == list.tail) {
		list.tail = b;
	}
	if (b == list.tail) {
		list.tail = a;
	}
	//меняем начало списка если один из элементов начало
	if (a == list.current) {

		list.current = b;
	}
	else {
		if (b == list.current) {
			list.current = a;
		}
	}

	//если элемнты рядом
	if (a->next == b || b->next == a) {
		//меняем указатели местами если они в другом порядке
		if (b->next == a) {
			Node* temp = a;
			a = b;
			b = temp;
		}
		//меняем указатели
		b->prev = a->prev;
		a->next = b->next;
		b->next = a;
		//если начало
		if (a->prev != nullptr) {
			a->prev->next = b;
		}
		//если конец
		if (a->next != nullptr) {
			a->next->prev = a;
		}
		a->prev = b;
	}
	//если элементы не рядом
	else {
		//сохраняем вспомогательные ноды
		Node* tempbn = b->next;
		Node* tempbp = b->prev;
		//меянем указатели
		b->prev = a->prev;
		//если b начало
		if (b->prev != nullptr) {
			b->prev->next = b;
		}
		b->next = a->next;
		//если b конец
		if (a->next != nullptr) {
			a->next->prev = b;
		}
		a->next = tempbn;
		a->prev = tempbp;
		//если a конец
		if (a->next != nullptr) {
			a->next->prev = a;
		}
		//если a начало
		if (a->prev != nullptr) {
			a->prev->next = a;
		}
	}
}

//построение кучи
void heapify(List& list, int n, int i)
{
	//наибольший элемент как корень
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2; 
	//если левый нод больше
	if (l < n && list.get_node(l)->value > list.get_node(largest)->value)
		largest = l;
	//если правый нод больше наибольшего
	if (r < n && list.get_node(r)->value > list.get_node(largest)->value)
		largest = r;
	//eсли самый большой нод не корень
	if (largest != i)
	{
		//cвапаем местами
		swap(list,list.get_node(i), list.get_node(largest));
		//вызов рекурсси на меньшем дереве
		heapify(list, n, largest);
	}
}
//пирамидальная сортировка
void heapSort(List& list)
{
	//узнаем размер
	int n = list.size;
	//построение кучи
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(list, n, i);
	//перебираем элементы
	for (int i = n - 1; i >= 0; i--)
	{
		//перемещаем текущий корень в конец
		swap(list,list.get_node(0), list.get_node(i));
		//вызываем процедуру heapify на уменьшенной куче
		heapify(list, i, 0);
	}
}

//удаление и вставка элемента
void InsertionElement(List& list, Node* insertNode, Node* place) {

	//удаляем элемент
	if (insertNode->next) { //если не конец
		//меняем указатели между элементами 
		insertNode->next->prev = insertNode->prev; 
		insertNode->prev->next = insertNode->next;
	}
	else {//если конец
		insertNode->prev->next = nullptr;
	}
	//вставка
	if (place == nullptr) { //если начало
		//меняем указатели
		list.current->prev = insertNode;
		insertNode->next = list.current;
		insertNode->prev = nullptr;
		list.current = insertNode;
	}
	else {//если не начало
		//меняем указатели
		place->next->prev = insertNode;
		insertNode->prev = place;
		insertNode->next = place->next;
		place->next = insertNode;
	}
}
//сортировка вставками
void InsertionSort(List& list) {

	//второй элемент по списку
	Node* node = list.current->next;

	while (node != nullptr) { //перебираем элементы

		//сохраняем до и после ноды
		Node* prev = node->prev;
		Node* temp = node->next;

		//перебор назад
		while (prev && (node->value < prev->value )) {
			prev = prev->prev;
		}
		//вызываем функцию
		InsertionElement(list, node, prev);
		//переход
		node = temp;
	}
}

int main() {

	ifstream in("input.txt"); //открываем файл для чтения
	ofstream out("output.txt"); //открываем файл для записи
	
	//считываем ключ для сортировки
	int key;
	in >> key;
	//объявляем лист
	List list;
	double value;
	//считываем элементы по очереди
	while (in >> value) {
		//создаем новый элемент
		Node* newNode = new Node(value);
		//добавляем новый элемент в конец
		list.push_back(newNode);

	}

	//свитч для сортировок
	switch (key) {
	case 0:
		//пирамидальная сортировка
		heapSort(list);
		break;
	case 1:
		//сортировка вставками
		InsertionSort(list);
		break;
	}

	//вывод листа
	print(out, list);
	print(cout, list);
	
	//закрываем файлы
	out.close();
	in.close();
}