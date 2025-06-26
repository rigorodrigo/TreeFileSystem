#include <vector>
#include <string>
#include <algorithm>
#include <filesystem>
#include "verificarArquivoRegular.cpp"
#include <iostream>
#include <functional>
#include <fstream>


namespace fs = std::filesystem;  // nomeando um namespace para facilitar 

struct node{ // para representar cada arquivo ou pasta , estrutra para isso
    std::string name;
    std::string path;
    bool directory;
    ssize_t size;//tamanho em bytes para arquivo
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

    node* loadRecursive (const std::string &path) {  


        if(!fs::exists(path)){
            return nullptr; // caminho nao existe 
        }

        if (!verificaArqRegular(path.c_str())) return nullptr;   // chamando a função que verifica se é um arquivo regular ou uma pasta (usando o "c_str")




        //usando a bilbioteca filesystem, verifica se é um diretório
        if (!std::filesystem::is_directory(path)){

            ssize_t fileSize = 0;


                //tratamento de erro (ideias de POO)
             try {
                   fileSize = fs::file_size(path);  //se for arquivo retorna com seu tamanho
                 }  
                 catch (const fs::filesystem_error& e) {

                    //vereficar 
                    //executa somente quando ocorre erro, cerr(exclusivo para erros)                 e.what() -> retorna String que descreve o erro detalhadamente
            std::cerr << "Aviso: Nao foi possível obter o tamanho do arquivo '" << path << "': " << e.what() << ". Sera considerado 0 bytes." << std::endl;
            return new node(fs::path(path).filename().string(), path, false, 0);
        }


            // se não for,  assume que é um nó folha (arquivo), e então retorna um  novo nó sem filhos,e seu nome,caminho,false para pasta e seu tamanho 
            // (também contando com ajuda da lib filesystem)
            
             return new node(fs::path(path).filename().string(), path, false, fileSize);
        }

        node * directoryNode = new node (fs::path(path).filename().string(),path,true);      // se for um diretório, cria um nó para ele


        // e irei iterar sobre os arquivos do diretório com o "directory_iterator" ,também da lib filesystem

        try{
        for (const auto& n : fs::directory_iterator(path)){

            // chama recursivamente a função passando o nó filho como parâmetro
            node * childrenNode = loadRecursive(n.path().string());             // path pega o caminho da variável n que percorre o diretório e é convertido para string (argumento da função)

            if (childrenNode != nullptr) {
                directoryNode->children.push_back(childrenNode);       // se o nó filho existir (não for nulo), será adicionado ao vetor dos filhos
            }
        }
        } catch (const fs::filesystem_error& erro) {
            // se não tiver permissão para acessar, ignora o diretório
        }


        return directoryNode;
    }

     ssize_t directorySize(node *n) const {   // função para pegar o tamanho em bytes do diretório
        ssize_t size = 0;
        
        std::function<void(node*)> accSize; // declaração prévia da função lambda
        accSize = [&](node* n) { 
            if (!n) return; //se o nó é nulo, retorna imediatamente

            if (n->directory) { //verifica se o nó é um diretório
                for(auto a: n->children){
                   size += a->size; //laço para atualizar o size conforme o tamanho dos filhos
                }
            }

            for (node* child : n->children) { //percorre recursivamente todos os filhos do nó atual chamando find() 
                accSize(child);
            }
        };

        accSize(n); //chama a função lambda

        return size;
     }

   

     void showRecursiveTree(node* n, const std::string& prefix = "", bool isLast = true) {
        if (!n) return; 

        std::cout << prefix; //imprime o prefix

        if (!prefix.empty()) {
            std::cout << (isLast ? "└── " : "├── "); //se for o nó raiz o prefix é vazio, caso contrário entra em uma condicional usando o isLast para saber qual símbolo imprimir
        }

        if (n->directory) {
            std::cout << n->name << " (" << n->children.size() << " filhos, " << directorySize(n) << " bytes)" << std::endl; //se for pasta, imprime o nome, quantidade de filhos e tamanho
        } else {
            std::cout << n->name << " (" << n->size << " bytes)" << std::endl; //se for arquivo, imprime o nome e tamanho
        }

        for (size_t i = 0; i < n->children.size(); ++i) { //inicia um loop para visitar todos os filhos do nó atual
            bool last = (i == n->children.size() - 1); //verifica se o filho atual é o ultimo da lista
            showRecursiveTree(n->children[i], prefix + (isLast ? "    " : "│   "), last); //chama a função recursivamente para o filho atual
        }
     }
    
