#include<iostream> 
using namespace std;

class Persona{
    string nombre;
    string dirrecion;
    string telefono;
    string numero;
};


template <class T>
struct BTreeNode{ 
	T *datos;
	int grado;
	BTreeNode<T> **hijos;
	int actual;
	bool hoja;
    BTreeNode(T _grado, bool _hoja) { 
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
	    	cout << " " << datos[i]; 
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







int main() 
{ 
	BTree<int> t(4);
	t.insertar(10); 
	t.insertar(20); 
	t.insertar(5); 
	t.insertar(6); 
	t.insertar(12); 
	t.insertar(30); 
	t.insertar(7); 
	t.insertar(17); 

	cout << "Traversal of the constucted tree is "; 
	t.recorrer(); 

	int k = 6; 
	(t.search(k) != NULL)? cout << "\nPresent" : cout << "\nNot Present\n"; 

	k = 15; 
	(t.search(k) != NULL)? cout << "\nPresent" : cout << "\nNot Present\n"; 

	return 0; 
} 
