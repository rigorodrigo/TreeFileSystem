#include <vector>
#include <string>

struct node{ // para representar cada arquivo ou pasta , estrutra para isso
    std::string name;
    std::string path;
    bool directory;
    long long size;//tamanho em bytes para arquivo
    std::vector<node*> children;

    node(std::string n, std::string p, bool Diretorio, long long s =0/*size*/);

};

node::node (std::string n ,std::string p, bool Diretorio, long long s){  // construtor para inicializar os atributos
    name = n;
    path = p;
    directory = Diretorio;
    size = s;
}