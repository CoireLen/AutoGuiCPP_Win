#include <windows.h>
#include <random>
#include <vector>
struct ScreenZoom
{
    double x;
    double y;
    /* data */
};

class autogui
{
private:
    std::default_random_engine RandEngine;
    std::uniform_int_distribution<unsigned> RandValue10_30;
    ScreenZoom Zoom={0,0};
    void MouseMove(int x,int y); //将鼠标移动到(x,y)
    void MouseLeftButtonClick(); //点击鼠标左键
    POINT MouseLocation(); //取得鼠标位置
    
    /* data */
public:
    std::vector<HWND> FindWindowByName(char * classname,char * windowname); //取得所有匹配的窗口句柄
    POINT ScreenSize={0,0};
    void click(int x,int y,float time=0); //移动并点击到x,y; 移动到x,y所用的时间(秒)
    autogui(/* args */);
    ~autogui();
};

