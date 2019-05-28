#include<iostream>

using namespace std;

template <class T>
struct Nodo{
    T *datos;
    int grado;
    Nodo **hijos;
    int actual;
    bool leaf;
    Nodo(T _grado, bool _leaf){
        grado = _grado;
        leaf = leaf;
        datos = new T[2*grado-1];
        hijos = new Nodo* [2*grado];
        actual = 0;
    }
    void imprimir(){
        int i;
        for (i = 0; i < actual; i++){
            if(leaf == false)
                hijos[i]->imprimir();
            cout << "" << datos[i];
        }
        if(leaf == false)
            hijos[i]->imprimir();
        
    }
    Nodo* buscar(T dato){
        int i = 0;
        while(i < actual && dato > datos[i])
            i++;
        if(datos[i == dato]){
            return this;
        }
        return hijos[i]->buscar(dato);
    }

    void dividirHijos(int i, Nodo<T> *y){
        Nodo<T>* z = new Nodo(y->grado,y->leaf);
        z->actual = grado-1;

        for(int j = 0; j < grado-1; j++){
            z->datos[j] = y->datos[j+grado];
        }
        if(y->leaf == false){
            for (int j = 0; j < grado; j++){
                z->hijos[j] = y->hijos[j+grado];
            }
        }
        y->actual = grado-1;

        for(int j = actual; j >= i+1; j--)
            hijos[j+1] = hijos[j];
        hijos[i+1] = z;

        for(int j = actual-1; j>=i; j--){
            datos[j+1] = datos[j];
        }
        datos[j] = y->datos[t-1];
        n++;
    }

    void insertNonFull(T k) { 
    int i = actual-1; 
  
    if (leaf == true){ 
        while (i >= 0 && datos[i] > k) 
        { 
            datos[i+1] = datoas[i]; 
            i--; 
        } 
  
        datos[i+1] = k; 
        actual = actual+1; 
    } 
    else{ 
        while (i >= 0 && datos[i] > k) 
            i--; 
  
        if (hijos[i+1]->actual == 2*grado-1){ 
            dividirHijos(i+1, hijos[i+1]); 
  
            if (datos[i+1] < k) 
                i++; 
        } 
        hijos[i+1]->insertNonFull(k); 
    } 
} 

};
template <class T>
struct BTree{
    Nodo<T> *raiz;
    int grado;
    BTree(int _grado){
        grado = _grado;
        raiz = NULL;
    }
    void imprimir(){
        if(raiz!=NULL)
            raiz->imprimir();
    }
    void insert(T dato){
        if(raiz == NULL){
            raiz = new Nodo<T>(grado,false);
            raiz->datos[0] = dato;
            raiz->actual = 1;
        }
        else{
            if(raiz -> n == 2*grado-1){
                Nodo<T>* temp = new Nodo<T>(grado,false);
                temp->datos[0] = raiz;
                temp->dividirHijos(0,raiz);
                int i = 0;
                if(temp->datos[0] < dato)
                    i++;
                temp -> hijos[i]->insertNoLleno(dato);

                raiz = temp;
            }
            else{
                raiz->insertNoLleno(dato);
            }
        }

    }
    

};

int main(){
    BTree<int> a(3);
    a.insert(10); 
    a.insert(20); 
    a.insert(5); 
    a.insert(6); 
    a.insert(12); 
    a.insert(30); 
    a.insert(7); 
    a.insert(17);

    a.imprimir();
}
