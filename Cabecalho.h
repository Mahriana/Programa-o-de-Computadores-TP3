#pragma once

// struct para representar produto
struct Produto {
    char nome[24];
    float preco;
    unsigned quantidade;
};


Produto* aumentarvetor(Produto pedido[], int numProdutos);
Produto* adicionarProduto(Produto estoque[], int *numProdutos);
Produto* adicionarcarrinho(Produto pedido[], int* numItens, Produto estoque[], int *numProdutos, int tam);
void excluirProduto(Produto estoque[], int *numProdutos);
void listarProdutos(const Produto estoque[], int *numProdutos);
void salvarEstoque(const Produto estoque[], int *numProdutos);
void gerarRecibo(Produto pedido[], int numItens, float desconto, char pagamento, int contador, Produto estoque[], int *numProdutos);