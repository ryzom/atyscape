import os, shutil, sys

dirs = os.listdir(sys.argv[1])

listtools = []
for tool in dirs:
    dir = sys.argv[1]+"/"+tool
    if os.path.isdir(dir) and os.path.isfile(dir+"/infos.txt"):
        f = open(dir+"/infos.txt")
        fr = f.read().split("\n")
        f.close()
        
        listtools.append(fr[0].split(".")[0])
        f = open("addons/updater/userTools/"+fr[0].split(".")[0]+".txt", "w")
        f.write("\n".join(fr[1:]))
        f.close()
        
        curdir = os.getcwd()
        os.chdir(dir)
        os.system("c:\\python25\\python setup.py install")
        os.chdir(curdir)
        
        shutil.copy2(dir+"/dist/"+fr[0].split(".")[0]+".exe", "addons/updater/")

f = open("addons/updater/userTools/list.txt", "w")
f.write("\n".join(listtools))
f.close()
