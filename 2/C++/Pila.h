template <class T>
struct Nodo{
    T dato;
    Nodo<T>* sig;
    Nodo(): sig(NULL){}
    Nodo(T v): sig(NULL), dato(v){}
};

template <class T>
struct Pila{
    Nodo<T>* tope = new Nodo<T>();
    void push(T v){
        if(!tope -> sig){
            tope -> sig = new Nodo<T>(v);
            return;
        }
        Nodo<T>* temp = new Nodo<T>(v);
        temp -> sig = tope -> sig;
        tope -> sig = temp;
    }
    bool isEmpty(){
        return !tope -> sig;
    }

    T pop(){
        if(isEmpty())
            return 0;
        T temp;
        temp = tope -> sig -> dato;
        tope -> sig = tope -> sig -> sig;
        return temp;
    }
    T top(){
        if(isEmpty())
            return -1;
        return tope -> sig -> dato;
    }
};
