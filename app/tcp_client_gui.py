import tkinter as tk
from tkinter import *
import socket
import sys
from PIL import Image, ImageTk


#------------------------------ Funtzioak ------------------------------#


def proba(ip, port):
    print("IP:" + ip + "PORT:" + port + "\n")


def tcp_connect(ip, port):
    global sock
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    adr = (ip[:-1], int(port))

    try:
        s.connect(adr);
        print("[*] Konektatuta!")
        debug.configure(text = "Konektatuta!")
    except socket.gaierror:
        print("[!] Helbidea gaizki") 
        debug.configure(text = "Helbidea gaizki")
    except socket.error:
        print("[!] Konexio errorea")
        debug.configure(text = "Konexio errorea")
    sock = s
   

def tcp_send(s):
    mezua = "GET\r"
    s.send(mezua.encode('utf-8'))
    mezua = ""
    while True:
        buf = s.recv(4)
        mezua += buf.decode('utf-8')
        if mezua.find('\n') != -1:
            break
    print("[SERVER RESPONSE]\n" + mezua)
    data_label.configure(text = mezua)

def tcp_close(s):
    s.close()
    print("[*] Deskonektatuta!")
    debug.configure(text = "Deskonektatuta!")

def close():
    print("Agur!")
    debug.configure(text = "Agur!")
    exit()
#-----------------------------------------------------------------------#


#Cminimeteo_connecteate 
minimeteo_connect = tk.Tk()
minimeteo_connect.title('Minimeteo')
minimeteo_connect.geometry('1200x700')

conf_bar = Frame(minimeteo_connect)
conf_bar.place(height = 50, width = 1200)
conf_bar.configure(bg='#5e81ac')

main = Frame(minimeteo_connect)
main.place(x = 0, y = 50, height = 650, width = 1200)
main.configure(bg='#434c5e')


ip_label = Label(conf_bar, text='IP:', font = ("Hack", 15))
ip_label.place(relx=.02, rely=.5, anchor="center")
ip_label.configure(bg='#5e81ac')

ip_box = Text(conf_bar, height = 1, width = 16)
ip_box.place(relx = .1, rely = .5, anchor = "center")
ip_box.configure(bg='#e5e9f0')
ip_box.insert('end', "192.168.4.1")

port_label = Label(conf_bar, text='PORTUA:', font = ("Hack", 15))
port_label.place(relx=.2, rely=.5, anchor="center")
port_label.configure(bg='#5e81ac')

port_box = Text(conf_bar, height = 1, width = 16)
port_box.place(relx = .3, rely = .5, anchor = "center")
port_box.configure(bg='#e5e9f0')
port_box.insert('end', 4567)

#Create button to connect

connect = tk.Button(conf_bar, text='Connect', width=10, command= lambda: tcp_connect(ip_box.get(1.0, 'end'), port_box.get(1.0, 'end')), font = ("Hack", 15))
connect.place(relx=.45, rely=.5, anchor="center")
connect.configure(bg='#a3be8c')

debug = Label(conf_bar, text = "", font = ("Hack", 15))
debug.place(relx=.6, rely=.5, anchor="center")
debug.configure(bg='#5e81ac')

disconnect = tk.Button(conf_bar, text='Disconnect', width=10, command= lambda: tcp_close(sock), font = ("Hack", 15))
disconnect.place(relx=.8, rely=.5, anchor="center")
disconnect.configure(bg='#d08770')

exit_button = tk.Button(conf_bar, text='Exit', width=6, command= close, font = ("Hack", 15))
exit_button.place(relx=.95, rely=.5, anchor="center")
exit_button.configure(bg='#bf616a')



title_label = Label(main, text='MINIMETEO', font = ("Hack", 50), fg = '#e5e9f0')
title_label.place(relx=.5, rely=.1, anchor="center")
title_label.configure(bg = '#434c5e')

button2 = tk.Button(main, text='Send', width=15, command=lambda:tcp_send(sock), font = ("Hack", 15))
button2.place(relx=.5, rely=.5, anchor="center")
button2.configure(bg='#a3be8c')


tmp_label1 = Label(main, text='Tenperatura:', font = ("Hack", 20), fg = '#e5e9f0')
tmp_label1.place(relx=.1, rely=.3, anchor = "center")
tmp_label1.configure(bg = '#434c5e')

tmp_data = Label(main, text = "", font = ("Hack", 15), fg = '#e5e9f0')
tmp_data.place(relx=.25, rely=.3, anchor="center")
tmp_data.configure(bg = '#434c5e')

tmp_label2 = Label(main, text='°C', font = ("Hack", 20), fg = '#e5e9f0')
tmp_label2.place(relx=.35, rely=.3, anchor = "center")
tmp_label2.configure(bg = '#434c5e')


h_label1 = Label(main, text='Hezetasuna:', font = ("Hack", 20), fg = '#e5e9f0')
h_label1.place(relx=.1, rely=.4, anchor = "center")
h_label1.configure(bg = '#434c5e')

h_data = Label(main, text = "", font = ("Hack", 15), fg = '#e5e9f0')
h_data.place(relx=.25, rely=.4, anchor="center")
h_data.configure(bg = '#434c5e')

h_label2 = Label(main, text='%', font = ("Hack", 20), fg = '#e5e9f0')
h_label2.place(relx=.35, rely=.4, anchor = "center")
h_label2.configure(bg = '#434c5e')



minimeteo_connect.mainloop()
