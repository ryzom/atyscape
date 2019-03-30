# -*- coding: utf-8 -*-
import math, wx, os, sys, shutil


class MyFrame(wx.Frame):
    def __init__(self, *args, **kwds):
        # begin wxGlade: MyFrame.__init__
        kwds["style"] = wx.DEFAULT_FRAME_STYLE
        wx.Frame.__init__(self, *args, **kwds)
        self.label_1 = wx.StaticText(self, -1, "UnBNP\n-\nRyturn Project (2008)", style=wx.ALIGN_CENTRE)
        self.label_2 = wx.StaticText(self, -1, "Liste des BNP Ryry :")
        self.bnps_list = wx.ListCtrl(self, -1, style=wx.LC_LIST)
        self.label_3 = wx.StaticText(self, -1, u"Répertoire de sortie : ")
        self.out_path = wx.TextCtrl(self, -1, "")
        self.button_1 = wx.Button(self, -1, u"Sélectionner")
        self.status = wx.StaticText(self, -1, u"Sélectionner un ou plusieurs BNP et un dossier où extraire les données", style=wx.ALIGN_CENTRE)
        self.generate = wx.Button(self, -1, "Generer")

        self.__set_properties()
        self.__do_layout()

        self.Bind(wx.EVT_BUTTON, self.cbSelectPath, self.button_1)
        self.Bind(wx.EVT_BUTTON, self.cbGenerate, self.generate)
        # end wxGlade
        
        self.dirselector = wx.DirDialog(self, "Sélectionner le dossier de sortie")
        self.outPath = ""
        
        f = open("atyscape_user.cfg")
        fr = f.read().split("\n")
        f.close()
        
        self.datapath = ""
        for line in fr:
            if line.split(" : ")[0] == "datapath":
                self.datapath = line.split(" : ")[1]
        
        bnps = os.listdir(self.datapath)
        self.bnps = []
        self.bnps_list.InsertColumn(0, "")
        #self.bnps_list.A
        for bnp in bnps:
            if bnp.split(".")[-1] == "bnp":
                self.bnps_list.InsertStringItem(0, bnp)
                self.bnps.append(bnp)

    def __set_properties(self):
        # begin wxGlade: MyFrame.__set_properties
        self.SetTitle("UnBNP - Rytun User Tool")
        self.SetSize((800, 400))
        self.SetBackgroundColour(wx.Colour(212, 226, 255))
        self.label_1.SetFont(wx.Font(12, wx.SWISS, wx.SLANT, wx.BOLD, 0, ""))
        # end wxGlade

    def __do_layout(self):
        # begin wxGlade: MyFrame.__do_layout
        sizer_2 = wx.BoxSizer(wx.VERTICAL)
        sizer_1 = wx.BoxSizer(wx.HORIZONTAL)
        sizer_2.Add(self.label_1, 0, wx.ALL|wx.EXPAND, 3)
        sizer_2.Add(self.label_2, 0, wx.EXPAND, 3)
        sizer_2.Add(self.bnps_list, 1, wx.EXPAND, 0)
        sizer_2.Add(self.label_3, 0, wx.ALL, 3)
        sizer_1.Add(self.out_path, 1, wx.EXPAND, 0)
        sizer_1.Add(self.button_1, 0, 0, 0)
        sizer_2.Add(sizer_1, 0, wx.ALL|wx.EXPAND, 3)
        sizer_2.Add(self.status, 0, wx.EXPAND, 0)
        sizer_2.Add(self.generate, 0, wx.ALL|wx.ALIGN_CENTER_HORIZONTAL, 3)
        self.SetSizer(sizer_2)
        self.Layout()
        # end wxGlade

    def cbGenerate(self, event): # wxGlade: MyFrame.<event_handler>

        self.status.SetLabel(u"Désarchivage en cours...")
        self.Update()
        curdir = os.getcwd()
        os.chdir(self.out_path.GetValue().encode("latin1"))
        
        selected = self.bnps_list.GetFirstSelected()
        while (selected != -1):
            shutil.copy(self.datapath + "\\" + self.bnps_list.GetItemText(selected), ".")
            os.system("\"" + curdir + "\\bnp_make.exe\" /u " + self.bnps_list.GetItemText(selected))
            os.remove(self.bnps_list.GetItemText(selected))
            selected = self.bnps_list.GetNextSelected(selected)
        self.status.SetLabel(u"Désarchivage OK")
        os.chdir(curdir)
        
    def cbSelectPath(self, event): # wxGlade: MyFrame.<event_handler>
        self.dirselector.ShowModal()
        self.out_path.SetValue(self.dirselector.GetPath())


# end of class MyFrame

if __name__ == "__main__":
    app = wx.PySimpleApp(0)
    wx.InitAllImageHandlers()
    frame_1 = MyFrame(None, -1, "")
    app.SetTopWindow(frame_1)
    frame_1.Show()
    app.MainLoop()


