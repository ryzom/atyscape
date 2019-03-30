import os, sys, shutil

def copytree(src, dst=""):
    names = os.listdir(src)
    if dst and not os.path.isdir(dst):
        os.mkdir(dst)
    for name in names:
        srcname = os.path.join(src, name)
        dstname = os.path.join(dst, name)
        try:
            if os.path.isdir(srcname):
                copytree(srcname, dstname)
            else:
                shutil.copy2(srcname, dstname)
        except (IOError, os.error), why:
            f = open("log_unpack.log", "a")
            f.write("Erreur !!! Impossible de copier de %s vers %s: %s" % (`srcname`, `dstname`, str(why)))	
            f.close()


f = open("log_unpack.log", "w")
f.write("")
f.close()

sys.path.append(".")

if os.path.isfile("one_update.py"):
    os.remove("one_update.py")
    
if os.path.isfile("one_update.pyo"):
    os.remove("one_update.pyo")

src = "unpack"

if os.path.isfile(src+"\\one_update.py"):
    fs = open(src+"\\one_update.py", "r")
    fd = open("one_update.py", "w")
    fd.write(fs.read())
    fd.close()
    fs.close()

    import one_update

if os.path.isdir(src):
    copytree(src)

f = open("log_unpack.log", "r")
fr = f.read()
f.close()

if fr != "":
    os.system("start log_unpack.log")
else:
    if os.path.isdir(src):
        shutil.rmtree(src)
    
os.execl("launcher.exe", "")
