/* UNIVERSIDADE ESTADUAL DE MONTES CLAROS - UNIMONTES
Centro de Ciências Exatas e Tecnológicas
Departamento de Ciências da Computação
Curso de Sistemas de Informação
Professor: Renato Afonso Cota Silva
Academico: Nilton Rodrigues Pereira
Academico: Yuri Rodrigo*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

#define TRUE  1
#define FALSE 0
#define MAX 89

typedef struct{
    int cod;
    char nome[51];
    char fabri[51];
    float valor;
    int quantidade;
}TipoItem;

//===============================================================================
//======================== ESTRUTURAS DE LISTA ==================================
typedef struct celula *Apontador;

typedef struct celula{
    TipoItem item;
    Apontador prox;
    Apontador ant;
}Celula;

typedef struct{
    Apontador primeiro;
    Apontador ultimo;
}TipoLista;

//===============================================================================
//==========================ESTRUTURAS DE ÁRVORE SBB=============================

typedef enum {
  Vertical, Horizontal
}Inclinacao;

typedef struct no* ApontadorNo;

typedef struct no{
  TipoItem Reg;
  ApontadorNo Esq, Dir;
  Inclinacao BitE, BitD;
}No;
//==================PROTOTIPOS  de LISTA========================================
void IniciarLista (TipoLista *Lista);
int  TesteListaVazia (TipoLista Lista);
void InserirCelula (TipoLista *Lista, TipoItem X);
void RetiraL(int w, TipoLista *Lista, TipoItem *Item);
void ImprimeLista (TipoLista Lista);
int  Verificar (int  z, TipoLista Lista);
//===================QUICK SORT==================================================
void Ordena(int esq, int dir, TipoLista *Lista);
void Particao(int esq, int dir, int *i, int *j, TipoLista *Lista);
void QuickSortLista(TipoLista *Lista, int tamanho);
//=============================================================================
//====================== FUNCOES PARA HASH ===========================

void PesquisaHashNome( TipoLista *Hash, TipoItem *x);
int CalculoPosicaoNome(TipoItem x);

// PROTOTIPOS DE ARVORE SBB - usadas em ambas estruturas
void EE(ApontadorNo *Ap);
void ED(ApontadorNo *Ap);
void DD(ApontadorNo *Ap);
void DE(ApontadorNo *Ap);
void DesalocaArvore (ApontadorNo *Arvore);
void Inicializa(ApontadorNo *Arvore);
void EsqCurto(ApontadorNo *Ap, short *Fim);
void DirCurto(ApontadorNo *Ap, short *Fim);
void Antecessor(ApontadorNo q, ApontadorNo *r, short *Fim);
//===========================================================================
// PROTOTIPOS DE ARVORE SBB - PESQUISA POR CODIGO DO PRODUTO
void IInsere(TipoItem x, ApontadorNo *Ap, Inclinacao *IAp, short *Fim);
void Insere(TipoItem x, ApontadorNo *Ap);
void Retira(TipoItem x, ApontadorNo *Ap);
void IRetira(TipoItem x, ApontadorNo *Ap, short *Fim);
void Pesquisa(TipoItem *x, ApontadorNo *p, int quantidade);
//===========================================================================
// PROTOTIPOS DE ARVORE SBB - PESQUISA POR NOME DO FABRICANTE DO PRODUTO
void IInsere_nome(TipoItem x, ApontadorNo *Ap, Inclinacao *IAp, short *Fim);
void Insere_nome(TipoItem x, ApontadorNo *Ap);
void Retira_nome(TipoItem x, ApontadorNo *Ap);
void IRetira_nome(TipoItem x, ApontadorNo *Ap, short *Fim);
void Pesquisa_nome(TipoItem *x, ApontadorNo *p, int quantidade);
//=========================OUTROS PROTOTIPOS==================================
void menu();
void Salvar(TipoLista Lista, FILE *pFile);
int Tamanho(TipoLista Lista);
void condicao(TipoLista Lista, TipoItem *X);
//=========================FUNÇÃO PRINCIPAL===================================
int main(){

    system("title Controle De Estoque 2011");
    system("color 0f");

    int op,z,d,i,k,a,h,l,posicao;
    char resp,c,e;

    TipoItem item;
    TipoLista Lista;
    ApontadorNo Arvore_cod;
    ApontadorNo Arvore_nome;

    IniciarLista(&Lista);
    Inicializa(&Arvore_cod);
    Inicializa(&Arvore_nome);

    TipoLista Hash_nome[MAX];

    i=0;

    FILE *ArqDados;

    ArqDados = fopen ("Registro_AEDSII.txt","a+");

    for(h=0;h<MAX;h++){
        IniciarLista(&Hash_nome[i]);
    }

    do{
        menu();
		scanf("%d",&op);
		system("cls");
        if(op==1){
            do{
                printf("\t\tGERENCIAMENTO DE ESTOQUE\n\n\tINCLUSAO DE NOVO CADASTRO\n\n");
                fflush(stdin);
                printf("Digite o codigo do produto: ");
                scanf("%d",&item.cod);
                printf("\nDigite o nome do produto: ");
                fflush(stdin);
                gets(&item.nome[i]);
                printf("\nDigite o valor: ");
                fflush(stdin);
                scanf("%f",&item.valor);
                printf("\nDigite o fabricante: ");
                fflush(stdin);
                gets(&item.fabri[i]);
                printf("\nDigite a quantidade: ");
                fflush(stdin);
                scanf("%d",&item.quantidade);
                InserirCelula(&Lista,item);
                printf("\n\tDeseja digita novamente? (S/N).:");
                fflush(stdin);
                Insere(item,&Arvore_cod);
                Insere_nome(item,&Arvore_nome);
                posicao = CalculoPosicaoNome(item);
                InserirCelula(&Hash_nome[posicao], item);
                posicao=0;
                scanf("%c",&resp);
                system("cls");
            }while(resp=='s');
            system("cls");
        }

        if(op==2){
            printf("\t\t\tESTOQUE\n");
            ImprimeLista(Lista);
            system("pause");
            system("cls");
        }

        if(op==3){
            if(TesteListaVazia(Lista)){
                ImprimeLista(Lista);
                system("pause");
                system("cls");
            }
            else{
                ImprimeLista(Lista);
                do{
                    printf("\n\tQual deseja remover.:");
                    scanf("%d",&k);
                    if(Verificar(k,Lista)==1){
                        fflush(stdin);
                        RetiraL(k,&Lista,&item);
                        Retira(item, &Arvore_cod);
                        Retira_nome(item, &Arvore_nome);
                        fflush(stdin);
                        printf("\n\tDeseja Remover novamente? (S/N).:");
                        fflush(stdin);
                        scanf("%c",&resp);
                    }
                }while(resp=='s');
                system("pause");
                system("cls");
            }
        }

        if(op==4){
            if(TesteListaVazia(Lista)){
                ImprimeLista(Lista);
                system("pause");
                system("cls");
            }
            else{
                printf("\t\tOrdenado por valor\n");
                d=Tamanho(Lista);
                QuickSortLista(&Lista,d);
                ImprimeLista(Lista);
                system("pause");
                system("cls");
            }
        }

        if(op==5){
            if(TesteListaVazia(Lista)){
                ImprimeLista(Lista);
                system("pause");
                system("cls");
            }
            else{
                printf("\n\n\n Digite o codigo que deseja encontrar: ");
                scanf("%d", &item.cod);
                fflush(stdin);
                Pesquisa(&item, &Arvore_cod, item.quantidade);
                printf("\n");
                system("pause");
            }
            system("cls");

        }

        if(op==6){
            if(TesteListaVazia(Lista)){
                ImprimeLista(Lista);
                system("pause");
                system("cls");
            }
            else{
                printf("\n\n\nDigite o nome que deseja pesquisar: ");
                fflush(stdin);
                gets(&item.nome[i]);
                fflush(stdin);
                posicao=CalculoPosicaoNome(item);
                PesquisaHashNome(&Hash_nome[posicao], &item);
                posicao=0;
                system("pause");
                system("cls");
            }
            system("cls");
        }

        if(op==7){
            if(TesteListaVazia(Lista)){
                ImprimeLista(Lista);
                system("pause");
                system("cls");
            }
            else{
                printf("\n\n\nDigite o nome do Fabricante que deseja pesquisar: ");
                fflush(stdin);
                gets(&item.fabri[i]);
                fflush(stdin);
                Pesquisa_nome(&item, &Arvore_nome, item.quantidade);
                system("pause");
                system("cls");
            }
            system("cls");
        }

        if(op==8){
            if(TesteListaVazia(Lista)){
                ImprimeLista(Lista);
                system("pause");
                system("cls");
            }
            else{
                ArqDados = fopen ("Registro_AEDSII.txt","w");
                Salvar(Lista,ArqDados);// salva os dados no documento
                fclose (ArqDados);
            }
            system("pause");
            system("cls");
        }

        if(op==9){
            system("cls");
            if((ArqDados=fopen("Registro_AEDSII.txt","a+"))!= NULL){
                printf("\n\t\tVisualizar o historico\n\n");
                while( (e=fgetc(ArqDados)) != EOF){
                       putchar(e);
                    }
            }
            else{
                printf("\n Dados indisponiveis. \n\n");
                }

            printf("\n\n\n");
            system("pause");
            fclose(ArqDados);
            system("cls");
        }

        if(op<1||op>10){
            system("color 4f");
            printf("\tOpcao Invalida\n");
            system("pause");
            system("cls");
            system("color 0f");
        }

         else if(op==10){
            exit(1);
        }

    }while(op>0||op<10);
}

//---------------FUNÇÕES DE LISTA----------------------------
void IniciarLista(TipoLista *Lista){
    Lista->primeiro=(Apontador)malloc(sizeof(Celula));
    Lista->primeiro->prox=NULL;
    Lista->primeiro->ant=NULL;
    Lista->ultimo=Lista->primeiro;
}

int TesteListaVazia(TipoLista Lista){
    return(Lista.primeiro==Lista.ultimo);
}

void InserirCelula(TipoLista *Lista, TipoItem X){
    Apontador aux;
    aux=Lista->ultimo;
    Lista->ultimo->prox=(Apontador)malloc(sizeof(Celula));
    Lista->ultimo=Lista->ultimo->prox;
    Lista->ultimo->ant=aux;
    Lista->ultimo->item=X;
    Lista->ultimo->prox=NULL;
}

void RetiraL(int w, TipoLista *Lista, TipoItem *item){
    Apontador q,Aux;
    Aux = Lista->primeiro;
    q = Aux->prox;
    if(TesteListaVazia(*Lista)==1){
        printf("Erro: Lista vazia ou posicao nao existe \n");
        return;
    }
    while(q != NULL){
        if(q->item.cod==w){
            *item = q->item;
            Aux->prox=q->prox;
            if(Aux->prox==NULL){
                Lista->ultimo=Aux;
            }
            free(q);
            return;
        }
        q=q->prox;
        Aux = Aux->prox;
    }
}

void ImprimeLista(TipoLista Lista){
    Apontador aux;
    int p=0;
    if(TesteListaVazia(Lista) == 1){
        printf("\n\n Erro: Vazia!\n\n");
        return;
    }
    aux=Lista.primeiro->prox;
    while(aux != NULL){
        printf("\n%d \tCodigo do produto: %d\n",p ,aux->item.cod);
        printf("\tNome do produto: %s\n",aux->item.nome);
        printf("\tValor:R$ %.2f\n", aux->item.valor);
        printf("\tFabricante: %s\n",aux->item.fabri);
        printf("\tEm estoque: %d\n",aux->item.quantidade);
        p++;
        aux=aux->prox;
    }
}

int Tamanho(TipoLista Lista){
    int cont=0;
    Apontador Aux;
    Aux=Lista.primeiro->prox;
    while(Aux!=NULL){
        Aux=Aux->prox;
        cont++;
    }
    //printf("\n\tTamanho da Lista %d\n",cont);
    return(cont);
}

int Verificar(int z, TipoLista Lista){
    Apontador Aux;
    int i=0;
    Aux=Lista.primeiro->prox;
    if(TesteListaVazia(Lista)==1){
        printf("Erro:Lista vazia!\n");
        system("pause");
        return(0);
    }
    while(Aux!=NULL){
        if(Aux->item.cod==z){
            printf("\n\tNumero encontrado\n");
            printf("Posicao: %d\n\n",i);
            system("pause");
            return(1);
        }
        Aux=Aux->prox;
        i++;
    }
    printf("\n\tNumero nao encontrado\n");
    system("pause");
    return(0);
}

//============== Funções para o Quicksort ================================
void QuickSortLista(TipoLista *Lista, int tamanho){
    Ordena( 1, tamanho, Lista);
}

void Ordena(int esq, int dir, TipoLista *Lista){
    int i, j;
    Particao( esq, dir, &i, &j, Lista );
    if( esq<j){
        Ordena( esq, j, Lista);
    }
    if(i<dir){
        Ordena(i, dir, Lista);
    }
}

void Particao(int esq, int dir, int *i, int *j, TipoLista *Lista){
    int val1, val2;
    Apontador aux, aux2, aux_pivo;
    int pivo, prim,ulti, piv;
    TipoItem tmp;
    *i=esq;
    *j=dir;
    // Inicializa a posicao dos ponteiros
    aux=Lista->primeiro->prox;
    aux2= Lista->primeiro->prox;
    //Faz a busca para chegar na cell 'i'
    prim=1;
    while(prim!=(*i)){
            aux=aux->prox;
            prim++;
    }
    // Faz a busca para chegar na cell 'j'
    ulti=1;
    while(ulti!=(*j)){
            aux2=aux2->prox;
            ulti++;
    }
    // Calcula a posicao do pivo
    pivo=(*i+*j)/2;
    piv=*i;
    aux_pivo=aux;
    while((piv!=pivo)){
            aux_pivo=aux_pivo->prox;
            piv++;
    }
    pivo=aux_pivo->item.valor;
    // Comparações
    do{
        // Confere se o item da esquerda é maior que o pivo
        while(pivo < aux->item.valor){
            (*i)++;
            aux=aux->prox;
        }
        // Confere se o item da direita é menor que o pivo
        while(pivo > aux2->item.valor){
            (*j)--;
            aux2= aux2->ant;
        }
        // se o da direita for menor que o da esquerda, troca.
        if( (*i)<=(*j)){
            tmp = aux->item;
            aux->item = aux2->item;
            aux2->item = tmp;
            // o da direita passa pro proximo da esquerda
            (*i)++;
            aux=aux->prox;
            // o da esquerda volta para o anterior da direita
            (*j)--;
            aux2= aux2->ant;
        }
    }while((*i)<=(*j));
}

//===================== FUNCOES DE ARVORE SBB =========================

void DesalocaArvore(ApontadorNo *No){
    if((*No) == NULL){
       return;
    }
    DesalocaArvore(&((*No)->Esq));
    DesalocaArvore(&((*No)->Dir));
    free(*No);
    return;
}

void EE(ApontadorNo *Ap) {
  ApontadorNo Ap1;

  Ap1 = (*Ap)->Esq;
  (*Ap)->Esq = Ap1->Dir;
  Ap1->Dir = *Ap;
  Ap1->BitE = Vertical;
  (*Ap)->BitE = Vertical;
  *Ap = Ap1;
}

void ED(ApontadorNo *Ap) {
  ApontadorNo Ap1, Ap2;

  Ap1 = (*Ap)->Esq;
  Ap2 = Ap1->Dir;
  Ap1->BitD = Vertical;
  (*Ap)->BitE = Vertical;
  Ap1->Dir = Ap2->Esq;
  Ap2->Esq = Ap1;
  (*Ap)->Esq = Ap2->Dir;
  Ap2->Dir = *Ap;
  *Ap = Ap2;
}

void DD(ApontadorNo *Ap) {
  ApontadorNo Ap1;

  Ap1 = (*Ap)->Dir;
  (*Ap)->Dir = Ap1->Esq;
  Ap1->Esq = *Ap;
  Ap1->BitD = Vertical;
  (*Ap)->BitD = Vertical;
  *Ap = Ap1;
}

void DE(ApontadorNo *Ap) {
  ApontadorNo Ap1, Ap2;

  Ap1 = (*Ap)->Dir;
  Ap2 = Ap1->Esq;
  Ap1->BitE = Vertical;
  (*Ap)->BitD = Vertical;
  Ap1->Esq = Ap2->Dir;
  Ap2->Dir = Ap1;
  (*Ap)->Dir = Ap2->Esq;
  Ap2->Esq = *Ap;
  *Ap = Ap2;
}

void Inicializa(ApontadorNo *Arvore) {
  *Arvore = NULL;
}

void EsqCurto(ApontadorNo *Ap, short *Fim) {
  /* Folha esquerda retirada => arvore curta na altura esquerda */
  ApontadorNo Ap1;
  if ((*Ap)->BitE == Horizontal) {
	(*Ap)->BitE = Vertical;
	*Fim = TRUE;
	return;
  }
  if ((*Ap)->BitD == Horizontal) {
	Ap1 = (*Ap)->Dir;
    (*Ap)->Dir = Ap1->Esq;
    Ap1->Esq = *Ap;
    *Ap = Ap1;
    if ((*Ap)->Esq->Dir->BitE == Horizontal) {
    	DE(&(*Ap)->Esq);
    	(*Ap)->BitE = Horizontal;
	}
    else
      if ((*Ap)->Esq->Dir->BitD == Horizontal) {
      	DD(&(*Ap)->Esq);
      	(*Ap)->BitE = Horizontal;
	  }
    *Fim = TRUE;
    return;
  }
  (*Ap)->BitD = Horizontal;
  if ((*Ap)->Dir->BitE == Horizontal) {
	DE(Ap);
	*Fim = TRUE;
	return;
  }
  if ((*Ap)->Dir->BitD == Horizontal) {
	DD(Ap);
	*Fim = TRUE;
  }
}

