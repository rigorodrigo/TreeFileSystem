# Árvore do Sistema de Arquivos

Este projeto é de natureza exclusivamente didática, para fins de aprendizado sobre árvores em sistemas computacionais. Ele foi desenvolvido na linguagem C++ e tem como objetivo representar o sistema de arquivos em forma de árvore. A aplicação é capaz de carregar a estrutura de diretórios e arquivos a partir de um caminho informado (caso nenhum caminho seja especificado, a pasta atual será utilizada como diretório inicial), exibindo-os em formato de árvore no terminal. Além disso, oferece funcionalidades de busca e exportação para HTML.

## Funcionalidades Implementadas: 
- Exibir sistema arquivos em formato de árvore via terminal;
- Exportar a árvore para um arquivo HTML;
- Permite buscar por:
    - Maior arquivo presente no caminho selecionado;
    - Arquivos maiores que um valor específico (em bytes) digitado pelo usuário;
    - Todos os arquivos de uma determinada extensão ( ex: .cpp,.pdf, etc.);
    - A pasta com mais arquivos no caminho especificado;
    - Pastas vazias;

Lembrando que o projeto irá considerar apenas arquivos regulares e pastas (diretórios), ignorando links, dispositivos,sockets.

## Como executar

### Requisitos

- Compilador C++ compatível com C++17 ou superior;
- Sistema operacional Linux;

### Esecução

No terminal (dentro do diretório que contém os arquivos), digite: 
   ```bash
g++ main.cpp -o <nome_do_binario>
``` 
Substitua <nome_do_binario> pelo nome que desejar para o executável. Exemplo:

 ```bash
g++ main.cpp -o explorador
```

Agora, para executar : 
```bash
./explorador [caminho_opcional]
```
Se não informar o caminho, será usado o diretório atual.
