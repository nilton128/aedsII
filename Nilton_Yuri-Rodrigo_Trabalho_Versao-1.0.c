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

//==================PROTOTIPOS  de LISTA========================================
void IniciarLista (TipoLista *Lista);
int  TesteListaVazia (TipoLista Lista);
void InserirCelula (TipoLista *Lista, TipoItem X);
void RetiraL(int w, TipoLista *Lista, TipoItem *Item);
void ImprimeLista (TipoLista Lista);
int  Verificar (int  z, TipoLista Lista);

//=========================OUTROS PROTOTIPOS==================================
void menu();
int Tamanho(TipoLista Lista);

//=========================FUNÇÃO PRINCIPAL===================================
int main(){

    system("title Controle De Estoque 2011");
    system("color 0f");

    int op,z,d,i,k;
    char resp,c;

    TipoItem item;
    TipoLista Lista;

    IniciarLista(&Lista);

    i=0;

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

        }

        if(op==5){

        }

        if(op==6){

        }

        if(op==7){

        }

        if(op==8){

        }

        if(op==9){

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
//=====================================================================
//===========================OUTRAS FUNÇÔES============================
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
