import tk

class App(tk.Frame):
    def __init__(self, master):
        super().__init__(master)
        self.pack()

        self.en = tk.Entry()
        self.en.pack()

        self.cons = tk.StringVar()
        self.cons.set('This is variable')
        self.en['textvariable'] = self.cons

        self.en.bind('<Key-Return>', self.print_contents)

    def print_contents(self, event):
        print('Hi, The entry contents is :', self.cons.get())

root = tk.Tk()
app = App(root)
app.mainloop()
