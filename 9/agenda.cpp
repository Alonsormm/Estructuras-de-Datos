#include <bits/stdc++.h>

using namespace std;

int obtenerMasGrande(string a, string b){
    int tama = a.size();
    int tamb = b.size();
    int tamF;
    if(tama >= tamb)
        tamF = tama;
    else
        tamF = tamb;
    return tamF;
}

struct Persona{
    string nombre;
    string dirrecion;
    string telefono;
    string correo;

    Persona(string n, string d, string t, string c){
        nombre = n;
        dirrecion = d;
        telefono = t;
        correo = c;
    }
    Persona(){}

    bool operator>(Persona a){
        int tamF = obtenerMasGrande(nombre, a.nombre);
        for(int i = 0 ; i < tamF; i++){
            if(nombre[i] == a.nombre[i])
                continue;
            else if(nombre[i] > a.nombre[i])
                return true;
        }
        return false;
    }
    bool operator<(Persona a){
        int tamF = obtenerMasGrande(nombre, a.nombre);
        for(int i = 0 ; i < tamF; i++){
            if(nombre[i] == a.nombre[i])
                continue;
            else if(nombre[i] < a.nombre[i])
                return true;
        }
        return false;
    }
    bool operator== (Persona a){
        int tam = nombre.size();
        if(a.nombre.size() != tam)
            return false;
        for(int i = 0 ; i < tam ; i++)
            if(a.nombre[i] != nombre[i])
                return false;
        return true;
    }
    bool operator<= (Persona a){
        return nombre < a.nombre || nombre == a.nombre;
    }
    bool operator>= (Persona a){
        return nombre > a.nombre || nombre == a.nombre;
    }
    
};

ostream &operator << (ostream& os,const Persona &a){
     os << "Nombre: " << a.nombre << '\n';
     os << "Dirrecion: " << a.dirrecion << '\n';
     os << "Telefono: " << a.telefono << '\n';
     os << "Correo: " << a.correo << '\n';
     return os;
}

template <class T>
struct BTreeNode{ 
	T *datos;
	int grado;
	BTreeNode<T> **hijos;
	int actual;
	bool hoja;
    BTreeNode(int _grado, bool _hoja) { 
    	grado = _grado; 
    	hoja = _hoja; 

    	datos = new T[2*grado-1]; 
    	hijos = new BTreeNode<T> *[2*grado]; 

    	actual = 0; 
    } 

    void insertarNoLleno(T k) { 
    	int i = actual-1; 

    	if (hoja == true){ 
    		while (i >= 0 && datos[i] > k){ 
    			datos[i+1] = datos[i]; 
    			i--; 
    		} 

    		datos[i+1] = k; 
    		actual++; 
    	} 
    	else{ 
    		while (i >= 0 && datos[i] > k) 
    			i--; 

    		if (hijos[i+1]->actual == 2*grado-1){ 
    			dividirHijos(i+1, hijos[i+1]); 

    			if (datos[i+1] < k) 
    				i++; 
    		} 
    		hijos[i+1]->insertarNoLleno(k); 
    	} 
    } 

    void dividirHijos(int i, BTreeNode<T> *y){ 
    	BTreeNode<T> *z = new BTreeNode(y->grado, y->hoja); 
    	z->actual = grado - 1; 

    	for (int j = 0; j < grado-1; j++) 
    		z->datos[j] = y->datos[j+grado]; 

    	if (y->hoja == false){ 
    		for (int j = 0; j < grado; j++) 
    			z->hijos[j] = y->hijos[j+grado]; 
    	} 

    	y->actual = grado - 1; 

    	for (int j = actual; j >= i+1; j--) 
    		hijos[j+1] = hijos[j]; 

    	hijos[i+1] = z; 

    	for (int j = actual-1; j >= i; j--) 
    		datos[j+1] = datos[j]; 

    	datos[i] = y->datos[grado-1]; 

    	actual++; 
    }  

	void recorrer(){ 
	    int i; 
	    for (i = 0; i < actual; i++){ 
	    	if (hoja == false) 
	    		hijos[i]->recorrer(); 
	    	cout << datos[i]; 
	    } 

	    if (hoja == false) 
	    	hijos[i]->recorrer(); 
    }  

	BTreeNode<T> *search(T k){ 
	    int i = 0; 
	    while (i < actual && k > datos[i]) 
	    	i++; 
	    if (datos[i] == k) 
	    	return this; 
	    if (hoja == true) 
	    	return NULL; 
	    return hijos[i]->search(k); 
    } 
 

}; 
template <class T>
struct BTree{ 
	BTreeNode<T> *raiz;
	int grado;
	BTree(int _grado){
        raiz = NULL;
        grado = _grado;
    } 

	void recorrer(){
        if (raiz != NULL) raiz->recorrer();
    } 

	BTreeNode<T>* search(T k){
        return (raiz == NULL)? NULL : raiz->search(k);
    } 

	void insertar(T k){ 
	    if (raiz == NULL){ 
	    	raiz = new BTreeNode<T>(grado, true); 
	    	raiz->datos[0] = k; 
	    	raiz->actual = 1;
	    } 
	    else{ 
	    	if (raiz->actual == 2*grado-1){ 
	    		BTreeNode<T> *s = new BTreeNode<T>(grado, false); 

	    		s->hijos[0] = raiz; 

	    		s->dividirHijos(0, raiz); 

	    		int i = 0; 
	    		if (s->datos[0] < k) 
	    			i++; 
	    		s->hijos[i]->insertarNoLleno(k); 

	    		raiz = s; 
	    	} 
	    	else
	    		raiz->insertarNoLleno(k); 
	    } 
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

void ficheroArbol(BTree<Persona> &arbol){
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
    }
    fflush(stdin);
    txtFile.close();
}



int main() { 
	BTree<Persona> t(4);
    Persona a("Alonso", "asda", "asda","asda");

    Persona b("Blonso", "asda", "asda","asda");

    Persona c("Alan", "asda", "asda","asda");

	t.insertar(a);
	t.insertar(b); 
	t.insertar(c); 
	t.recorrer();
	return 0; 
} 