void DirCurto(ApontadorNo *Ap, short *Fim) {
  /* Folha direita retirada => arvore curta na altura direita */
  ApontadorNo Ap1;
  if ((*Ap)->BitD == Horizontal) {
	(*Ap)->BitD = Vertical;
	*Fim = TRUE;
	return;
  }
  if ((*Ap)->BitE == Horizontal) {
  	Ap1 = (*Ap)->Esq;
  	(*Ap)->Esq = Ap1->Dir;
  	Ap1->Dir = *Ap;
  	*Ap = Ap1;
    if ((*Ap)->Dir->Esq->BitD == Horizontal) {
		ED(&(*Ap)->Dir);
		(*Ap)->BitD = Horizontal;
	}
    else
      if ((*Ap)->Dir->Esq->BitE == Horizontal) {
		EE(&(*Ap)->Dir);
		(*Ap)->BitD = Horizontal;
	  }
    *Fim = TRUE;
    return;
  }
  (*Ap)->BitE = Horizontal;
  if ((*Ap)->Esq->BitD == Horizontal) {
  	ED(Ap);
  	*Fim = TRUE;
  	return;
  }
  if ((*Ap)->Esq->BitE == Horizontal) {
  	EE(Ap);
  	*Fim = TRUE;
  }
}

void Antecessor(ApontadorNo q, ApontadorNo *r, short *Fim) {
  if ((*r)->Dir != NULL) {
  	Antecessor(q, &(*r)->Dir, Fim);
    if (!*Fim)
		DirCurto(r, Fim);
    return;
  }
  q->Reg = (*r)->Reg;
  q = *r;
  *r = (*r)->Esq;
  free(q);
  if (*r != NULL)
    *Fim = TRUE;

}

