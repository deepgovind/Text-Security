#ifndef GLOBLEFUNCATION_H
#define GLOBLEFUNCATION_H


void DrawBGImage(HWND hwnd)
{
	 
	        BITMAP bm;
			PAINTSTRUCT ps;
			HDC hdc;
		    hdc = BeginPaint(hwnd, &ps);
			HDC hdcMem = CreateCompatibleDC(hdc);
			HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, SelectionBG);
			GetObject(SelectionBG, sizeof(bm), &bm);
			BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
			SelectObject(hdcMem, hbmOld);
 
			DeleteDC(hdcMem);
			EndPaint(hwnd, &ps);
}

  BOOL	compress_flag = FALSE;
  BOOL	quiet_flag = FALSE;
  int	line_length = 80;

  void	password_set (const char *passwd);
  BOOL	message_extract (FILE *inf, FILE *outf);
  void	space_calculate (FILE *inf);

  void	compress_init (void);
  BOOL	compress_bit (int bit, FILE *inf, FILE *outf);
  BOOL	compress_flush (FILE *inf, FILE *outf);

  void	uncompress_init (void);
  BOOL	uncompress_bit (int bit, FILE *outf);
  BOOL	uncompress_flush (FILE *outf);

  void	encrypt_init (void);
  BOOL	encrypt_bit (int bit, FILE *inf, FILE *outf);
  BOOL	encrypt_flush (FILE *inf, FILE *outf);

  void	decrypt_init (void);
  BOOL	decrypt_bit (int bit, FILE *outf);
  BOOL	decrypt_flush (FILE *outf);

  void	encode_init (void);
  BOOL	encode_bit (int bit, FILE *inf, FILE *outf);
  BOOL	encode_flush (FILE *inf, FILE *outf);

  void PopFileInitialize (HWND hwnd)
{
     static TCHAR szFilter[] = TEXT ("Text Files (*.txt)\0*.txt\0")  \
                               TEXT ("All Files (*.*)\0*.*\0\0") ;
     
     ofn.lStructSize       = sizeof (OPENFILENAME) ;
     ofn.hwndOwner         = hwnd ;
     ofn.hInstance         = NULL ;
     ofn.lpstrFilter       = szFilter ;
     ofn.lpstrCustomFilter = NULL ;
     ofn.nMaxCustFilter    = 0 ;
     ofn.nFilterIndex      = 0 ;
     ofn.lpstrFile         = NULL ;       
     ofn.nMaxFile          = MAX_PATH ;
     ofn.lpstrFileTitle    = NULL ;        
     ofn.nMaxFileTitle     = MAX_PATH ;
     ofn.lpstrInitialDir   = NULL ;
     ofn.lpstrTitle        = NULL ;
     ofn.Flags             = 0 ;         
     ofn.nFileOffset       = 0 ;
     ofn.nFileExtension    = 0 ;
     ofn.lpstrDefExt       = TEXT ("txt") ;
     ofn.lCustData         = 0L ;
     ofn.lpfnHook          = NULL ;
     ofn.lpTemplateName    = NULL ;
}

BOOL PopFileOpenDlg(HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName)
{
     ofn.hwndOwner         = hwnd ;
     ofn.lpstrFile         = pstrFileName ;
     ofn.lpstrFileTitle    = pstrTitleName ;
     ofn.Flags             = OFN_HIDEREADONLY | OFN_CREATEPROMPT ;
     
     return GetOpenFileName(&ofn) ;
}
BOOL PopFileSaveDlg (HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName)
{
     ofn.hwndOwner         = hwnd ;
     ofn.lpstrFile         = pstrFileName ;
     ofn.lpstrFileTitle    = pstrTitleName ;
     ofn.Flags             = OFN_OVERWRITEPROMPT ;
     
     return GetSaveFileName (&ofn) ;
}

int FileSaveAs(HWND  hwndEdit,char* FileName)
{
	 DWORD  dwBytesWritten ;
     HANDLE hFile ;
     int    iLength ;
     PTSTR  pstrBuffer ;
     WORD   wByteOrderMark = 0xFEFF ;
     
     if (INVALID_HANDLE_VALUE == (hFile = CreateFile (FileName, GENERIC_WRITE, 0,  NULL, CREATE_ALWAYS, 0, NULL)))
                return FALSE ;

      iLength = GetWindowTextLength (hwndEdit) ;
     pstrBuffer = (PTSTR) malloc ((iLength + 1) * sizeof (TCHAR)) ;
     
     if (!pstrBuffer)
     {
          CloseHandle (hFile) ;
          return FALSE ;
     }
	 
        
#ifdef UNICODE
     WriteFile (hFile, &wByteOrderMark, 2, &dwBytesWritten, NULL) ;
#endif

       GetWindowText (hwndEdit, pstrBuffer, iLength + 1) ;
       WriteFile (hFile, pstrBuffer, iLength * sizeof (TCHAR), &dwBytesWritten, NULL) ;
     
     if ((iLength * sizeof (TCHAR)) != (int) dwBytesWritten)
     {
          CloseHandle (hFile) ;
          free (pstrBuffer) ;
          return FALSE ;
     }
     
     CloseHandle (hFile) ;
     free (pstrBuffer) ;

	 return 1; 
}
void ShowControlR2()
{
	                       EnableWindow(Openfile1,0);
					       EnableWindow(ReadButton,0);
						   EnableWindow(TextBox1,0);
					      
						   if(r1 == 1)
						   {
							  EnableWindow(Openfile2,1);
							  ShowWindow(st3, SW_HIDE);
						      ShowWindow(TextBox4, SW_HIDE);

						 	  MoveWindow (TextBox3,  10, 103, 430,355, TRUE) ;
                           }
						   if(r2 == 1)
						   {
                                 EnableWindow(Openfile2,0);
								  ShowWindow(st3, SW_SHOW);
						          ShowWindow(TextBox4, SW_SHOW);

							MoveWindow (TextBox3,  10, 103, 430,155, TRUE) ;
						    } 
						   EnableWindow(SChoiceRedio1,1);
						   EnableWindow(SChoiceRedio2,1);
					       EnableWindow(TextBox2,1);
						 
					       EnableWindow(SaveFile,1);
           		           ShowWindow(SaveFile, SW_SHOW);
						   ShowWindow(TextBox2, SW_SHOW);
						   ShowWindow(st1, SW_SHOW);
						   ShowWindow(st4, SW_SHOW);
						   ShowWindow(st2, SW_HIDE);
						   ShowWindow(SaveFile2, SW_HIDE);
}
void hideControlR1()
{
	                         ShowWindow(st3, SW_HIDE);
						     ShowWindow(TextBox4, SW_HIDE);
                            MoveWindow (TextBox3,  10, 103, 430,355, TRUE) ;

	                       EnableWindow(Openfile1,1);
					       EnableWindow(ReadButton,1);
						   EnableWindow(TextBox1,1);
					       EnableWindow(SaveFile2,1);

						   EnableWindow(SChoiceRedio1,0);
					       EnableWindow(SChoiceRedio2,0);
						   EnableWindow(TextBox2,0);
						   EnableWindow(Openfile2,0);
					       EnableWindow(SaveFile,0);

						   ShowWindow(TextBox4, SW_HIDE);
						   ShowWindow(SaveFile, SW_HIDE);
						   ShowWindow(TextBox2, SW_HIDE);
						   ShowWindow(st1, SW_HIDE);
						   ShowWindow(st3, SW_HIDE);
						   ShowWindow(st4, SW_HIDE);
						   ShowWindow(st2, SW_SHOW);
						   ShowWindow(SaveFile2, SW_SHOW);
}

 
#endif