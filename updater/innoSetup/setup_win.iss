[Setup]
OutputDir=.
AppCopyright=Under GPL license
AppName=AtyScape
LicenseFile=GPL.rtf
LanguageDetectionMethod=uilanguage
RestartIfNeededByRun=false
PrivilegesRequired=none
AllowUNCPath=false
UsePreviousGroup=false
WizardImageFile=atyscape.bmp
WizardImageBackColor=clBlack
WizardSmallImageFile=atys.bmp
SetupIconFile=atyscape_package.ico
AppID={{E53A2CA2-331A-4738-9FD3-668EB39D369D}
VersionInfoCopyright=GPL
AppVerName=AtyScape v0.9.0
DefaultDirName={pf}\atyscape\
DefaultGroupName=Atyscape
SourceDir=.
OutputBaseFilename=AtyscapeSetup
WizardImageStretch=false
AppendDefaultGroupName=false
[_ISTool]
UseAbsolutePaths=false
[Languages]
Name: "fr"; MessagesFile: "compiler:Languages\French.isl"
Name: "en"; MessagesFile: "compiler:Default.isl"
[Files]
Source: src\*; DestDir: {app} ; Flags : recursesubdirs
Source: atyscape.ico; DestDir: {app}
Source: atyscape_package.ico; DestDir: {app}
Source: Wiki.URL; DestDir: {app}
Source: firefox2005_icon_ico.ico; DestDir: {app}
[Icons]
Name: AtyScape\; Filename: {app}\updater\atyscape.exe; WorkingDir: {app}; IconFilename: {app}\updater\atyscape.ico; IconIndex: 0
Name: {userdesktop}\AtyScape; Filename: {app}\updater\atyscape.exe; WorkingDir: {app}\updater; IconFilename: {app}\atyscape.ico
Name: {group}\Atyscape; Filename: {app}\updater\atyscape.exe; WorkingDir: {app}\updater; IconFilename: {app}\atyscape.ico; IconIndex: 0
Name: {group}\Atyscape - Wiki; Filename: {app}\Wiki.URL; WorkingDir: {app}; IconFilename: {app}\firefox2005_icon_ico.ico; IconIndex: 0
Name: "{group}\Destroy Atyscape - Mouahahahahaha"; Filename: "{uninstallexe}"

[Run]
Filename: "{app}\updater\directx\dxwebsetup.exe"; Description: "Install DirectX"; Flags: postinstall