// ============= SBB PARA PESQUISA POR CODIGO DO PRODUTO ===============

void IRetira(TipoItem x, ApontadorNo *Ap, short *Fim) {
  No *Aux;
  if (*Ap == NULL) {
    system("color 4f");
	printf("\n\n\t Codigo invalido ou inexistente. \n");
	system("pause");
	system("color 0f");
	*Fim = TRUE;
	return;
	}
  if (x.cod < (*Ap)->Reg.cod) {
  	IRetira(x, &(*Ap)->Esq, Fim);
    if (!*Fim)
		EsqCurto(Ap, Fim);
    return;
  }
  if (x.cod > (*Ap)->Reg.cod) {
  	IRetira(x, &(*Ap)->Dir, Fim);
    if (!*Fim)
		DirCurto(Ap, Fim);
    return;
  }
  *Fim = FALSE;
  Aux = *Ap;
  if (Aux->Dir == NULL) {
	*Ap = Aux->Esq;
    free(Aux);
    if (*Ap != NULL)
      *Fim = TRUE;
    return;
  }
  if (Aux->Esq == NULL) {
	*Ap = Aux->Dir;
	free(Aux);
    if (*Ap != NULL)
	  *Fim = TRUE;
    return;
  }
  Antecessor(Aux, &Aux->Esq, Fim);
  if (!*Fim)
	EsqCurto(Ap, Fim); /* Encontrou chave */
}

