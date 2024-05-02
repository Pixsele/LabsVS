#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<vector>
#include<cstring>

using namespace std;
//возможные типы лексем
enum Type { kw, vl, id, co, eq, ao, wl, sc };
//состояния автомата
enum AState { S, A, B, P, L, Q, C, R, NQ, E, AF, BF, QF, CF, RF, SrF, EF };
//типы символом
enum Symbols { alfa, digit, lef, prav, eqq, scc, pm, other, space };

//массив для текстово обозначения типов лексем
const char* type_word[8] = { "kw","vl","id","co","eq","ao","wl","sc" };

//функция проверки на ключевое слово
bool searc_kw(const char* lex) {
    return !(strcmp(lex, "do") && strcmp(lex, "loop") && strcmp(lex, "while") && strcmp(lex, "and") && strcmp(lex, "or") && strcmp(lex, "not"));
}

//таблица состояний
void new_table(AState(*table)[17]) {
    table[alfa][S] = A;
    table[digit][S] = B;
    table[lef][S] = P;
    table[prav][S] = L;
    table[eqq][S] = Q;
    table[scc][S] = C;
    table[pm][S] = R;
    table[other][S] = E;
    table[space][S] = S;

    table[alfa][A] = A;
    table[digit][A] = A;
    table[lef][A] = AF;
    table[prav][A] = AF;
    table[eqq][A] = AF;
    table[scc][A] = AF;
    table[pm][A] = AF;
    table[other][A] = E;
    table[space][A] = AF;

    table[alfa][B] = E;
    table[digit][B] = B;
    table[lef][B] = BF;
    table[prav][B] = BF;
    table[eqq][B] = BF;
    table[scc][B] = BF;
    table[pm][B] = BF;
    table[other][B] = E;
    table[space][B] = BF;

    table[alfa][P] = SrF;
    table[digit][P] = SrF;
    table[lef][P] = SrF;
    table[prav][P] = NQ;
    table[eqq][P] = SrF;
    table[scc][P] = SrF;
    table[pm][P] = SrF;
    table[other][P] = SrF;
    table[space][P] = SrF;

    table[alfa][L] = SrF;
    table[digit][L] = SrF;
    table[lef][L] = SrF;
    table[prav][L] = SrF;
    table[eqq][L] = SrF;
    table[scc][L] = SrF;
    table[pm][L] = SrF;
    table[other][L] = SrF;
    table[space][L] = SrF;

    table[alfa][Q] = QF;
    table[digit][Q] = QF;
    table[lef][Q] = QF;
    table[prav][Q] = QF;
    table[eqq][Q] = QF;
    table[scc][Q] = QF;
    table[pm][Q] = QF;
    table[other][Q] = QF;
    table[space][Q] = QF;

    table[alfa][C] = CF;
    table[digit][C] = CF;
    table[lef][C] = CF;
    table[prav][C] = CF;
    table[eqq][C] = CF;
    table[scc][C] = CF;
    table[pm][C] = CF;
    table[other][C] = CF;
    table[space][C] = CF;

    table[alfa][R] = RF;
    table[digit][R] = RF;
    table[lef][R] = RF;
    table[prav][R] = RF;
    table[eqq][R] = RF;
    table[scc][R] = RF;
    table[pm][R] = RF;
    table[other][R] = RF;
    table[space][R] = RF;

    table[alfa][NQ] = SrF;
    table[digit][NQ] = SrF;
    table[lef][NQ] = SrF;
    table[prav][NQ] = SrF;
    table[eqq][NQ] = SrF;
    table[scc][NQ] = SrF;
    table[pm][NQ] = SrF;
    table[other][NQ] = SrF;
    table[space][NQ] = SrF;

    table[alfa][E] = E;
    table[digit][E] = E;
    table[lef][E] = EF;
    table[prav][E] = EF;
    table[eqq][E] = EF;
    table[scc][E] = EF;
    table[pm][E] = EF;
    table[other][E] = E;
    table[space][E] = EF;

    table[alfa][AF] = AF;
    table[digit][AF] = AF;
    table[lef][AF] = AF;
    table[prav][AF] = AF;
    table[eqq][AF] = AF;
    table[scc][AF] = AF;
    table[pm][AF] = AF;
    table[other][AF] = AF;
    table[space][AF] = AF;

    table[alfa][BF] = BF;
    table[digit][BF] = BF;
    table[lef][BF] = BF;
    table[prav][BF] = BF;
    table[eqq][BF] = BF;
    table[scc][BF] = BF;
    table[pm][BF] = BF;
    table[other][BF] = BF;
    table[space][BF] = BF;

    table[alfa][QF] = QF;
    table[digit][QF] = QF;
    table[lef][QF] = QF;
    table[prav][QF] = QF;
    table[eqq][QF] = QF;
    table[scc][QF] = QF;
    table[pm][QF] = QF;
    table[other][QF] = QF;
    table[space][QF] = QF;

    table[alfa][CF] = CF;
    table[digit][CF] = CF;
    table[lef][CF] = CF;
    table[prav][CF] = CF;
    table[eqq][CF] = CF;
    table[scc][CF] = CF;
    table[pm][CF] = CF;
    table[other][CF] = CF;
    table[space][CF] = CF;

    table[alfa][RF] = RF;
    table[digit][RF] = RF;
    table[lef][RF] = RF;
    table[prav][RF] = RF;
    table[eqq][RF] = RF;
    table[scc][RF] = RF;
    table[pm][RF] = RF;
    table[other][RF] = RF;
    table[space][RF] = RF;

    table[alfa][SrF] = SrF;
    table[digit][SrF] = SrF;
    table[lef][SrF] = SrF;
    table[prav][SrF] = SrF;
    table[eqq][SrF] = SrF;
    table[scc][SrF] = SrF;
    table[pm][SrF] = SrF;
    table[other][SrF] = SrF;
    table[space][SrF] = SrF;

    table[alfa][EF] = EF;
    table[digit][EF] = EF;
    table[lef][EF] = EF;
    table[prav][EF] = EF;
    table[eqq][EF] = EF;
    table[scc][EF] = EF;
    table[pm][EF] = EF;
    table[other][EF] = EF;
    table[space][EF] = EF;
}

