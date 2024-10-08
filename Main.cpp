#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "Cabecalho.h"
using namespace std;

int main(int argc, char** argv) {
    int numProdutos = 0, numItens = 0;
    float taxaEntrega = 6.00, desconto = 0;
    char pagamento = 0;

    Produto* estocador;
    Produto* pedido  = nullptr;
    ifstream arquivo;
    arquivo.open("estoque.dat", ios_base::out | ios_base::binary);
    if (!arquivo.is_open())
    {
       estocador = nullptr;
    }
    else
    {
        arquivo.read((char*)&numProdutos, sizeof(int));
     estocador = new Produto[numProdutos];
    for (int i = 0; i < numProdutos; ++i)
        arquivo.read((char*)&estocador[i], sizeof(Produto));
    arquivo.close();
   

    }
    

    char op;
    if (argc > 1 && !strcmp(argv[1], "-c"))
    {
        char opcao;
        // Inicializar o ponteiro para o estoque
        do {
            cout << "RapiZinho\n===========\n";
            cout << "(A) Adicionar\n";
            cout << "(E) Excluir\n";
            cout << "(L) Listar\n";
            cout << "(S)Sair\n";
            cout << "Opção: ";
            cin >> opcao;

            switch (opcao) {
            case 'A':
            case 'a':
                estocador = adicionarProduto(estocador,& numProdutos);
                break;
            case 'E':
            case 'e':
                excluirProduto(estocador,& numProdutos);
                break;
            case 'L':
            case 'l':
                listarProdutos(estocador, &numProdutos);
                break;
            case 'S':
            case 's':
                
                break;
            default:
                cout << "Opção inválida.\n";
            }
        } while (opcao != 'S' && opcao != 's');



    }
    else
    {
        do {
            char letra[19];
            cout << "RapiZinho\n===========\n";
            if (numItens > 0)
            {
                for (int i = 0; i < numItens; i++)
                {
                    cout << pedido[i].quantidade << " x " << pedido[i].nome << " de R$"; 
                    cout.setf(ios_base::fixed,ios_base::floatfield);
                    cout.precision(2);
                    cout << pedido[i].preco << " = R$" << pedido[i].quantidade * pedido[i].preco << endl;
                    
                    
                       
                    
                }cout << "===========\n";
            }
            

            for (int i = 0; i < numProdutos; (i++))
            {
                cout << "(" << char('A' + i) << ")";
                letra[i] = char('A'+i);

                cout << estocador[i].nome << endl;
            }

            cout << "(S) Sair\n";
            cout << "Opção[ ]\b\b";
            cin >> op;
            op = toupper(op);
            for (int i = 0; i < numProdutos; i++)
            {
                if (op == letra[i])
                {
                   pedido = adicionarcarrinho(pedido, &numItens, estocador,& numProdutos, i);

                }
            }
            
            }while (op != 'S' && op != 's');
            if (numItens==0)
            {
                cout << "Fim!\n";
            }
            else
            {
            int contador = 1;
            gerarRecibo(pedido,numItens, desconto, pagamento, contador, estocador, &numProdutos);
            
            }
           
           
    }


    salvarEstoque(estocador, &numProdutos);
    
}
