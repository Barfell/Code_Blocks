from  Tkinter import *
import RPi.GPIO as gpio
import time

ap_1 = 4
ap_2 = 17
ap_3 = 27
ap_4 = 22
ap_5 = 10
ap_6 = 9
ap_7 = 11
ap_8 = 5


gpio.setwarnings(False)
gpio.setmode(gpio.BCM)
gpio.setup(ap_1, gpio.OUT)
gpio.setup(ap_2, gpio.OUT)
gpio.setup(ap_3, gpio.OUT)
gpio.setup(ap_4, gpio.OUT)
gpio.setup(ap_5, gpio.OUT)
gpio.setup(ap_6, gpio.OUT)
gpio.setup(ap_7, gpio.OUT)
gpio.setup(ap_8, gpio.OUT)


# ------------------------------------// Initialization \\--------------------------------
root = Tk()
root.title("Root")
var1 = IntVar()
var2 = IntVar()
var3 = IntVar() 
var4 = IntVar()
var5 = IntVar()
var6 = IntVar()
var7 = IntVar()
var8 = IntVar()
var9 = IntVar()
var10 = IntVar()
var11 = IntVar()
var12 = IntVar()
var13 = IntVar()



# ------------------------------------// Method Definitions \\----------------------------



def a():
    top = Toplevel()
    top.title("Room1")

    Message(top, text= "Room #1 Selected !").grid(padx = 30, pady = 30, sticky = N+S+W+E)
    

def b():
    top = Toplevel()
    top.title("Room2")

    Message(top, text= "Room #2 Selected !").grid(padx = 30, pady = 30, sticky = N+S+W+E)
    

def callback():
        
        a = [var1.get(),var2.get(),var3.get(),var4.get(),var5.get(),var6.get(),var7.get(),var8.get(),var9.get()]
        print a

        count = 0
  
	if var1.get() == 1:
		gpio.output(ap_1, gpio.HIGH)
                print '$>>--- AP_1 is ON ----<<$'
	if var1.get() == 0:
		gpio.output(ap_1,gpio.LOW)
	
	if var2.get() == 1:
		gpio.output(ap_2, gpio.HIGH)
		print '$>>--- AP_2 is ON ----<<$'
	if var2.get() == 0:
		gpio.output(ap_2,gpio.LOW)

	if var3.get() == 1:
		gpio.output(ap_3, gpio.HIGH)
		print '$>>--- AP_3 is ON ----<<$'
	if var3.get() == 0:
		gpio.output(ap_3,gpio.LOW)

	if var4.get() == 1:
		gpio.output(ap_4, gpio.HIGH)
		print '$>>--- AP_4 is ON ----<<$'
	if var4.get() == 0:
		gpio.output(ap_4,gpio.LOW)

	if var5.get() == 1:
		gpio.output(ap_5, gpio.HIGH)
		print '$>>--- AP_5 is ON ----<<$'
	if var5.get() == 0:
		gpio.output(ap_5,gpio.LOW)
	

	if var6.get() == 1:
		gpio.output(ap_6, gpio.HIGH)
		print '$>>--- AP_6 is ON ----<<$'
	if var6.get() == 0:
		gpio.output(ap_6,gpio.LOW)

	if var7.get() == 1:
		gpio.output(ap_7, gpio.HIGH)
		print '$>>--- AP_7 is ON ----<<$'
	if var7.get() == 0:
		gpio.output(ap_7,gpio.LOW)

	if var8.get() == 1:
		gpio.output(ap_8, gpio.HIGH)
		print '$>>--- AP_8 is ON ----<<$'
	if var8.get() == 0:
		gpio.output(ap_8,gpio.LOW)




        return

# -------------------------------------// Button Config \\-------------------------------------

Button(root, text = "#1", command = a).grid(row = 1, column = 2, padx = 50, pady = 50)
Button(root, text = "#2").grid(row = 11, column = 2)
Button(root, text='Send', command = callback).grid(row=17, sticky=S, pady=10)

# -----------------------------------// Label Config \\---------------------------------------

Label(root, text = "Please select room  ===>").grid(row =0, sticky = N)
Label(root, text = "Room 1").grid(row = 1, column = 0, sticky = W)
Label(root, text = "Room 2").grid(row = 11, column = 0, sticky = W)


# --------------------------------- // Room 1 Checkbuttons \\----------------------------------
a1 = Checkbutton(root, text="Ap_1", offvalue = 0, onvalue = 1, variable = var1).grid(row=2, padx = 17)
b1 = Checkbutton(root, text="Ap_2", offvalue = 0, onvalue = 1, variable = var2).grid(row=3, padx = 17)
c1 = Checkbutton(root, text="Ap_3", offvalue = 0, onvalue = 1, variable = var3).grid(row=4, padx = 17)
d1 = Checkbutton(root, text="Ap_4", offvalue = 0, onvalue = 1, variable = var4).grid(row=5, padx = 17)
e1 = Checkbutton(root, text="Ap_5", offvalue = 0, onvalue = 1, variable = var5).grid(row=6, padx = 17)
f1 = Checkbutton(root, text="Ap_6", offvalue = 0, onvalue = 1, variable = var6).grid(row=7, padx = 17)
g1 = Checkbutton(root, text="Ap_7", offvalue = 0, onvalue = 1, variable = var7).grid(row=8, padx = 17)
h1 = Checkbutton(root, text="Ap_8", offvalue = 0, onvalue = 1, variable = var8).grid(row=9, padx = 17)
# -----------------------------------------------------------------------------------------------

# --------------------------------- // Room 2 Checkbuttons \\----------------------------------

b2=Checkbutton(root, text="Ap_2", offvalue = 0, onvalue = 1, variable = var10).grid(row=13, padx = 17)
c2=Checkbutton(root, text="Ap_3", offvalue = 0, onvalue = 1, variable = var11).grid(row=14, padx = 17)
d2=Checkbutton(root, text="Ap_4", offvalue = 0, onvalue = 1, variable = var12).grid(row=15, padx = 17)
e2=Checkbutton(root, text="Ap_5", offvalue = 0, onvalue = 1, variable = var13).grid(row=16, padx = 17)
# -----------------------------------------------------------------------------------------------


root.mainloop()