//струртура лексемы
struct Lex {
    char* str;
    Type type;
};

//проверка на арифетические знаки
bool ispm(char c) {
    return (c == '+' || c == '-' || c == '/' || c == '*');
}

//функий для определения символа
Symbols wtfsymbol(char c) {
    if (isalpha(c)) return Symbols::alfa;
    if (isdigit(c)) return Symbols::digit;
    if (c == '<') return Symbols::lef;
    if (c == '>') return Symbols::prav;
    if (ispm(c)) return Symbols::pm;
    if (c == '=') return Symbols::eqq;
    if (isspace(c) || c == '\0') return Symbols::space;
    if (c == ';') return Symbols::scc;
    else return Symbols::other;
}

char* new_word(const char* text, int start, int cur) {
    int lenght = cur - start;
    char* word = new char[lenght + 1];
    strncpy(&word[0], &text[0] + start, lenght);
    word[lenght] = '\0';
    return word;
}

Type get_type_from_state(const char* text, AState state) {
    if (state == AF && (strlen(text) < 6)) {
        if (searc_kw(text)) {
            return kw;
        }
        return id;
    }
    if (state == BF && atoi(text) <= 32768) {
        return vl;
    }
    if (state == QF) {
        return eq;
    }
    if (state == CF) {
        return sc;
    }
    if (state == RF) {
        return ao;
    }
    if (state == SrF) {
        return co;
    }
    return wl;
}

//анализатор
void Steps(char* text, vector<Lex>& result, AState(*state_table)[17]) {

    int  cur = 0, start = 0;
    AState state = AState::S;
    Lex lexema;
    int size_text = strlen(text) + 1;
    while (cur != size_text) {
        char cur_char = text[cur];

        state = state_table[wtfsymbol(cur_char)][state];
        if (state == AState::AF || state == AState::BF || state == AState::QF || state == AState::CF || state == AState::RF || state == AState::SrF || state == AState::EF) {

            lexema.str = new_word(text, start, cur);
            lexema.type = get_type_from_state(lexema.str, state);
            result.push_back(lexema);
            state = state_table[wtfsymbol(cur_char)][AState::S];
            start = cur;
        }
        ++cur;
        if (state == S) {
            start = cur;
        }
    }
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
        AState states_table[9][17];
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