import csv
import copy

def strcpr (a,b):
    tama = len(a)
    tamb = len(b)
    if tama > tamb:
        tamF = tama
    else:
        tamF = tamb
    i = 0
    while(i < tamF):
        if a[i] == b[i]:
            i+=1
            continue
        elif a[i]>b[i]:
            return 1
        else:
            return -1
    return 0


class Nodo(object):
    def __init__(self, nombre, dirrecion, correo, numero):
        self.nombre = nombre
        self.dirrecion = dirrecion
        self.correo = correo
        self.numero = numero
        self.izq = None
        self.der = None
        self.peso = 1
    def imprimirNodo(self):
        print("Nombre: " + self.nombre + "\nDirrecion: " + self.dirrecion + "\nCorreo: " + self.correo + "\nNumero: " + self.numero + '\n')
    

class AVL_Tree(object):

    def insert(self, root, nombre, dir, correo, num): 
      
        if not root: 
            return Nodo(nombre, dir, correo, num) 
        elif strcpr(nombre,root.nombre) == -1: 
            root.izq = self.insert(root.izq, nombre, dir, correo, num) 
        else: 
            root.der = self.insert(root.der, nombre, dir, correo, num) 
  
        root.peso = 1 + max(self.obtenerPeso(root.izq), 
                           self.obtenerPeso(root.der)) 
  
        balance = self.obtenerBalanceo(root) 


        if balance > 1 and strcpr(nombre,root.izq.nombre) == -1:
            return self.rightRotate(root) 
  
        if balance < -1 and strcpr(nombre,root.der.nombre) == 1: 
            return self.leftRotate(root) 
  
        if balance > 1 and strcpr(nombre,root.izq.nombre) == 1: 
            root.izq = self.leftRotate(root.izq) 
            return self.rightRotate(root) 
  
        if balance < -1 and strcpr(nombre,root.der.nombre) == -1:
            root.der = self.rightRotate(root.der) 
            return self.leftRotate(root) 

        return root
    def eliminar(self,root,nombre):
        if not root:
            return root
        elif strcpr(nombre,root.nombre) == -1: 
            root.izq = self.eliminar(root.izq, nombre) 
        elif strcpr(nombre,root.nombre) == 1: 
            root.der = self.eliminar(root.der, nombre)
        else:
            if root.izq is None: 
                temp = root.der 
                root = None
                return temp 
  
            elif root.der is None: 
                temp = root.izq 
                root = None
                return temp 
            temp = self.getMinValueNode(root.der) 
            root.nombre = temp.nombre
            root.der = self.delete(root.right, temp.nombre)

        if root is None:
                return root
        root.peso = 1 + max(self.obtenerPeso(root.izq), 
                           self.obtenerPeso(root.der)) 
  
        balance = self.obtenerBalanceo(root) 


        if balance > 1 and self.obtenerBalanceo(root.izq) >= 0: 
            return self.rightRotate(root) 
  
        if balance < -1 and self.obtenerBalanceo(root.der) <= 0: 
            return self.leftRotate(root) 
  
        if balance > 1 and self.obtenerBalanceo(root.izq) < 0: 
            root.izq = self.leftRotate(root.izq) 
            return self.rightRotate(root) 
  
        if balance < -1 and self.obtenerBalanceo(root.der) > 0: 
            root.der = self.rightRotate(root.der) 
            return self.leftRotate(root) 
  
        return root 



    def leftRotate(self, z): 
        y = z.der 
        T2 = y.izq 
  
        y.izq = z 
        z.der = T2 
  
        z.peso = 1 + max(self.obtenerPeso(z.izq), 
                         self.obtenerPeso(z.der)) 
        y.peso = 1 + max(self.obtenerPeso(y.izq), 
                         self.obtenerPeso(y.der)) 
  
        return y 
  
    def rightRotate(self, z): 
  
        y = z.izq
        T3 = y.der 
  
        y.der = z 
        z.izq = T3 
  
        z.peso = 1 + max(self.obtenerPeso(z.izq), 
                        self.obtenerPeso(z.der)) 
        y.peso = 1 + max(self.obtenerPeso(y.izq), 
                        self.obtenerBalanceo(y.der))
    def obtenerPeso(self, root):
        if not root:
            return 0
        return root.peso

    #factor de balanceo
    def obtenerBalanceo(self, root): 
        if not root: 
            return 0
  
        return self.obtenerBalanceo(root.izq) - self.obtenerBalanceo(root.der)
    def inorder(self, root):
        if not root:
            return
        root.imprimirNodo()
        self.inorder(root.izq)
        self.inorder(root.der)
    def getMinValueNode(self, root): 
        if root is None or root.izq is None: 
            return root 
  
        return self.getMinValueNode(root.izq) 

    def buscar(self,r, n):
        if r == None:
            return None
        if r.nombre == n:
            return r
        if strcpr(n,r.nombre) == 1:
            return self.buscar(r.der,n)
        else:
            return self.buscar(r.izq,n)


def archivo(r,a):
    csv.register_dialect('agenda',delimiter = ',')
    with open('datos_agenda.csv','r') as csvFile:
        reader = csv.reader(csvFile, dialect='agenda')
        for row in reader:
            nombre = row[0]
            direc = row[1]
            num = row[2]
            correo = row[3]
            r = a.insert(r,nombre,direc,correo,num)
    return r

def consultarAgenda(r,a):
    print("Escriba el nomnbre que desesa consultar: ")
    nombre = input()
    respuesta = a.buscar(r,nombre)
    if respuesta is None:
        print("Registro no encontrado :c")
    else:
        respuesta.imprimirNodo()


def insertarAgenda(r,a):
    print("Ingrese los siguientes datos: ")
    print("Nombre completo: ")
    nombre = input()
    print("Dirrecion: ")
    dirrecion = input()

    print("Correo: ")
    correo = input()
    print("Numero de telefono")
    num = input()
    return a.insert(r,nombre,dirrecion,correo,num)

def eliminarAgendar(r,a):
    while 8123:
        print("Escriba el nombre de la persona que desea eliminar: ")
        nombre = input()
        resp = a.buscar(r,nombre)
        print("Este es el registro que desea eliminar?")
        resp.imprimirNodo()
        print("1.-Si 2.-No")
        opc = input()
        if opc == '1':
            a.eliminar(r,nombre)
            print("El registro fue eliminado con exito!")
            break
        else:
            break

def menu():
    arbol = AVL_Tree()
    raiz = None
    raiz = archivo(raiz,arbol)
    print("Bienvenido a la Agenda AVL")
    while 8123:
        print("Elija la opcion deseada: ")
        print("1.-Agregar persona\n2.-Quitar Persona\n3.-Imprimir Agenda\n4.-Consultar Registro\n5.-Salir")
        opc = input();
        if opc == '1':
            raiz = insertarAgenda(raiz,arbol)
            print("El registro fue agregado con exito")
        elif opc == '2':
            eliminarAgendar(raiz,arbol)
        elif opc == '3':
            arbol.inorder(raiz)
        elif opc =='4':
            consultarAgenda(raiz,arbol)
        else:
            break
        





menu()