void IInsere(TipoItem x, ApontadorNo *Ap, Inclinacao *IAp, short *Fim) {
  if (*Ap == NULL) {
  	*Ap = (ApontadorNo)malloc(sizeof(No));
    *IAp = Horizontal;
    (*Ap)->Reg = x;
    (*Ap)->BitE = Vertical;
    (*Ap)->BitD = Vertical;
    (*Ap)->Esq = NULL;
    (*Ap)->Dir = NULL;
    *Fim = FALSE;
    return;
  }
  if (x.cod < (*Ap)->Reg.cod) {
  	IInsere(x, &(*Ap)->Esq, &(*Ap)->BitE, Fim);
    if (*Fim)
		return;
    if ((*Ap)->BitE != Horizontal) {
    	*Fim = TRUE;
    	return;
	}
    if ((*Ap)->Esq->BitE == Horizontal) {
    	EE(Ap);
    	*IAp = Horizontal;
    	return;
	}
    if ((*Ap)->Esq->BitD == Horizontal) {
    	ED(Ap);
    	*IAp = Horizontal;
	}
    return;
  }
  IInsere(x, &(*Ap)->Dir, &(*Ap)->BitD, Fim);
  if (*Fim)
	return;
  if ((*Ap)->BitD != Horizontal) {
  	*Fim = TRUE;
  	return;
  }
  if ((*Ap)->Dir->BitD == Horizontal) {
  	DD(Ap);
  	*IAp = Horizontal;
  	return;
  }
  if ((*Ap)->Dir->BitE == Horizontal) {
  	DE(Ap);
  	*IAp = Horizontal;
  }
}

