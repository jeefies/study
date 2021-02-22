import tk
from tk import spdl

root = tk.Tk()

# validate kwargs are ('initialvalue', 'minvalue', 'maxvalue', 'parent')

r = spdl.askstring('head title', 'question', initialvalue='your answer', parent=root)
print(r)

f = spdl.askfloat('flaot asking', 'A Float', initialvalue=1.23)
print(f)

# also has spdl.askinteger
# However there is a class named Dialog(parent, title)
# see github.com/python/cpython/blob/3.9/Lib/tkinter/simpledialog.py
