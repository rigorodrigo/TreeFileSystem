#include <sys/stat.h>
#include<sys/types.h>

/* utilizando mesma função usada na aula de Sistemas Operacionais I
fazendo chamada de sistema para verificar se é um arquivo regular ou uma pasta
passando como parâmetro o caminho do que se deseja verificar    */

bool verificaArqRegularOuPasta (const char *caminho) {      
                                      
struct stat file_info;               // struct para armazenar informações do arquivo                      

if (lstat(caminho,&file_info) == -1) {  // recebendo informações do arquivo
return false;              
}

return (S_ISREG(file_info.st_mode) || S_ISDIR(file_info.st_mode));   //retorna se for um dos dois (st_mode contém os bits que indicam as permissões e privilégios do arquivo)
}