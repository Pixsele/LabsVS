#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<vector>
#include<cstring>

using namespace std;

enum Type { kw, vl, id, co, eq, ao, wl,sc };
enum AState { S, A, B, R, Q, P, R2, P2, Q2, E, E2,Rq,C,C2, F };
enum Symbols { alfa, digit, lef,prav, eqq, pm, space, other,scc };


const char* type_word[8] = { "kw","vl","id","co","eq","ao","wl","sc"};
const char* key_words[6] = { "do","loop","while","and","or","not"};

bool searc_kw(char* lex) {
    for (int i = 0; i < 6; i++) {
        if (strcmp(lex, key_words[i]) == 0) {
            return true;
        }
    }
    return false;
}


const AState state_table[9][14] = {
    {A,A,E2,A,A,A,A,A,A,E,E2,A,A,A},
    {B,A,B,B,B,B,B,B,B,E,E2,B,B,B},
    {R,R,R,R2,R,R,R,R,R,R,R,R,R,R},
    {R2,R2,R2,R,R2,R2,R,R2,R2,R2,R2,R2,R2,R2},
    {Q,Q,Q,Rq,Q2,Q,Rq,R,Q,Q,Q,Q,Q,Q},
    {P,P,P,P,P,P2,P,P,P,P,P,P,P,P},
    {S,F,F,F,F,F,F,F,F,F,F,F,F,F},
    {E,E2,E2,E,E,E,E,E,E,E,E2,E,E},
    {C,C,C,C,C,C,C,C,C,C,C,C,C2,C}
};

struct Lex {

    char* str;
    Type type;

};

bool isprav(char c) {
    return c == '>';
}


bool islef(char c) {
    return c == '<';
}

bool iseq(char c) {
    return c == '=';
}

bool ispm(char c) {
    return (c == '+' || c == '-' || c == '/' || c == '*');
}
bool issc(char c) {
    return c == ';';
}

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

void newstrlex(Lex& lexema, char*& text, int pos, int firstpos, Type tp, vector<Lex>& result) {
    int lenght = pos - firstpos;//считаем длину лексемы
    lexema.str = new char[lenght];
    strncpy(&lexema.str[0], &text[0] + firstpos, lenght);//записываем всё в lexema
    lexema.str[lenght] = '\0';


    lexema.type = tp;

    if (lexema.type == Type::id && lenght > 5) {
        lexema.type = Type::wl;
    }

    if (lexema.type == Type::vl && atoi(lexema.str) > 32767) {
        lexema.type = Type::wl;
    }

    if (lexema.type == Type::id && searc_kw(lexema.str)) {
        lexema.type = Type::kw;
    }

    result.push_back(lexema);//добаляем в вектор с результами
}

vector<Lex> Steps(char* text) {
    vector<Lex> result;
    int pos = 0;
    AState state = AState::S;
    AState prevstate = state;
    Lex lexema;
    int firstpos;
    do {
        char curChar = text[pos];

        if (state == AState::S && !isspace(curChar)) {
            firstpos = pos;
        }
        prevstate = state;
        state = state_table[wtfsymbol(curChar)][state];

        if (prevstate != AState::S && state != AState::S && prevstate != state && state != AState::E2 && state != AState::Rq) {
            int temppos = firstpos;
            firstpos = pos;
            switch (prevstate) {
            case A: {
                newstrlex(lexema, text, pos, temppos, Type::id, result);
                break;
            }
            case B: {
                newstrlex(lexema, text, pos, temppos, Type::vl, result);
                break;
            }
            case AState::R:
            case AState::R2: {
                newstrlex(lexema, text, pos, temppos, Type::co, result);
                break;
            }
            case AState::Q:
            case AState::Q2: {
                newstrlex(lexema, text, pos, temppos, Type::eq, result);
                break;
            }
            case AState::P:
            case AState::P2: {
                newstrlex(lexema, text, pos, temppos, Type::ao, result);
                break;
            }
            case AState::E:
            case AState::E2: {
                newstrlex(lexema, text, pos, temppos, Type::wl, result);
                break;
            }
            case AState::Rq: {
                newstrlex(lexema, text, pos, temppos, Type::co, result);
                break;
            }
            case AState::C:
            case AState::C2: {
                newstrlex(lexema, text, pos, temppos, Type::sc, result);
                break;
            }

            case S:
            case F:
                break;
            }
            if (state == AState::F) {
                state = AState::S;
            }
        }
        pos++;

    } while (text[pos - 1] != '\0');

    return result;
}


char* textinit() {
    //отрытие файлов для чтения и записи
    ifstream in("input.txt");

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

    in.close();

    return str;
}

void print(vector<Lex>& ans) {

    ofstream out("output.txt");
    vector<Lex> s;
    //выводим каждый элемент вектора и очищаем память
    for (size_t i = 0; i < ans.size(); i++) {
        out << ans[i].str << "[" << type_word[ans[i].type] << "]" << ' ';
        cout << ans[i].str << "[" << type_word[ans[i].type] << "]" << ' ';
    };
    out << endl;
    cout << endl;
    for (size_t i = 0; i < ans.size(); i++) {
        if (ans[i].type == Type::id) {
            cout << ans[i].str << ' ';
            out << ans[i].str << ' ';

        }
    }
    out << endl;
    cout << endl;
    for (size_t i = 0; i < ans.size(); i++) {
        if (ans[i].type == Type::vl) {
            cout << ans[i].str << ' ';
            out << ans[i].str << ' ';

        }
    }
    out.close();

}

int main() {
    char* text = textinit();

    vector<Lex> ans = Steps(text);

    print(ans);

    for (size_t i = 0; i < ans.size(); i++) {
        delete ans[i].str;
    }
}