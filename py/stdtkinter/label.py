import tk
import tkinter.font as tkf

class App(tk.Frame):
    def __init__(self, master):
        super().__init__(master)
        self.pack()
        self.addlabel()

    def addlabel(self):
        ft = tk.Font(self, size=20, weight=tkf.BOLD, underline=1, overstrike=1, slant = tkf.ROMAN)
        label = tk.Label(font=ft, bg='white', fg='red')
        label['text'] = 'My label'
        label.pack()

root = tk.Tk()
root['bg'] = 'white'
root.geometry('400x100')
app = App(root)
app.mainloop()
