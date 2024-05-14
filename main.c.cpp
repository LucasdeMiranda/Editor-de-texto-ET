#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max 70
#define cancelacaractere '#'
#define cancelatudo '-'
#define saltarlinha '*'

typedef struct {
    char palavras[max];
} tipotexto;

typedef struct {
    tipotexto texto[max];
    int topo;
} tipopilha;

void fpvazia(tipopilha *pilha) {
    pilha->topo = 0;
}

int vazia(tipopilha pilha) {
    return (pilha.topo == 0);
} 

void empilha(tipotexto aux, tipopilha *pilha) {
    if (pilha->topo == max) {
        printf("pilha está cheia\n");
    } else {
        pilha->topo++;
        pilha->texto[pilha->topo] = aux;
    }
}

void desempilha(tipopilha *pilha, tipotexto *texto) {
    if (!vazia(*pilha)) {
        *texto = pilha->texto[pilha->topo];
        pilha->topo--;
    }
}

 void imprime(tipopilha *pilha) {
    tipopilha aux;
    tipotexto texto;
    fpvazia(&aux);

    // Copiar pilha para uma pilha auxiliar invertendo a ordem
    while (!vazia(*pilha)) {
        desempilha(pilha, &texto);
        empilha(texto, &aux);
    }

    // Imprimir textos na ordem correta
    while (!vazia(aux)) {
        desempilha(&aux, &texto);
        printf("%s", texto.palavras);
    }
    printf("\n"); 
}


void tratartexto(tipopilha *pilha, tipotexto *texto) {
    char input[max];
    printf("Digite seu texto: ");
    fgets(input, max, stdin);
    input[strcspn(input, "\n")] = '\0'; // Remover o caractere de nova linha
    
    for (int i = 0; i < strlen(input); i++) {
        if (input[i] == cancelacaractere && i > 0) {
            if (!vazia(*pilha)) {
                desempilha(pilha, texto);
            }
        } else if (input[i] == cancelatudo) {
            fpvazia(pilha);
        } else if (input[i] == saltarlinha) {
            imprime(pilha);
        } else {
            tipotexto novoTexto;
            novoTexto.palavras[0] = input[i];
            novoTexto.palavras[1] = '\0';
            empilha(novoTexto, pilha);
        }
    }

    // Verificar se há algum texto restante na pilha e imprimir
    while (!vazia(*pilha)) {
        desempilha(pilha, texto);
        printf("%s", texto->palavras);
    }
}


int main(int argc, char** argv) {
    tipopilha pilha;
    fpvazia(&pilha);

    tipotexto texto;
    tratartexto(&pilha, &texto);

    return 0;
}
