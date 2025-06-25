# Árvore do Sistema de Arquivos

Este projeto é de natureza exclusivamente didática, para fins de aprendizado sobre árvores em sistemas computacionais. Ele foi desenvolvido na linguagem C++ e tem como objetivo representar o sistema de arquivos em forma de árvore. A aplicação é capaz de carregar a estrutura de diretórios e arquivos a partir de um caminho informado (caso nenhum caminho seja especificado, a pasta atual será utilizada como diretório inicial.), exibindo-os em formato de árvore no terminal. Além disso, oferece funcionalidades de busca e exportação para HTML.

## Funcionalidades Implementadas: 
- Exibir o  sistema  de arquivos em formato de árvore via terminal;
- Exportar a árvore para um arquivo HTML;
- Permite buscar por:
    - Maior arquivo presente no caminho selecionado;
    - Arquivos maiores que um valor específico (em bytes) digitado pelo usuário;
    - Todos os arquivos de uma determinada extensão ( ex: .cpp,.pdf, etc.);
    - A pasta com mais arquivos no caminho especificado;
    - Pastas vazias;

Lembrando que o projeto irá considerar apenas arquivos regulares e pastas (diretórios), ignorando links, dispositivos, sockets.

## Estrutura do Projeto

- `main.cpp`: controla o menu e a interação com o usuário.  
- `tree.cpp`: possui toda a implementação da lógica da árvore e funcionalidades relacionadas a ela.  
- `verificarArquivoRegular.cpp`: verifica se o caminho é um arquivo regular ou diretório.  

## Como executar

### ⚙️  Requisitos

- Compilador C++ compatível com C++17 ou superior;
- Sistema operacional Linux;

### 🖥️ Execução

No terminal (dentro do diretório que contém os arquivos), digite: 
   ```bash
g++ main.cpp -o <nome_do_binario>
``` 
Substitua <nome_do_binario> pelo nome que desejar para o executável. Exemplo:

 ```bash
g++ main.cpp -o explorador
```

Agora, para executar: 
```bash
./explorador [caminho_opcional]
```
Se não informar o caminho, será usado o diretório atual.

Ao executar o binário, ele irá mostrar algo mais ou menos assim: 

```bash
Árvore carregada com sucesso! Pronto para explorar.
--- Menu ---
1. Mostrar arquivos
2. Exportar para HTML 
3. Submenu
0. Sair do programa
```

No submenu: 
```bash
--- Buscar ---
1. Maior arquivo
2. Arquivos maiores que N bytes
3. Pasta com mais arquivos
4. Arquivos por extensão específica
5. Pastas vazias
9. Voltar ao menu principal
```

## Autores: 

- **Nomes**: Rodrigo Rigo, Augusto Pasqualotto, Grégori Kempf
- **Curso**: Ciência da Computação
- **Universidade**: Universidade de Passo Fundo, UPF