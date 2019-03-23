#include <bits/stdc++.h>
using namespace std;

int strcpr(string a, string b){
    int tama = a.size();
    int tamb = b.size();
    int tamF;
    if(tama >= tamb)
        tamF = tamb;
    else
        tamF = tama;
    for(int i = 0; i < tamF; i++){
        if(a[i] == b[i])
            continue;
        else if(a[i]>b[i])
            return 1;
        else
            return -1;
    }
    return 0;
}


struct Nodo{
	string nombre;
	string direccion;
	string numero;	
	string correo;
	Nodo *left, *right;
	Nodo(string n, string d, string num, string c):nombre(n),direccion(d),numero(num),correo(c),left(NULL),right(NULL){}
	void printNodo(){
        cout << "Nombre: " << nombre << "\nDireccion: " << direccion << "\nTelefono: " << numero << "\nEmail: " << correo << "\n\n";
	}
};

vector<string> dividir(string dato){
    vector<string> temp(4);
    int j = 0;
    for(int i = 0 ; i < dato.size(); i++){
        if(dato[i]==','){
            j++;
            continue;
        }
        temp[j]+=dato[i];
    }
    return temp;
}

 
void inorder(Nodo* root){
	if (root == NULL)
		return;
 
	inorder(root->left);
	root->printNodo();
	inorder(root->right);
}


void insert(Nodo* &raiz, string nombre, string direccion, string numero, string email){
	if (raiz == NULL){
		raiz = new Nodo(nombre,direccion,numero,email);
		return;
	}
 
	if(strcpr(nombre,raiz->nombre) == -1)
		insert(raiz->left, nombre,direccion,numero,email);
	else
		insert(raiz->right, nombre,direccion,numero,email);
}

Nodo* Query(Nodo* &raiz, string nombre){
	if (raiz->nombre == nombre || raiz == NULL){
        return raiz;
    }
	if(strcpr(nombre,raiz->nombre) == -1)
        return Query(raiz->left, nombre);
    else
        return Query(raiz->right, nombre);
}

void ficheroLista(Nodo* &raiz){
    fstream txtFile;
    string dato, nombre,direccion, numero, correo;
    vector<string> temp(4);
    txtFile.open("datos_agenda - data.csv");
    while(getline(txtFile,dato)){
        temp = dividir(dato);
        nombre = temp[0];
        direccion = temp[1];
        numero = temp[2];
        correo = temp[3];
        insert(raiz,nombre,direccion,numero,correo);
    }
    fflush(stdin);
    txtFile.close();
}


int main(){
	Nodo* arbol = NULL;
	ficheroLista(arbol);
 
	//inorder(arbol);
	Nodo* temp = Query(arbol, "Zenia Giraldez");
	if(temp){
		temp -> printNodo();
	}
	return 0;
}