     void findDirsRecursive(node* n, int& maxCount, std::vector<node*>& result) { //nó atual, referência ao maior número de filhos até agora, referência ao vetor onde serão armazenados os diretórios
        if (!n || !n->directory) return;

        int fileCount = 0;

        for (auto child : n->children) {
            if (!child->directory) {
                fileCount++; //itera sobre os filhos do nó atual, incrementando fileCount caso não seja um diretório
            }
        }

        if (fileCount > maxCount) {
            maxCount = fileCount;
            result.clear();
            result.push_back(n); //se o valor do fileCount é maior que o maxCount atual, atualiza maxCount com esse valor, limpa o vetor antigo e adiciona n ao vetor 
        } else if (fileCount == maxCount) {
            result.push_back(n); //se o file count é igual ao maxCount atual, apenas adiciona n ao vetor
        }

        for (auto child : n->children) {
            if (child->directory) {
                findDirsRecursive(child, maxCount, result); //faz a chamada da função recursiva para os filhos que sejam diretórios, assim rodando toda a árvore
            }
        }
     }

     void findEmptyDirsRecursive(node* n, std::vector<node*>& result){
        if (!n || !n->directory) return; //se n não existe ou é arquivo, termina a execução da função

        if (n->children.empty()){
            result.push_back(n); //se n não tem filhos, adiciona n ao vetor que guarda as pastas vazias
        }

        for(auto child : n->children){
            if (child && child->directory)
            {
                findEmptyDirsRecursive(child, result); //roda recursivamente a função para os filhos do nó atual
            }
        }
     }

     void clearTree (node *root) {
        if (!root) return;
        for (auto a : root->children){
            clearTree(a);
        }

        delete root;
     }

    public:

    Tree() : root(nullptr) {}  // construtor  inicializando o root como null (sem essa inicialização possivelmente ele poderia pegar lixo de memória ou afins) 

    // método público que inicializa a árvore a partir do caminho fornecido

    bool LoadTree (const std::string &path) {   

        if (root != nullptr){  // se já existe uma árvore inicializada...
            clearTree(root);  // limpa ela da memóriaAdd commentMore actions
            root = nullptr;
        }

        if (!fs::exists(path)) {         // verifica se o caminho realmente existe
            return false;
        }

        root = loadRecursive(path);       // armazenando o nó raiz

        return root != nullptr;        // retorna true se o carregamento foi feito com sucesso
                                      // caso contrário, retorna false
    }

    void findBiggerFile() const {
        long long biggerSize = -1;
        std::vector<std::string> biggerFiles; //cria um vetor que guarda o caminho para os maiores arquivos

        std::function<void(node*)> find; // declaração prévia da função lambda
        find = [&](node* n) { 
            if (!n) return; //se o nó é nulo, retorna imediatamente

            if (!n->directory) { //verifica se o nó não é um diretório
                if (n->size > biggerSize) { //verifica se o tamanho de n é maior que o biggerSize atual
                    biggerSize = n->size; //seta o maior atual como n
                    biggerFiles.clear(); //limpa  o vetor
                    biggerFiles.push_back(n->path); //coloca o caminho de n no vetor
                } else if (n->size == biggerSize) { //se n for do mesmo tamanho que o maior atual
                    biggerFiles.push_back(n->path); //coloca o caminho dele no vetor também
                }
            }

            for (node* child : n->children) { //percorre recursivamente todos os filhos do nó atual chamando find() 
                find(child);
            }
        };

        find(root);

        if (biggerFiles.empty()) { //se o vetor está vazio
            std::cout << "Nenhum arquivo encontrado.\n";
        } else { //imprimindo os encontrados
            std::cout << "Maior(es) arquivo(s):\n";
            for (const std::string& path : biggerFiles) {
                std::cout << path << " (" << biggerSize << " bytes)\n";
            }
        }
    }

    void biggerThan(long long value) const {
        std::vector<node*> bigFiles; //cria um vetor para armazenar os arquivos
        
        std::function<void(node*)> find; //declaração da função lambda
        find = [&](node* n){ 
            if(!n) return; //se o né é nulo, retorna 

            if(!n->directory){ //verifica se o nó não é um diretório
                if (n->size > value) 
                {
                    bigFiles.push_back(n); //se o tamanho do nó for maior que o valor desejado coloca ele no vetor
                }
            }

            for(node* child : n->children){
                find(child); //chama recursivamente a função de busca para o filho desse nó
            }
        };

        find(root);

        if(bigFiles.empty()){
            std::cout << "Nenhum arquivo encontrado.\n";
        } else{
            std::cout << "Arquivo(s) maior(es) que " << value << " bytes.\n";
            for(node* n : bigFiles){
                std::cout << n->path << "(" << n->size << " bytes)\n"; //percorre o vetor imprimindo caminho e tamanho dos arquivos
            }
        }
        
    }


