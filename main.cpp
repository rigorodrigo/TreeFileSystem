#include <iostream>
#include <string>
#include <limits>
#include "tree.cpp"

using namespace std; 

void displayMainMenu() {
    cout << "\n--- Menu ---" << endl;
    cout << "1. Mostrar arquivos" << endl;
    cout << "2. Exportar para HTML (ainda não feito)" << endl;
    cout << "3. Submenu" << endl;
    cout << "0. Sair do progrma" << endl;
    cout << "-----------------------" << endl;
    cout << "opção: ";
}

void displaySearchSubMenu() {
    cout << "\n--- Buscar ---" << endl;
    cout << " 1. Maior arquivo" << endl;
    cout << " Arquivos maiores que N bytes" << endl;
    cout << " Pasta com mais arquivos" << endl;
    cout << " Arquivos por extensão específica" << endl;
    cout << " Pastas vazias" << endl;
    cout << " 9. Voltar ao menu principal" << endl;
    cout << "---------------------------" << endl;
    cout << "Escolha uma tarefa de busca: ";
}

int main(int argc, char* argv[]) {
    Tree fileSystemExplorer;

    string startPath = "."; //como não é especificado ele pega os arquivos da pasta em que esta inserido / Ajustar isso 
    if (argc > 1) {
        startPath = argv[1];
    }

    cout << "Tentando carregar o sistema de arquivos de: '" << startPath << "'..." << endl;
    if (!fileSystemExplorer.LoadTree(startPath)) {
        cerr << "Puxa! Não foi possível carregar a árvore do sistema de arquivos de '" << startPath
                  << "'. Talvez o caminho esteja errado, ou as permissões estejam complicadas?" << endl;
        return 1;
    }
    cout << "Árvore carregada com sucesso! Pronto para explorar." << endl;

    int choice;

    while (true) {
        displayMainMenu();
        cin >> choice;

        if (cin.fail()) {
            cout << "Isso não foi um número. Por favor, tente novamente com uma opção válida!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                cout << "\n--- Exibindo Árvore do Sistema de Arquivos ---" << endl;
                fileSystemExplorer.showTree();
                break;
            case 2:
                cout << "Exportar para HTML: Ainda na prancheta. Volte mais tarde!" << endl;
                break;
            case 3: {
                int subChoice;
                while (true) {
                    displaySearchSubMenu();
                    cin >> subChoice;

                    if (cin.fail()) {
                        cout << "Hmm, não é um número válido. Tente novamente!" << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }
                    if (subChoice == 1) {
                        fileSystemExplorer.findBiggerFile();
                        break;
                    }
                    if (subChoice == 9) {
                        cout << "Retornando ao menu principal." << endl;
                        break;
                    }

                    cout << "Essa funcionalidade de busca (" << subChoice << ") ainda não está implementada. Paciência, jovem padawan!" << endl;
                }
                break;
            }
            case 0:
                cout << "Saindo. Obrigado por usar o Explorador de Sistema de Arquivos! Adeus!" << endl;
                return 0;
            default:
                cout << "Opção inválida! Por favor, escolha um número do menu." << endl;
                break;
        }
    }

    return 0;
}