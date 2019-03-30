import os, sys

#
#  ryzom_texture_name example : fy_hom_armor00_torse_c1_MA_U2.dds
#   => RACE_GENDER_TYPE_PART_TEX_SKIN_RACE_COLOR
#

DEBUG = 0

RACE = {
"fy" : "f",
"zo" : "z",
"tr" : "t",
"ma" : "m",
}

GENDER = {
"hom" : "m",
"hof" : "f",
"mo" : "c",
}

TYPE = {
"underwear" : "n",
"armor00" : "m",
"armor01" : "h",
"caster" : "c",
"caster01" : "c",
"civil01" : "l",
"civil01" : "l",
"casque01" : "h",
"casque02" : "h",
"casque03" : "h",
"casque04" : "h",

#Mobs
"dag" : "_dag",
    
#Mobs
"skel" : "*",

}

PART = {
"cheveux" : "c",
"visage" : "f",
"gilet" : "v1",
"torso" : "v1",
"torse" : "v1",
"dos" : "v2",
"back" : "v2",
"epaule" : "s1",
"bras" : "s",
"avt-bras" : "s2",
"avbras" : "s2",
"avtbras" : "s1",
"armpad" : "s",
"arm01" : "s",
"arm02" : "s",
"hand" : "g1",
"palm" : "g1",
"hand-upside" : "g1",
"hand-downside" : "g2",
"cuisseavt" : "p1",
"cuisseav" : "p1",
"cuisse-avt" : "p1",
"cuisse_avt" : "p1",
"cuissearr" : "p2",
"cuissear" : "p2",
"cuisse-arr" : "p2",
"cuisse_arr" : "p2",
"mollet" : "b1",
"molet" : "b0",
"pantabottes" : "p1",
"pieds" : "b2",
"pied" : "b2",
"foot" : "b2",
"bottes" : "b1",
"botte" : "b1",
}

MAKEUP = {
"makeup00" : "_A0_",
"makeup01" : "_A1_",
"makeup02" : "_A2_",
"makeup03" : "_A3_",
"makeup04" : "_A4_",
"makeup05" : "_A5_",
"makeup06" : "_A6_",
"makeup07" : "_A7_",
"makeup08" : "_A8_",
"makeup09" : "_A9_",
"makeup10" : "_B0_",
"makeup11" : "_B1_",
"makeup12" : "_B2_",
"makeup13" : "_B3_",
"makeup14" : "_B4_",
"makeup15" : "_B5_",
"makeup16" : "_B6_",
"makeup17" : "_B7_",
"makeup18" : "_B8_",
"makeup19" : "_B9_",
"makeup20" : "_C0_",
"makeup21" : "_C1_",
"makeup22" : "_C2_",
"makeup23" : "_C3_",
"makeup24" : "_C4_",
"makeup25" : "_C5_",
"makeup26" : "_C6_",
"makeup27" : "_C7_",
"makeup28" : "_C8_",
"makeup29" : "_C9_",
"makeup30" : "_D0_",
"makeup31" : "_D1_",
"makeup32" : "_D2_",
"makeup33" : "_D3_",
"makeup34" : "_D4_",
"makeup35" : "_D5_",
"makeup36" : "_D6_",
"makeup37" : "_D7_",
"makeup38" : "_D8_",
"makeup39" : "_D9_",
"makeup40" : "_E0_",
"makeup41" : "_E1_",
"makeup42" : "_E2_",
"makeup43" : "_E3_",
"makeup44" : "_E4_",
"makeup45" : "_E5_",
"makeup46" : "_E6_",
"makeup47" : "_E7_",
"makeup48" : "_E8_",
"makeup49" : "_E9_",
"makeup50" : "_F0_",
"makeup51" : "_F1_",
"makeup52" : "_F2_",
"makeup53" : "_F3_",
"makeup54" : "_F4_",
"makeup55" : "_F5_",
"makeup56" : "_F6_",
"makeup57" : "_F7_",
"makeup58" : "_F8_",
"makeup59" : "_F9_",
"makeup60" : "_G0_",
"makeup61" : "_G1_",
"makeup62" : "_G2_",
"makeup63" : "_G3_",
}


SKIN = {
"c1" : "b",
"c2" : "m",
"c3" : "h",
"short01" : "s",
"shave01" : "h",
"medium01" : "m",
"long01" : "l",
"artistic03" : "a",
"style03" : "y",
"fp" : "?",
}

SKIN.update(MAKEUP)