void Insere(TipoItem x, ApontadorNo *Ap) {
  short Fim;
  Inclinacao IAp;
  IInsere(x, Ap, &IAp, &Fim);
}

void Retira(TipoItem x, ApontadorNo *Ap) {
  short Fim;
  IRetira(x, Ap, &Fim);
}

void Pesquisa(TipoItem *x, ApontadorNo *p, int quantidade) {
  int i;
  if (*p == NULL) {
    system("color 4f");
  	printf("\n\n\t Erro: Registro nao encontrado! \n");
  	system("pause");
    system("cls");
  	system("color 0f");
    return;
  }

  if (x->cod < (*p)->Reg.cod) {
  	Pesquisa(x, &(*p)->Esq, quantidade);
    return;
  }

  if (x->cod > (*p)->Reg.cod)
	Pesquisa(x, &(*p)->Dir, quantidade);
  else
    *x = (*p)->Reg;

    if( x->cod == (*p)->Reg.cod){
        printf("\n\n\t Registro Encontrado: \n");
        printf("\n Codigo do produto: %d\t\t",x->cod);
        printf("\n Nome: %s",x->nome);
        printf("\n Valor: %.2f ",x->valor);
        printf("\tFabricante: %s\n",x->fabri);
        printf("\n Estoque: %d ",x->quantidade);
        return;
    }
}

