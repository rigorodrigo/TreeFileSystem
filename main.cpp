#include <iostream>
#include <vector>
#include "verificarArquivoRegular.cpp"

using namespace std;

struct node{ // para representar cada arquivo ou pasta , estrutra para isso
    string name;
    string path;
    bool directory;
    long long size;//tamanho em bytes para arquivo
    vector<node*> children;

    node(string n, string p, bool Diretorio, long long s =0/*size*/);

};


int main () {



    return 0;
}