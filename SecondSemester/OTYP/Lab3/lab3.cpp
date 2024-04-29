#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<vector>
#include<cstring>

using namespace std;
//возможные типы лексем
enum Type { kw, vl, id, co, eq, ao, wl,sc };
//состояния автомата
enum AState { S, A, B, R, Q, P, R2, P2, Q2, E, E2,C,C2,R3,R4,R5, F };
//типы символом
enum Symbols { alfa, digit, lef,prav, eqq, pm, space, other,scc };

//массив для текстово обозначения типов лексем
const char* type_word[8] = { "kw","vl","id","co","eq","ao","wl","sc"};
//массив для ключевых слов
const char* key_words[6] = { "do","loop","while","and","or","not"};

//функция проверки на ключевое слово
bool searc_kw(char* lex) {
    for (int i = 0; i < 6; i++) {
        if (strcmp(lex, key_words[i]) == 0) {
            return true;
        }
    }
    return false;
}

//таблица состояний
void new_table(AState(*table)[16]) {
    table[alfa][S] = A;
    table[alfa][A] = A;
    table[alfa][B] = E2;
    table[alfa][R] = A;
    table[alfa][Q] = A;
    table[alfa][P] = A;
    table[alfa][R2] = A;
    table[alfa][P2] = A;
    table[alfa][Q2] = A;
    table[alfa][E] = E;
    table[alfa][E2] = E2;
    table[alfa][C] = A;
    table[alfa][C2] = A;
    table[alfa][R3] = A;
    table[alfa][R4] = A;
    table[alfa][R5] = A;

    table[digit][S] = B;
    table[digit][A] = A;
    table[digit][B] = B;
    table[digit][R] = B;
    table[digit][Q] = B;
    table[digit][P] = B;
    table[digit][R2] = B;
    table[digit][P2] = B;
    table[digit][Q2] = B;
    table[digit][E] = E;
    table[digit][E2] = E2;
    table[digit][C] = B;
    table[digit][C2] = B;
    table[digit][R3] = B;
    table[digit][R4] = B;
    table[digit][R5] = B;

    table[lef][S] = R;
    table[lef][A] = R;
    table[lef][B] = R;
    table[lef][R] = R3;
    table[lef][Q] = R;
    table[lef][P] = R;
    table[lef][R2] = R;
    table[lef][P2] = R;
    table[lef][Q2] = R;
    table[lef][E] = R;
    table[lef][E2] = R;
    table[lef][C] = R;
    table[lef][C2] = R;
    table[lef][R3] = R;
    table[lef][R4] = R;
    table[lef][R5] = R;

    table[prav][S] = R2;
    table[prav][A] = R2;
    table[prav][B] = R2;
    table[prav][R] = R5;
    table[prav][Q] = R2;
    table[prav][P] = R2;
    table[prav][R2] = R4;
    table[prav][P2] = R2;
    table[prav][Q2] = R2;
    table[prav][E] = R2;
    table[prav][E2] = R2;
    table[prav][C] = R2;
    table[prav][C2] = R2;
    table[prav][R3] = R2;
    table[prav][R4] = R2;
    table[prav][R5] = R2;

    table[eqq][S] = Q;
    table[eqq][A] = Q;
    table[eqq][B] = Q;
    table[eqq][R] = Q;
    table[eqq][Q] = Q2;
    table[eqq][P] = Q;
    table[eqq][R2] = Q;
    table[eqq][P2] = Q;
    table[eqq][Q2] = Q;
    table[eqq][E] = Q;
    table[eqq][E2] = Q;
    table[eqq][C] = Q;
    table[eqq][C2] = Q;
    table[eqq][R3] = Q;
    table[eqq][R4] = Q;
    table[eqq][R5] = Q;

    table[pm][S] = P;
    table[pm][A] = P;
    table[pm][B] = P;
    table[pm][R] = P;
    table[pm][Q] = P;
    table[pm][P] = P2;
    table[pm][R2] = P;
    table[pm][P2] = P;
    table[pm][Q2] = P;
    table[pm][E] = P;
    table[pm][E2] = P;
    table[pm][C] = P;
    table[pm][C2] = P;
    table[pm][R3] = P;
    table[pm][R4] = P;
    table[pm][R5] = P;

    table[space][S] = S;
    table[space][A] = F;
    table[space][B] = F;
    table[space][R] = F;
    table[space][Q] = F;
    table[space][P] = F;
    table[space][R2] = F;
    table[space][P2] = F;
    table[space][Q2] = F;
    table[space][E] = F;
    table[space][E2] = F;
    table[space][C] =  F;
    table[space][C2] = F;
    table[space][R3] = F;
    table[space][R4] = F;
    table[space][R5] = F;

    table[other][S] = E;
    table[other][A] = E2;
    table[other][B] = E2;
    table[other][R] = E;
    table[other][Q] = E;
    table[other][P] = E;
    table[other][R2] = E;
    table[other][P2] = E;
    table[other][Q2] = E;
    table[other][E] = E;
    table[other][E2] = E2;
    table[other][C] = E;
    table[other][C2] = E;
    table[other][R3] = E;
    table[other][R4] = E;
    table[other][R5] = E;

    table[scc][S] = C;
    table[scc][A] = C;
    table[scc][B] = C;
    table[scc][R] = C;
    table[scc][Q] = C;
    table[scc][P] = C;
    table[scc][R2] = C;
    table[scc][P2] = C;
    table[scc][Q2] = C;
    table[scc][E] = C;
    table[scc][E2] = C;
    table[scc][C] = C2;
    table[scc][C2] = C;
    table[scc][R3] = C;
    table[scc][R4] = C;
    table[scc][R5] = C;
}

