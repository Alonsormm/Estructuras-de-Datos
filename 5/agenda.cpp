#include <bits/stdc++.h>
using namespace std;
#define tamanoListaAgenda 1000

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

unsigned long hashing(string str){
    unsigned long hash = 5381;
    int c;
    for(int i = 0 ; i < str.size(); i++){
        c = str[i];
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash&(tamanoListaAgenda-1);
}


struct Nodo{
    string nombre;
    string telefono;
    string email;
    Nodo* sig;
    Nodo* ant;
    Nodo(): sig(NULL),ant(NULL){}
    Nodo(string n, string t, string e): sig(NULL), ant(NULL), nombre(n), telefono(t), email(e){}
    void printNodo(){
        cout << "Nombre: " << nombre << "\nTelefono: " << telefono << "\nEmail: " << email << "\n\n";
    }
};

struct List{
    Nodo* ini = new Nodo();
    Nodo* fin = new Nodo();
    bool isEmpty(){
        return ini-> sig == NULL;
    }

    void InsertFirst(string n, string t, string e){
        if(!ini -> sig){
            Nodo* temp = new Nodo(n,t,e);
            ini -> sig =  temp;
            fin -> sig = temp;
            return;
        }
        Nodo* temp = new Nodo(n,t,e);
        temp -> sig = ini -> sig;
        ini -> sig -> ant = temp;
        ini -> sig = temp;
    }
    void DelateFirst(){
        if(ini -> sig == fin -> sig){
            ini -> sig = NULL;
            fin -> sig = NULL;
            return;
        }
        if(isEmpty())
            return;
        ini -> sig = ini -> sig -> sig;
        ini -> sig -> ant = NULL;
    }

    void InsertLast(string n, string t, string e){
        if(!ini -> sig){
            Nodo* temp = new Nodo(n,t,e);
            ini -> sig =  temp;
            fin -> sig = temp;
            return;
        }
        Nodo* temp = new Nodo(n,t,e);
        temp -> ant = fin -> sig;
        fin -> sig -> sig = temp;
        fin -> sig = temp;
    }
    void DelateLast(){
        if(ini -> sig == fin -> sig){
            ini -> sig = NULL;
            fin -> sig = NULL;
            return;
        }
        if(isEmpty())
            return;
        fin -> sig = fin -> sig -> ant;
        fin -> sig = NULL;
    }

    void printList(){
        Nodo* temp = new Nodo();
        temp = ini -> sig;
        while(temp){
            temp ->printNodo();
            temp = temp -> sig;
        }
    }

    void InsertDespues(Nodo* izq, string n , string t, string e){
        Nodo* der = new Nodo();
        der = izq -> sig;
        Nodo* temp = new Nodo(n,t,e);
        temp -> ant = izq;
        temp -> sig = der;
        izq -> sig = temp;
        der -> ant = temp;
    }

    void DelateDespues(Nodo* temp){
        Nodo* izq = new Nodo();
        Nodo* der = new Nodo();
        izq = temp -> ant;
        der = temp -> sig;
        izq -> sig = der;
        der -> ant = izq;
    }

    void Insert(string n, string t, string e){
        if(isEmpty()){
            InsertFirst(n,t,e);
            return;
        }
        if(strcpr(ini -> sig -> nombre, n)==1){
            InsertFirst(n,t,e);
            return;
        }
        if(strcpr(fin -> sig -> nombre, n)==-1){
            InsertLast(n,t,e);
            return;
        }
        Nodo* temp = new Nodo();
        temp = ini -> sig;
        while(temp){
            if(strcpr(temp -> nombre, n) != strcpr(temp ->sig -> nombre, n)){
                InsertDespues(temp,n,t,e);
                return;
            }
            temp = temp -> sig;
        }
        
    }

    Nodo* Query(string n){
        if(isEmpty())
            return NULL;
        Nodo* temp = new Nodo();
        temp = ini -> sig;
        while(temp){
            if(temp->nombre== n){
                return temp;
            }
            temp = temp -> sig;            
        }
        return NULL;
    }
    void Delate(string n){
        Nodo* temp = new Nodo();
        temp = Query(n);
        if(!temp){
            cout << "El registro no existe\n";
            return;
        }
        if(temp -> sig == NULL){
            DelateLast();
            return;
        }
        if(temp -> ant == NULL){
            DelateFirst();
            return;
        }
        DelateDespues(temp);
    }

    void Modificar(string n){
        Nodo* temp = new Nodo();
        Nodo* nFinal;
        temp = Query(n);
        int opc;
        if(!temp){
            cout << "No se encontro el registro que quiere modificar\n";
            return;
        }
        string nombreTemp = n;
        string telTemp = temp -> telefono;
        string emTemp = temp -> email;
        while(1){    
            cout << "El registro que quiere modificar es el siguiente: \n\n";
            temp -> printNodo();
            cout << "Seleccione que desea hacer:\n1.-Modificar nombre\n2.-Modificar Telefono\n3.-Modificar Email\n4.-Salir\n";
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
                telTemp;
                cout << "Dame el nuevo telefono: ";
                cin >> telTemp;
                temp -> telefono = telTemp;
                cout << "El registro fue modificado: \n";
                temp -> printNodo();
            }
            if(opc == 3){
                emTemp;
                cout << "Dame el nuevo Email: ";
                cin >> emTemp;
                temp -> email = emTemp;
                cout << "El registro fue modificado: \n";
                temp -> printNodo();
            }
            if(opc == 4){
                Delate(nombreTemp);
                Insert(nombreTemp,telTemp,emTemp);
                return;
            }
        }
        
    }
};

vector<string> dividir(string dato){
    vector<string> temp(3);
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

vector<List> ficheroLista(vector<List> agenda){
    fstream txtFile;
    string dato, nombre, numero, correo;
    vector<string> temp(3);
    txtFile.open("Prueba.txt");
    while(getline(txtFile,dato)){
        temp = dividir(dato);
        nombre = temp[0];
        numero = temp[1];
        correo = temp[2];
        long g= hashing(nombre);
        agenda[g].Insert(nombre,numero,correo);
        agenda[g].Query(nombre)->printNodo();
        //cout << nombre << '\n' << numero << '\n' << correo << '\n';
    }
    txtFile.close();
    return agenda;
}

int main(){
    vector <List> temp(tamanoListaAgenda);
    temp = ficheroLista(temp);
}
