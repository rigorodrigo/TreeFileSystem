
#include <string>
#include <limits>
#include "tree.cpp"

using namespace std; 
//ver de passar um diretorio
//para uma melhor organização do código

void displayMainMenu() {
    cout << "\n--- Menu ---" << endl;
    cout << "1. Mostrar arquivos" << endl;
    cout << "2. Exportar para HTML (ainda não feito)" << endl;
    cout << "3. Submenu" << endl;
    cout << "0. Sair do progrma" << endl;
    cout << "-----------------------" << endl;
    cout << "opção: ";
}
//teste de commit
void displaySearchSubMenu() {
    cout << "\n--- Buscar ---" << endl;
    cout << " Maior arquivo" << endl;
    cout << " Arquivos maiores que N bytes" << endl;
    cout << " Pasta com mais arquivos" << endl;
    cout << " Arquivos por extensão específica" << endl;
    cout << " Pastas vazias" << endl;
    cout << " Voltar ao menu principal" << endl;
    cout << "---------------------------" << endl;
    cout << "Escolha uma opçao: ";
}

int main(int argc, char* argv[]) { //main receber argumentos 
    Tree fileSystemExplorer;

    string startPath = ".";
    if (argc > 1) {
        startPath = argv[1];
    }

    
    if (!fileSystemExplorer.LoadTree(startPath)) { //cerr, saida de erro padrao
        cerr << "Não foi possível carregar a árvore do sistema de arquivos de '" << startPath
                   << endl;
        return 1;
    }
    cout << "Árvore carregada !" << endl;

    int choice;

    while (true) {
        displayMainMenu();
        cin >> choice;

        if (cin.fail()) { //um checker pra entrada
            cout << "opção válida!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');//pra limpeza do buffer de forma boa, invez do .clear()
            continue;
        }

        switch (choice) {
            case 1:
                cout << "\n--- Exibindo Árvore do Sistema de Arquivos ---" << endl;
                fileSystemExplorer.showTree();
                break;
            case 2:
                cout << "Exportar para HTML:(Nao feito)" << endl;
                break;
            case 3: {
                int subChoice;
                while (true) {
                    displaySearchSubMenu();
                    cin >> subChoice;

                    if (cin.fail()) {
                        cout << " não é um número válido. Tente novamente!" << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }

                    if (subChoice == 9) { //teste
                        cout << "Retornando ao menu principal." << endl;
                        break;
                    }

                    cout << " ---- " << endl;
                }
                break;
            }
            case 0:
                cout << "saindo!" << endl;
                return 0;
            default:
                cout << "Opção inválida!" << endl;
                break;
        }
    }

    return 0;
}
