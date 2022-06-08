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
    auto i=ag.screen.capture();
    auto img=cv::Mat(ag.ScreenSize.y,ag.ScreenSize.x,CV_8UC4,i);
    cv::imshow("",img);
    cv::waitKey();
    delete i;
   // cv::imdecode()
}
