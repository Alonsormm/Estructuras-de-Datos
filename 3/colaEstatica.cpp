#include<iostream>

using namespace std;

template <class T>
struct Queue{
    T* cola;
    int tam;
    int ini,fin;
    Queue(int t){
        tam = t;
        cola = new T[t];
        ini = -1;
        fin = -1;
    }
    bool isEmpty(){
        return fin == -1;
    }
    void push(T dato){
        if(fin + 1 == tam){
            if(ini == 0)
                cout << "La cola esta llena :C\n";
            else{
                fin = 0;
                cola[fin] = dato;
            }
        }
        else{
            if(fin + 1 == ini)
                cout << "La cola esta llena :C\n";
            else{
                fin++;
                cola[fin] = dato;
                if(ini == -1)
                    ini = 0;
            }
        }
    }
    T pop(){
        if(ini == fin){
            int temp = ini;
            ini = -1;
            fin = -1;
            return cola[temp];
        }
        if(ini + 1 == tam){
            ini = 0;
            return cola[tam-1];
        }
        ini++;
        return cola[ini-1];
    }
    void imprimirCola(){
        int i = ini;
        while(-1){
            cout << cola[i] << '\n';            
            i++;
            if(i-1 == fin)
                break;
            if(i == fin)
                break;
            if(i == tam && i-1!=fin && ini!=0)
                i = 0;
            
        }
        cout << cola[fin] << '\n';            
    }
};

void menu(){
    int opc;
    int t;
    cout << "Dame el tamanio de la cola: ";
    cin >> t;
    Queue <int> cola(t);
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
            cola.imprimirCola();
        }
        else if(opc == 4)
            break;
    }
}

int main(){
    menu();
}
