#!/usr/bin/env python
# -*- coding: utf-8 -*-
# generated by wxGlade 0.6.3 on Thu Jul 10 00:22:54 2008

import wx
from gettext import get_text as _
from gettext import close

# begin wxGlade: extracode
# end wxGlade



class MyFrame(wx.Frame):
    def __init__(self, *args, **kwds):
        # begin wxGlade: MyFrame.__init__
        kwds["style"] = wx.DEFAULT_FRAME_STYLE
        wx.Frame.__init__(self, *args, **kwds)
        self.sizer_4_staticbox = wx.StaticBox(self, -1, _("DDFInit"))
        self.sizer_6_staticbox = wx.StaticBox(self, -1, _("SetEvent"))
        self.sizer_1_staticbox = wx.StaticBox(self, -1, _("AltImageCreator"))
        self.label_1 = wx.StaticText(self, -1, _("Ban"), style=wx.ALIGN_CENTRE)
        self.label_2 = wx.StaticText(self, -1, _("ImageRef"))
        self.text_ctrl_1 = wx.TextCtrl(self, -1, "")
        self.button_1 = wx.Button(self, -1, _("Select"))
        self.label_2_copy = wx.StaticText(self, -1, _("ImageMap"))
        self.text_ctrl_1_copy = wx.TextCtrl(self, -1, "")
        self.button_1_copy = wx.Button(self, -1, _("Select"))
        self.button_2 = wx.Button(self, -1, _("Create"))
        self.label_52 = wx.StaticText(self, -1, _("ImageAlt"))
        self.text_ctrl_51 = wx.TextCtrl(self, -1, "")
        self.button_51 = wx.Button(self, -1, _("Select"))
        self.button_2_copy = wx.Button(self, -1, _("Init"))
        self.combo_box_1 = wx.ComboBox(self, -1, choices=[], style=wx.CB_DROPDOWN)
        self.label_4_copy = wx.StaticText(self, -1, _("EventName"))
        self.combo_box_2 = wx.ComboBox(self, -1, choices=[_("MouseMove"), _("MouseUp"), _("MouseDown"), _("MouseClick")], style=wx.CB_DROPDOWN|wx.CB_READONLY)
        self.label_4 = wx.StaticText(self, -1, _("FunctionName"))
        self.combo_box_2_copy = wx.ComboBox(self, -1, choices=[_(".Move"), _(".Alt")], style=wx.CB_DROPDOWN)
        self.label_5 = wx.StaticText(self, -1, _("Args"))
        self.combo_box_2_copy_copy = wx.ComboBox(self, -1, choices=[_(".Move"), _(".Alt")], style=wx.CB_DROPDOWN)
        self.button_3 = wx.Button(self, -1, _("Add"))
        self.button_4 = wx.Button(self, -1, _("Del"))
        self.list_box_1 = wx.ListBox(self, -1, choices=[])
        self.button_62 = wx.Button(self, -1, _("Save"))
        self.text_ctrl_3 = wx.TextCtrl(self, -1, "")

        self.__set_properties()
        self.__do_layout()
        # end wxGlade

    def __set_properties(self):
        # begin wxGlade: MyFrame.__set_properties
        self.SetTitle(_("Title"))
        self.SetSize((800, 600))
        self.SetBackgroundColour(wx.Colour(212, 226, 255))
        self.SetForegroundColour(wx.Colour(103, 0, 0))
        self.label_1.SetFont(wx.Font(12, wx.SWISS, wx.SLANT, wx.BOLD, 0, ""))
        self.label_2.SetMinSize((65, 13))
        self.label_2_copy.SetMinSize((65, 13))
        self.label_52.SetMinSize((65, 13))
        self.combo_box_2.SetSelection(-1)
        self.combo_box_2_copy.SetSelection(-1)
        self.combo_box_2_copy_copy.SetSelection(-1)
        self.text_ctrl_3.SetBackgroundColour(wx.Colour(255, 189, 21))
        # end wxGlade

    def __do_layout(self):
        # begin wxGlade: MyFrame.__do_layout
        sizer_2 = wx.BoxSizer(wx.VERTICAL)
        sizer_6 = wx.StaticBoxSizer(self.sizer_6_staticbox, wx.VERTICAL)
        sizer_7 = wx.BoxSizer(wx.HORIZONTAL)
        sizer_8 = wx.BoxSizer(wx.VERTICAL)
        sizer_11 = wx.BoxSizer(wx.VERTICAL)
        sizer_10 = wx.BoxSizer(wx.VERTICAL)
        sizer_9 = wx.BoxSizer(wx.VERTICAL)
        sizer_4 = wx.StaticBoxSizer(self.sizer_4_staticbox, wx.VERTICAL)
        sizer_5 = wx.BoxSizer(wx.HORIZONTAL)
        sizer_1 = wx.StaticBoxSizer(self.sizer_1_staticbox, wx.VERTICAL)
        sizer_3_copy = wx.BoxSizer(wx.HORIZONTAL)
        sizer_3 = wx.BoxSizer(wx.HORIZONTAL)
        sizer_2.Add(self.label_1, 0, wx.ALL|wx.EXPAND, 3)
        sizer_3.Add(self.label_2, 0, 0, 0)
        sizer_3.Add(self.text_ctrl_1, 1, wx.EXPAND, 0)
        sizer_3.Add(self.button_1, 0, 0, 0)
        sizer_1.Add(sizer_3, 0, wx.EXPAND, 0)
        sizer_3_copy.Add(self.label_2_copy, 0, 0, 0)
        sizer_3_copy.Add(self.text_ctrl_1_copy, 1, wx.EXPAND, 0)
        sizer_3_copy.Add(self.button_1_copy, 0, 0, 0)
        sizer_1.Add(sizer_3_copy, 0, wx.EXPAND, 0)
        sizer_1.Add(self.button_2, 0, wx.ALIGN_RIGHT, 0)
        sizer_2.Add(sizer_1, 0, wx.EXPAND, 0)
        sizer_5.Add(self.label_52, 0, 0, 0)
        sizer_5.Add(self.text_ctrl_51, 1, wx.EXPAND, 0)
        sizer_5.Add(self.button_51, 0, 0, 0)
        sizer_4.Add(sizer_5, 0, wx.EXPAND, 0)
        sizer_4.Add(self.button_2_copy, 0, wx.ALIGN_RIGHT, 0)
        sizer_2.Add(sizer_4, 0, wx.EXPAND, 0)
        sizer_6.Add(self.combo_box_1, 0, wx.EXPAND, 0)
        sizer_9.Add(self.label_4_copy, 0, wx.TOP|wx.BOTTOM|wx.EXPAND, 2)
        sizer_9.Add(self.combo_box_2, 0, wx.EXPAND, 0)
        sizer_7.Add(sizer_9, 1, wx.EXPAND, 0)
        sizer_10.Add(self.label_4, 0, wx.TOP|wx.BOTTOM|wx.EXPAND, 2)
        sizer_10.Add(self.combo_box_2_copy, 0, wx.EXPAND, 0)
        sizer_7.Add(sizer_10, 1, wx.EXPAND, 0)
        sizer_11.Add(self.label_5, 0, wx.TOP|wx.BOTTOM|wx.EXPAND, 2)
        sizer_11.Add(self.combo_box_2_copy_copy, 0, wx.EXPAND, 0)
        sizer_7.Add(sizer_11, 1, wx.EXPAND, 0)
        sizer_8.Add(self.button_3, 0, wx.ALIGN_RIGHT, 0)
        sizer_8.Add(self.button_4, 0, wx.ALIGN_RIGHT, 0)
        sizer_7.Add(sizer_8, 0, wx.EXPAND, 0)
        sizer_6.Add(sizer_7, 0, wx.EXPAND, 0)
        sizer_6.Add(self.list_box_1, 1, wx.EXPAND, 0)
        sizer_6.Add(self.button_62, 0, wx.ALIGN_RIGHT, 0)
        sizer_2.Add(sizer_6, 1, wx.EXPAND, 0)
        sizer_2.Add(self.text_ctrl_3, 0, wx.EXPAND, 0)
        self.SetSizer(sizer_2)
        self.Layout()
        # end wxGlade

# end of class MyFrame


class MyApp(wx.App):
    def OnInit(self):
        wx.InitAllImageHandlers()
        frame_1 = MyFrame(None, -1, "")
        self.SetTopWindow(frame_1)
        frame_1.Show()
        return 1

# end of class MyApp

if __name__ == "__main__":
    app = MyApp(0)
    app.MainLoop()
    close()