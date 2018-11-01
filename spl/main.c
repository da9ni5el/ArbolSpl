#include <stdio.h>
#include <stdlib.h>
#include "recurso.h"

int escribirMenu()
{
    int opcion = 0;
    puts("1- INSERTAR");
    puts("2- MODIFICAR");
    puts("3- ELIMINAR");
    puts("4- BUSCAR");
    puts("5- GRAFICAR");
    puts("6- SALIR");
    scanf("%d", &opcion);
    return opcion;        
}


void menu()
{
    int opcion = 0;
    int valor = 0;
    while((opcion = escribirMenu())<=5)
    {        
        switch (opcion)
        {
            case 1:
                puts("Ingrese un digito cualquiera");
                scanf("%d", &valor);
                insertar(&raiz, valor);
                break;
            case 2:
                puts("Ingrese el digito que desea modificar");

                puts("Ingrese el nuevo valor");
                break;
            case 3:
                puts("Ingrese el digito que desea eliminar");
                break;
            case 4:
                puts("Ingrese el digito que desea buscar");
                break;
            case 5:
                puts("Graficando...");
                graficar(raiz);
                break;
        }
    }    
}

nodo*crearNuevo(int valor)
{
    nodo*nuevo = (nodo*)malloc(sizeof(nodo));
    nuevo->valor = valor;
    nuevo->izdo = NULL;
    nuevo->dcho = NULL;
    nuevo->padre = NULL;
    return nuevo;
}

int insertar(nodo**raiz, int valor)
{
    nodo*padre = NULL;
    nodo*pivote = *raiz;

    while(pivote != NULL)
    {
        padre = pivote;
        if(valor > pivote->valor)
            pivote = pivote->dcho;
        else if(valor < pivote->valor)
            pivote = pivote->izdo;
    }
    if(padre == NULL)
    {
        *raiz = crearNuevo(valor);
        return 1;
    }
    else if(valor < padre->valor)
    {
        padre->izdo = crearNuevo(valor);
        padre->izdo->padre = padre;
        balancear((padre->izdo));
        return 1;
    }
    else if(valor > padre->valor)
    {
        padre->dcho = crearNuevo(valor);
        padre->dcho->padre = padre;
        balancear((padre->dcho));
        return 1;
    }
}

int buscar(nodo**raiz, int buscado)
{
    nodo*padre = NULL;
    nodo*pivote = *raiz;

    while(pivote != NULL)
    {
        padre = pivote;
        if(buscado > pivote->valor)
            pivote = pivote->dcho;
        else if(buscado < pivote->valor)
            pivote = pivote->izdo;
        else if(buscado == pivote->valor)
        {
            balancear(pivote);
            return pivote->valor;
        }        
    }
}

int eliminar(nodo**raiz, int valor)
{
    buscar(&(*raiz), valor);
    nodo*padre = NULL;
    nodo*temporal;
    int aux;

    nodo*pivote = *raiz;
    while(pivote != NULL)
    {
        if(valor == pivote->valor)
        {
            if(pivote->izdo == NULL && pivote->dcho == NULL)
            {
                if(padre != NULL)
                {
                    if(padre->dcho == pivote)
                        padre->dcho = NULL;
                    else if(padre->izdo == pivote)
                        padre->izdo = NULL;                    
                }
                free(pivote);
                return 1;
            }
            else
            {
                padre = pivote;
                if(pivote->dcho != NULL)
                {
                    temporal = pivote->dcho;
                    while(temporal->izdo)
                    {
                        padre = temporal;
                        temporal = temporal->izdo;
                    }
                }
                else
                {
                    temporal = pivote->izdo;
                    while(pivote->dcho)
                    {
                        padre = temporal;
                        temporal = temporal->dcho;
                    }
                }
                aux = pivote->valor;
                pivote->valor = temporal->valor;
                temporal->valor = aux;
                pivote = temporal;
            }
        }
        else
        {
            padre = pivote;
            if(valor > pivote->valor)
                pivote = pivote->dcho;
            else if(valor < pivote->valor)
                pivote = pivote->izdo;
            else if(valor == pivote->valor)
                pivote = pivote->dcho;
        }
    }
    return 0;
}

