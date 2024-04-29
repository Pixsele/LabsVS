#include<iostream>
#include<fstream>
//лист дерева
struct Leafs
{
    //значение
    long long val;
    //левый и правый потомки
    Leafs* l;
    Leafs* r;
    //получение высоты
    int GetsHieght();
    //конструктор
    Leafs(long long c);
};
//констурктор
Leafs::Leafs(long long c) {
    this->val = c;
    this->l = nullptr;
    this->r = nullptr;
}
//функция для получения высоты
int Leafs::GetsHieght() {
    int lev, prav;
    //проверяем левого потомка
    if (l) {
        lev = l->GetsHieght();
    }
    else {
        lev = 0;
    }
    //проверяем правого потомка
    if (r) {
        prav = r->GetsHieght();
    }
    else {
        prav = 0;
    }

    return 1 + std::min(lev, prav);
}
//добавление новых элементов в дерево
void AddsNew(Leafs*& root, Leafs* new_elem) {
    //если корень не пустой
    if (root) {
        //согласно сбалансированному дерево вставляем элементы и вызываем рекурсивно функции
        if (root->l == nullptr) {
            root->l = new_elem;
        }
        else if (root->r == nullptr) {
            root->r = new_elem;
        }
        else if (root->l->GetsHieght() <= root->r->GetsHieght()) {
            AddsNew(root->l, new_elem);
        }
        else {
            AddsNew(root->r, new_elem);
        }
    }
    //если корень пустой
    else {
        root = new_elem;
    }

}
//фунция для отражения значения элементов
long long rev(long long v) {
    long long n = std::abs(v);
    long long result = 0;
    //переворачиваем
    while (n > 0) {
        result *= 10;
        result += n % 10;
        n /= 10;
    }
    //проверка на отрицательное
    if (v < 0) {
        result *= -1;
    }
    return result;
}
//фукнция для отраженения значений элементов дерева
void OborotElem(Leafs*& root)
{
    if (root){
        root->val = rev(root->val);

        if (root->l) {
            OborotElem(root->l);
        }
        if (root->r) {
            OborotElem(root->r);
        }
    }
}
//функция создания нового дерева
void CreateTree(std::ifstream& in, Leafs*& root) {

    long long v;
    //считываем значения
    while (in >> v)
    {
        //создаем элемент
        Leafs* new_node = new Leafs(v);
        //рекурсия
        AddsNew(root, new_node);
    }
}
//симметричный вывод
void out(std::ofstream& exit, Leafs*& r) {
    if (r) {
        //рекурсия для левого потомка
        out(exit,r->l);
        //вывод в консоль
        std::cout << r->val << ' '; 
        //вывод в файл
        exit << r->val << ' ';
        //рекусрия для правого потомка
        out(exit, r->r);
        //очистка памяти
        delete r;
    }
}



int main() {
    //открываем файлы
    std::ifstream in("input.txt");
    std::ofstream exit("output.txt");
    //создаем корень дерева
    Leafs* head = nullptr;
    //считываем дерево
    CreateTree(in, head);
    //выполняем отражение значений элементов дерева
    OborotElem(head);
    //симметричный обход
    out(exit,head);
    //закрываем файлы
    in.close();
    exit.close();
}