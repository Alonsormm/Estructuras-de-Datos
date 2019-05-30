#include<iostream> 
using namespace std;
template <class T>
struct BTreeNode{ 
	T *datos;
	int t;
	BTreeNode<T> **C;
	int n;
	bool leaf;
    BTreeNode(T t1, bool leaf1) { 
    	t = t1; 
    	leaf = leaf1; 

    	datos = new T[2*t-1]; 
    	C = new BTreeNode<T> *[2*t]; 

    	n = 0; 
    } 

    void insertNonFull(T k) { 
    	int i = n-1; 

    	if (leaf == true){ 
    		while (i >= 0 && datos[i] > k){ 
    			datos[i+1] = datos[i]; 
    			i--; 
    		} 

    		datos[i+1] = k; 
    		n = n+1; 
    	} 
    	else{ 
    		while (i >= 0 && datos[i] > k) 
    			i--; 

    		if (C[i+1]->n == 2*t-1){ 
    			splitChild(i+1, C[i+1]); 

    			if (datos[i+1] < k) 
    				i++; 
    		} 
    		C[i+1]->insertNonFull(k); 
    	} 
    } 

    void splitChild(int i, BTreeNode<T> *y){ 
    	BTreeNode<T> *z = new BTreeNode(y->t, y->leaf); 
    	z->n = t - 1; 

    	for (int j = 0; j < t-1; j++) 
    		z->datos[j] = y->datos[j+t]; 

    	if (y->leaf == false){ 
    		for (int j = 0; j < t; j++) 
    			z->C[j] = y->C[j+t]; 
    	} 

    	y->n = t - 1; 

    	for (int j = n; j >= i+1; j--) 
    		C[j+1] = C[j]; 

    	C[i+1] = z; 

    	for (int j = n-1; j >= i; j--) 
    		datos[j+1] = datos[j]; 

    	datos[i] = y->datos[t-1]; 

    	n = n + 1; 
    }  

	void traverse(){ 
	    int i; 
	    for (i = 0; i < n; i++){ 
	    	if (leaf == false) 
	    		C[i]->traverse(); 
	    	cout << " " << datos[i]; 
	    } 

	    if (leaf == false) 
	    	C[i]->traverse(); 
    }  

	BTreeNode<T> *search(T k){ 
	    int i = 0; 
	    while (i < n && k > datos[i]) 
	    	i++; 
	    if (datos[i] == k) 
	    	return this; 
	    if (leaf == true) 
	    	return NULL; 
	    return C[i]->search(k); 
    } 
 

}; 
template <class T>
struct BTree{ 
	BTreeNode<T> *root;
	int t;
	BTree(int _t){
        root = NULL;
        t = _t;
    } 

	void traverse(){
        if (root != NULL) root->traverse();
    } 

	BTreeNode<T>* search(T k){
        return (root == NULL)? NULL : root->search(k);
    } 

	void insert(T k){ 
	    if (root == NULL){ 
	    	root = new BTreeNode<T>(t, true); 
	    	root->datos[0] = k; 
	    	root->n = 1;
	    } 
	    else{ 
	    	if (root->n == 2*t-1){ 
	    		BTreeNode<T> *s = new BTreeNode<T>(t, false); 

	    		s->C[0] = root; 

	    		s->splitChild(0, root); 

	    		int i = 0; 
	    		if (s->datos[0] < k) 
	    			i++; 
	    		s->C[i]->insertNonFull(k); 

	    		root = s; 
	    	} 
	    	else
	    		root->insertNonFull(k); 
	    } 
    } 
}; 







int main() 
{ 
	BTree<int> t(4);
	t.insert(10); 
	t.insert(20); 
	t.insert(5); 
	t.insert(6); 
	t.insert(12); 
	t.insert(30); 
	t.insert(7); 
	t.insert(17); 

	cout << "Traversal of the constucted tree is "; 
	t.traverse(); 

	int k = 6; 
	(t.search(k) != NULL)? cout << "\nPresent" : cout << "\nNot Present"; 

	k = 15; 
	(t.search(k) != NULL)? cout << "\nPresent" : cout << "\nNot Present"; 

	return 0; 
} 