//================ PESQUISA POR NOME DO FABRICANTE DO PRODUTO =================

void IInsere_nome(TipoItem x, ApontadorNo *Ap, Inclinacao *IAp, short *Fim) {
  if (*Ap == NULL) {
  	*Ap = (ApontadorNo)malloc(sizeof(No));
    *IAp = Horizontal;
    (*Ap)->Reg = x;
    (*Ap)->BitE = Vertical;
    (*Ap)->BitD = Vertical;
    (*Ap)->Esq = NULL;
    (*Ap)->Dir = NULL;
    *Fim = FALSE;
    return;
  }

  // se o primeiro nome for menor que o segundo nome
  // este será inserido a direita
  if (strcmpi(x.nome,(*Ap)->Reg.nome)> 0) {
  	IInsere_nome(x, &(*Ap)->Esq, &(*Ap)->BitE, Fim);
    if (*Fim)
		return;
    if ((*Ap)->BitE != Horizontal) {
    	*Fim = TRUE;
    	return;
	}
    if ((*Ap)->Esq->BitE == Horizontal) {
    	EE(Ap);
    	*IAp = Horizontal;
    	return;
	}
    if ((*Ap)->Esq->BitD == Horizontal) {
    	ED(Ap);
    	*IAp = Horizontal;
	}
    return;
  }

  // Caso o primeiro nome seja maior que o segundo
  // este sera inserido a sua esquerda
  IInsere_nome(x, &(*Ap)->Dir, &(*Ap)->BitD, Fim);
  if (*Fim)
	return;
  if ((*Ap)->BitD != Horizontal) {
  	*Fim = TRUE;
  	return;
  }
  if ((*Ap)->Dir->BitD == Horizontal) {
  	DD(Ap);
  	*IAp = Horizontal;
  	return;
  }
  if ((*Ap)->Dir->BitE == Horizontal) {
  	DE(Ap);
  	*IAp = Horizontal;
  }
}

