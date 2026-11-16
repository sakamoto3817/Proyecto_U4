import tkinter as tk

def nuevoNumero(numero):
    entrada.insert(tk.END,numero)

def operacion():
    try:
        resultado=eval(entrada.get())
        entrada.delete(0,tk.END)
        entrada.insert(tk.END,str(resultado))

    except Exception as e:
        entrada.delete(0,tk.END)
        entrada.insert(tk.END,"Error")

def limpiar():
    entrada.delete(0,tk.END)

ventana=tk.Tk()
ventana.title("Calculadora")

entrada=tk.Entry(ventana, font=("Arial",20), justify="right")
entrada.grid(row=0,column=0, columnspan=4, padx=110, pady=10)

botones=[
    ("7",1,0),("8",1,1),("9",1,2),("/",1,3),    
    ("4",2,0),("5",2,1),("6",2,2),("*",2,3),
    ("1",3,0),("2",3,1),("3",3,2),("-",3,3),
    ("0",4,0),(".",4,1),("=",4,2),("+",4,3)
]

for valor, fila, columna in botones:
    boton=tk.Button(ventana, text=valor, font=("Arial",20),command=lambda v=valor: nuevoNumero(v))
    boton.grid(row=fila, column=columna, padx=5, pady=6, sticky="nsew")

BotonLimpiar=tk.Button(ventana, text="C", font=("Arial",20),command=limpiar)
BotonLimpiar.grid(row=5, column=0, padx=5, pady=5, columnspan=2, sticky="nsew")

calcularBoton=tk.Button(ventana, text="=", font=("Arial",20), command=operacion)
calcularBoton.grid(row=5, column=2, padx=5, pady=5, columnspan=2, sticky="nsew")

ventana.mainloop()
