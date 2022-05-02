#include <windows.h>


LRESULT CALLBACK MainWinProc(HWND,UINT,WPARAM,LPARAM);
#define IDM_MYMENURESOURCE 3
#define IDM_DELETE 6
#define IDM_ADD 9
#define IDM_MOVE 10
#define IDM_EDITWINDOW 77
#define IDM_BASE 88
#define IDM_BUTADD 13


char const szWindowTitle[] = "������ ���������";

//����
void MyMenu(HWND hw){
    HMENU hmenu = CreateMenu();
    HMENU hMenuPopup = CreateMenu();
    AppendMenu(hMenuPopup,MF_STRING,IDM_ADD,"��������");
    AppendMenu(hMenuPopup,MF_STRING,IDM_MOVE,"��������");
    AppendMenu(hMenuPopup,MF_STRING,5,"�����������");
    AppendMenu(hMenuPopup,MF_STRING,IDM_DELETE,"�������");
    AppendMenu(hmenu, MF_POPUP,(UINT) hMenuPopup, "��������");
    SetMenu(hw,hmenu);
    SetMenu(hw,hMenuPopup);
}


HINSTANCE hInst;
int WINAPI WinMain(HINSTANCE hInst,HINSTANCE,LPSTR,int ss) 
{
   /* ������� � ������������ ����� �������� ���� */
   WNDCLASS wc;
   wc.style=CS_HREDRAW | CS_VREDRAW;
   wc.lpfnWndProc=MainWinProc;
   wc.cbClsExtra=wc.cbWndExtra=0;
   wc.hInstance=hInst;
   wc.hIcon=LoadIcon(NULL, IDI_APPLICATION);
   wc.hCursor=LoadCursor(NULL,IDC_ARROW);
   wc.hbrBackground=(HBRUSH(COLOR_WINDOW+9));
   wc.lpszMenuName="����";
   wc.lpszClassName="Stud";
   if (!RegisterClass(&wc)) 
                        return FALSE;  
   /* ������� ������� ���� � ���������� ��� */
   HWND hMainWnd=CreateWindow(
      "Stud",
      szWindowTitle,
      WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT,
      CW_USEDEFAULT,
      CW_USEDEFAULT,
      CW_USEDEFAULT,
      NULL,
      NULL,
      hInst,
      NULL                  
      );
   if (!hMainWnd) 
                return FALSE;
   ShowWindow(hMainWnd,ss);
   UpdateWindow(hMainWnd);
  
   MSG msg; /* ���� ��������� ������� */
   while (GetMessage(&msg,NULL,0,0))
    {
      TranslateMessage(&msg); 
      DispatchMessage(&msg); 
    } 
   return msg.wParam; 
}
static HWND hbut;
static HWND hMainWnd;
static HWND hstatic;
static HWND hBase;
static HWND hEdit;
static HWND hListBox;
HWND hwnd;
LRESULT CALLBACK MainWinProc(HWND hw,UINT msg,WPARAM wp,LPARAM lp) 
{
 switch (msg) 
 {

  case WM_CREATE:
  //������
  hListBox = CreateWindow("listbox", NULL,
         WS_CHILD | WS_VISIBLE | LBS_STANDARD |
         LBS_WANTKEYBOARDINPUT | LBS_NOTIFY,
         110, 10, 1000, 150,
         hw, (HMENU) 33, hInst, NULL);
 SendMessage(hListBox,LB_INSERTSTRING, 0,(LPARAM) "������ ������ ��������");
 SendMessage(hListBox,LB_INSERTSTRING, 1,(LPARAM) "��������� ����� ������������");


 hstatic = CreateWindow("static","����",
   WS_CHILD|WS_VISIBLE,
   330, 330, 300, 20,
   hw,NULL,hInst,NULL);

 hbut = CreateWindow("button","��������",
    WS_CHILD|WS_VISIBLE,
    150,170,100,20,
    hw,(HMENU)IDM_BUTADD,hInst,NULL); 


   hEdit = CreateWindow("edit","������� ��� ��������",
   WS_CHILD|WS_VISIBLE|ES_UPPERCASE|ES_LEFT|WS_TABSTOP|WS_BORDER,
   130, 230, 300, 20,
   hw,NULL,hInst,NULL);

  //����
  MyMenu(hw);
  // ������ 
  break;
  // case WM_SETFOCUS:
  //   {
  //     SetFocus(hEdit);
  //     return 0;
  //   }
  
  case WM_COMMAND:

  //????????????????????????????????????????????????? ������� ������ ????????????????????
  if((HIWORD(wp)==0) && (LOWORD(wp)==IDM_DELETE))
    {
      MessageBox(hw,"����������� �������� ��������� ������","MessageBox",MB_OK|MB_ICONWARNING|MB_OKCANCEL);
      int iIndexDelete = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
      SendMessage(hListBox, LB_DELETESTRING, iIndexDelete, 0);
      return 0;
    }
  // ???????????????????????????????????????????????? ������� ������ ??????????????????????


  //! ????????????????????????????????????????????????? �������� ������ ??????????????????

  

  //! ???????????????????????????????????????????????? �������� ������ ???????????????????



if ((HIWORD(wp)==0) && (LOWORD(wp)==IDM_BUTADD)){
        char buf[50];
        GetWindowText(hEdit,buf,50);
        SetWindowText(hstatic,buf);
        MessageBox(hw,buf,"�����",MB_OK);
        SendMessage(hListBox,LB_ADDSTRING, 0,(LPARAM) buf);
       return 0; 

    }

   return 0;


//   WM_DESTROY
  case WM_DESTROY:
   /* ������������ ������ ����, ��������� ����� ����������� */
   PostQuitMessage(0);
   return 0;
   
 }

 
 return DefWindowProc(hw,msg,wp,lp);
}