//струртура лексемы
struct Lex {
    char* str;
    Type type;
};

//проверка на >
bool isprav(char c) {
    return c == '>';
}
//проверка на <
bool islef(char c) {
    return c == '<';
}
//проверка на =
bool iseq(char c) {
    return c == '=';
}
//проверка на арифетические знаки
bool ispm(char c) {
    return (c == '+' || c == '-' || c == '/' || c == '*');
}
//проверка на точку с запятой
bool issc(char c) {
    return c == ';';
}
//функий для определения символа
Symbols wtfsymbol(char c) {
    if (isalpha(c)) return Symbols::alfa;
    else if (isdigit(c)) return Symbols::digit;
    else if (islef(c)) return Symbols::lef;
    else if (isprav(c)) return Symbols::prav;
    else if (ispm(c)) return Symbols::pm;
    else if (iseq(c)) return Symbols::eqq;
    else if (isspace(c) || c == '\0') return Symbols::space;
    else if (issc(c)) return Symbols::scc;
    else return Symbols::other;
}
//запись новой лексемы в вектор и определения типа лексемы
void newstrlex(Lex& lexema, char*& text, int pos, int firstpos, Type tp, vector<Lex>& result) {
    int lenght = pos - firstpos;//считаем длину лексемы
    lexema.str = new char[lenght]; //выделение памяти
    strncpy(&lexema.str[0], &text[0] + firstpos, lenght);//записываем всё в lexema
    lexema.str[lenght] = '\0';
    //определяем тип лексемы
    lexema.type = tp;
    //проверка на длину
    if (lexema.type == Type::id && lenght > 5) {
        lexema.type = Type::wl;
    }
    //проверка на макс число
    if (lexema.type == Type::vl && atoi(lexema.str) > 32767) {
        lexema.type = Type::wl;
    }
    //проверка на ключевое слово
    if (lexema.type == Type::id && searc_kw(lexema.str)) {
        lexema.type = Type::kw;
    }

    result.push_back(lexema);//добаляем в вектор с результами
}
//анализатор
void Steps(char* text, vector<Lex>& result, AState (*state_table)[16]) {
    int pos = 0; //позиция в тексте
    AState state = AState::S; //начальное состояние
    AState prevstate = state; //предыдущие состояние
    Lex lexema; //лексема
    int firstpos; //начало лексемы
    //идем по файлу
    do {
        //текущий символ
        char curChar = text[pos];
        //проверка на начало лексемы
        if (state == AState::S && !isspace(curChar)) {
            firstpos = pos;
        }
        //переход по таблице состояний
        prevstate = state;
        state = state_table[wtfsymbol(curChar)][state];

        //запись лексемы
        if (prevstate != AState::S && state != AState::S && prevstate != state && state != AState::E2 && state != AState::R5) {
            int temppos = firstpos; //временная переменная для позиции в лексеме
            firstpos = pos;
            //запись нужной лексемы
            switch (prevstate) {
            case A: {
                newstrlex(lexema, text, pos, temppos, Type::id, result); //если индификатор
                break;
            }
            case B: {
                newstrlex(lexema, text, pos, temppos, Type::vl, result); //если константа
                break;
            }
            case AState::R:
            case AState::R2:
            case AState::R3:
            case AState::R4:
            case AState::R5:{
                newstrlex(lexema, text, pos, temppos, Type::co, result); //если сравнение
                break;
            }
            case AState::Q:
            case AState::Q2: {
                newstrlex(lexema, text, pos, temppos, Type::eq, result); //если равно
                break;
            }
            case AState::P:
            case AState::P2: {
                newstrlex(lexema, text, pos, temppos, Type::ao, result); //если арифм. знаки
                break;
            }
            case AState::E:
            case AState::E2: {
                newstrlex(lexema, text, pos, temppos, Type::wl, result); //если ошибочный символ
                break;
            }
            case AState::C:
            case AState::C2: {
                newstrlex(lexema, text, pos, temppos, Type::sc, result); //если точка с запятой
                break;
            }

            case S:
            case F:
                break;
            }
            //если конечной состояние то переходим в начальное
            if (state == AState::F) {
                state = AState::S;
            }
        }
        pos++;
    } while (text[pos - 1] != '\0');
}

