#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "Cabecalho.h"
using namespace std;
Produto* aumentarvetor(Produto vetor[], int numProdutos)
    {
    Produto* expanda = new Produto[numProdutos + 1];
    for (int i = 0; i < numProdutos; i++)
    {
        expanda[i] = vetor[i];
    }
    delete[] vetor;

    return expanda;
}

// Função para adicionar um produto ao estoque
Produto* adicionarProduto(Produto estoque[], int* numProdutos) {
    Produto novoProduto;
    cout << "Produto: ";
    cin.ignore();
    cin.getline(novoProduto.nome, 24);
    cout << "Preço: ";
    cin >> novoProduto.preco;
    cout << "Quantidade: ";
    cin >> novoProduto.quantidade;

    // Verifica se o produto já existe no estoque
    bool produtoExistente = false;
    for (int i = 0; i < *numProdutos; ++i) {
        if (strcmp(estoque[i].nome, novoProduto.nome) == 0) {
            estoque[i].preco = novoProduto.preco;
            estoque[i].quantidade += novoProduto.quantidade;
            produtoExistente = true;
           
        }
    }
    
    // Se o produto não existir, adiciona-o ao estoque
    if (!produtoExistente) {
        estoque = aumentarvetor(estoque, *numProdutos);
        strcpy(estoque[*numProdutos].nome, novoProduto.nome);
        estoque[*numProdutos].preco = novoProduto.preco;
        estoque[*numProdutos].quantidade = novoProduto.quantidade;
        (*numProdutos)++;
    }

    cout << "Produto adicionado ao estoque.\n";

    return estoque;
}

