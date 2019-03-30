import httplib, urllib, os

def getUpdates() :
    conn = httplib.HTTPConnection("packages.ryturn.org")
    conn.request("GET", "/index.html")
    r1 = conn.getresponse()
    print r1.status, r1.reason

    data = r1.read().split('\n')
    conn.close()
    
    print urllib.urlretrieve("http://packages.ryturn.org/preview.jpg", "imgs/preview.jpg")
    print urllib.urlretrieve("http://packages.ryturn.org/infos.txt", "infos.txt")

    
    fullPackage = ["", ""]
    avaPackage = ""

    for line in data:
        if line and line[0] == "-":
            sline = line.split(" ")
            print sline
            if sline[1] == "FullWinPackage":
                vers = sline[3][1:].split("<")[0]
                link = ""
                if sline[4] == "<a":
                    link = sline[6].split('"')[1]
                fullPackage = [vers, link]
            if sline[1] == "WinPackage":
                avaPackage = sline[3][1:].split("<")[0]


    return [avaPackage, fullPackage]
    
def download(url, dest, hook) :
    print url.split("/")[0] + "//".join(url.split("/")[1:])
    #conn = httplib.HTTPConnection(url.split("/")[0])
    #conn.request("GET", "/"+"/".join(url.split("/")[1:]))
    #r1 = conn.getresponse()
    #print r1.getheaders()
    #print r1.getheader("content-length")
    #fileLen = int(r1.getheader("content-length"))
    #sections = fileLen / 1024
    #downBytes = 0
    #fulldata = ""
    #i = 0
    #while downBytes < fileLen:
        #~ data = r1.read(1024)
        #~ downBytes = downBytes + 1024
        #~ fulldata = fulldata + data
        #~ print (100*downBytes)/fileLen

    if not os.path.isdir(os.path.dirname(dest)):
        os.makedirs(os.path.dirname(dest))
    print urllib.urlretrieve(url, dest, hook)

   # f = open(dest+"/atyscape.zip", "w")
   # f.write(fulldata)
   # f.close()

    #conn.close()
