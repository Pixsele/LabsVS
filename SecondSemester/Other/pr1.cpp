#include<iostream>
#include<fstream>

using namespace std;

int newNumber(int v){
    int n = v;

    int result = 0;
    while(n > 0){
        result*= 10;
        result += n%10; 
        n/= 10;
    }

    return result;
}




int main(){
    int v = 123;

    cout << v << endl;

    int r = newNumber(v);

    cout << r;


}