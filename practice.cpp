#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ofstream fout("test.txt");
    fout << "Hello File";
    fout.close();

    ifstream fin("test.txt");
    string data;
    fin >> data;

    cout << "Data: " << data;

    fin.close();
    return 0;
}
