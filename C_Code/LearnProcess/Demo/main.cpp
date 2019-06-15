#include <iostream>
#include <cmath>
#include <climits>

void  showUnicodeChar();
int main() {
    using namespace std;
    int carrots = 0;
    cout << "How many carrots do you have?" << endl;
    cin >> carrots;
    cout << "Here are " << carrots << " carrots!" << endl;
    carrots += 2;
    cout << "Now you have " << carrots << " carrots!" << endl;


    double  area;
    cout << "Enter your area of your home in square: ";
    cin >> area;
    double  side;
    side = sqrt(area);
    cout << "That's the equipment of a square: " << side
         << "feet to the side!" << endl;
    cout << "how fascinating!"<<endl;

    showUnicodeChar();

    wcout << "welcome to the wchar_t world"<< endl;
    wchar_t  bo[2]= L"P";
    wcout << bo<<endl;
    wcout << L"tall" << endl;
    return 0;
}



void  showUnicodeChar(){
    using namespace std;

    cout << "test unicode char set with simple instance" << endl;

    cout << "let's them eat g\u00E2teau.\n";
    cout << "different char after g ,as you see!"<< endl;

}