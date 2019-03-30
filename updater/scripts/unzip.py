import sys, zipfile, os, hashlib

def unzip_file_into_dir(file, dir):
    if not os.path.isdir(dir):
        os.mkdir(dir, 0777)
    zfobj = zipfile.ZipFile(file, "r", zipfile.ZIP_DEFLATED)
    if(zfobj.testzip()):
        print "ERROR"
        return
    control = zfobj.read("control.sha")
    controls = {}
    for line in control.split("\n")[2:]:
        if line:
            sline = line.split("\t")
        print sline
        controls[sline[1][:-1]] = sline[0]

    for name in zfobj.namelist():
        if name.endswith('/'):
            os.mkdir(os.path.join(dir, name))
        else:
            if not os.path.isdir(os.path.join(dir, os.path.dirname(name))):
                os.makedirs(os.path.join(dir, os.path.dirname(name)))
            contents = zfobj.read(name)
            print ">>", name
            if (name == "control.sha"):
                continue
            if (hashlib.sha224(contents).hexdigest() != controls[name]):
                print "CHECK ERROR file : ", name
            outfile = open(os.path.join(dir, name), 'wb')
            outfile.write(zfobj.read(name))
            outfile.close()
            

def main():
    unzip_file_into_dir(sys.argv[1], sys.argv[2])

if __name__ == '__main__': main()
