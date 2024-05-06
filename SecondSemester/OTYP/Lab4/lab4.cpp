#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<vector>
#include<cstring>

using namespace std;
//возможные типы лексем
enum Type { ao, co, d, eq, id, lo, lp, no, sc, vl, wh, wl };
//состояния для лексиечского анализатора
enum AState { S, A, B, P, L, Q, C, R, NQ, E, AF, BF, QF, CF, RF, SrF, EF };
//состояния для синтаксического анализатора
enum CState { CS, OP, OP2, OP3, OP4, CS2, L1, L2, CS3, NO, BIN, CE };
//типы символом
enum Symbols { alfa, digit, lef, prav, eqq, scc, pm, other, space };
//струртура лексемы
struct Lex {
    char* str;
    Type type;
};
//массив для текстово обозначения типов лексем
const char* type_word[12] = { "ao","co","do","eq","id","lo","lp","no","sc","vl","wh","wl" };
//создание таблицы для синтаксического анализатора
void ctable(CState(*Ctable)[12]) {
    Ctable[d][CS] = OP;
    Ctable[wh][CS] = CE;
    Ctable[lp][CS] = CE;
    Ctable[co][CS] = CE;
    Ctable[eq][CS] = CE;
    Ctable[id][CS] = CE;
    Ctable[vl][CS] = CE;
    Ctable[ao][CS] = CE;
    Ctable[lo][CS] = CE;
    Ctable[no][CS] = CE;
    Ctable[sc][CS] = CE;
    Ctable[wl][CS] = CE;

    Ctable[d][OP] = CE;
    Ctable[wh][OP] = CE;
    Ctable[lp][OP] = CE;
    Ctable[co][OP] = CE;
    Ctable[eq][OP] = CE;
    Ctable[id][OP] = OP2;
    Ctable[vl][OP] = CE;
    Ctable[ao][OP] = CE;
    Ctable[lo][OP] = CE;
    Ctable[no][OP] = CE;
    Ctable[sc][OP] = CE;
    Ctable[wl][OP] = CE;

    Ctable[d][OP2] = CE;
    Ctable[wh][OP2] = CE;
    Ctable[lp][OP2] = CE;
    Ctable[co][OP2] = CE;
    Ctable[eq][OP2] = OP3;
    Ctable[id][OP2] = CE;
    Ctable[vl][OP2] = CE;
    Ctable[ao][OP2] = CE;
    Ctable[lo][OP2] = CE;
    Ctable[no][OP2] = CE;
    Ctable[sc][OP2] = CE;
    Ctable[wl][OP2] = CE;

    Ctable[d][OP3] = CE;
    Ctable[wh][OP3] = CE;
    Ctable[lp][OP3] = CE;
    Ctable[co][OP3] = CE;
    Ctable[eq][OP3] = CE;
    Ctable[id][OP3] = OP4;
    Ctable[vl][OP3] = OP4;
    Ctable[ao][OP3] = CE;
    Ctable[lo][OP3] = CE;
    Ctable[no][OP3] = CE;
    Ctable[sc][OP3] = CE;
    Ctable[wl][OP3] = CE;

    Ctable[d][OP4] = CE;
    Ctable[wh][OP4] = CE;
    Ctable[lp][OP4] = CS2;
    Ctable[co][OP4] = CE;
    Ctable[eq][OP4] = CE;
    Ctable[id][OP4] = CE;
    Ctable[vl][OP4] = CE;
    Ctable[ao][OP4] = OP3;
    Ctable[lo][OP4] = CE;
    Ctable[no][OP4] = CE;
    Ctable[sc][OP4] = OP;
    Ctable[wl][OP4] = CE;

    Ctable[d][CS2] = CE;
    Ctable[wh][CS2] = CS3;
    Ctable[lp][CS2] = CE;
    Ctable[co][CS2] = CE;
    Ctable[eq][CS2] = CE;
    Ctable[id][CS2] = CE;
    Ctable[vl][CS2] = CE;
    Ctable[ao][CS2] = CE;
    Ctable[lo][CS2] = CE;
    Ctable[no][CS2] = CE;
    Ctable[sc][CS2] = CE;
    Ctable[wl][CS2] = CE;

    Ctable[d][L1] = OP;
    Ctable[wh][L1] = CE;
    Ctable[lp][L1] = CE;
    Ctable[co][L1] = L2;
    Ctable[eq][L1] = L2;
    Ctable[id][L1] = CE;
    Ctable[vl][L1] = CE;
    Ctable[ao][L1] = CE;
    Ctable[lo][L1] = BIN;
    Ctable[no][L1] = CE;
    Ctable[sc][L1] = CE;
    Ctable[wl][L1] = CE;

    Ctable[d][L2] = CE;
    Ctable[wh][L2] = CE;
    Ctable[lp][L2] = CE;
    Ctable[co][L2] = CE;
    Ctable[eq][L2] = CE;
    Ctable[id][L2] = L1;
    Ctable[vl][L2] = L1;
    Ctable[ao][L2] = CE;
    Ctable[lo][L2] = CE;
    Ctable[no][L2] = CE;
    Ctable[sc][L2] = CE;
    Ctable[wl][L2] = CE;

    Ctable[d][CS3] = CE;
    Ctable[wh][CS3] = CE;
    Ctable[lp][CS3] = CE;
    Ctable[co][CS3] = CE;
    Ctable[eq][CS3] = CE;
    Ctable[id][CS3] = L1;
    Ctable[vl][CS3] = L1;
    Ctable[ao][CS3] = CE;
    Ctable[lo][CS3] = CE;
    Ctable[no][CS3] = NO;
    Ctable[sc][CS3] = CE;
    Ctable[wl][CS3] = CE;

    Ctable[d][NO] = CE;
    Ctable[wh][NO] = CE;
    Ctable[lp][NO] = CE;
    Ctable[co][NO] = CE;
    Ctable[eq][NO] = CE;
    Ctable[id][NO] = L1;
    Ctable[vl][NO] = L1;
    Ctable[ao][NO] = CE;
    Ctable[lo][NO] = CE;
    Ctable[no][NO] = CE;
    Ctable[sc][NO] = CE;
    Ctable[wl][NO] = CE;

    Ctable[d][BIN] = CE;
    Ctable[wh][BIN] = CE;
    Ctable[lp][BIN] = CE;
    Ctable[co][BIN] = CE;
    Ctable[eq][BIN] = CE;
    Ctable[id][BIN] = L1;
    Ctable[vl][BIN] = L1;
    Ctable[ao][BIN] = CE;
    Ctable[lo][BIN] = CE;
    Ctable[no][BIN] = L2;
    Ctable[sc][BIN] = CE;
    Ctable[wl][BIN] = CE;

    Ctable[d][CE] = CE;
    Ctable[wh][CE] = CE;
    Ctable[lp][CE] = CE;
    Ctable[co][CE] = CE;
    Ctable[eq][CE] = CE;
    Ctable[id][CE] = CE;
    Ctable[vl][CE] = CE;
    Ctable[ao][CE] = CE;
    Ctable[lo][CE] = CE;
    Ctable[no][CE] = CE;
    Ctable[sc][CE] = CE;
    Ctable[wl][CE] = CE;
}
//создание таблицы для лексического анализатора
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
//функция для поиска лексемы которая должна быть
void search_not_ce(CState state, ofstream& out, CState(*C_table)[12]) {
    //проходим по столбцу и ищем не ошибочные лексемы и вывожим их
    for (int i = 0; i < 12; i++) {
        if (C_table[i][state] != CState::CE) {
            cout << type_word[i] << " ";
            out << type_word[i] << " ";
        }
    }
}
//синт. анализатор
void CEanyliz(vector<Lex>& lexems, ofstream& out, CState(*C_table)[12]) {
    //начальное состояние
    CState state = CState::CS;
    //текущая позиция
    int pos = 0;
    //колесчтво лексем
    int size_str = lexems.size();
    //флаг ошибки
    bool error = false;
    //идеи по векторы с лексемами и переходим по состояниям
    if (size_str == 0) {
        cout << pos << " ";
        out << pos << " ";

        search_not_ce(state, out, C_table);
        error = true;
    }
    while (pos != size_str) {
        //если ошибочное состояние то выводим позицию и нужные лексемы
        if (C_table[lexems[pos].type][state] == CState::CE) {
            cout << pos << " ";
            out << pos << " ";

            search_not_ce(state, out, C_table);
            error = true;
            break;
        }
        else {
            state = C_table[lexems[pos].type][state];
        }
        //проверка последней лексемы на то что она конечная
        if (pos == size_str - 1 && state != CState::L1) {
            cout << pos + 1 << " ";
            out << pos + 1 << " ";
            search_not_ce(state, out, C_table);
            error = true;
        }
        ++pos;
    }
    //если не было ошибок то OK
    if (!error) {
        cout << "OK";
        out << "OK";
    }
};
//проверка на арифетические знаки
bool ispm(char c) {
    return (c == '+' || c == '-' || c == '/' || c == '*');
}
//функий для определения символа
Symbols seasumb(char c) {
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
//функция для нового слова
char* new_word(const char* text, int start, int cur) {
    //считаем длину
    int lenght = cur - start;
    //выделяем память
    char* word = new char[lenght + 1];
    //записываем слово
    strncpy(&word[0], &text[0] + start, lenght);
    word[lenght] = '\0';
    return word;
}
//функция опредления типа лексемы
Type get_type_from_state(const char* text, AState state) {
    if (state == AF && (strlen(text) < 6)) {
        if (!(strcmp(text, "do"))) {
            return d;
        }
        if (!(strcmp(text, "loop"))) {
            return lp;
        }
        if (!(strcmp(text, "while"))) {
            return wh;
        }
        if (!(strcmp(text, "and"))) {
            return lo;
        }
        if (!(strcmp(text, "or"))) {
            return lo;
        }
        if (!(strcmp(text, "not"))) {
            return no;
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
//лекс. анализатор
void Steps(char* text, vector<Lex>& result, AState(*state_table)[17]) {
    //текущая и начальная позиция
    int  cur = 0, start = 0;
    //начальное состояние
    AState state = AState::S;
    //лексема
    Lex lexema;
    //размер строки
    int size_text = strlen(text) + 1;
    //проход по всей строке
    while (cur != size_text) {
        char cur_char = text[cur];
        //меняем состояние
        state = state_table[seasumb(cur_char)][state];
        //если состояние конечное то записываем слово
        if (state == AState::AF || state == AState::BF || state == AState::QF || state == AState::CF || state == AState::RF || state == AState::SrF || state == AState::EF) {
            //сохраняем слово
            lexema.str = new_word(text, start, cur);
            //определяем тип лексемы
            lexema.type = get_type_from_state(lexema.str, state);
            result.push_back(lexema);
            //переход по начальному состоянию
            state = state_table[seasumb(cur_char)][AState::S];
            //смещаем начало
            start = cur;
        }
        ++cur;
        //если начальное то смещаем
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
    return str;
}
//функция вывода результата
void print(vector<Lex>& ans, ofstream& out) {
    //выводим каждый элемент вектора особым образом
    for (size_t i = 0; i < ans.size(); i++) {
        out << ans[i].str << "[" << type_word[ans[i].type] << "]" << ' ';
        cout << ans[i].str << "[" << type_word[ans[i].type] << "]" << ' ';
    };
    out << endl;
    cout << endl;
}

int main() {
    //отрытие файлов для чтения
    ifstream in("input.txt");
    //отрытие файлов для записи
    ofstream out("output.txt");
    if (in) {
        //таблицы для автоматов
        AState states_table[9][17];
        CState c_table[12][12];
        new_table(states_table);
        ctable(c_table);
        //считываение текста
        char* text = textinit(in);
        //лекс. обработка
        vector<Lex> ans;
        Steps(text, ans, states_table);
        //вывод
        print(ans, out);
        //синтаксический анализатор
        CEanyliz(ans, out, c_table);
        //очистка памяти лексем
        for (size_t i = 0; i < ans.size(); i++) {
            delete[] ans[i].str;
        }
        //очистка памяти текста
        delete[] text;
    }
    //закрытие файлов
    in.close();
    out.close();
}
