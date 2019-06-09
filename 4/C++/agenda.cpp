#include<iostream>

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
    
    int imprimirCercanos(string n){
        int encontro = 0;
        if(isEmpty())
            return 0;
        Nodo* temp = new Nodo();
        temp = ini -> sig;
        while(temp){
            if(temp->nombre.find(n) != string::npos){
                temp->printNodo();
                encontro = 1;
            }
            temp = temp -> sig;          
        }
        if(encontro){
            cout << "Pero se encontraron estos registros\n";
            return 1;
        }
        cout << "No se encontraron registros parecidos\n";
        return 0;
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

void menu(){
    List l;
    int opc, eliminar;
    string nombre, telefono, email;
    cout << "Bienvenidos a la Agenda Enlazada\n";
    while(1){
        cout << "Seleccione que desea hacer:\n1.-Agregar entrada a la agenda\n2.-Eliminar entrada de la agenda\n3.-Consultar\n4.-Imprimir agenda\n5.-Modificar datos\n6.-Salir\n";
        cin >> opc;
        if(opc == 1){
            cout << "Dame el nuevo nombre completo empezando por nombre: ";
            cin.ignore(256, '\n');
            getline(cin, nombre);
            cout << "Dame el telefono: ";
            cin >> telefono;
            cout << "Dame Email: ";
            cin >> email;
            l.Insert(nombre,telefono,email);
            cout << "El registro se hizo correctamnte: \n\n";
            l.Query(nombre)->printNodo();
        }
        else if(opc == 2){
            if(l.isEmpty()){
                cout << "La lista esta vacia :c\n";
                continue;
            }
            cout << "Dame el nuevo nombre completo empezando por nombre que desea eliminar: ";
            cin.ignore(256, '\n');
            getline(cin, nombre, '\n');
            Nodo* temp;
            temp = l.Query(nombre);
            if(temp){
                temp->printNodo();
                cout << "1.-Eliminar registro\n2.-No hacer nada\n\n";
                cin>> eliminar;
                if(eliminar == 1)
                    l.Delate(nombre);
                else
                    continue;
            }
            else
                cout << "El registro no existe\n";
        }
        else if(opc == 3){
            if(l.isEmpty()){
                cout << "La lista esta vacia :c\n";
                continue;
            }
            Nodo* temp = new Nodo();
            cout << "Dame el nombre que desea buscar: ";
            cin.ignore(256, '\n');
            getline(cin, nombre, '\n');
            temp = l.Query(nombre);
            if(!temp){
                if(!l.imprimirCercanos(nombre));
                continue;
            }
            cout << "El registro es: \n\n";
            temp -> printNodo();
        }
        else if(opc == 4){
            if(l.isEmpty()){
                cout << "La lista esta vacia :c\n";
                continue;
            }
            l.printList();
        }
        else if(opc == 5){
            if(l.isEmpty()){
                cout << "La lista esta vacia :c\n";
                continue;
            }
            cout << "Dame el nombre que desea modificar: ";
            cin.ignore(256, '\n');
            getline(cin, nombre, '\n');
            l.Modificar(nombre);
        }
        else{
            break;
        }
    }
}



int main(){
    menu();
}