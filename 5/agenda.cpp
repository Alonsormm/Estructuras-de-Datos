#include <bits/stdc++.h>
using namespace std;
#define tamanoListaAgenda 100000

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
    string address;
    Nodo* sig;
    Nodo* ant;
    Nodo(): sig(NULL),ant(NULL){}
    Nodo(string n,string a,string t, string e): sig(NULL), ant(NULL), nombre(n), address(a),telefono(t), email(e){}
    void printNodo(){
        cout << "Nombre: " << nombre << "\nDireccion: " << address << "\nTelefono: " << telefono << "\nEmail: " << email << "\n\n";
    }
};

struct List{
    Nodo* ini = new Nodo();
    Nodo* fin = new Nodo();
    bool isEmpty(){
        return ini-> sig == NULL;
    }

    void InsertFirst(string n,string a,string t, string e){
        if(!ini -> sig){
            Nodo* temp = new Nodo(n,a,t,e);
            ini -> sig =  temp;
            fin -> sig = temp;
            return;
        }
        Nodo* temp = new Nodo(n,a,t,e);
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

    void InsertLast(string n,string a, string t, string e){
        if(!ini -> sig){
            Nodo* temp = new Nodo(n,a,t,e);
            ini -> sig =  temp;
            fin -> sig = temp;
            return;
        }
        Nodo* temp = new Nodo(n,a,t,e);
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

    void InsertDespues(Nodo* izq, string n, string a, string t, string e){
        Nodo* der = new Nodo();
        der = izq -> sig;
        Nodo* temp = new Nodo(n,a,t,e);
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

    void Insert(string n,string a, string t, string e){
        if(isEmpty()){
            InsertFirst(n,a,t,e);
            return;
        }
        if(strcpr(ini -> sig -> nombre, n)==1){
            InsertFirst(n,a,t,e);
            return;
        }
        if(strcpr(fin -> sig -> nombre, n)==-1){
            InsertLast(n,a,t,e);
            return;
        }
        Nodo* temp = new Nodo();
        temp = ini -> sig;
        while(temp){
            if(strcpr(temp -> nombre, n) != strcpr(temp ->sig -> nombre, n)){
                InsertDespues(temp,n,a,t,e);
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

    Nodo* Modificar(string n){
        Nodo* temp = new Nodo();
        Nodo* nFinal;
        temp = Query(n);
        int opc;
        if(!temp){
            cout << "No se encontro el registro que quiere modificar\n";
            return NULL;
        }
        string nombreTemp = n;
        string telTemp = temp -> telefono;
        string emTemp = temp -> email;
        string aTemp = temp ->address;
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
                temp -> address = aTemp;
                cout << "El registro fue modificado: \n";
                temp -> printNodo();
            }
            if(opc == 3){
                telTemp;
                cout << "Dame el nuevo telefono: ";
                cin >> telTemp;
                temp -> telefono = telTemp;
                cout << "El registro fue modificado: \n";
                temp -> printNodo();
            }
            if(opc == 4){
                emTemp;
                cout << "Dame el nuevo Email: ";
                cin >> emTemp;
                temp -> email = emTemp;
                cout << "El registro fue modificado: \n";
                temp -> printNodo();
            }
            if(opc == 5){
                Delate(nombreTemp);
                //Insert(nombreTemp,aTemp,telTemp,emTemp);
                return temp;
            }
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

void ficheroLista(vector<List> &agenda){
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
        long g= hashing(nombre);
        agenda[g].Insert(nombre,direccion,numero,correo);
        //agenda[g].Query(nombre)->printNodo();
        //cout << nombre << '\n' << numero << '\n' << correo << '\n';
    }
    fflush(stdin);
    txtFile.close();
}

void imprimirAgenda(vector<List> &agenda){
    for(int i = 0 ; i < agenda.size(); i++){
        if(agenda[i].isEmpty())
            continue;
        cout << i << '\n';
        agenda[i].printList();
    }
}

void consultaRegistro(vector<List> &agenda){
    string nombre;
    cout << "Escriba el nombre completo del registro que desea buscar: ";
    cin.ignore(256, '\n');
    getline(cin, nombre, '\n');
    int hastDato = hashing(nombre);
    Nodo* temp = agenda[hastDato].Query(nombre);
    if(temp){
        cout << "El registro fue encontrado!\n";
        temp->printNodo();
        return;
    }
    cout << "El registro no existe :c \n";
}

void agregarRegistro(vector<List> &agenda){
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
    int hashDato = hashing(nombre);
    agenda[hashDato].Insert(nombre,direccion,numero,correo);
    ofstream archivo;
    archivo.open("datos_agenda - data.csv",ios::app);
    cadenaFinal = nombre + ',' + direccion + ',' + numero + ',' + correo + '\n';
    archivo << cadenaFinal;
    archivo.close();
    cout << "El registro de ha agregado correctamente :)\n";
}

void menu(vector <List> &agenda){
    char opc;
    cout << "Bienvenido a la agenda c++" << endl;
    while(1934){
        cout << "Ingrese la opcion que desea\n";
        cout << "1.-Agregar Dato\n2.-Consultar Dato\n3.-Modificar Dato\n4.-Imprimir agenda\n";
        cin >> opc;
        if(opc == '1'){
            agregarRegistro(agenda);
        }
        else if(opc == '2'){
            consultaRegistro(agenda);
        }
        else if(opc == '3'){
            string nombreTemp;
            cout << "Dame el nombre completo de la entrada que deaseas modificar: ";
            cin.ignore(256, '\n');
            getline(cin, nombreTemp);
            int hash = hashing(nombreTemp);
            cout << hash;
            Nodo* temp = agenda[hash].Modificar(nombreTemp);
            if(temp == NULL)
                continue;
            hash = hashing(temp -> nombre);
            agenda[hash].Insert(temp->nombre, temp -> address, temp -> telefono, temp -> email);
        }
        else if(opc == '4'){
            imprimirAgenda(agenda);
        }
        else{
            break;
        }
    }
}

int main(){
    vector <List> temp(tamanoListaAgenda);
    ficheroLista(temp);
    menu(temp);
}
