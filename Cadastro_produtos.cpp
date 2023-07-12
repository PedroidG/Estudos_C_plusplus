#include <iostream>
#include <fstream>

using namespace std;

/*
    Faça um programa que busque um item e ordene os produtos
    de uma loja de acordo com o seu preço, seu programa ainda
    devera guardar os produtos ordenados por preço em um
    arquivo.
*/

//struct com informações dos produtos
struct produto{
    string nome;
    string marca;
    float preco;
    //int unidades;
};

//procedimento de busca
void busca(produto *produtos, int quantidade, string busca){
    int i = 0;
    int posicao = -1;

    while(i < quantidade and busca != produtos[i].nome){
        i++;
    }
    if(busca == produtos[i].nome){
        posicao = i;
    }
    if(posicao == -1){
        cout << "Produto nao encontrado!" << endl;
    }else{
        cout << "Produto encontrado!" << endl;
        cout << "Nome: " << produtos[posicao].nome << "\t";
        cout << "Marca: " << produtos[posicao].marca << "\t";
        cout << "Preco: " << "R$" << produtos[posicao].preco << "\t";
    }
}

//procedimento de ordenação
void ordenacao(produto *produtos, int quantidade){
    produto pivo;
    int i, j;
    for(i = 1; i < quantidade; i++){
        pivo = produtos[i];
        j = i - 1;
        while(j >= 0 and pivo.preco <= produtos[j].preco){
            produtos[j + 1] = produtos[j];
            j = j - 1;
        }
        produtos[j + 1] = pivo;
    }
}

//impressao dos dados
void imprimir(produto *produtos, int quantidade){
    int i;
    for(i = 0; i < quantidade; i++){
        cout << "Nome: " << produtos[i].nome << "\t";
        cout << "Marca: " << produtos[i].marca << "\t";
        cout << "Preco: " << "R$" << produtos[i].preco << "\t";
        cout << endl;
    }
}

int main(){
    int quantidade; //quantidade de produtos que serão cadastrados
    int i; //variável auxiliar
    cin >> quantidade;
    cin.ignore();
    produto *produtos = new produto[quantidade]; //vetor de produtos

    //entrada de dados dos produtos
    for(i = 0; i < quantidade; i++){    //laço que faz a inserção dos dados no vetor
        cout << "Digite o nome do produto: ";
        getline(cin, produtos[i].nome);
        cout << "Digite a marca do produto: ";
        getline(cin, produtos[i].marca);
        cout << "Digite o preco do produto: ";
        cin >> produtos[i].preco;
        cin.ignore();
        cout << endl;
    }

    //mostra os produtos cadastrados
    cout << "Produtos cadastrados: " << endl;
    imprimir(produtos, quantidade);
    cout << endl;

    //busca produtos
    string buscador;
    cout << "Digite o nome do produto que quer buscar: ";
    getline(cin, buscador);
    cout << endl;
    busca(produtos, quantidade, buscador);
    cout << endl;

    //ordena produtos de acordo com o preço
    ordenacao(produtos, quantidade);
    cout << endl;

    //mostra os produtos ordenados
    cout << "Produtos ordenados de acordo com o preco: " << endl;
    imprimir(produtos, quantidade);
    cout << endl;

    //grava os produtos já ordenados em um arquivo csv com todos os campos separados corretamente em colunas
    ofstream arquivo("dados.csv");
    char separador = ';';   //char que separa cada campo em colunas no Excel
    if(arquivo.is_open()){  //verifica de o arquivo foi corretamente aberto
        arquivo << "Produto" << separador << "Marca" << separador << "Preco" << endl; //escreve o cabeçalho
        for(i = 0; i < quantidade; i++){    //laço que escreve os dados enquanto houver produtos
            arquivo << produtos[i].nome << separador;
            arquivo << produtos[i].marca << separador;
            arquivo << "R$" << produtos[i].preco << endl;
        }
        arquivo.close();
        cout << "Arquivo criado com sucesso!" << endl;
    }else{
        cout << "Arquivo nao foi criado!" << endl;
    }
    cout << "Programa finalizado!" << endl;
    return 0;
}