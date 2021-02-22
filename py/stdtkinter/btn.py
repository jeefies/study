import tk

class App(tk.Frame):
    def __init__(self, master):
        super().__init__(master)
        self.pack()
        self.create_items()

    def create_items(self):
        self.btn = tk.Button(self)
        self.btn.config(text='Hi there', command=self.ehlo)
        self.btn.pack(side='top')

        self.quit = tk.Button(self, text='QUIT', fg='red')
        self.quit['bg'] = 'blue'
        self.quit.config(command=self.master.destroy)
        self.quit.pack(side='bottom', expand=0)

    def ehlo(self):
        print('Hello, there some one clicking me!')

root = tk.Tk()
app = App(root)
app.mainloop()
