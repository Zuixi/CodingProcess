#include <iostream>
#include <cmath>
#include <climits>
#include <stdio.h>
#include "test.h"
#define  PRICE 30

int main() {
    using namespace std;

    int  a, b;
    a = b = 0;

    while(true){

        cin >> a;
        // if don't input a int num
        if(cin.fail()){
            char ch;
            // clear all and refresh
            cin.clear();
            ch = getchar();

            if(ch == '|') {
                cout << "not illegal" << endl;
                break;
            }
        }

        cin >> b;
        // if don't input a int num
        if(cin.fail()){
            char ch;
            // clear all and refresh
            cin.clear();
            ch = getchar();
            if(ch == '|') {
                cout << "not illegal" << endl;
                break;
            }
        }
        cout << "a = " << a << "\tb = " << b <<endl;
    }

    int N,Total;
    N = 10;
    Total = N * PRICE;
    printf("Total = %d\n",Total);
    return 0;
}


