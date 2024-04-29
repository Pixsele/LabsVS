#include<iostream>
#include<fstream>

struct Leafs
{
    int val;
    Leafs* l;
    Leafs* r;

    int GetsHieght();
};

int Leafs::GetsHieght() {
    int lev, prav;
    if (l) {
        lev = l->GetsHieght();
    }
    else {
        lev = 0;
    }

    if (r) {
        prav = r->GetsHieght();
    }
    else {
        prav = 0;
    }

    return 1 + std::min(lev, prav);
}

void AddsNew(Leafs*& root, Leafs* new_elem) {
    if (root) {
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

}


void CreateTree(std::ifstream& in,Leafs*& root){

    int v;
    //считываем поочередно элементы
    while (in>>v)
    {
        //новый элемент
        Leafs* new_node = new Leafs(v);
        //запускаем рекурсию
        AddNewNode(root,new_node);
    }
}




int main() {



}