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
struct Queue{
    Nodo<T>* ini = new Nodo<T>();
    Nodo<T>* fin = new Nodo<T>();    
    void push(T v){
        if(!ini -> sig){
            Nodo<T>* temp = new Nodo<T>(v);
            ini -> sig =  temp;
            fin -> sig = temp;
            return;
        }
        Nodo<T>* temp = new Nodo<T>(v);
        fin -> sig -> sig = temp;
        fin -> sig = temp;
    }
    bool isEmpty(){
        return !ini -> sig;
    }

    T pop(){
        if(isEmpty())
            return -1;
        T temp;
        temp = ini -> sig -> dato;
        ini -> sig = ini -> sig -> sig;
        return temp;
    }
    T top(){
        if(isEmpty())
            return -1;
        return ini -> sig -> dato;
    }
    void printCola(){
        Nodo<T>* temp;
        temp = ini->sig;
        while(temp){
            cout << temp -> dato << " ";
            temp = temp -> sig;
        }
        cout << '\n';
    }
};



void menu(){
    int opc;
    Queue <int> cola;
    int temp;
    while(1){
        cout << "Elija una opcion\n1.-Insetar elemento\n2.-Sacar elemento\n3.-Imprimir cola\n4.-Salir\n";
        cin >> opc;
        if(opc == 1){
            cout << "Dame un numero: ";
            cin  >> temp;
            cola.push(temp);
        }
        else if(opc == 2){
            if(cola.isEmpty()){
                cout << "La Cola esta vacia\n";
                continue;
            }
            cout << "El dato que sacaste es: " << cola.pop() << "\n";
        }
        else if(opc == 3){
            if(cola.isEmpty()){
                cout << "La Cola esta vacia\n";
                continue;
            }
            cola.printCola();
        }
        else if(opc == 4)
            break;
    }
}

int main(){
    menu();
}