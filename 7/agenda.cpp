#include <bits/stdc++.h>
using namespace std;




struct Nodo{
	string dato;
	Nodo *left, *right;
	Nodo(string d):dato(d),left(NULL),right(NULL){}
	Nodo():left(NULL),right(NULL){}
	void printNodo(){
        cout << dato;
	}
};
 
void inorder(Nodo* &raiz){
	if(raiz == NULL)
		return;
	inorder(raiz->left);
	raiz->printNodo();
	inorder(raiz->right);
}

void postorder(Nodo* &raiz){
	if(raiz == NULL)
        return;
    postorder(raiz->left);
    postorder(raiz->right);
	raiz->printNodo();
}

int precedencia(char c){
	if(c == '+' || c == '-')
		return 1;
	if(c == '*' || c =='/')
		return 2;
	if(c == '^')
		return 3;
	return 0;
}

bool existeOperando(string t){
	for(int i = 0; i < t.size(); i++)
		if(t[i] == '+' || t[i] == '-' ||t[i] == '*' ||t[i] == '/'||'^')
			return 1;
}

void expresionToTree(Nodo* &raiz,string t){
	if(!existeOperando(t)){
		raiz = new Nodo(t);
		return;
	}
	//cout << t<<'\n';
	int temp = 4;
	int indice = 0;
	int parentesis = 0;
	string a;
	for(int i = 0; i < t.size(); i++){
		if(t[i] == '(')
            parentesis++;
        if(t[i] == ')')
            parentesis--;
		if(parentesis > 0)
			continue;
		if(t[i] == '+' || t[i] == '-' ||t[i] == '*' ||t[i] == '/'||t[i] == '^'){
			if(precedencia(t[i])<temp){
				temp = precedencia(t[i]);
				indice = i;
			}
		}
	}
	raiz = new Nodo(a+=t[indice]);
	string izq = t.substr(0,indice);
	string der = t.substr(indice+1,t.size());
	if(izq[0] == '(' && izq[izq.size()-1] == ')')
        izq = izq.substr(1,izq.size()-2);
	if(der[0] == '(' && der[der.size()-1] == ')')
        der = der.substr(1,der.size()-2);
	expresionToTree(raiz->left,izq);
	expresionToTree(raiz->right, der);
}

double eval(Nodo* &root){
	string t =""; 
	t+=root->dato;
	if(!root)
		return 0;
	if(!root->left && !root->right)
		return strtof(t);
	float l_val = eval(root->left);
	float r_val = eval(root->right);
	if(root->dato == "+")
		return l_val + r_val;
	if(root->dato == "-")
        return l_val - r_val;
	if(root->dato == "*")
        return l_val * r_val;
	if(root->dato == "/")
        return l_val / r_val;
	if(root->dato == "^")
        return pow(l_val,r_val);
}

int main(){
	string exp = "2*5-2";
	Nodo* ar = new Nodo();
	expresionToTree(ar,exp);
	inorder(ar);
	cout << '\n';
	postorder(ar);
	cout << eval(ar) << '\n';
}
