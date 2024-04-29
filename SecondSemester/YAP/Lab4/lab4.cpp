#include<iostream>
#include<fstream>


//Элементы бинарного дерева
struct  TreeNode
{
    double data; //значение
    TreeNode* left; //левый потомок
    TreeNode* right; //правый потомок

    TreeNode(double value); //коснтруктор для элемента
    
};
//констурктор для элеметта
TreeNode::TreeNode(double value) {
    this->data = value;
    this->left = NULL;
    this->right = NULL;
}
//добавление нового элемента в дерево
void AddNewNode(TreeNode*& root, TreeNode* node) {
    //если существует корень, то смотрим его потомков
    if (root) {
        //рекурсивно вызываем для потомков 
        if (node->data <= root->data) {
            AddNewNode(root->left, node);
        }
        else {
            AddNewNode(root->right, node);
        }
    }
    else {
        root = node;
    }
};
//фунция для создания дерева
void LoadTree(std::ifstream& in,TreeNode*& root){
    double v;
    //считываем поочередно элементы
    while (in>>v)
    {
        //новый элемент
        TreeNode* new_node = new TreeNode(v);
        //запускаем рекурсию
        AddNewNode(root,new_node);
    }
}
//обратный обход дерева
void PrintTree(std::ofstream& out, TreeNode* tree) {
    if (tree) {
        //рекурсвино печаем элементы
        PrintTree(out, tree->left);
        PrintTree(out, tree->right);
        out << tree->data << " ";
        std::cout << tree->data << " ";
        //очистка памяти
        delete tree;
    }
}
//фунция для отражения дерева
void mirrorTree(TreeNode*& root)
{   if(root){
    //перемешаем элементы
    TreeNode* t = root->left;
    root->left = root->right;
    root->right = t;
    //рекурсивно вызываем для остальных элементов
    if (root->left)
        mirrorTree(root->left);
    if (root->right)
        mirrorTree(root->right);
   
    }
}

int main() {
    //окрытие файла для чтения
    std::ifstream in("input.txt");
    //новон дерево
    TreeNode* R = NULL;
    //создаем дерево
    LoadTree(in,R);
    //отражаем дереов
    mirrorTree(R);
    //файл для записи
    std::ofstream out("output.txt");
    //вывод элементов
    PrintTree(out,R);   
    //закрываем файлы
    in.close();
    out.close();
}