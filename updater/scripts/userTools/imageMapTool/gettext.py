import os

def get_text(text):
    global texts
    if text in texts.keys():
        return texts[text]
    else:
        texts[text] = '###'+text+'###'
        return text
            
def close():
    global texts
    final = ""
    for text, trs in texts.items():
        trs = trs.replace("\n", "\\n")
        final += text + " : " + trs + "\n"
        
    f = open("i18n_log.txt", "w")
    f.write(final)
    f.close()
            

f = open("lang.txt")
lang = f.read()
f.close()

texts = {}

if os.path.isfile("i18n_"+lang+".txt"):
    f = open("i18n_"+lang+".txt")
    fr = f.read().split("\n")
    f.close()

    for line in fr :
        line = line.replace("\\n", "\n")
        sline = line.split(" : ")
        if len(sline) >= 2:
            texts[sline[0]] = " : ".join(sline[1:])

    