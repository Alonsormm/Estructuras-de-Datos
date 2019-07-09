class Pila(object):
    def __init__(self):
        self.arreglo = []
    
    def insertar(self,dato):
        self.arreglo.append(dato)
    
    def obtenerTope(self):
        if(len(self.arreglo) == 0):
            return None
        else:
            return self.arreglo[-1]
    def sacarElemento(self):
        if(len(self.arreglo) == 0):
            return None
        else:
            return self.arreglo.pop()
    def imprimir(self):
        print(self.arreglo)