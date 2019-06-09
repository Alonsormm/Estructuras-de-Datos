#include<bits/stdc++.h>
#include"Pila.h"
using namespace std; 

int prec(char c){ 
	if(c == '^') 
		return 3; 
	else if(c == '*' || c == '/') 
		return 2; 
	else if(c == '+' || c == '-') 
		return 1; 
	else
		return -1; 
}

bool isOperator(char c){
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

bool isNumber(char c){
	return c >= '0' && c <= '9';
}

string infixToPostfix(string s){ 
	Pila<char> itp; 
	itp.push('N'); 
	int tam = s.size(); 
	string p; 
	for(int i = 0; i < tam; i++){ 
		if(isNumber(s[i])) 
		    p+=s[i];

		else if(s[i] == '(') 
		    itp.push('('); 
		
		else if(s[i] == ')') { 
			while(itp.top() != 'N' && itp.top() != '(') 
			    p += itp.pop(); 
			if(itp.top() == '(') 
				itp.pop(); 
		} 

		else{ 
			while(itp.top() != 'N' && prec(s[i]) <= prec(itp.top())) 
				p += itp.pop();
			itp.push(s[i]); 
		} 
	}
	while(itp.top() != 'N') 
		p += itp.pop();  
	return p;
}



float resolverPost(string p){
	Pila<float> s; 
	float operando1, operando2, resultado;
	for(int i = 0 ; i < p.size(); i++){
		if(isOperator(p[i])){
			operando2 = s.pop();
			operando1 = s.pop();
			if(p[i]=='^')
				resultado = (int)pow(operando1,operando2);
			else if(p[i] == '*')
				resultado = operando1 * operando2;
			else if(p[i] == '/')
				resultado = operando1 / operando2;
			else if(p[i] == '+')
				resultado = operando1 + operando2;
			else if(p[i] == '-')
				resultado = operando1 - operando2;
			s.push(resultado);
			continue;
		}
		s.push(p[i] - '0');
	}
	resultado = s.pop();
	return resultado;
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
			if((expresion[i] >= '0' && expresion[i] <= '9') && (expresion[i-1] >= '0' && expresion[i-1] <= '9')){
				error = 1;
				break;
			}
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
    string post;
	post = comprobar();
	post = infixToPostfix(post);
	cout << "La expresion el postfijo: " << post  << '\n';
	cout << "El resultado es: " << resolverPost(post) << '\n'; 
	return 0;
} 
