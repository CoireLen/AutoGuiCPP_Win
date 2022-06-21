#include "autogui.h"
#include <string.h>
autogui::autogui(/* args */)
{
    RandValue10_30=std::uniform_int_distribution<unsigned> (10,30);
    DEVMODE dm;
    dm.dmSize = sizeof(dm);
    dm.dmDriverExtra = 0;
    MONITORINFOEX miex;
    HWND hWnd = GetDesktopWindow();
    HMONITOR hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
    miex.cbSize = sizeof(miex);
    GetMonitorInfo(hMonitor, &miex);
    EnumDisplaySettings(miex.szDevice, ENUM_CURRENT_SETTINGS, &dm);
    int cx= dm.dmPelsWidth;
    int cy = dm.dmPelsHeight;
    ScreenSize={cx,cy};
    Zoom={65535.0/cx,65535.0/cy};
}

autogui::~autogui()
{
}
void autogui::click(int x,int y,float time){
    if (time<=0){
        MouseMove(x,y);
        MouseLeftButtonClick();
    }
}
void  autogui::MouseMove(int x,int y){
    mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MOVE,x*Zoom.x,y*Zoom.y,0,NULL);
}
void autogui::MouseLeftButtonClick(){
    //Sleep((DWORD)RandValue10_30(RandEngine));
    mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,NULL);
    Sleep((DWORD)RandValue10_30(RandEngine));//点击释放间隔
    mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,NULL);
}
POINT autogui::MouseLocation(){
    POINT p;
    GetCursorPos(&p);
    return p;
}
std::vector<HWND> autogui::FindWindowByName(char *classname,char * windowname){
    std::vector<HWND> vHWND;
    HWND hwnd=FindWindowA(classname,windowname);
    if (hwnd==NULL){
        return vHWND;
    }
    vHWND.push_back(hwnd);
    while((hwnd=FindWindowExA(NULL,hwnd,classname,windowname))!=NULL){
        vHWND.push_back(hwnd);
    }
    return vHWND;
}
std::vector<HWND> autogui::FindChildWindow(HWND hwndparent,char *classname,char * windowname){
    std::vector<HWND> vhwnd;
    HWND hwnd=NULL;
    while((hwnd=FindWindowExA(hwndparent,hwnd,classname,windowname))!=NULL){
        vhwnd.push_back(hwnd);
    }
    return vhwnd;
}
RECT autogui::GetRect(HWND hwnd){
    RECT rt={0,0,0,0};
    if (GetWindowRect(hwnd,&rt)==0)
    {
        printf("GetWindowRect Fail\n");
    }
    return rt;
}
std::vector<RECT> autogui::GetRect(std::vector<HWND> hwnd){
    std::vector<RECT> vRECT;
    for (HWND i:hwnd){
        vRECT.push_back(GetRect(i));
    }
    return vRECT;
}


clipboard::clipboard(/* args */)
{
}

clipboard::~clipboard()
{
}
void clipboard::setvalue(char * str){
    if (OpenClipboard(GetActiveWindow())){
        EmptyClipboard();
        int b = strnlen(str,1000);
        int size =sizeof(char)* (b+1);
        LPWSTR pData = (LPWSTR)GlobalAlloc(GMEM_MOVEABLE,size);
        if (pData ==NULL){
            printf("clipboard alloc mem fail");
            return;
        }
        auto hData=GlobalLock(pData);
        if (hData==NULL){
            printf("clipboard lock mem fail");
            return;
        }
        if (size < 1000)
            memcpy(hData,(void *)str, size);
        GlobalUnlock(hData);
        if (SetClipboardData(CF_TEXT,hData)==NULL){
            CloseClipboard();
            printf("set clipboard data fail");
            return;
        }
        CloseClipboard();
    }
    else{
        printf("opencliboard fail");
    }
}
void clipboard::setvalue(std::wstring str){
    if (OpenClipboard(GetActiveWindow())){
        EmptyClipboard();
        int b = str.length();
        int size =sizeof(str[0])* (b+1);
        LPWSTR pData = (LPWSTR)GlobalAlloc(GMEM_MOVEABLE,size);
        if (pData ==NULL){
            printf("clipboard alloc mem fail");
            return;
        }
        auto hData=GlobalLock(pData);
        if (hData==NULL){
            printf("clipboard lock mem fail");
            return;
        }
        if (size < 1000)
            memcpy(hData,(void *)str.data(), size);
        GlobalUnlock(hData);
        if (SetClipboardData(CF_UNICODETEXT,hData)==NULL){
            CloseClipboard();
            printf("set clipboard data fail");
            return;
        }
        CloseClipboard();
    }
    else{
        printf("opencliboard fail");
    }
}
void clipboard::setimg(u_char * img,u_int height,u_int weidth){
    if (OpenClipboard(GetActiveWindow())){
        EmptyClipboard();
        u_int size =height*weidth*4;
        LPWSTR pData = (LPWSTR)GlobalAlloc(GMEM_MOVEABLE,size);
        if (pData ==NULL){
            printf("clipboard alloc mem fail");
            return;
        }
        auto hData=GlobalLock(pData);
        if (hData==NULL){
            printf("clipboard lock mem fail");
            return;
        }
        if (size < 1000)
            memcpy(hData,(void *)img, size);
        GlobalUnlock(hData);
        if (SetClipboardData(CF_BITMAP,hData)==NULL){
            CloseClipboard();
            printf("set clipboard data fail");
            return;
        }
        CloseClipboard();
    }
    else{
        printf("opencliboard fail");
    }
}