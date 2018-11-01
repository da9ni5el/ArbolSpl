//Metodos para el menu
int escribirMenu();
void menu();

struct nodo
{
    int valor;
    struct nodo*izdo;
    struct nodo*dcho;
    struct nodo*padre;
};

typedef struct nodo nodo;

nodo*raiz;
FILE*fp;

int insertar(nodo**raiz, int valor);
int buscar(nodo**raiz, int buscado);
void modificar(nodo**raiz, int buscado, int nuevoValor);//NO ESTA IMPLEMENTADO
int eliminar(nodo**raiz, int valor);
void balancear(nodo*raiz);
void graficar(nodo*raiz);
void toDot(nodo*raiz, FILE*fp);
nodo*crearNuevo(int valor);
void inicializarNodo(nodo**temporal);