void Insere_nome(TipoItem x, ApontadorNo *Ap) {
  short Fim;
  Inclinacao IAp;
  IInsere_nome(x, Ap, &IAp, &Fim);
}

void IRetira_nome(TipoItem x, ApontadorNo *Ap, short *Fim) {
  No *Aux;
  if (*Ap == NULL) {
    system("cls");
    system("color 4f");
	printf("\n\n\t Este nome nao esta na arvore. \n");
	*Fim = TRUE;
	return;
	}
  // Caso o nome seja menor
  if (strcmpi(x.nome,(*Ap)->Reg.nome)>0) {
  	IRetira_nome(x, &(*Ap)->Esq, Fim);
    if (!*Fim)
		EsqCurto(Ap, Fim);
    return;
  }
  // Caso o nome seja maior
  if (strcmpi(x.nome, (*Ap)->Reg.nome)<0) {
  	IRetira_nome(x, &(*Ap)->Dir, Fim);
    if (!*Fim)
		DirCurto(Ap, Fim);
    return;
  }

  *Fim = FALSE;
  Aux = *Ap;
  if (Aux->Dir == NULL) {
	*Ap = Aux->Esq;
    free(Aux);
    if (*Ap != NULL)
      *Fim = TRUE;
    return;
  }
  if (Aux->Esq == NULL) {
	*Ap = Aux->Dir;
	free(Aux);
    if (*Ap != NULL)
	  *Fim = TRUE;
    return;
  }
  Antecessor(Aux, &Aux->Esq, Fim);
  if (!*Fim)
	EsqCurto(Ap, Fim); /* Encontrou chave */
}

void Retira_nome(TipoItem x, ApontadorNo *Ap) {
  short Fim;
  IRetira_nome(x, Ap, &Fim);
}

