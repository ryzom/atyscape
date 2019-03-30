import os, sys

import pygame

def load_image(filename):
    surf = pygame.image.load(filename)
    return surf
    
def get_sections(surf, filter = []):
    sections = {}
    colors = []
    for y in range(surf.get_height()):
        for x in range(surf.get_width()):
            color = surf.get_at((x, y))
            if color[0] != 254 :
                if filter == [] or color in filter :
                    if not color[0] in sections.keys():
                        sections[color[0]] = [x, y, x, y, color]
                        colors.append(color)
                    else:
                        col = sections[color[0]]
                        if x < col[0]:
                            sections[color[0]][0] = x
                        if x > col[2]:
                            sections[color[0]][2] = x
                        if y < col[1]:
                            sections[color[0]][1] = y
                        if y > col[3]:
                            sections[color[0]][3] = y

    return sections, colors

def create_alt(surf, sections, src, dst):
    surf = pygame.image.load(src)
    max_h = 0
    max_w = 0
    for sec in sections.values():
        max_w += sec[2] - sec[0] + 2
        sec[2] = sec[2] - sec[0]
        sec[3] = sec[3] - sec[1]
        if sec[3] > max_h : max_h = sec[3]
    
    print max_w, max_h
    new_surf = pygame.surface.Surface((max_w, max_h))
    i = 0
    for sec in sections.values():
        new_surf.blit(surf, (i+1, 1), sec[:4]);
        pygame.draw.rect(new_surf, sec[4], (i, 0, sec[2]+2, sec[3]+2), 1)
        i += sec[2]+2
    pygame.image.save(new_surf, dst)
            

def load_ddf(file):
    pass

def create_ddf(sections, sections_alt, file):
    final = ""
    for color, sec in sections.items():
        final += "{"+str(color)+"\n"
        final += "rect "+str(sec[0])+" "+str(sec[1])+" "+str(sec[2])+" "+str(sec[3])+"\n"
        i = 0
        if color in sections_alt.keys():
            col = sections_alt[color]
            final += "alt "+chr(ord("A")+i)+" "+str(col[0])+" "+str(col[1])+" "+str(col[2]-col[0])+" "+str(col[3]-col[1])+"\n"
        final += "}\n\n"

    f = open(file, "w")
    f.write(final)
    f.close()

surf = load_image("gui_map.png")
sections, colors = get_sections(surf)
create_alt(surf, sections, "gui.jpg", "gui_map_alt.bmp")
sections_alt, colors_alt = get_sections(load_image("gui_map_alt.bmp"), colors)
print sections_alt
create_ddf(sections, sections_alt, "gui.ddf")
