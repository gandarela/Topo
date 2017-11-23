#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>



struct _Lista{
  int data;
  struct _Lista *prox;
  int cor; // 1 = rubro. 0 = negro
};

typedef struct _Lista LISTA;

LISTA* cria(int v){
  LISTA *pt = (LISTA *) malloc(v * sizeof(LISTA));
  if(pt == NULL)
    exit(1);
  return pt;
}

void insere(LISTA *pt, int x){
  LISTA *aux = NULL;
  aux = pt;
  while(aux->prox != NULL){
    aux = aux->prox;
  }
  aux->prox = malloc(sizeof(LISTA));
  aux->prox->data = x;
  aux->prox->prox = NULL;
}

void imprime(LISTA *pt){
  LISTA *aux = NULL;
  for(aux = pt->prox; aux != NULL; aux = aux->prox)
    printf("%d\n", aux->data);
  free(aux);
}

void listas(int *cont, LISTA *pt, int *c){
  int i;
  char *v = (char *)malloc(sizeof(char) * 30);
  if(v == NULL){
    exit(1);
  }

  gets(v);
  for(i = 0; i < 30; i++){
    if(isdigit(v[i])){
      int a = atoi(&v[i]);
        c[--a]++;
        insere(pt + *(cont), ++a);
        while(a > 9){
          i++;
          a = a/10;
        }
    }
  }
  v = NULL;
  free(v);
}

void topolo(LISTA *pt, int *c, int *topo, int j, int v){
  if(j == v){
    return;
  }
  LISTA *aux = NULL;
  int i;
  for(i = 0; i < v; i++){
    if(c[i] == 0){
      for(aux = (pt + i)->prox; aux != NULL; aux = aux->prox){
        int help = aux->data-1;
        c[help]--;
      }
      *(topo+j) = i+1;
      j++;
      c[i] = -1;
    }
  }
  topolo(pt,c,topo,j,v);
}




int main(void){
  int v, i, a;
  scanf(" %d %d\n", &v, &a);
  int *c = (int *)malloc(sizeof(int) * v);
  for(i = 0; i < v; i++)
    c[i] = 0;

  LISTA *pt = NULL;
  pt = cria(v);
  for(i = 0; i < v;  i++){
    listas(&i,pt,c);
  }

  int *topo = (int *) malloc(sizeof(int) * v);
  if(topo == NULL)
    exit(1);
  for(i = 0; i < v; i++)
    topo[i] = 0;


  i = 0;
  topolo(pt,c,topo,i,v);
  for(i = 0; i < v;  i++){
    printf("%d ", topo[i]);
  }
  printf("\n");

  free(c);
  free(topo);
  free(pt);

  return 0;
}
