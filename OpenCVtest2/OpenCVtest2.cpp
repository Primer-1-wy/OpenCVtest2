#include<opencv2/opencv.hpp>
#include<iostream>
#include<quickjopencv.h>


using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("C:/Users/LENOVO/Desktop/work/picture/2.png");//加载为灰度图像
	if (src.empty())//没找到图像
	{
		printf("could not find picture!\n");
		return -1;
	}
	//namedWindow("输入窗口", WINDOW_FREERATIO);//窗口名字：输入窗口。图像大小：自由比例
	imshow("输入窗口", src);//输入窗口名字：输入窗口

	QuickDemo qd;
	//qd.channels_demo(src);//通道的分离与合并
	//	qd.bitwise_demo(src);//图像的填充和绘制以及图像的位操作
	//	qd.color_style_demo(src);//OpenCV自带颜色操作
	//	qd.key_demo(src);//按键控制
	//	qd.tracking_bar_demo(src);//根据拉动滑动条来控制亮度
	//	qd.operators_demo(src);//操作像素点
	//	qd.pixel_visit_demo(src);//读写像素点
	//	qd.colorSpace_Demo(src);//调整图像的色彩并保存
	//	qd.mat_creation_demo(src);//创建一个图像

	waitKey(0);
	destroyAllWindows();
	return 0;
}

