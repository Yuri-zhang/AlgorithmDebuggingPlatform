#include "foo.h"
#include <iostream>
#include <opencv.hpp>

using namespace std;
int main(int argc, char** argv) {
    cv::Mat img=cv::imread("D:\\AlgorithmDebuggingPlatform\\1.bmp");    
    cout<<"宽度:"<<img.rows<<endl;
    cout << "add(1, 2) = " << add(1, 2) << endl;
    cout<<"失败"<<endl;
    return 0;
}
