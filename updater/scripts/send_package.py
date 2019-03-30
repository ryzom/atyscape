import ftplib, os, sys


f = open("ftp_server.txt")
fr = f.read().split("\n")
f.close()

params = {}

for line in fr:
    sline = line.split(" = ")
    if len(sline) == 2:
        params[sline[0]] = sline[1]

version = raw_input("Version : ")
password = raw_input("Password : ")
ftp = ftplib.FTP(params["server"])
ftp.set_debuglevel(2)
ftp.login(params["login"], password)

archive = open("atyscape.zip", "rb")
preview = open("../web/v"+version.replace(".", "_")+".jpg", "rb")
ftp.storbinary('STOR atyscape.zip', archive)
ftp.storbinary('STOR preview.jpg', preview)
ftp.quit()
archive.close()