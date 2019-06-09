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
	if(raiz==NULL)
		return NULL;
	if (raiz->nombre == nombre){
        return raiz;
    }
	if(strcpr(nombre,raiz->nombre) == -1)
        return Query(raiz->left, nombre);
    else
        return Query(raiz->right, nombre);
}

void ficheroArbol(Nodo* &raiz){
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

void agregarRegistro(Nodo* &raiz){
    string nombre,direccion, numero, correo, cadenaFinal;
    cout << "Dame el nombre completo empezando por nombre: ";
    cin.ignore(256, '\n');
    getline(cin, nombre);
    cout << "Dame la direccion: ";
    getline(cin, direccion);
    cout << "Numero de telefono: ";
    cin >> numero;
    cout << "Correo Electronico: ";
    cin >> correo;
    insert(raiz,nombre,direccion,numero,correo);
    ofstream archivo;
    archivo.open("datos_agenda - data.csv",ios::app);
    cadenaFinal = nombre + ',' + direccion + ',' + numero + ',' + correo + '\n';
    archivo << cadenaFinal;
    archivo.close();
    cout << "El registro de ha agregado correctamente :)\n";
}

void consultaRegistro(Nodo* &raiz){
    string nombre;
    cout << "Escriba el nombre completo del registro que desea buscar: ";
    cin.ignore(256, '\n');
    getline(cin, nombre, '\n');
    Nodo* temp = Query(raiz,nombre);
    if(temp!=NULL){
        cout << "El registro fue encontrado!\n";
        temp->printNodo();
        return;
    }
    cout << "El registro no existe :c \n";
}

void modificarRegistro(Nodo* raiz){
	string nombreTemp,aTemp,telTemp,emTemp;
	int opc;
	cout << "Dame el nombre completo de la entrada que deaseas modificar: ";
	cin.ignore(256, '\n');
	getline(cin, nombreTemp);
	Nodo* temp = Query(raiz,nombreTemp);
	if(temp==NULL){
        cout << "El registro no existe:c";
        return;
    }
	while(1){
		cout << "El registro que quiere modificar es el siguiente: \n\n";
        temp -> printNodo();
        cout << "Seleccione que desea hacer:\n1.-Modificar nombre\n2.-Modificar direccion\n3.-Modificar Telefono\n4.-Modificar Email\n5.-Salir\n";
        cin >> opc;
		if(opc == 1){
			nombreTemp;
			cout << "Dame el nuevo nombre completo empezando por nombre: ";
            cin.ignore(256, '\n');
            getline(cin, nombreTemp, '\n');
            temp -> nombre = nombreTemp;
            cout << "El registro fue modificado: \n";
			temp -> printNodo();
        }
		if(opc == 2){
			cout << "Dame la nueva direccion: ";
            cin.ignore(256, '\n');
            getline(cin, aTemp, '\n');
            temp -> direccion = aTemp;
            cout << "El registro fue modificado: \n";
            temp -> printNodo();
		}
        if(opc == 3){
			telTemp;
            cout << "Dame el nuevo telefono: ";
            cin >> telTemp;
            temp -> numero = telTemp;
            cout << "El registro fue modificado: \n";
            temp -> printNodo();
        }
        if(opc == 4){
            emTemp;
            cout << "Dame el nuevo Email: ";
            cin >> emTemp;
            temp -> correo = emTemp;
            cout << "El registro fue modificado: \n";
            temp -> printNodo();
        }
        if(opc == 5){
            return;
        }
	}
}


void menu(){
	Nodo* raiz = NULL;
	ficheroArbol(raiz);
    char opc;
    cout << "Bienvenido a la agenda c++" << endl;
    while(1934){
        cout << "Ingrese la opcion que desea\n";
        cout << "1.-Agregar Dato\n2.-Consultar Dato\n3.-Modificar Dato\n4.-Imprimir Agenda\n5.-Salir\n";
        cin >> opc;
        if(opc == '1'){
            agregarRegistro(raiz);
        }
        else if(opc == '2'){
            consultaRegistro(raiz);
        }
        else if(opc == '3'){
			modificarRegistro(raiz);
        }
        else if(opc == '4'){
            inorder(raiz);
        }
        else{
            break;
        }
    }
}



int main(){
	menu();
}
