#ifndef GLOBLEVARIABLES_G
#define GLOBLEVARIABLES_G

#define IDC_Redio1    1
#define IDC_Redio2    2
#define IDC_Open1     3
#define IDC_Label1    4
#define IDC_TextBox1  5
#define IDC_Read1     6
#define IDC_SRedio1   7
#define IDC_SRedio2   8
#define IDC_SLabel1   9
#define IDC_SOpen1   10
#define IDC_TextBox2 11
#define IDC_TextBox3 12
#define IDC_SSave1   13
#define IDC_SSave2   14
#define IDC_TextBox4 15
#define help         16

int r1,r2,r3,r4;
HBITMAP SelectionBG = NULL;

HWND Openfile1,Openfile2,SaveFile,SaveFile2,mainW;;
HWND ReadButton,SelectItem,st1,st2,st3,st4,st5;
HWND ChoiceGroupB1,ChoiceGroupB2,ChoiceGroupB3,ChoiceGroupB4;
HWND ChoiceRedio1,ChoiceRedio2, SChoiceRedio1,SChoiceRedio2,Label1;
HWND TextBox1,TextBox2,TextBox3,TextBox4;

static OPENFILENAME ofn ;
      
	 char ErroeM[260];
	 char Stri[10485760]; //10mb

static TCHAR     szFileName[MAX_PATH], szTitleName[MAX_PATH];

BOOL		errflag = FALSE;
 
#endif