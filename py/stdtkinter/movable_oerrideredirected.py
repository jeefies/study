import tk


class TopmoveFrame(tk.Frame): 
    ow = None
    oh = None
    xy = None

    @classmethod
    def _init(cls, root):
        cls.ow = root.winfo_x()
        cls.oh = root.winfo_y()
        cls.root = root

    @classmethod
    def _start(cls, x, y):
        cls.xy = x - cls.ow, y - cls.oh

    @classmethod
    def _move(cls, x, y):
        return x - cls.xy[0],  y - cls.xy[1]

    def __init__(self, master):
        super().__init__(master, {tk.Pack: dict(fill='x', side='top')}, \
                bg='white', height=30)

        self.bind('<Button1-Motion>', self.move)
        self.bind('<Button-1>', self.start)

    def move(self, e):
        self.master.geometry('+%d+%d' % self._move(e.x_root, e.y_root))

    def start(self, e):
        self._init(self.master)
        self._start(e.x_root, e.y_root)

class Tk(tk.Tk):
    def __init__(self):
        super().__init__()

        self.overrideredirect(True)

        self.geometry('100x50+100+100')
        self.closebitmap = tk.BitmapImage('@images/close2.xbm')

        self.crt_movef()

    def crt_movef(self):
        frame = TopmoveFrame(self)
        l = tk.Label(frame, {tk.Pack: dict(side='right')}, bitmap=self.closebitmap,
                bg='white')
        red = lambda e: l.configure(bg='red')
        white = lambda e: l.configure(bg='white')
        l.bind('<Enter>', red)
        l.bind('<Leave>', white)
        l.bind('<Button-1>', lambda e: self.destroy())


root = Tk()
tk.Button(root, command = root.destroy, text='destroy').pack()
root.mainloop()
