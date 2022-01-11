#pragma once
#include<opencv2/opencv.hpp>

using namespace cv;

class QuickDemo {
public:
	void colorSpace_Demo(Mat &image);//调整图像的色彩并保存
	void mat_creation_demo(Mat &image);//创建一个图像
	void pixel_visit_demo(Mat &image);//读写像素点
	void operators_demo(Mat &image);//操作像素点
	void tracking_bar_demo(Mat &image);//根据拉动滑动条来控制亮度
	void key_demo(Mat &image);//按键控制
	void color_style_demo(Mat &image);//OpenCV自带颜色操作
	void bitwise_demo(Mat &image);//图像的填充和绘制以及图像的位操作
	void channels_demo(Mat &image);//通道的分离与合并
};