COLOR = {
"u1" : "r",
"u2" : "e",
"u3" : "g",
"u4" : "t",
"u5" : "b",
"u6" : "p",
"u7" : "w",
"u8" : "k",
"e1" : "w",
"e2" : "y",
"e3" : "r",
"e4" : "u",
"e5" : "g",
"e6" : "p",
"e7" : "o",
"e8" : "b",
"h1" : "w",
"h2" : "y",
"h3" : "b",
"h4" : "r",
"h5" : "u",
"h6" : "g",
}

SIZE = {
"small" : "s",
"mid" : "m",
"big" : "b",
"fp" : "f",
}

WEIGHT = {
"slim" : "s",
"fat" : "f"
}

texdatadefs = (RACE, GENDER, TYPE, PART, SKIN, RACE, COLOR)
shapedatadefs = (RACE, GENDER, TYPE, PART, SKIN, RACE, COLOR)
skeldatadefs = (RACE, GENDER, TYPE, SIZE, WEIGHT)

duplicated = {
"f?lg?*?" : (("tr_B_civil01_hand-upside_E_G.dds", "0"),),
"ffls???" : (("fy_hof_civil01_avt-bras_E_G.dds", "2"),),
"fmls?*?" : (("fy_hom_underwear_epaule_fy.dds", "0"),),
"fmlb???" : (("fy_hom_civil01_pied_E_F.dds", "1"),),
"fmlv?f?" : (("fy_hom_civil01_dos_E_F_G.dds", "2"),),
"fmlp???" : (("fy_hom_civil01_cuisse-avt_E_F_G.dds", "1"),),
"fm*f???" : (("fy_hom_visage_D_E_F.dds", "1"), ("fy_hom_ruflaket_E_h6.dds", "2"),("fy_hom_visage_D_E_F.dds", "3"),("fy_hom_visage_D_fy_F.dds", "4"),),

"m?ls???" : (("ma_B_civil01_epaule_E_F_G.dds", "1"), ("ma_B_civil01_avtbras_E_G.dds", "3"),),
"mflv???" : (("ma_hof_civil01_dos_E_F_G.dds", "2"), ("ma_hof_civil01_dos_E_F_G.dds", "3"),),
"mflp???" : (("ma_hof_civil01_cuisse-avt_E_F_G.dds", "0"),),
"mmlp?*?" : (("ma_hom_civil01_cuisse-avt_E.dds", "1"),),

"tflv???" : (("tr_hof_civil01_torso_E_F_G.dds", "1"),),
"tflp???" : (("tr_hof_civil01_cuissearr_E_G.dds", "2"),),

"zflp???" : (("zo_hof_civil01_cuisse-arr_E_F_G.dds", "2"),),
"zfls?z?" : (("zo_hof_civil01_epaule_E_F_G.dds", "1"), ("zo_hof_civil01_avt-bras_E_G.dds", "5"),),
"zfls?t?" : (("zo_hof_civil01_epaule_E_tr_G.dds", "1"), ("zo_hof_civil01_avt-bras_E_G.dds", "4"), ("zo_hof_civil01_avt-bras_E_G.dds", "5"),),
"zfls?f?" : (("zo_hof_civil01_epaule_E_fy_G.dds", "1"), ("zo_hof_civil01_avt-bras_E_G.dds", "4"), ("zo_hof_civil01_avt-bras_E_G.dds", "5"),),
"zfls?m?" : (("zo_hof_civil01_epaule_E_ma_G.dds", "1"), ("zo_hof_civil01_avt-bras_E_G.dds", "4"), ("zo_hof_civil01_avt-bras_E_G.dds", "5"),),
"zmls???" : (("zo_hom_civil01_epaule_E.dds", "1"),),
"zmlb???" : (("zo_hom_civil01_mollet_E_G.dds", "1"),),
}

multi_use_tex = {
"t?lg???" : ("mAlgBCD", "fAlgBCD", "zAlgBCD",),
}

multi_use_shape = {
"t?lg" : ("fAlg", "mAlg", "zAlg",)
}

translations = {
"ff*cs*?" : "ff*csf?",

"m?lp?*?" : "m?lp?m?",
"m?lb?*?" : "m?lb?m?",
"mmls?*?" : "mmls?m?",

#"t?lb?*?" : "t?lb?t?",
 #"t?ls?*?" : "t?ls?t?",
    
"z?ls?*?" : "z?ls?z?",
"zmlp?*?" : "zmlp?z?",

}

replication = {
"z?*fbz#" : (("w", "y", "r", "u", "g", "p", "o", "b"),),
"f?lb?#?" : (("f", "m", "z", "t"),),
"fflp?#?" : (("f", "m", "z", "t"),),
"t?lb?#?" : (("f", "m", "z", "t"),),
"t?ls?#?" : (("f", "m", "z", "t"), ("tr_B_underwear_epaule_#.dds", "0", ("fy", "ma", "zo", "tr")),),
}


