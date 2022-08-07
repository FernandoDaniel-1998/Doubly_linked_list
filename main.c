/* Fernando Daniel Marcelino RA 156490 Turma IB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// CRIANDO A ESTRUTURA DA LISTA DUPLAMENTE ENCADEADA
typedef struct lista2 {
int coeficiente;
int grau;
struct lista2* ant;
struct lista2* prox;
}TLista2;
typedef TLista2 *Pointer;

// DECLARACAO DAS FUNCOES USADAS NA IMPLEMENTACAO
Pointer novo_polinomio(Pointer l,char expressao[]);
Pointer insere_ordenado (Pointer l, int coeficiente, int graupoli);
void libera_rec (Pointer l);
void imprime (Pointer l);
void soma(Pointer Ppoli1, Pointer Ppoli2);
void subrtrair(Pointer Ppoli1, Pointer Ppoli2);
void derivacao(Pointer Ppoli);


int main(void) {

  // CRIANDO E APONTANDO OS PONTEIROS QUE DARAO INICIO DA MINHA LISTA
  Pointer Ppoli1 = NULL;
  Pointer Ppoli2 = NULL;

  int aux,numpoli;

  char expressao1[100], expressao2[100];

  do{

    printf("O que deseja fazer? Digite:\n1 para inserir novos polinomios;\n2 para somar polinimios;\n3 para subtrair polinomios;\n4 para derivar alguma polinomio de sua escolha; e\n5 para sair deste menu.\n\n"); // MENU DE OPCOES

    scanf("%d",&aux); // VARIAVEL USADA PARA IDENTIFICAR O PEDIDO

    switch(aux){

      case 1: 
        printf("Entre com a primeira expressao:\n"); // PEDINDO E LENDO A EXPRESSAO DE ENTRADA
        scanf("%s",expressao1);

        Ppoli1 = novo_polinomio(Ppoli1,expressao1); // CHAMANDO A 1A FUNCAO QUE TRANSFORMARA A ENTRADA EM UMA LISTA

        printf("Entre com a segunda expressao:\n");
        scanf("%s",expressao2);

        Ppoli2 = novo_polinomio(Ppoli2,expressao2); // CHAMANDO A 2A FUNCAO QUE TRANSFORMARA A ENTRADA EM UMA LISTA

        break;
      
      case 2: 
        printf("\nA soma dos polinomios ficara: ");
        soma(Ppoli1 ,Ppoli2); // CHAMANDO A FUNCAO QUE SOMA OS ELEMENTOS DA LISTA

        break;

      case 3:
        printf("\nA subtracao dos polinomios ficara: ");
        subrtrair(Ppoli1, Ppoli2); // CHAMANDO A FUNCAO QUE SUBTRAI OS ELEMENTOS DA LISTA

        break;

      case 4:
        printf("Deseja devidar o polinimio 1 ou 2?\n");
        scanf("%d",&numpoli); // PEDINDO O NUMERO DO POLINOMIO QUE DESEJA DERIVAR

        do{
        switch(numpoli){

          case 1:
          printf("\nA derivada do polinomio de numero 1 ficara: ");
          derivacao(Ppoli1); // DERIVANDO O POLINOMIO 1
          break;

          case 2:
          printf("\nA derivada do polinomio de numero 2 ficara: ");
          derivacao(Ppoli2); // DERIVANDO O POLINOMIO 2
          break;

          default:
          printf("Digito invalido!! Digite 1 para derivar o polinomio 1 e 2 para derivar o polinomio 2.\n");
          break;
        }
        } while(numpoli != 1 && numpoli != 2); // FORCA QUE SOMENTE SEJA ADMITIDO 2 VALORES

        break;

      case 5:
        printf("Voce saiu do menu.\n"); // SAIDA DO MENU
        
        break;

      default:
        printf("Digito invalido!! Digite somente as opcoes oferecidas.\n"); // DIGITO INVALIDO

        break;

    }

  } while (aux != 5); // CONDICAO DE PARADA DO LACO DO MENU
  
  libera_rec(Ppoli1); // DESALOCANDO AS LISTAS
  libera_rec(Ppoli2);

  return 0;
}

Pointer insere_ordenado (Pointer l, int coeficiente, int graupoli) {

  Pointer aux, ant;
  Pointer novo = (Pointer) malloc(sizeof(TLista2));
  // ADOTANDO VALORES PARA A LISTA
  novo -> coeficiente = coeficiente;
  novo -> grau = graupoli;

  if (l == NULL) { // sera o primeiro

    novo->ant = NULL;
    novo->prox = NULL;

    l = novo;
  }
  else {

    aux = l;

    while(aux -> prox != NULL && aux -> grau > graupoli)

      aux = aux -> prox;

      if(aux -> grau > graupoli){ /* insere novo no fim */
        novo->prox = NULL;
        novo->ant = aux;
        aux->prox = novo;
      }
      else{ /* insere depois de aux */
        novo->prox = aux;
        novo->ant = aux->ant;
        if(aux->ant!=NULL) /* se não for o 1o. nó */
        aux->ant->prox = novo;
        else{
          l = novo;/*atualiza início da lista */
          novo->ant = NULL;
        }
        aux->ant = novo;
      }
  }

  return l;
}

void libera_rec (Pointer l){
  
  if (l!=NULL){ // CONFICAO DE PARADA DA RECURSIVIDADE
  libera_rec(l->prox);
  free(l); // DESALOCANDO
  }

}