void Pesquisa_nome(TipoItem *x, ApontadorNo *p, int quantidade) {
  int i;
  if (*p == NULL) {
    system("color 4f");
  	printf("\n\n\t Erro: Registro nao encontrado! \n");
  	system("pause");
    system("cls");
  	system("color 0f");
    return;
  }
  // Caso o nome a ser procurado seja menor
  if (strcmpi(x->nome, (*p)->Reg.nome)>0) {
  	Pesquisa_nome(x, &(*p)->Esq, quantidade);
    return;
  }
  if (strcmpi(x->nome, (*p)->Reg.nome)<0)
	Pesquisa_nome(x, &(*p)->Dir, quantidade);
  else
    *x = (*p)->Reg;

    if( strcmpi(x->nome,(*p)->Reg.nome) == 0){
        printf("\n\t Registro encontrado: \n\n");
        printf("Codigo do produto: %d\n",x->cod);
        printf("Nome: %s\n",x->nome);
        printf("Valor: %.2f\n",x->valor);
        printf("Fabricante: %s\n",x->fabri);
        printf("Estoque: %d \n",x->quantidade);
        return;
    }
}

//================= FUNCOES DE TABELA HASH ============================

int CalculoPosicaoNome(TipoItem x){
    int i, posicao;
    i = atoi(x.nome);
    posicao=i%MAX;
    return(posicao);
}

void PesquisaHashNome(TipoLista *Hash, TipoItem *x){
    Apontador aux;
    int i;
    // caso a lista da tabela esteja vazia
    if( TesteListaVazia(*Hash) == 1){
        system("cls");
        system("color 4f");
        printf("\n Tabela vazia. \n");
        system("pause");
        system("cls");
        system("color 0f");
        return;
    }
    // aux recebe a primeira celula com conteudo
    aux = Hash->primeiro->prox;
    while(aux != NULL){
        // caso o item procurado seja o apontado por aux
        if(strcmpi(aux->item.nome,(*x).nome)==0){
            *x = aux -> item;
            printf("\n\n\t Registro Encontrado: \n");
            printf("\n Codigo do produto: %d\t\t",x->cod);
            printf("\n Nome: %s",x->nome);
            printf("\n Valor: %.2f ",x->valor);
            printf("\tFabricante: %s\n",x->fabri);
            printf("\n Estoque: %d \n",x->quantidade);
            return;
        }
        aux = aux -> prox;
    }
    system("cls");
    system("color 4f");
    printf("\n Posicao vazia. \n");
    system("color 0f");
}
//=====================================================================
//===========================OUTRAS FUNÇÔES============================
void Salvar(TipoLista Lista,FILE *pFile){
    	Apontador Aux;
    	if (TesteListaVazia(Lista)){
    		printf("Erro:Lista vazia!\n");
    		system("pause");
    		return;
    	}
    	Aux = Lista.primeiro->prox;
    	while(Aux != NULL){
            fprintf (pFile,"\tCodigo: %d\n",Aux->item.cod);
            fprintf (pFile,"Nome: %s\n",Aux->item.nome);
            fprintf (pFile,"Valor: %f\n",Aux->item.valor);
            fprintf (pFile,"Fabricante: %s\n",Aux->item.fabri);
            fprintf (pFile,"Estoque: %d\n\n",Aux->item.quantidade);
    		Aux = Aux->prox;
    	}
    	printf("\t\tDados salvos\n");
    	system("pause");
}

void condicao(TipoLista Lista, TipoItem *X){
    Apontador Aux;
    if (TesteListaVazia(Lista)){
    		printf("Erro:Lista vazia!\n");
    		system("pause");
    		return;
    }
    Aux = Lista.primeiro->prox;
    while(Aux != NULL){
        if(Aux==Aux->prox){
            printf("ERRO - O codigo ja existe\n");
            system("pause");
            system("cls");
        }
        Aux = Aux->prox;
    }
}

void menu(){
    printf("\n-------------------Controle De Estoque--------------------\n\n");
    printf("\t\tO que voce desejar fazer:\n");
    printf("\n\t[1] Inserindo\n");
    printf("\t[2] Exiba os produtos\n");
    printf("\t[3] Retirando\n");
    printf("\t[4] Ordenar\n");
    printf("\t[5] Pesquisar por Codigo\n");
    printf("\t[6] Pesquisar por Nome\n");
    printf("\t[7] Pesquisar por Fabricante\n");
    printf("\t[8] Salvar\n");
    printf("\t[9] Visualizar o historico\n");
    printf("\t[10] Sair\n");
    printf("\n\t\tOPCAO.:");
}
