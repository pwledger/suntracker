import tkinter

window = tkinter.Tk()

window.title("tkinter_example")
window.geometry("640x400+100+100")
window.resizable(False, False)

label = tkinter.Label(window, text = "파이썬", width=10, height=5, fg="red", relief="solid")
label.pack()

window.mainloop()