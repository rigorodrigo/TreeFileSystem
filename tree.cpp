#include <vector>
#include <string>
#include <algorithm>
#include <filesystem>
#include "verificarArquivoRegular.cpp"
#include <iostream>

namespace fs = std::filesystem;  // nomeando um namespace para facilitar 

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

        // método privado que realmente carrega a arvore de maneira recursiva. usei ele como private por causa do encapsulamento 

    node* loadRecursive (const std::string &path)  {  

        if (!verificaArqRegularPasta(path.c_str())) return nullptr;   // chamando a função que verifica se é um arquivo regular ou uma pasta (usando o "c_str")

        //usando a bilbioteca filesystem, verifica se é um diretório
        if (!std::filesystem::is_directory(path)){
            // se não for,  assume que é um nó folha (arquivo), e então retorna um  novo nó sem filhos,e seu nome,caminho,false para pasta e seu tamanho 
            // (também contando com ajuda da lib filesystem)
            return new node (fs::path(path).filename(),path,false,fs::file_size(path));
        }

        node * directoryNode = new node (fs::path(path).filename(),path,true);      // se for um diretório, cria um nó para ele

        // e irei iterar sobre os arquivos do diretório com o "directory_iterator" ,também da lib filesystem

        for (const auto& n : fs::directory_iterator(path)){

            // chama recursivamente a função passando o nó filho como parâmetro
            node * childrenNode = loadRecursive(n.path().string());             // path pega o caminho da variável n que percorre o diretório e é convertido para string (argumento da função)

            if (childrenNode != nullptr) {
                directoryNode->children.push_back(childrenNode);       // se o nó filho existir (não for nulo), será adicionado ao vetor dos filhos
            }
        }


        return directoryNode;
    }

     void showRecursiveTree (node* n, int level = 0,std::string s = "") const  {

        if (!n) return;

        if (n->directory){       // se for uma pasta
            std::cout << s << n->name << " ( " << n->children.size() << " filhos, " << n->size << " bytes)" << std::endl;
        }
        else {   // se for um arquivo
            std::cout << n->name << " (" << n->size << " bytes)" << std::endl;
        }

        for (int i = 0; i < n->children.size(); i++){       // iiterando sobre o vetor com os filhos
            if ( i == (n->children.size() - 1) ){        // se for o último filho
                showRecursiveTree(n->children[i],level +1, s + "└── ");
            }
            else{         // se não for o último filho
                showRecursiveTree(n->children[i],level + 1, s + "├──");
            }
        }

     }

     void clearTree (node *root) {
        if (!root) return;
        for (auto c : root->children){
            clearTree(c);
        }

        delete root;
     }


    public:

    // método público que inicializa a árvore a partir do caminho fornecido

    bool LoadTree (const std::string &path)  {   

        if (root != nullptr){  // se já existe uma árvore inicializada...
            clearTree(root);  // limpa ela da memória
            root = nullptr;
        }

        if (!fs::exists(path)) {         // verifica se o caminho realmente existe
            return false;
        }

        root = loadRecursive(path);       // armazenando o nó raiz

        return root != nullptr;        // retorna true se o carregamento foi feito com sucesso
                                      // caso contrário, retorna false
    }

    void showTree() const {

        showRecursiveTree(root);

    }
};