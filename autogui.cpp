#include "autogui.h"
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