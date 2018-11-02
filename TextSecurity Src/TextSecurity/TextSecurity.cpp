#include <Windows.h>
#include <string.h>
#include <stdio.h>
#include <commdlg.h>

#include "resource1.h"
#include "GlobleVar.h"
#include "GlobleFun.h"

#include "encript.h"
#include "Compress.h"
#include "GlobleTSF.h"

char* GetWindText(HWND win)
{
	   int mLength;
	   PTSTR  mstrBuffer ;
       mLength = GetWindowTextLength (win) ;
	   mstrBuffer = (PTSTR) malloc ((mLength + 1) * sizeof (TCHAR)) ;
     
     if (!mstrBuffer)
     {
		 MessageBox(mainW,"Reading Char From Text Box Error !","Error !",MB_OK | MB_ICONERROR); 
		 mstrBuffer = "";
		 mLength = 0;
		 return "";
     }
        GetWindowText (win, mstrBuffer, mLength + 1) ;


    return mstrBuffer;
}

int  PopFileWrite(HWND  hwndEdit,char* szFileName)
{
	 
	  char* string1 = GetWindText(TextBox4);
	  char* fn = GetWindText(st5);
	  FileSaveAs(TextBox3,"TextSecurity_temp.txt");
	  char* pass  = GetWindText(TextBox2);

     if(r3 == 1)
	  {
		     char *argv1[] = {"","-C","-f",fn,"-p",pass,"TextSecurity_temp.txt",szFileName};
			 mainstart(8,argv1);
	  }
	  if(r4 == 1)
	  {
		     char *argv1[] = {"","-C","-m",string1,"-p",pass,"TextSecurity_temp.txt",szFileName};
			 mainstart(8,argv1);
	  }
	
	 if(!errflag)
	 {
          DeleteFile("TextSecurity_temp.txt");  
          SetWindowText(mainW,"TextSecurity");
		  strcat(ErroeM,"File Sucessfull ! Created");
	      MessageBox(mainW,ErroeM,"File Informetion",MB_OK | MB_ICONASTERISK);   
		  SetWindowText(TextBox4,"");
		  SetWindowText(TextBox2,"");
 
      	return TRUE;
	 }
	 else
	 {
		    DeleteFile("TextSecurity_temp.txt");  
		   SetWindowText(mainW,"TextSecurity - Error !");
		 return FALSE;
	 }
	  

}
void ReadfileE(char* szFileName1)
{
	   char* pass  = GetWindText(TextBox1);

	   char *argv1[] = {"","-C","-p",pass,szFileName1};

	 SetWindowText(mainW,"TextSecurity - Reading File...........");
	
	   SetWindowText(TextBox3," There Is No Hidden Text....");

	   mainstart(5,argv1);
	   SetWindowText(TextBox3,Stri);
	   SetWindowText(TextBox1,"");
	  SetWindowText(mainW,"TextSecurity");

	  strcpy(Stri,"");
}
int OpenDia(HWND hwnd)
{
                     char* ase  = GetWindText(TextBox2);
				 	   if(memcmp(ase,"",1) == 0)
					   {
						     
							   int m1;
						    m1 =  MessageBox(hwnd, "Do You Went To Continue Without Password !","Error !",MB_YESNO | MB_ICONERROR) ;
					      if(m1 == 6)
						  {
							  if (PopFileSaveDlg (mainW, szFileName, szTitleName))
                                {
							        SetWindowText(mainW,"TexySecurity - Please Wait File Is Creating ..........");
                                    if (PopFileWrite(TextBox3,szFileName))
                                   {
                                       return 1 ;
                                   }
                                   else
                                    {
							           char ar[50];
							           sprintf(ar,"Could not write file: %s",szTitleName);
									   MessageBox(hwnd, ar,"Error !",MB_OK | MB_ICONERROR) ;

                                      return 0 ;
                                    }
				                }
						  }
					 
					   }
					   else
					   {
						   if (PopFileSaveDlg (mainW, szFileName, szTitleName))
                                {
							        SetWindowText(mainW,"TexySecurity - Please Wait File Is Creating ..........");
                                    if (PopFileWrite(TextBox3,szFileName))
                                   {
                                       return 1 ;
                                   }
                                   else
                                    {
							           char ar[50];
							           sprintf(ar,"Could not write file: %s",szTitleName);
									   MessageBox(hwnd, ar,"Error !",MB_OK | MB_ICONERROR) ;

                                      return 0 ;
                                    }
				                }
					   }
}
BOOL CALLBACK IDD_Process(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
 
	 switch(Message)
	{   
		
		case WM_INITDIALOG:
		{

			 	 
    ChoiceGroupB3 =  CreateWindow ( TEXT("button"), "",  WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                                      0, 0, 450,57,  hwnd,NULL,  GetModuleHandle(NULL), NULL);
		             CreateWindow ( TEXT("button"), "",  WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                                      0, 70, 450,425,  hwnd,NULL,  GetModuleHandle(NULL), NULL);

		 st5 =   CreateWindow ( TEXT("STATIC"), "",  WS_CHILD | WS_VISIBLE |SS_LEFT ,
					   10,  33, 350,20,   hwnd,(HMENU)IDC_SLabel1,  GetModuleHandle(NULL), NULL) ;
		 st1 = 	 CreateWindow(TEXT("STATIC"), "Write Text To Show In File >",  WS_CHILD | WS_VISIBLE |SS_LEFT ,
					 10, 83, 200,16,   hwnd, NULL,  GetModuleHandle(NULL), NULL) ;

		 st2 = 	 CreateWindow ( TEXT("STATIC"), "Hear Is Hiddon Code Of File >",  WS_CHILD | WS_VISIBLE |SS_LEFT ,
					 10, 83, 200,16,   hwnd, NULL,  GetModuleHandle(NULL), NULL) ;

		 st3 =    CreateWindow ( TEXT("STATIC"), "Write Text To Hide In File >",  WS_CHILD | WS_VISIBLE |SS_LEFT ,
					 10, 256, 190,16,   hwnd, NULL,  GetModuleHandle(NULL), NULL) ;


	  Openfile2 =  CreateWindow ( TEXT("button"), "Select File",  WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                       370, 29, 75,20,  hwnd,(HMENU)IDC_SOpen1,  GetModuleHandle(NULL), NULL);
 
  SChoiceRedio1 =  CreateWindow ( TEXT("button"), "Select Text File To Hide",  WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                                       40,13, 180,15,  hwnd,(HMENU)IDC_SRedio1,  GetModuleHandle(NULL), NULL);
		  
	///------------
     SChoiceRedio2 =  CreateWindow ( TEXT("button"), "Write Text File",  WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                                       40, 60, 150,15,  hwnd,(HMENU)IDC_SRedio2,  GetModuleHandle(NULL), NULL);

	           st4 =  CreateWindow ( TEXT("STATIC"), "Enter Password : ",  WS_CHILD | WS_VISIBLE |SS_LEFT ,
					 10, 465, 115,20,    hwnd,NULL,  GetModuleHandle(NULL), NULL) ;

	    TextBox2  =  CreateWindow ( TEXT("EDIT"), "",  WS_CHILD | WS_VISIBLE  |ES_PASSWORD ,
					 130, 465, 230,20,    hwnd,(HMENU)IDC_TextBox2,  GetModuleHandle(NULL), NULL) ;
        

	    TextBox3  =  CreateWindow ( TEXT("EDIT"), "",  WS_CHILD | WS_VISIBLE | WS_VSCROLL  | ES_MULTILINE | ES_AUTOVSCROLL  ,
					 10, 102, 430,150,    hwnd,(HMENU)IDC_TextBox3,  GetModuleHandle(NULL), NULL) ;

     	TextBox4  =  CreateWindow ( TEXT("EDIT"), "",  WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
					 10, 277, 430,180,    hwnd,(HMENU)IDC_TextBox4,  GetModuleHandle(NULL), NULL) ;


         SaveFile =  CreateWindow ( TEXT("button"), "Save File",  WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                       370, 465, 70,20,  hwnd,(HMENU)IDC_SSave1,  GetModuleHandle(NULL), NULL);

	    SaveFile2 =  CreateWindow ( TEXT("button"), "Save File",  WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                       370, 465, 70,20,  hwnd,(HMENU)IDC_SSave2,  GetModuleHandle(NULL), NULL);


	        SendMessage (SChoiceRedio1, BM_SETCHECK, 1, 0) ;
			 r1 =1;
			 r2 =0;
			 r3 =1;
			 r4 =0;
		}
		break;
		case WM_PAINT:
		{
		 	DrawBGImage(hwnd);
	 
         }
		break;
		case WM_CTLCOLORSTATIC :
		{
		 	SetBkMode((HDC)wParam,TRANSPARENT);
			return (INT_PTR)(HBRUSH)GetStockObject(NULL_BRUSH);
	    }
		 case WM_COMMAND:
		{
               switch(LOWORD(wParam))
			{  
				     case IDC_SRedio1:
                   {
					      r1 =1;
					      r2 =0;
						  r3 =1;
						  r4 =0;
					       EnableWindow(Openfile2,1);
					      ShowWindow(st3, SW_HIDE);
						  ShowWindow(TextBox4, SW_HIDE);

						 MoveWindow (TextBox3,  10, 103, 430,355, TRUE) ;

				    break;
				   }
				   case IDC_SRedio2:
                   {
					       r1 =0;
					       r2 =1;
						   r3 =0;
						   r4 =1;
					       EnableWindow(Openfile2,0);
						   ShowWindow(st3, SW_SHOW);
						   ShowWindow(TextBox4, SW_SHOW);

				     MoveWindow (TextBox3,  10, 103, 430,155, TRUE) ;

				    break;
				   }
				   case IDC_SOpen1:
                   {
							if(PopFileOpenDlg(hwnd, szFileName, szTitleName))
                           {
							        SetDlgItemText(hwnd,IDC_SLabel1,szFileName);
                                 
						   }
					 
					break;         
                   }
				    case IDC_SSave1:
                   {

					     if(r3 == 1)
						 {
							   char* ase1  = GetWindText(st5);
					           if(memcmp(ase1,"",1) == 0)
					           {
						          MessageBox(mainW, " Please Select a file ! ","Error !",MB_OK | MB_ICONERROR) ;
							   }
							    else
					     	   {
							     OpenDia(hwnd)  ;
						       }
						  }
						 else
						 {
							  OpenDia(hwnd)  ;
						 }
						   
					   break;
				    }
				    case IDC_SSave2:
                   {
					      if (PopFileSaveDlg (hwnd, szFileName, szTitleName))
                         {
                                if (FileSaveAs(TextBox3,szFileName))
                               {
                                    return 1 ;
                               }
                               else
                               {
							       char ar[50];
							      sprintf(ar,"Could not write file: %s",szTitleName);
							       MessageBox(hwnd, ar,"Error !",MB_OK | MB_ICONERROR) ;

                                   return 0 ;
                              }
                         }
        
					   break;
				   }
			}
 	   }
	    break;
	  case WM_CLOSE:
			EndDialog(hwnd, 0);
		break;
	 
		 default:
			return FALSE;
	}
	return TRUE;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
      
   switch(msg)
	{ 
		
	 
		case WM_CREATE:
		{        

			     CreateWindow ( TEXT("button"), "Help",  WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                      405, 0, 80,15,  hwnd,(HMENU)help,  GetModuleHandle(NULL), NULL);
		 
		  SelectionBG = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP2));
		 	         if(SelectionBG == NULL)
				            MessageBox(hwnd, "Could not load IDB_BITMAP2!", "Error", MB_OK | MB_ICONEXCLAMATION);
 
        ChoiceGroupB1 =  CreateWindow ( TEXT("button"), "",  WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                                       20,  20, 470,67,  hwnd,NULL,  GetModuleHandle(NULL), NULL);

         ChoiceRedio1 =  CreateWindow ( TEXT("button"), "Show Text",  WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                                       40, 10, 100,15,  hwnd,(HMENU)IDC_Redio1,  GetModuleHandle(NULL), NULL);
		       SendMessage (ChoiceRedio1, BM_SETCHECK, 1, 0) ;

	        Openfile1 =  CreateWindow ( TEXT("button"), "Open File",  WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                       405, 35, 80,20,  hwnd,(HMENU)IDC_Open1,  GetModuleHandle(NULL), NULL);
		 
	       ReadButton =  CreateWindow ( TEXT("button"), "Read",  WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                       405, 60, 80,20,  hwnd,(HMENU)IDC_Read1,  GetModuleHandle(NULL), NULL);

		                  CreateWindow ( TEXT("STATIC"), "",  WS_CHILD | WS_VISIBLE |SS_LEFT ,
				          	 30, 35, 360,20,    hwnd,(HMENU)IDC_Label1,  GetModuleHandle(NULL), NULL) ;

	                      CreateWindow ( TEXT("STATIC"), "Enter Password : ",  WS_CHILD | WS_VISIBLE |SS_LEFT ,
			             		 30, 60, 115,20,    hwnd,NULL,  GetModuleHandle(NULL), NULL) ;

	       TextBox1  =  CreateWindow ( TEXT("EDIT"), "",  WS_CHILD | WS_VISIBLE  |ES_PASSWORD,
					 150, 60, 240,20,    hwnd,(HMENU)IDC_TextBox1,  GetModuleHandle(NULL), NULL) ;

        	SelectItem = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1),  hwnd, IDD_Process);
		        if(SelectItem != NULL)
		   	   {
		          ShowWindow(SelectItem, SW_SHOW);
			    }
		        else
		 	    {
			     	MessageBox(hwnd, "CreateDialog returned NULL", "Warning!", MB_OK | MB_ICONINFORMATION);
		        }
          ChoiceGroupB2 =  CreateWindow ( TEXT("button"), "",  WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                                       20,  105, 470,520,  hwnd,NULL,  GetModuleHandle(NULL), NULL);
		
           ChoiceRedio2 =  CreateWindow ( TEXT("button"), "Hide Text",  WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                                        40, 95, 100,15,  hwnd,(HMENU)IDC_Redio2,  GetModuleHandle(NULL), NULL);
			

		   mainW = hwnd;
		   PopFileInitialize (hwnd) ;

                      hideControlR1();
		}
		break;
		case WM_PAINT:
		{
		 	DrawBGImage(hwnd);
        
	    }
		break;
		case WM_CTLCOLORSTATIC :
		{
	 		SetBkMode((HDC)wParam,TRANSPARENT);
			return (INT_PTR)(HBRUSH)GetStockObject(NULL_BRUSH);
	    }
		case WM_CLOSE:
			DestroyWindow(hwnd);
		break;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{  
			       case IDC_Redio1:
                   {
					      hideControlR1();
						 
			 	    break;
				   }
				   case IDC_Redio2:
                   {
					      ShowControlR2();
				     break;
				   }
				   case IDC_Open1:
                   {
							if(PopFileOpenDlg(hwnd, szFileName, szTitleName))
                           {
							        SetDlgItemText(hwnd,IDC_Label1,szFileName);
                                 
						   }
					 
					break;         
                   }
				     case IDC_SOpen1:
                   {
							if(PopFileOpenDlg(hwnd, szFileName, szTitleName))
                           {
							        SetDlgItemText(hwnd,IDC_SLabel1,szFileName);
                           }
					 
					break;         
                   }
				    case IDC_Read1:
                   {
					     
						   if(strlen(szFileName)<2 || strlen(szTitleName)<1)
					           MessageBox(hwnd,"Please Select a TextSecurity Encripted Text File ", "Warning ! ", MB_OK | MB_ICONWARNING);
					      else
					     {
                             ReadfileE(szFileName);
						  }
				    break;
				   }
				    case help:
                   {
					   MessageBox(NULL," GOVT. Polytechnic Unnao \n \
									        Deep Govind  CSE Final Year  - 2015 / 2016 \n\
									       Email - deepgovind4@gmailo.com  Mo. - 7388966141 \n\
										  --- This is a Text Hiding Software , Select A text File Or \n \
										   Write file Using inbilt Notepad and Click Save File With \n\
										   any Other File Name , If you Show Error ! Message then \n\
										   Restart Application And Try Again ---\n\
										   If you Enter Wrong Password Then You Find Encript Data ","Help Point ",MB_OK);
				    break;
				   }
      	  }
 
		break;
		case WM_DESTROY:
	     	PostQuitMessage(0);
		break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;
   
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.style		 = 0;
	wc.lpfnWndProc	 = WndProc;
	wc.cbClsExtra	 = 0;
	wc.cbWndExtra	 = 0;
	wc.hInstance	 = hInstance;
	wc.hIcon		 = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(MAIN_ICO));
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName =  "MainWindow";
	wc.hIconSm		 = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(MAIN_ICO), IMAGE_ICON, 16, 16, 0);

	if(!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	} 

	hwnd = CreateWindowEx( WS_EX_STATICEDGE, "MainWindow", "TextSecurity",WS_OVERLAPPED     | \
                             WS_CAPTION        | \
                             WS_SYSMENU        | \
                             WS_MINIMIZEBOX,
                    CW_USEDEFAULT, CW_USEDEFAULT, 530, 680, NULL, NULL, hInstance, NULL);
 
	if(hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while(GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}
