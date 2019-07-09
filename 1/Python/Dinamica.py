class Nodo(object):
    def __init__(self, dato:int):
        self.dato = dato
        self. sig = None

class Pila(object):
    def __init__(self):
        self.inicio = None
        self.tope = None
    def insertar(self,dato):
        if self.inicio == None:
            self.inicio = Nodo(dato)
            self.tope = self.inicio
            return
        self.tope.sig = Nodo(dato)
        self.tope = self.tope.sig

    def obtenerTope(self):
        if self.tope == None:
            return
        return self.tope.dato

    def sacarElemento(self):
        if self.tope == None:
            return
        datoASacar = self.tope.dato
        self.tope = None
        temp = self.inicio
        while(temp.sig != None):
            temp = temp.sig
        self.tope = temp
        return datoASacar

    def imprimir(self):
        if(self.inicio == None):
            return
        temp = self.inicio
        while(temp != None):
            print(temp.dato)
            temp = temp.sig