def make_textures_datadef(texroot):
    texdirs = os.listdir(texroot)
    final = ""
    files = {}
    filters = {}
    allready_dup = []
    allready_replic = []
    
    for texdir in texdirs:
        if (texdir[:16] == "characters_maps_") or (texdir == "fauna_maps"):
            texfiles = os.listdir(texroot+"/"+texdir)
            for file in texfiles:
                files[file.lower()] = file

    for texdir in texdirs:
        if (texdir != "characters_maps_hr") and ((texdir[:16] == "characters_maps_") or (texdir == "fauna_maps")):
            texfiles = os.listdir(texroot+"/"+texdir)

            for file in texfiles:
                if DEBUG:
                    print file+"=",
                sfile = file.lower()[:-4].split("_")
                filter = ""
                element_idx = 0
                datadefs_idx = 0
                pos_filter = "0"
                while ((element_idx < len(sfile)) and (datadefs_idx < len(texdatadefs))):
                    if sfile[element_idx] in texdatadefs[datadefs_idx]:
                        filter_e = texdatadefs[datadefs_idx][sfile[element_idx]]
                        element_idx += 1
                        datadefs_idx += 1
                    elif element_idx < len(sfile)-1 and sfile[element_idx]+"_"+sfile[element_idx+1] in texdatadefs[datadefs_idx]:
                        filter_e = texdatadefs[datadefs_idx][sfile[element_idx]+"_"+sfile[element_idx+1]]
                        element_idx += 2
                        datadefs_idx += 1
                    else:
                        datadefs_idx += 1
                        filter_e = "*"
                    
                    if (filter_e[0] != "_") and (len(filter_e) > 1):
                        pos_filter = filter_e[1]
                        filter_e = filter_e[0]
                    
                    filter += filter_e
                if len(filter) < len(texdatadefs):
                    filter += "*"*(len(texdatadefs) - len(filter))
                    
                if DEBUG:
                    print filter
                    
                if not filter in filters.keys():
                    filters[filter] = [(pos_filter, file)]
                else:
                    filters[filter].append((pos_filter, file))
                
                for (dupli, texs) in duplicated.items():
                    is_valid = 1
                    i = 0
                    for c in dupli:
                        if (c != "?") and (c != filter[i]):
                            is_valid = 0
                            break
                        i += 1
                    if is_valid :
                        for (text, pos_filter) in texs:
                            i = 0
                            for c in sfile:
                                text = text.replace(chr(ord("A")+i), c)
                                i += 1
                            if (text in files) and (not filter in allready_dup) :
                                filters[filter].append((pos_filter, files[text]))
                            if not (text in files):
                                print "sfile", sfile
                                print "ERROR : ", text
                        allready_dup.append(filter)

                            
                            
                for (src, dests) in multi_use_tex.items():
                    is_valid = 1
                    i = 0
                    kcodes = ""
                    for c in src:
                        if (c == "?"):
                            kcodes += filter[i]
                        elif (c != filter[i]):
                            is_valid = 0
                            break
                        i += 1
                    if is_valid :
                        print "multi text :", filter, dests
                        for j in range(len(dests)):
                            i = 0
                            dest = dests[j]
                            for c in kcodes:
                                dest = dest.replace(chr(ord("A")+i), c)
                                i += 1
                        
                            filters[dest] = filters[filter]
                        
                for (src, dest) in translations.items():
                    is_valid = 1
                    i = 0
                    kcodes = ""
                    for c in src:
                        if (c == "?"):
                            kcodes += filter[i]
                        elif (c != "?") and (c != filter[i]):
                            is_valid = 0
                            break
                        else:
                            kcodes += dest[i]
                        i += 1
                    if is_valid :
                        if kcodes in filters :
                            filters[kcodes].extend(filters[filter])
                        else:
                            filters[kcodes] = filters[filter]
                            
                        del(filters[filter])
                        
                for (src, dests) in replication.items():
                    is_valid = 1
                    i = 0
                    kcodes = ""
                    for c in src:
                        if (c == "?"):
                            kcodes += filter[i]
                        elif (c != "?") and (c != "#") and (c != filter[i]):
                            is_valid = 0
                            break
                        else:
                            kcodes += src[i]
                        i += 1
                    if is_valid :
                        i = 0
                        for dst in dests[0]:
                            filters[kcodes.replace("#", dst)] = filters[filter][:]
                            if (len(dests) > 1) and (not filter in allready_replic) :
