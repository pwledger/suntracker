import tkinter
from math import *

window = tkinter.Tk()
window.title("tkinter_example")
window.geometry("640x400+100+100")
window.resizable(False, False)

b1=tkinter.Button(window, text="top")
b2=tkinter.Button(window, text="bottom")
b3=tkinter.Button(window, text="left")
b4=tkinter.Button(window, text="right")
b5=tkinter.Button(window, text="center", bg="green")

b1.pack(side="top")
b2.pack(side="bottom")
b3.pack(side="left")
b4.pack(side="right")
b5.pack(expand=True, fill="both")

window.mainloop()