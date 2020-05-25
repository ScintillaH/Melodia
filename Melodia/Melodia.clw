; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMelodiaDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "melodia.h"
LastPage=0

ClassCount=5
Class1=CMelodiaApp
Class2=CAboutDlg
Class3=CMelodiaDlg

ResourceCount=5
Resource1=IDD_MELODIA_DIALOG
Resource2=IDD_LOGIN
Resource3=IDD_REGISTER
Class4=CLogin
Resource4=IDD_ABOUTBOX
Class5=CRegister
Resource5=IDR_MENU

[CLS:CMelodiaApp]
Type=0
BaseClass=CWinApp
HeaderFile=Melodia.h
ImplementationFile=Melodia.cpp
LastObject=CMelodiaApp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=MelodiaDlg.cpp
ImplementationFile=MelodiaDlg.cpp
LastObject=IDOK

[CLS:CMelodiaDlg]
Type=0
BaseClass=CDialog
HeaderFile=MelodiaDlg.h
ImplementationFile=MelodiaDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=CMelodiaDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_MELODIA_DIALOG]
Type=1
Class=CMelodiaDlg
ControlCount=0

[MNU:IDR_MENU]
Type=1
Class=?
Command1=ID_LEAP_START
Command2=ID_LEAP_SELECT
Command3=ID_DISPLAY_FPS
Command4=ID_DISPLAY_RESOLUTION1
Command5=ID_DISPLAY_RESOLUTION2
Command6=ID_DISPLAY_RESOLUTION3
Command7=ID_HELP_ABOUT
CommandCount=7

[DLG:IDD_LOGIN]
Type=1
Class=CLogin
ControlCount=6
Control1=IDC_USERNAME,edit,1342242944
Control2=IDC_PASSWORD,edit,1342242976
Control3=IDOK,button,1342275585
Control4=IDCANCEL,button,1342275584
Control5=IDC_STATIC,static,1342308864
Control6=IDC_STATIC,static,1342308864

[CLS:CLogin]
Type=0
HeaderFile=Login.h
ImplementationFile=Login.cpp
BaseClass=CDialog
Filter=D
LastObject=CLogin
VirtualFilter=dWC

[DLG:IDD_REGISTER]
Type=1
Class=CRegister
ControlCount=8
Control1=IDC_USERNAME,edit,1342242944
Control2=IDC_PASSWORD,edit,1342242976
Control3=IDC_CONFIRM,edit,1342242976
Control4=IDOK,button,1342275585
Control5=IDCANCEL,button,1342275584
Control6=IDC_STATIC,static,1342308864
Control7=IDC_STATIC,static,1342308864
Control8=IDC_STATIC,static,1342308864

[CLS:CRegister]
Type=0
HeaderFile=Register.h
ImplementationFile=Register.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

