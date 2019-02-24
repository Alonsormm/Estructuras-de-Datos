#include<iostream>

using namespace std;

template <class T>
struct Pila{
    T* p;
    int tope;
    int tam;

    Pila(int tamanio){
         tam = tamanio;
         p = new T[tam];
         tope = -1;
    }

    bool isFull(){
        return tope == (tam - 1);
    }

    bool isEmpty(){
        return tope == -1;
    }

    void push(T v){
        if(tope >= tam-1){
            cout << "lel";
            return;
        }
        tope++;
        *(p+tope) = v;
    }
    T pop(){
        if(isEmpty())
            return 0;
        tope--;
        return *(p+tope+1);
    }
    T top(){
        if(tope == -1)
            return 0;
        return *(p+tope);
    }
    void print(){
        if(isEmpty())
            return;
        else
            for(int i = tope; i >= 0 ; i--)
                cout << *(p+i) << '\n';
    }
};



int main(){
    int tamTemp;
    cout << "Dame tamanio de la pila: ";
    cin >> tamTemp;
    Pila<int> pi(tamTemp);
    int datoTemp;
    int opc;
    while(1){
        cout << "Menu\n1.- Insertar elemento 2.-Sacar elemento 3.-Esta vacia? 4.- Mostrar Elementos 5.- Salir\n";
        cin >> opc;
        if(opc == 1){
            if(pi.isFull()){
                cout << "La pila esta llena\n";
                continue;
            }
            cout << "Dame elemento a insertar: ";
            cin >> datoTemp;
            pi.push(datoTemp);
            pi.print();
        }
        else if(opc == 2){
            if(pi.isEmpty())
                cout << "Esta vacia";
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