#                                allready_replic.append(filter)
                                for (texdup, texpos, dupdst) in dests[1:]:
                                    j = 0
                                    for c in sfile:
                                        texdup = texdup.replace(chr(ord("A")+j), c)
                                        j += 1
                                    print "dupli", kcodes.replace("#", dst), texdup.replace("#", dupdst[i]), sfile
                                    filters[kcodes.replace("#", dst)].append((texpos, files[texdup.replace("#", dupdst[i])]))
                            i += 1
                            
            
    for (filter, defs) in filters.items():
        definition = "{" + filter + "\n"
        defs.sort()
        for d in defs:
            definition += d[1] + "\n"
        definition += "}\n"
        final += definition
        final += "\n"
    
    custom = open("tex_custom.txt", "r")
    c = custom.read()
    custom.close()
    f = open("tex_datadefs.txt", "w")
    f.write(final)
    f.write(c)
    f.close()

def make_shapes_datadef(shaperoot):
    shapedirs = os.listdir(shaperoot)
    filters = {}
    
    final = ""
    
    for shapedir in shapedirs:		
        if ((shapedir == "characters_shapes") or (shapedir == "fauna_shapes")):
            shapefiles = os.listdir(shaperoot+"/"+shapedir)

            for file in shapefiles:
                if DEBUG:
                    print file+"=",
                sfile = file.lower()[:-6].split("_")
                filter = ""
                element_idx = 0
                datadefs_idx = 0
                
                while (datadefs_idx < len(shapedatadefs)) and (element_idx < len(sfile)):
                    if sfile[element_idx] in shapedatadefs[datadefs_idx].keys():
                        filter_e = shapedatadefs[datadefs_idx][sfile[element_idx]]
                        element_idx += 1
                        datadefs_idx += 1
                    else:
                        datadefs_idx += 1
                        filter_e = "*"
                            
                    if (filter_e[0] != "_") and (len(filter_e) > 1):
                        filter_e = filter_e[0]
                        
                    filter += filter_e
                                
                if DEBUG:
                    print filter
                if not filter in filters.keys():
                    filters[filter] = [file]
                else:
                    filters[filter].append(file)

                for (src, dests) in multi_use_shape.items():
                    is_valid = 1
                    i = 0
                    kcodes = ""
                    if len(src) != len(filter):
                        break
                    for c in src:
                        if (c == "?"):
                            kcodes += filter[i]
                        elif (c != filter[i]):
                            is_valid = 0
                            break
                        i += 1
                    if is_valid :
                        for j in range(len(dests)):
                            i = 0
                            dest = dests[j]
                            for c in kcodes:
                                dest = dest.replace(chr(ord("A")+i), c)
                                i += 1
                        
                            filters[dest] = filters[filter]

    for (filter, defs) in filters.items():
        definition = "{" + filter + "\n"
        for d in defs:
            definition += d + "\n"
        definition += "}\n"
        final += definition
        final += "\n"
                
                
                #final += "{" + filter + "\n" + defs + "\n}\n\n"
            
    custom = open("shape_custom.txt", "r")
    c = custom.read()
    custom.close()
    
    f = open("shape_datadefs.txt", "w")
    f.write(final)
    f.write(c)
    f.close()

def make_skeletons_datadef(skelroot):
    skelsroots = os.listdir(skelroot)
    filters = {}

    final = ""
    for skeldir in skelsroots:
        if (skeldir == "characters_skeletons") or (skeldir == "fauna_skeletons"):
            skelsfiles = os.listdir(skelroot+"/"+skeldir)
            filters = {}

            for file in skelsfiles:
                if DEBUG:
                    print file+"=",
                sfile = file.lower()[:-5].split("_")
                filter = ""
                element_idx = 0
                datadefs_idx = 0
                while (datadefs_idx < len(skeldatadefs)):
                    if (element_idx >= len(sfile)):
                        datadefs_idx += 1
                        filter_e = "*"
                    else:
                        if sfile[element_idx] in skeldatadefs[datadefs_idx].keys():
                            filter_e = skeldatadefs[datadefs_idx][sfile[element_idx]]
                            element_idx += 1
                            datadefs_idx += 1
                        else:
                            datadefs_idx += 1
                            filter_e = "*"
                        
                    filter += filter_e
                                
                if DEBUG:
                    print filter
                if not filter in filters.keys():
                    filters[filter] = [file]
                else:
                    filters[filter].append(file)
                    
            for (filter, defs) in filters.items():
                definition = "{" + filter + "\n"
                for d in defs:
                    definition += d + "\n"
                definition += "}\n"
                final += definition
                final += "\n"

    custom = open("skel_custom.txt", "r")
    c = custom.read()
    custom.close()

    f = open("skel_datadefs.txt", "w")
    f.write(final)
    f.write(c)
    f.close()	

def main():
    make_textures_datadef(sys.argv[1])
    make_shapes_datadef(sys.argv[2])
    make_skeletons_datadef(sys.argv[3])

if __name__ == '__main__': main()