//фунция для инициализации текста из файла
char* textinit(ifstream& in) {
    //узанем размер файла
    in.seekg(0, ios::end); //перемещаем в конец файла указатель
    streampos filesize = in.tellg(); //узнаем текущую позицию указателя - размер файла
    in.seekg(0, ios::beg);//перемещаем в начало файла указатель

    int size = filesize;

    //память под строку
    char* str = new char[size + 1];

    //считываем строку
    in.getline(str, size + 1, '\0');
    //закрытие файла
    in.close();

    return str;
}
//функция вывода результата
void print(vector<Lex>& ans) {
    //отрытие файлов для записи
    ofstream out("output.txt");
    //выводим каждый элемент вектора особым образом
    for (size_t i = 0; i < ans.size(); i++) {
        out << ans[i].str << "[" << type_word[ans[i].type] << "]" << ' ';
        cout << ans[i].str << "[" << type_word[ans[i].type] << "]" << ' ';
    };
    out << endl;
    cout << endl;
    //вывод всех индификаторов
    for (size_t i = 0; i < ans.size(); i++) {
        if (ans[i].type == Type::id) {
            cout << ans[i].str << ' ';
            out << ans[i].str << ' ';
        }
    }
    out << endl;
    cout << endl;
    //вывод всех констант
    for (size_t i = 0; i < ans.size(); i++) {
        if (ans[i].type == Type::vl) {
            cout << ans[i].str << ' ';
            out << ans[i].str << ' ';
        }
    }
    //закрытие файла
    out.close();
}

int main() {
    //отрытие файлов для чтения
    ifstream in("input.txt");
    if (in) {
        AState states_table[9][16];
        new_table(states_table);
        //считываение текста
        char* text = textinit(in);
        //обработка
        vector<Lex> ans;
        Steps(text, ans, states_table);
        //вывод
        print(ans);
        //очистка памяти лексем
        for (size_t i = 0; i < ans.size(); i++) {
            delete[] ans[i].str;
        }
        //очистка памяти текста
        delete[] text;
    }
}