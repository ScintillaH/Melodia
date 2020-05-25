; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMelodiaEditorDoc
LastTemplate=CFormView
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MelodiaEditor.h"
LastPage=0

ClassCount=8
Class1=CMelodiaEditorApp
Class2=CMelodiaEditorDoc
Class3=CMelodiaEditorView
Class4=CMainFrame

ResourceCount=5
Resource1=IDR_MAINFRAME
Resource2=IDD_PROJECTINFO
Class5=CAboutDlg
Class6=CNoteInfoView
Resource3=IDD_AUDIOVIEW
Class7=CProjectInfo
Resource4=IDD_ABOUTBOX
Class8=CAudioView
Resource5=IDD_NOTEINFOVIEW

[CLS:CMelodiaEditorApp]
Type=0
HeaderFile=MelodiaEditor.h
ImplementationFile=MelodiaEditor.cpp
Filter=N

[CLS:CMelodiaEditorDoc]
Type=0
HeaderFile=MelodiaEditorDoc.h
ImplementationFile=MelodiaEditorDoc.cpp
Filter=N
LastObject=CMelodiaEditorDoc
BaseClass=CDocument
VirtualFilter=DC

[CLS:CMelodiaEditorView]
Type=0
HeaderFile=MelodiaEditorView.h
ImplementationFile=MelodiaEditorView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CMelodiaEditorView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=MelodiaEditor.cpp
ImplementationFile=MelodiaEditor.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_EXPORT
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_VIEW_TOOLBAR
Command13=ID_VIEW_STATUS_BAR
Command14=ID_VIEW_PROJECTINFO
Command15=ID_APP_ABOUT
CommandCount=15

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[CLS:CNoteInfoView]
Type=0
HeaderFile=NoteInfoView.h
ImplementationFile=NoteInfoView.cpp
BaseClass=CFormView
Filter=D
LastObject=CNoteInfoView
VirtualFilter=VWC

[DLG:IDD_PROJECTINFO]
Type=1
Class=CProjectInfo
ControlCount=24
Control1=IDC_NAME,edit,1350631552
Control2=IDC_BPM,edit,1350631552
Control3=IDC_COMPOSER,edit,1350631552
Control4=IDC_STARTPOS,edit,1350631552
Control5=IDC_SELECT_BG,button,1342242816
Control6=IDC_SELECT_COVER,button,1342242816
Control7=IDC_SELECT_PREVIEW,button,1342242816
Control8=IDC_SELECT_FULL,button,1342242816
Control9=IDOK,button,1342242817
Control10=IDCANCEL,button,1342242816
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_NOTESNUM,edit,1350568064
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_BGBMP,edit,1350568064
Control18=IDC_STATIC,static,1342308352
Control19=IDC_COVERBMP,edit,1350568064
Control20=IDC_STATIC,static,1342308352
Control21=IDC_PREVIEW,edit,1350568064
Control22=IDC_STATIC,static,1342308352
Control23=IDC_FULL,edit,1350568064
Control24=IDC_STATIC,static,1342308352

[CLS:CProjectInfo]
Type=0
HeaderFile=ProjectInfo.h
ImplementationFile=ProjectInfo.cpp
BaseClass=CDialog
Filter=D
LastObject=CProjectInfo
VirtualFilter=dWC

[DLG:IDD_NOTEINFOVIEW]
Type=1
Class=CNoteInfoView
ControlCount=22
Control1=IDC_BAR,edit,1350631552
Control2=IDC_SPIN,msctls_updown32,1342177334
Control3=IDC_NUMERATOR,edit,1350631552
Control4=IDC_DENOMINATOR,edit,1350631552
Control5=IDC_HOLDNUMERATOR,edit,1350631552
Control6=IDC_HOLDDENOMINATOR,edit,1350631552
Control7=IDC_TRACK,edit,1350631552
Control8=IDC_ADD,button,1342242816
Control9=IDC_DELETE,button,1342242816
Control10=IDC_NOTELIST,listbox,1352728835
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_TIME,edit,1350568064
Control20=IDC_HOLD,edit,1350568064
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352

[DLG:IDD_AUDIOVIEW]
Type=1
Class=CAudioView
ControlCount=15
Control1=IDC_AUDIO_PLAY,button,1342242816
Control2=IDC_AUDIO_PAUSE,button,1342242816
Control3=IDC_AUDIO_POS,edit,1350631552
Control4=IDC_SET_START,button,1342242816
Control5=IDC_AUDIO_BAR,edit,1350631552
Control6=IDC_AUDIO_NUMERATOR,edit,1350631552
Control7=IDC_AUDIO_DENOMINATOR,edit,1350631552
Control8=IDC_LOCATE,button,1342242816
Control9=IDC_AUDIO_SLIDER,msctls_trackbar32,1342242874
Control10=IDC_STATIC,button,1342177287
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352

[CLS:CAudioView]
Type=0
HeaderFile=AudioView.h
ImplementationFile=AudioView.cpp
BaseClass=CFormView
Filter=D
VirtualFilter=VWC
LastObject=CAudioView

