
import sys, zipfile, os, hashlib, datetime, shutil

curdir = os.getcwd()

def copytree(src, dst=""):
    names = os.listdir(src)
    if dst and not os.path.isdir(dst):
        os.mkdir(dst)
    exclude = [".svn"]
    if os.path.isfile(src+"/exclude_files.txt"):
        print "[exclude_files.txt] X"
        exclude = open(src+"/exclude_files.txt").read().split("\n")
        exclude.append(".svn")
    for name in names:
        print "["+name+"]",
        if name in exclude :
            print "KO"
            continue
        print "OK"
        srcname = os.path.join(src, name)
        dstname = os.path.join(dst, name)
        try:
            if os.path.isdir(srcname):
                copytree(srcname, dstname)
            else:
                shutil.copy2(srcname, dstname)
        except (IOError, os.error), why:
            print "Can't copy %s to %s: %s" % (`srcname`, `dstname`, str(why))


def add_to_zip(src, zfile, controlfile):
    names = os.listdir(src)
    for name in names:
        if src:
            srcname = src+"/"+name
        else:
            srcname = name
        try:
            if os.path.isdir(srcname):
                if not os.path.isdir(curdir+"/atyscape_ref/"+srcname):
                    os.mkdir(curdir+"/atyscape_ref/"+srcname)
                add_to_zip(srcname, zfile, controlfile)
            else:
                hash = hashlib.sha224(open(srcname, "rb").read())
                fr = ""#hash.hexdigest()
                if os.path.isfile(curdir+"/atyscape_ref/"+srcname):      
                    f = open(curdir+"/atyscape_ref/"+srcname, "r")
                    fr = f.read()
                    f.close()

                if (sys.argv[4] == "full") or (hash.hexdigest() != fr) :
                    print "!=", srcname
                    f = open(curdir+"/atyscape_ref/"+srcname, "w")
                    f.write(hash.hexdigest())
                    f.close()
                    controlfile.write(hash.hexdigest()+"\t"+srcname+"\n")
                    zfile.write(srcname, srcname, zipfile.ZIP_DEFLATED)
                else:
                    print "=", srcname
                   
        except (IOError, os.error), why:
            print "Can't zip %s" % (`srcname`)

def main():
    os.system("setup_userTools.bat")
    copytree(sys.argv[1], sys.argv[2])
    copytree("addons", sys.argv[2])
    zfile = zipfile.ZipFile(sys.argv[3], "w")
    open("control.sha", "w").write("Control file : "+datetime.datetime.today().ctime()+"\n\n")
    controlfile = open("control.sha", "a")
    os.chdir(sys.argv[2])
    add_to_zip("", zfile, controlfile)
    controlfile.close()
    os.chdir("..")
    zfile.write("control.sha", "control.sha", zipfile.ZIP_DEFLATED)
    zfile.close()
    
if __name__ == '__main__': main()