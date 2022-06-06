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

#
# Funtzio honen bidez socket bat sortuko da tcp konexio bat irekitzeko.
#
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

    
#
# Funtzio honen bidez, datu bat didaliko da aurreko pausoan sortutako 
# socketa erabilita.
#
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

    # mezuaren tratamendua, informazioa ateratzeko
    mezua = mezua.strip()
    print(mezua)
    current_time = datetime.datetime.now()
    formated_date = str(current_time.year) + "/" + str(current_time.month) + "/" + str(current_time.day)
    formated_hour = str(current_time.hour) + ":" + str(current_time.minute)
    h_data.configure(text = mezua[3:7] )
    h_data2.configure(text = "%")
    time_label.configure(text = formated_date + ", " + formated_hour)
    #time_label2.configure(text = formated_date)
    #fahrenheit = (float(mezua[8:10])*1.8) + 32
    #tmp_data.configure(text = mezua[8:] + "°C, " + str(fahrenheit) + "°F")
    tmp_data.configure(text = mezua[8:12])
    tmp_data2.configure(text = "°C")
    anem = int(mezua[13:], 16)
    a_data.configure(text = str(anem) + ".0")
    a_data2.configure(text = "m/s")
    job_id = minimeteo_connect.after(3000, tcp_send, s)


#
# Fuztzio honen bidez tcp konexio bat itxiko da.
#
def tcp_close(s):
    global conn
    conn = False
    minimeteo_connect.after_cancel(job_id)
    s.close()
    print("[*] Deskonektatuta!")
    debug.configure(text = "Deskonektatuta!")
    print("Agur!")
    debug.configure(text = "Agur!")
    exit()

def get_data():
    global conn
    conn = 0

    
#-----------------------------------------------------------------------#


##### Leiho nagusia sortu #####
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
main.configure(bg='#b0c4de')


##### Goioko aldeko botoiak eta etiketen sorrera, aurreko Funtzioak erabiltzeko.

# IP helbidea jartzeko etiketa eta textbox-a
ip_label = Label(conf_bar, text='IP:', font = ("Hack", 15))
ip_label.place(relx=.02, rely=.5, anchor="center")
ip_label.configure(bg='#5e81ac')

ip_box = Text(conf_bar, height = 1, width = 16)
ip_box.place(relx = .1, rely = .5, anchor = "center")
ip_box.configure(bg='#e5e9f0')
ip_box.insert('end', "192.168.4.1")

# Portua jartzeko etiketa eta textbox-a
port_label = Label(conf_bar, text='PORTUA:', font = ("Hack", 15))
port_label.place(relx=.2, rely=.5, anchor="center")
port_label.configure(bg='#5e81ac')

port_box = Text(conf_bar, height = 1, width = 16)
port_box.place(relx = .3, rely = .5, anchor = "center")
port_box.configure(bg='#e5e9f0')
port_box.insert('end', 4567)

#Konektatzeko boitoia

connect = tk.Button(conf_bar, text='Connect', width=10, command= lambda: tcp_connect(ip_box.get(1.0, 'end'), port_box.get(1.0, 'end')), font = ("Hack", 15))
connect.place(relx=.45, rely=.5, anchor="center")
connect.configure(bg='#a3be8c')

debug = Label(conf_bar, text = "", font = ("Hack", 15))
debug.place(relx=.6, rely=.5, anchor="center")
debug.configure(bg='#5e81ac')

# Datuak lortzeko agindua emango duen botoia
getdatab = tk.Button(conf_bar, text='Get data', width=10, command= lambda: tcp_send(sock), font = ("Hack", 15))
getdatab.place(relx=.8, rely=.5, anchor="center")
getdatab.configure(bg='#d08770')

exit_button = tk.Button(conf_bar, text='Exit', width=6, command= lambda: tcp_close(sock), font = ("Hack", 15))
exit_button.place(relx=.95, rely=.5, anchor="center")
exit_button.configure(bg='#bf616a')


# Data eta ordua pantailaratzeko etiketa

time_label = Label(main, text="", font = ("Hack", 80), fg = '#1b2b40')
time_label.place(relx=.5, rely=.8, anchor = "center")
time_label.configure(bg = '#b0c4de')


# Momentuko eguraldia pantailaratu

tmp_label = Label(main, text='                              MOMENTUKO EGURALDIA                             ', font = ("Hack", 18), fg = '#e5e9f0')
tmp_label.place(relx=.5, rely=.1, anchor = "center")
tmp_label.configure(bg = '#4874ac')

tmp_data = Label(main, text = "", font = ("Hack", 80), fg = '#1b2b40')
tmp_data.place(relx=.15, rely=.3, anchor="center")
tmp_data.configure(bg = '#b0c4de')

tmp_data2 = Label(main, text = "", font = ("Hack", 40), fg = '#1b2b40')
tmp_data2.place(relx=.3, rely=.33, anchor="center")
tmp_data2.configure(bg = '#b0c4de')

h_data = Label(main, text = "", font = ("Hack", 80), fg = '#1b2b40')
h_data.place(relx=.45, rely=.3, anchor="center")
h_data.configure(bg = '#b0c4de')

h_data2 = Label(main, text = "", font = ("Hack", 40), fg = '#1b2b40')
h_data2.place(relx=.6, rely=.33, anchor="center")
h_data2.configure(bg = '#b0c4de')


a_data = Label(main, text = "", font = ("Hack", 80), fg = '#1b2b40')
a_data.place(relx=.75, rely=.3, anchor="center")
a_data.configure(bg = '#b0c4de')

a_data2 = Label(main, text = "", font = ("Hack", 40), fg = '#1b2b40')
a_data2.place(relx=.93, rely=.33, anchor="center")
a_data2.configure(bg = '#b0c4de')

h_label = Label(main, text='                                ORDUA ETA DATA                                ', font = ("Hack", 18), fg = '#e5e9f0')
h_label.place(relx=.5, rely=.6, anchor = "center")
h_label.configure(bg = '#4874ac')


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
