import tkinter
from math import *

window = tkinter.Tk()
window.title("tkinter_example")
window.geometry("640x400+100+100")
window.resizable(False, False)

def calc(event):
    label.config(text="결과="+str(eval(entry.get())))
    
entry=tkinter.Entry(window)
entry.bind("<Return>",calc)
entry.pack()
    
label = tkinter.Label(window)
label.pack()

window.mainloop()