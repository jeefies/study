import tk

class App(tk.Frame):
    def __init__(self, master=None):
        super().__init__(master)
        self.pack()

app = App()

app.master.title("My app")
w, h = app.master.maxsize()
print(w, h)
# this won't change the gui's size, but limit the size depends on following args
app.master.maxsize(200, 200)

app.mainloop()