    void findDirsWithMostFiles() {
        if (!root) {
            std::cout << "Árvore vazia.\n"; //se o nó raiz é nulo, informa que a árvore está vazia e encerra a função
            return;
        }

        int maxCount = -1;
        std::vector<node*> result;

        findDirsRecursive(root, maxCount, result); //chama a função recursiva para preencher maxCount e result

        if (maxCount <= 0) {
            std::cout << "Nenhuma pasta com arquivos encontrados.\n";
            return;
        }

        std::cout << "Pasta(s) com mais arquivos diretos (" << maxCount << " arquivo(s)):\n";
        for (auto dir : result) {
            std::cout << "- " << dir->path << std::endl; //percorre o vetor result com as pastas que contém mais arquivos, imprimindo-as
        }
    }

    void findEmptyDirs(){
        if (!root) {
            std::cout << "Árvore vazia.\n"; //se o nó raiz é nulo, informa que a árvore está vazia e encerra a função
            return;
        }

        std::vector<node*> result;

        findEmptyDirsRecursive(root, result); //chama a função recursiva no escopo privado que preenche o vetor result com as pastas vazias

        if (result.empty())
        {
            std::cout << "Nenhuma pasta sem arquivos encontrada.";
        }else{
            std::cout << "Pasta(s) vazia(s):\n";
            for (auto dir : result){
                std::cout << "- " << dir->path << std::endl; //se não tiver pastas vazias imprime uma mensagem, se tiver, imprime o caminho delas
            }
        }
    }

    void findFilesWithExtension(const std::string& extension) const {
        if (!root) {
            std::cout << "Árvore vazia.\n"; //vê se o nó raiz existe e, caso contrário encerra a função
            return;
        }

        std::vector<node*> matchingFiles; //vetor para armazenas as correspondências 

        std::function<void(node*)> find;
        find = [&](node* n) {
            if (!n) return; //se o nó atual for nulo, retorna imediatamente

            if (!n->directory) { 
                if (fs::path(n->name).extension() == extension) {
                    matchingFiles.push_back(n); //se n não for um diretório, verifica a extensão, e caso for correspondente adiciona n ao vetor
                }
            }

            for (node* child : n->children) {
                find(child); //roda recursivamente a função find a partir dos filhos 
            }
        };

        find(root);

        if (matchingFiles.empty()) {
            std::cout << "Nenhum arquivo com a extensão '" << extension << "' encontrado.\n";
        } else {
            std::cout << "Arquivo(s) com a extensão '" << extension << "':\n";
            for (node* file : matchingFiles) {
                std::cout << "- " << file->path << " (" << file->size << " bytes)\n"; //imprime, conforme foram encontrados(ou não) os arquivos
            }
        }
    }

    void exportToHTML(const std::string& filename) { //definição da função, que recebe como parâmetro o nome do arquivo de saída(precisa botar .html no final)
        std::ofstream out(filename); //cria um objeto de saída, e caso ele exista substitui
        if (!out.is_open()) {
            std::cerr << "Erro ao abrir o arquivo para escrita.\n"; //verifica se o arquivo abriu corretamente, e caso contrário, exibe uma mensagem de erro e termina a execução
            return;
        }
        out << "<html><body><ul>"; //escreve o início do arquivo html, iniciando uma unordered list onde cada item será um diretório ou arquivo
        std::function<void(node*, int)> writeHTML = [&](node* n, int indent) { //declara uma função lambda recursiva
            if (!n) return;
            out << "<li>" << n->name; //escreve no arquivo de saída o nome do diretório ou arquivo da árvore
            if (n->directory) { //verifica se n é uma pasta
                out << "<ul>"; //começa uma nova lista 
                for (node* child : n->children) {
                    writeHTML(child, indent + 1); //chama recursivamente a função para os filhos de n, aumentando a identação
                }
                out << "</ul>"; //fecha a lista 
            }
            out << "</li>"; //fecha o item da lista 
        };
        writeHTML(root, 0); //chama a função lambda passando a raiz e a identação 0
        out << "</ul></body></html>"; //fecha o documento html
        out.close(); //fecha o arquivo
        std::cout << "Árvore exportada com sucesso para " << filename << "\n"; //exibe mensagem de sucesso
    }

    void showTree() {

        showRecursiveTree(root);

    }
};
