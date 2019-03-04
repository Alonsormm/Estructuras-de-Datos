#include<iostream>
#include<cstdlib>

using namespace std;

//esta es una prueba de git;

int main(){
    int opc;
    while(1){
        cout << "Menu\n1.- Cola Dinamica 2.-Cola Estatica 3.- Salir\n";
        cin >> opc;
        if(opc == 1)
            system("./colaDinamica");
        else if(opc == 2)
            system("./colaEstatica");
        else
            break;
    }
}