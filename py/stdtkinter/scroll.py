from tkinter import *

if __name__ == '__main__':
    # 创建主窗口
    root = Tk()
    root.geometry("50x200+100+100")
    # Canvas,Scrollbar放置在主窗口上
    canvas = Canvas(master=root)
    scro = Scrollbar(master=root)
    scro.pack(side='right',fill='y')
    canvas.pack(side='right')
    # Frame作为容器放置组件
    frame = Frame(canvas)
    frame.pack()
    # 将Frame添加至Canvas上
    canvas.create_window((0,0),window=frame,anchor="nw")
    # 添加按钮，以grid布局
    button1 = Button(master=frame,text='1').grid(row=1,column=0)
    button2 = Button(master=frame,text='2').grid(row=2,column=0)
    button3 = Button(master=frame,text='3').grid(row=3,column=0)
    button4 = Button(master=frame,text='4').grid(row=4,column=0)
    button5 = Button(master=frame,text='5').grid(row=5,column=0)
    button6 = Button(master=frame,text='x').grid(row=6,column=0)
    button7 = Button(master=frame,text='y').grid(row=7,column=0)
    button8 = Button(master=frame,text='z').grid(row=8,column=0)
    button9 = Button(master=frame,text='@').grid(row=9,column=0)
    button10 = Button(master=frame,text='#').grid(row=10,column=0)
    # 更新Frame大小，不然没有滚动效果
    frame.update()
    # 将滚动按钮绑定只Canvas上
    print(canvas.bbox("all"))
    canvas.configure(yscrollcommand=scro.set, scrollregion=canvas.bbox("all"))
    scro.config(command=canvas.yview)

    root.mainloop()
