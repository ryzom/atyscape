
from random import randint as rand
from pygame import *

surf = image.load("test.tga")
surf.fill((0, 0, 0))

f = open("test.imageset")
fr = f.read().split("\n")
f.close()

rb = 255
gb = 255
bb = 255

s = 1
for line in fr:
    if (s == 1):
        rb = rb - 2
        r = rb
        g = rand(0, 255)
        b = rand(0, 255)
    if (s == 2):
        gb = gb - 2
        g = gb
        r = rand(0, 255)
        b = rand(0, 255)
    if (s == 3):
        bb = bb - 2
        b = bb
        g = rand(0 ,255)
        r = rand(0, 255)
        
    s = s + 1
    
    if s > 3:
        s = 1
    
    if line[:7] == "\t<Image":
        sline = line.split(" ")
        x, y, w, h = sline[2:6]
        x = x.split('"')[1]
        y = y.split('"')[1]
        w = w.split('"')[1]
        h = h.split('"')[1]
        print r, g, b
        rect = Rect(int(x), int(y), int(w), int(h))
        surf.fill((r, g, b), rect)

image.save(surf, "test_out.tga")