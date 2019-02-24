#include<iostream>

using namespace std;
template <class T>
struct Nodo{
    T dato;
    Nodo<T>* sig;
    Nodo(): sig(NULL){}
    Nodo(T v): sig(NULL), dato(v){}
};

template <class T>
struct Pila{
    Nodo<T>* tope = new Nodo<T>();
    void push(T v){
        if(!tope -> sig){
            tope -> sig = new Nodo<T>(v);
            return;
        }
        Nodo<T>* temp = new Nodo<T>(v);
        temp -> sig = tope -> sig;
        tope -> sig = temp;
    }
    bool isEmpty(){
        return !tope -> sig;
    }

    T pop(){
        if(isEmpty())
            return -1;
        T temp;
        temp = tope -> sig -> dato;
        tope -> sig = tope -> sig -> sig;
        return temp;
    }
    T top(){
        if(isEmpty())
            return -1;
        return tope -> sig -> dato;
    }
    void print(){
        Nodo<T>* temp;
        if(isEmpty()){
            cout << "Esta vacia\n";
            return;
        }
        temp = tope -> sig;
        do{
            cout << temp -> dato << '\n';
            temp = temp -> sig;
        }while(temp!= NULL);
    }
};


int main(){
    Pila<int> pi;
    int datoTemp;
    int opc;
    while(1){
        cout << "Menu\n1.- Insertar elemento 2.-Sacar elemento 3.-Esta vacia? 4.- Mostrar Elementos 5.- Salir\n";
        cin >> opc;
        if(opc == 1){
            cout << "Dame elemento a insertar: ";
            cin >> datoTemp;
            pi.push(datoTemp);
            pi.print();
        }
        else if(opc == 2){
            if(pi.isEmpty())
                cout << "Esta vacia\n";
            else{
                cout << "El elemento que has sacado es: " << pi.pop() << "\n";
                pi.print();
            }
        }
        else if(opc == 3){
            if(pi.isEmpty())
                cout << "Esta vacia\n";
            else
                cout << "No esta vacia\n";
        }
        else if(opc == 4)
            pi.print();
        else if(opc == 5)
            break;
    }
}