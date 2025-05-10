#include <vector>
#include <string>
#include <algorithm>
#include <filesystem>
#include "verificarArquivoRegular.cpp"

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

class Tree {

    node *root;

    private:

    node* loadRecursive (const std::string &path) {

        if (!verificaArqRegularPasta(path.c_str())) return nullptr;   // chamando a função que verifica se é um arquivo regular ou uma pasta (usando o "c_str")

        //usando a bilbioteca filesystem, verifica se é um diretório
        if (!std::filesystem::is_directory(path)){
            // se não for,  assume que é um nó folha (arquivo), e então retorna um  novo nó sem filhos,e seu nome,caminho,false para pasta e seu tamanho 
            // (também contando com ajuda da lib filesystem)
            return new node (std::filesystem::path(path).filename(),path,false,std::filesystem::file_size(path));
        }

        
    }


    public:

    node LoadTree (const std::string &path) {

        loadRecursive(path);

    }
};