void balancear(nodo*raiz_)
{
    if(raiz_ == raiz)
        return;
    else if(raiz_->padre->izdo == raiz_)
    {
        nodo*a = raiz_->padre;
        nodo*b = raiz_;
        nodo*c = raiz_->izdo;
        nodo*d = raiz_->dcho;
        nodo*e = raiz_->padre->dcho;
        b->izdo = c;
        b->dcho = a;
        a->izdo = d;
        a->dcho = e;
        if(a->padre != NULL && a->padre->izdo == a)        
            a->padre->izdo = b;
        else if(a->padre != NULL && a->padre->dcho == a)
            a->padre->dcho = b;
        b->padre = a->padre;
        if(c != NULL)
            c->padre = b;
        a->padre = b;
        if(d != NULL)
            d->padre = a;
        if(e != NULL)
            e->padre = a;
        if(a == raiz)
            raiz = b;
        if(raiz_ != raiz)
            balancear(raiz_);
    }
    else if(raiz_->padre->dcho == raiz_)
    {
        nodo*a = raiz_;
        nodo*b = raiz_->padre;
        nodo*c = raiz_->padre->izdo;
        nodo*d = raiz_->izdo;
        nodo*e = raiz_->dcho;
        a->dcho = e;
        a->izdo = b;
        b->izdo = c;
        b->dcho = d;
        if(b->padre != NULL && b->padre->izdo == b)
            b->padre->izdo = a;
        else if(b->padre != NULL && b->padre->dcho == b)
            b->padre->dcho = a;
        a->padre = b->padre;
        b->padre = a;
        if(e != NULL)
            e->padre = a;
        if(c != NULL)
            c->padre= b;
        if(d != NULL)
            d->padre = b;
        if(b == raiz)
            raiz = a;
        if(raiz_ != raiz)
            balancear(raiz_);
    }
}

void graficar(nodo*raiz)
{
    fp = fopen("spl.dot", "w");
    fprintf(fp, "digraph spl{\ngraph[overlap=true];\n");
    toDot(raiz, fp);
    fprintf(fp, "}");
    fclose(fp);
    system("dot -Tpng spl.dot -o spl.png");
    system("eog spl.png");
}

void toDot(nodo*raiz, FILE*fp)
{
    if(raiz == NULL)
        return;
    fprintf(fp, "nodo%p[label=\"Dato:%d\"];\n", &(*raiz), raiz->valor);
    if(raiz->izdo != NULL)
    {
        fprintf(fp, "nodo%p[label=\"Dato:%d\"];\n", &((*raiz->izdo)), raiz->izdo->valor);
        fprintf(fp, "nodo%p->nodo%p[label=\"izdo\"];\n", &(*raiz), &((*raiz->izdo)));
        toDot(raiz->izdo, fp);
    }
    if(raiz->dcho != NULL)
    {
        fprintf(fp, "nodo%p[label=\"Dato:%d\"];\n", &((*raiz->dcho)), raiz->dcho->valor);
        fprintf(fp, "nodo%p->nodo%p[label=\"dcho\"];\n", &(*raiz), &((*raiz->dcho)));
        toDot(raiz->dcho, fp);
    }
}

void inicializarNodo(nodo**temporal)
{
    (*temporal)->valor = 0;
    (*temporal)->izdo = NULL;
    (*temporal)->dcho = NULL;
    (*temporal)->padre = NULL;
}

int main()
{
    raiz = (nodo*)malloc(sizeof(nodo));
    inicializarNodo(&raiz);

    //inserciones 
    puts("INSERCIONES");
    insertar(&raiz, 45);
    insertar(&raiz, 15);
    insertar(&raiz, 20);
    insertar(&raiz, 2);
    insertar(&raiz, 5);
    insertar(&raiz, 8);
    insertar(&raiz, 30);
    insertar(&raiz, 19);
    insertar(&raiz, 4);
    insertar(&raiz, 12);
    insertar(&raiz, 22);
    insertar(&raiz, 7);
    insertar(&raiz, 26);
    insertar(&raiz, 9);
    insertar(&raiz, 17);
    graficar(raiz);

    //busquedas
    int busqueda = 0;
    puts("BUSQUEDAS");
    printf("Valor de Busqueda: %d \n", buscar(&raiz, 15));
    printf("Valor de Busqueda: %d \n", buscar(&raiz, 9));
    printf("Valor de Busqueda: %d \n", buscar(&raiz, 4));
    printf("Valor de Busqueda: %d \n", buscar(&raiz, 5));
    printf("Valor de Busqueda: %d \n", buscar(&raiz, 3));
    printf("Valor de Busqueda: %d \n", buscar(&raiz, 12));
    printf("Valor de Busqueda: %d \n", buscar(&raiz, 17));
    printf("Valor de Busqueda: %d \n", buscar(&raiz, 30));
    graficar(raiz);


    puts("ELIMINACIONES");
    eliminar(&raiz, 15);
    eliminar(&raiz, 12);
    eliminar(&raiz, 3);
    eliminar(&raiz, 30);
    eliminar(&raiz, 22);
    graficar(raiz);

    // menu();
    return 0;
}