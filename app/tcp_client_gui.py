import tkinter as tk
from tkinter import *
import socket
import select
import sys
import time
import requests
import datetime
from PIL import Image, ImageTk


#------------------------------ Funtzioak ------------------------------#


def tcp_connect(ip, port):
    global sock
    global conn
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
    conn = True

    
def tcp_send(s):
    global job_id 
    agindua = "GET\r"
    s.send(agindua.encode('utf-8'))
    mezua = ""
    s.settimeout(10)
    start = time.time()
    while True:
        try:
            buf = s.recv(4)
        except socket.timeout:
            print("timeout")
            break

        mezua += buf.decode('utf-8')
        end = time.time()
        elapsed = end - start
        if(elapsed >= 10):
            print("Itxarote denbora agortuta")
            break
        if(mezua.find('\n') != -1):
            break
    print("[SERVER RESPONSE]\n" + mezua)
    mezua = mezua[:-2]
    current_time = datetime.datetime.now()
    formated_time = str(current_time.year) + "/" + str(current_time.month) + "/" + str(current_time.day) + "  " + str(current_time.hour) + ":" + str(current_time.minute)
    h_data.configure(text = mezua[3:7] + "%")
    time_label.configure(text = formated_time)
    fahrenheit = (float(mezua[8:])*1.8) + 32
    tmp_data.configure(text = mezua[8:] + "°C, " + str(fahrenheit) + "°F")
    job_id = minimeteo_connect.after(5000, tcp_send, s)

def tcp_close(s):
    global conn
    conn = False
    minimeteo_connect.after_cancel(job_id)
    s.close()
    print("[*] Deskonektatuta!")
    debug.configure(text = "Deskonektatuta!")

def close():
    print("Agur!")
    debug.configure(text = "Agur!")
    exit()


def get_data():
    global conn
    conn = 0

    
#-----------------------------------------------------------------------#


#Cminimeteo_connecteate 
minimeteo_connect = tk.Tk()
minimeteo_connect.title('Minimeteo')
minimeteo_connect.geometry('1200x700')


conn = False
sock = 0
job_id = 0


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



title_label = Label(main, text='MINIMETEO', font = ("Hack", 80), fg = '#e5e9f0')
title_label.place(relx=.5, rely=.1, anchor="center")
title_label.configure(bg = '#434c5e')

button2 = tk.Button(main, text='Send', width=15, command=lambda:tcp_send(sock), font = ("Hack", 15))
button2.place(relx=.5, rely=.5, anchor="center")
button2.configure(bg='#a3be8c')

info_label = Label(main, text="", font = ("Hack", 25), fg = '#e5e9f0')
info_label.place(relx=.1, rely=.3, anchor = "center")
info_label.configure(bg = '#434c5e')



time_label = Label(main, text="", font = ("Hack", 35), fg = '#e5e9f0')
time_label.place(relx=.3, rely=.3, anchor = "center")
time_label.configure(bg = '#434c5e')



tmp_label = Label(main, text='Tenperatura:', font = ("Hack", 20), fg = '#e5e9f0')
tmp_label.place(relx=.1, rely=.5, anchor = "center")
tmp_label.configure(bg = '#434c5e')

tmp_data = Label(main, text = "", font = ("Hack", 20), fg = '#e5e9f0')
tmp_data.place(relx=.30, rely=.5, anchor="center")
tmp_data.configure(bg = '#434c5e')


h_label = Label(main, text='Hezetasuna:', font = ("Hack", 20), fg = '#e5e9f0')
h_label.place(relx=.1, rely=.6, anchor = "center")
h_label.configure(bg = '#434c5e')

h_data = Label(main, text = "", font = ("Hack", 20), fg = '#e5e9f0')
h_data.place(relx=.25, rely=.6, anchor="center")
h_data.configure(bg = '#434c5e')

#ip = requests.get("https://api.ipify.org").text

#ip = "83.213.146.232"
#url = "http://ip-api.com/json/" + ip
#
#resp = requests.get(url).json()
#
#info = resp['city'] + ", " + resp['country']
#info_label.configure(text = info)


if(conn == True):
    tcp_send(sock)

minimeteo_connect.mainloop()
