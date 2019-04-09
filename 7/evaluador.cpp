#include <bits/stdc++.h>
using namespace std;




struct Nodo{
	string dato;
	Nodo *left, *right;
	Nodo(string d):dato(d),left(NULL),right(NULL){}
	Nodo():left(NULL),right(NULL){}
	void printNodo(){
        cout << dato << ' ';
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

bool isOperand(string c){
	return c == "+" || c == "-" || c == "*" || c == "/" || c == "^";
}

bool isOperator(char c){
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

bool isNumber(char c){
    return c >= '0' && c <= '9';
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
		if(t[i] == '+' || t[i] == '-' ||t[i] == '*' ||t[i] == '/'||t[i] == '^')
			return 1;
}

void expresionToTree(Nodo* &raiz,string t){
	if(!existeOperando(t)){
		raiz = new Nodo(t);
		return;
	}
	int tam = t.size();
	if(t[0] == '('){
		if(t[tam-1]==')'){
			int count = 0;
			for(int i = 0; i < tam; i++){
				if(t[i] == ')'){
					if(i == tam-1){
						t = t.substr(1,tam-2);
					}
					else
						break;
				}
			}
		}
	}
	
	int temp = 5;
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

	expresionToTree(raiz->left,izq);
	expresionToTree(raiz->right, der);
}

float evaluar(Nodo* &raiz){
	if(isOperand(raiz->dato)){
		if(raiz->dato == "+")
			return evaluar(raiz->left) + evaluar(raiz->right);
		if(raiz->dato == "-")
            return evaluar(raiz->left) - evaluar(raiz->right);
		if(raiz->dato == "*")
            return evaluar(raiz->left) * evaluar(raiz->right);
		if(raiz->dato == "/")
            return evaluar(raiz->left) / evaluar(raiz->right);
		if(raiz->dato == "^")
            return pow(evaluar(raiz->left),evaluar(raiz->right));
	}
	return atof(raiz->dato.c_str());
}

string agregarFaltantes(string s){
    string temp = s;
    temp.erase( std::remove( temp.begin(), temp.end(), ' '), temp.end());
    int tam = temp.size()-1;
    for(int i = 0 ; i < tam; i++){
        if(temp[i] == '(' && isOperator(temp[i+1]))
            temp.insert(i+1,"0");
        if((temp[i] == '-' && isOperator(temp[i+1])) || (temp[i] == '+' && isOperator(temp[i+1]))){
            temp.insert(i+1,"(");
            temp.insert(i+2,"0");
            temp.insert(i+5,")");
        }
        if((temp[i] == '*' && isOperator(temp[i+1])) || (temp[i] == '/' && isOperator(temp[i+1]))){
            temp.insert(i+1,"(");
            temp.insert(i+2,"1");
            temp.insert(i+5,")");
        }
        if(temp[i] == '(' && isNumber(temp[i-1]))
            temp.insert(i,"*");
        if(temp[i] == ')' && isNumber(temp[i+1]))
            temp.insert(i+1,"*");
    }
    return temp;
}


string comprobar(){
    string expresion;
    while(7){
        bool error = 0;
        cout << "Introduzca la expresion a evaluar: " << '\n';
        getline(cin, expresion);
        expresion = agregarFaltantes(expresion);
        for(int i = 1 ; i  < expresion.size(); i++){
            if(isOperator(expresion[i]) && isOperator(expresion[i-1])){
                error = 1;
                break;
            }
        }
        if(error){
            cout << "Esta mal esrita la expresion, intente de nuevo\n";
            continue;
        }
        else
            break;
    }
    return expresion;
}



int main(){
	string exp = comprobar();
	Nodo* ar = new Nodo();
	expresionToTree(ar,exp);
	cout << "El resultado es: " << evaluar(ar) << '\n';
}
