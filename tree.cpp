#include <iostream>
#include <vector>
#include <sys/stat.h>
#include<sys/types.h>

using namespace std;

struct node{ // para representar cada arquivo ou pasta , estrutra para isso
    string name;
    string path;
    bool directory;
    long long size;//tamanho em bytes para arquivo
    vector<node*> children;

    node(string n, string p, bool Diretorio, long long s =0/*size*/);

};



bool verificaArqRegularPasta (const char *caminho) {         // utilizando mesma função usada na aula de SO
                                                            // para verificar se é um arquivo regular ou  uma pasta
    // struct para armazenar informações do arquivo         // passando como parâmetro o caminho do que se deseja verificar                                       
    struct stat file_info;                                  
    
    if (stat(caminho,&file_info) == -1) {  // recebendo informações do arquivo
        return false;              
    }

    return (S_ISREG(file_info.st_mode) || S_ISDIR(file_info.st_mode));   // aqui finalmente ocorre a verificação (st_mode contém os bits que indicam as permissões e privilégios do arquivo)
}


int main () {



    return 0;
}