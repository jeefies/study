from string import ascii_letters
import tkinter as tk
import tkinter.font as tkf

root = tk.Tk()

class BoxFrame(tk.Frame):
    def __init__(self, root):
        super().__init__(root)

        sb = tk.Scrollbar(self)
        sb.pack(side='right', fill='y')

        self.listbox = tk.Listbox(self, {tk.Pack: dict(fill='both', expand='yes')}, bg='white', yscrollcommand=sb.set)
        sb.configure(command=self.listbox.yview)

        self.fontfamilies = sorted(set(tkf.families(root)))

        for fml in self.fontfamilies:
            self.listbox.insert('end', fml)

        self.listbox.bind('<ButtonRelease-1>', self.pfont)
        #self.listbox.bind('<Return>', self.pfont)
        self.listbox.bind('<KeyRelease-Up>', self.pfont)
        self.listbox.bind('<KeyRelease-Down>', self.pfont)

        self.listbox.pack()
        self.pack(fill='y', expand='yes', side='left')

        self.update()
        self.listbox.update()

    def pfont(self, event = None):
        selected = self.listbox.curselection()
        family = self.listbox.get(selected[0])

        font.config(family = family)
        #root.geometry(size)

class FontFrame(tk.Frame):
    def __init__(self, root):
        super().__init__(root)

        text = tk.Text(self, font = font)

        text.insert('1.0', ascii_letters)
        text['state'] = 'disabled'
        text.pack(fill = 'both', expand = 'yes')
        self.pack(fill = 'both')

size = '600x200'
font = tkf.Font()
BoxFrame(root)
FontFrame(root)

root.geometry(size)
root.resizable(0,0)
root.title('Font Configure')

root.mainloop()