Produto* adicionarcarrinho(Produto pedido[], int* numItens, Produto estoque[], int* numProdutos, int posVetEstoque){
    
    cout << "Pedido\n";
    cout << "======\n";
    cout << estoque[posVetEstoque].nome << endl;
    cout << "R$ " << estoque[posVetEstoque].preco << endl;
    cout << "======\n";
    cout << "Quantidade: [ ]\b\b";
    int tanto;
    cin >> tanto;
   
    // Verifica se o produto já existe no pedido
    int produtoExistente = 0;
    for (int  i = 0; i < *numItens; ++i) {
        if (strcmp(pedido[i].nome, estoque[posVetEstoque].nome) == 0) {
            pedido[i].preco = estoque[posVetEstoque].preco;
            pedido[i].quantidade += estoque[posVetEstoque].quantidade;
            produtoExistente = 1;
            
        }
    }
    // Se o produto não existir, adiciona-o ao pedido
    if (!produtoExistente) {
        pedido = aumentarvetor(pedido, *numItens);
        (*numItens)++;
        strcpy(pedido[*numItens - 1].nome, estoque[posVetEstoque].nome);
        pedido[*numItens - 1].preco = estoque[posVetEstoque].preco;
        pedido[*numItens - 1].quantidade = tanto;
        
    }
    return pedido;
}
// Função para excluir um produto do estoque
void excluirProduto(Produto estoque[], int *numProdutos) {
    cout << "Produtos no estoque:\n";
    for (int i = 0; i < *numProdutos; ++i) {
        cout << i + 1 << ") " << estoque[i].nome << endl;
    }
    int escolha;
    cout << "Produto: ";
    cin >> escolha;

    if (escolha >= 1 && escolha <= *numProdutos) {
        cout << "Deseja excluir \"" << estoque[escolha - 1].nome << "\" (S/N)? ";
        char confirmacao;
        cin >> confirmacao;
        if (confirmacao == 'S' || confirmacao == 's') {
            for (int i = escolha - 1; i < *numProdutos - 1; ++i) {
                estoque[i] = estoque[i + 1];
            }
            (*numProdutos)--;
            cout << "Produto excluído do estoque.\n";
        }
    }
    
}
// Função para listar os produtos do estoque
void listarProdutos(const Produto estoque[], int *numProdutos) {
    cout << "Listagem\n";
    cout << "--------\n";
    for (int i = 0; i < *numProdutos; ++i) {
        cout << estoque[i].nome << " - R$" << fixed << setprecision(2) << estoque[i].preco
            << " - " << estoque[i].quantidade << " und." << endl;
    }
}
// Função para  o estoque em um arquivo de texto
void salvarEstoque(const Produto estoque[], int *numProdutos) {
    ofstream arquivo;
    arquivo.open("estoque.dat", ios_base::out | ios_base::binary);
    if (arquivo.is_open()) {
        arquivo.write((char*)numProdutos, sizeof(int));
        for (int i = 0; i < *numProdutos; ++i) {
            arquivo.write((char*)&estoque[i], sizeof(Produto));


        }
        arquivo.close();
        cout << "Estoque salvo com sucesso.\n";
    }
    else {
        cout << "Erro ao salvar o estoque.\n";
    }arquivo.close();
}
// Função para gerar o recibo de compra
void gerarRecibo(Produto pedido[], int numItens, float desconto, char pagamento, int contador, Produto estoque[], int *numProdutos) {
        char Pix;
        float valorDesconto = 0;
        const float taxaEntrega = 6.00;
        float totalPedido = 0;

        // Exibir o carrinho de compras
        cout << "Carrinho de Compras:\n";
        cout << "====================\n";
        for (int i = 0; i < numItens; i++) {
            totalPedido += pedido[i].preco * pedido[i].quantidade;
            cout << pedido[i].quantidade << " x " << pedido[i].nome << " - R$" << pedido[i].preco << " cada\n";
        }
        
         cout << "Taxa de Entrega: R$" << taxaEntrega << endl;
        cout << "====================\n";
        cout << "Total do Pedido: R$" << totalPedido << endl;

        // Calcular e exibir taxa de entrega
        totalPedido += taxaEntrega;
        cout << endl;
        cout << "[P] Pix\n";
        cout << "[C] Cartão\n";
        cout << "Pagamento: [ ]\b\b";

        cin >> Pix;
        switch (Pix)
        {
        case 'p':
        case'P':
            desconto = 0.1;
            break;
        case'c':
        case 'C':
            desconto = 0.05;
            break;
        }
        // Aplicar desconto, se houver
        if (desconto > 0) {
            valorDesconto = totalPedido * desconto;
            totalPedido -= valorDesconto;
            
        }
        // Exibir total final
        cout << "Carrinho de Compras:\n";
        cout << "====================\n";
        for (int i = 0; i < numItens; i++) {
            
            cout << pedido[i].quantidade << " x " << pedido[i].nome << " - R$" << pedido[i].preco << " cada\n";
        }

        cout << "Taxa de Entrega: R$" << taxaEntrega << endl;
        cout << "Desconto de " << desconto * 100 << "% = R$" << valorDesconto << endl;
        cout << "====================\n";
        cout << "Total a Pagar: R$" << totalPedido << endl;

        // Processar o pagamento
        char confirmacao;
        cout << "Confirmar Pedido (S/N): ";
        cin >> confirmacao;

        if (confirmacao == 'S' || confirmacao == 's') {
            // Gerar recibo em arquivo

            ofstream fout;
            char fds[20] = "pedido_";
            const unsigned int aux = 4;
            char op;
            
                char rede[4];
                cout.setf(ios_base::fixed, ios_base::floatfield);
                cout.precision(2);

                strcat(fds, _itoa(contador, rede, 10));
                strcat(fds, ".txt");

                fout.open(fds, ios_base::out | ios_base::binary);
                if (!fout.is_open())
                {
                    cout << "O arquivo não foi aberto corretamente!";
                    exit(1);
                }


                fout << "Pedido #" << contador << endl;

            if (fout.is_open()) {
                fout << "Recibo de Compra\n";
                fout << "====================\n";
                for (int i = 0; i < numItens; i++) {
                    fout << pedido[i].quantidade << " x " << pedido[i].nome << " - R$" << pedido[i].preco << " cada\n";
                }
                fout << "====================\n";
                fout << "Taxa de Entrega: R$" << taxaEntrega << endl;
                if (desconto > 0) {
                    fout << "Desconto: R$" << totalPedido * desconto << endl;
                }
                fout << "====================\n";
                fout << "Total: R$" << totalPedido << endl;
                fout.close();
                cout << "Recibo gerado com sucesso!\n";

                // Atualizar estoque
                for (int i = 0; i < numItens; i++) {
                    for (int j = 0; j < *numProdutos; j++) {
                        if (strcmp(pedido[i].nome, estoque[j].nome) == 0) {
                            estoque[j].quantidade -= pedido[i].quantidade;
                            
                        }
                    }
                }
            }
            else {
                cout << "Erro ao gerar recibo.\n";
            }
        }
        else {
            cout << "Pedido cancelado.\n";
        }
    }


