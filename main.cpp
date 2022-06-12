#include <iostream>
#include <algorithm>
#include "autogui.h"
#include <opencv2/highgui.hpp>
int main(int, char**) {
    autogui ag;
    std::cout<<"ScreenSize:"<<ag.ScreenSize.x<<","<<ag.ScreenSize.y<<std::endl;
    //ag.click(3169,682);
    auto hwnd=ag.FindWindowByName(NULL,NULL);
    std::cout <<"Search Have:"<<hwnd.size()<<std::endl;
    std::for_each(hwnd.begin(),hwnd.end(),[](HWND i){std::cout<<i<<std::endl;});
    //截取当前桌面
    auto i=ag.screen.capture();
    auto img=cv::Mat(ag.ScreenSize.y,ag.ScreenSize.x,CV_8UC4,i);
    cv::imshow("",img);
    cv::waitKey();
    delete i;
    //取得窗口位置
    auto rect=ag.GetRect(hwnd);
    std::for_each(rect.begin(),rect.end(),[](RECT i){printf("Left Top:(%d,%d)|Right Button:(%d,%d)\n",i.left,i.top,i.right,i.bottom);});
    ag.clipboard.setvalue("123\0");
}
