#include <iostream>
#include <string>

using namespace std;

int main (void){
    string str;
    cin >> str ;

    cout << str << endl;
    char ch = str.at(0) ;
    cout << ch << endl ;
    cout << (int) ch << endl ;

    return 0 ;
}