Pointer novo_polinomio(Pointer l,char expressao[]){

  char *pt;
  char expressaoaux[100];
  strcpy(expressaoaux,expressao); // COPIANDO A STRING PARA PEGAR NUMERO DE ELEMENTOS


  int coeficiente, expoente;
  int tamanho = 0;
  int count=0;
  int fator = 1;

  pt = strtok(expressao, "+-"); // QUEBRANDO EM MONOMIOS

  while (1){ // SOMENTE SAIRA QUANDO ACABAR O MONIMIO

    count++;
    tamanho += (int) strlen(pt);

    sscanf(pt,"%d x ^ %d",&coeficiente,&expoente);
    
    l = insere_ordenado(l,(coeficiente*fator),expoente); // INSERINDO OS ELEMENTOS DA STRING NA LISTA

    if(expressaoaux[tamanho+count-1] == '-'){ // SE O COEFICIENTE FOR NEGATIVO
      fator = -1;
    } else {
      fator = 1;
    }

    pt = strtok(NULL, "+-"); // GARANTINDO A QUEBRA DA STRING NOVAMENTE

    if (pt == NULL){ // CONDICAO DE PARADA DO WHILE
      break;
    }

    expoente = 1;

  }

  return l; // RETORNA A LISTA COMPLETA
}

void imprime (Pointer l){

  Pointer p;

  for (p = l; p != NULL; p = p->prox){
    if(p -> coeficiente > 0){ // SE COEFICIENTE > 0, ACRESCENTA "+", SENAO CONTINUA O "-"
      printf("+");
      printf("%dx^%d", p->coeficiente,p->grau);
    } else 
        printf("%dx^%d", p->coeficiente,p->grau);
  }

  printf("\n"); // APENAS ESTETICO

}

void soma(Pointer Ppoli1, Pointer Ppoli2){

  Pointer Psoma = NULL; // CRIANDO NO PARA PERCORRER E DEPOIS IMPRIMO-O

  while(Ppoli1 != NULL || Ppoli2 != NULL){ // ENQUANTO OS DOIS POLINOMIOS TIVEREM CONTEUDO, CONTINUAREI O LACO

    if(Ppoli1 -> grau > Ppoli2 -> grau){ // IMPLEMENTA NA LISTA DE SOMA QUANDO O MAIOR GRAU FOR DO PRIMEIRO POLINOMIO
      Psoma = insere_ordenado(Psoma,Ppoli1->coeficiente,Ppoli1->grau);
      Ppoli1 = Ppoli1->prox;
      }
        else if(Ppoli1 -> grau < Ppoli2 -> grau){ // IMPLEMENTA NA LISTA DE SOMA QUANDO O MAIOR GRAU FOR DO SEGUNDO POLINOMIO
        Psoma = insere_ordenado(Psoma,Ppoli2->coeficiente,Ppoli2->grau);
        Ppoli2 = Ppoli2->prox;
        } else { // SE FOREM IGUAIS, OCORRE A SOMA
          Psoma = insere_ordenado(Psoma,(Ppoli1->coeficiente+Ppoli2->coeficiente),Ppoli1->grau);
          Ppoli1 = Ppoli1->prox;
          Ppoli2 = Ppoli2->prox;
          }
  }

  imprime(Psoma); // IMPRESSAO DA LISTA

  libera_rec(Psoma);

}

void subrtrair(Pointer Ppoli1, Pointer Ppoli2){

  // ESTA FUNCAO EH IDENTICA A FUNCAO DE SOMA, CONTUDO O QUE MUDA É O SINAL DE "-", COMO DESTACADO

  Pointer Psubtrair = NULL;

  while(Ppoli1 != NULL || Ppoli2 != NULL){

    if(Ppoli1 -> grau > Ppoli2 -> grau){

      if(Ppoli1 -> coeficiente < 0){
        Ppoli1 -> coeficiente = -1*(Ppoli1 -> coeficiente);}

    Psubtrair = insere_ordenado(Psubtrair,Ppoli1->coeficiente,Ppoli1->grau);
    Ppoli1 = Ppoli1->prox;
    }
      else if(Ppoli1 -> grau < Ppoli2 -> grau){

        if(Ppoli2 -> coeficiente < 0){
          Ppoli2 -> coeficiente = -1* (Ppoli2 -> coeficiente);}

        Psubtrair = insere_ordenado(Psubtrair,Ppoli2->coeficiente,Ppoli2->grau);
        Ppoli2 = Ppoli2->prox;
        }
          else {
            Psubtrair = insere_ordenado(Psubtrair,(Ppoli1->coeficiente-Ppoli2->coeficiente),Ppoli1->grau); // AQUI EH ONDE OCORRE A MUDANCA
            Ppoli1 = Ppoli1->prox;
            Ppoli2 = Ppoli2->prox;
          }
  }

  imprime(Psubtrair);

  libera_rec(Psubtrair);

}

void derivacao(Pointer Ppoli){

  Pointer Pderivada = NULL;// CRIANDO A LISTA DE DERIVACAO
  
  int coef, expoe;

  while(Ppoli != NULL){

    expoe = (Ppoli -> grau) - 1; // USANDO A REGRA DO TOMBO
    coef = (Ppoli -> grau)*(Ppoli -> coeficiente);

    Pderivada = insere_ordenado(Pderivada,coef,expoe); // INSERINDO OS VALORES JA MODIFICADOS
    
    Ppoli = Ppoli -> prox;
  }

  imprime(Pderivada); // IMPRIMINDO-A

  libera_rec(Pderivada);

}