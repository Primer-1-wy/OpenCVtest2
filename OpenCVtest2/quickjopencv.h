#pragma once
#include<opencv2/opencv.hpp>

using namespace cv;

class QuickDemo {
public:
	void colorSpace_Demo(Mat &image);//����ͼ���ɫ�ʲ�����
	void mat_creation_demo(Mat &image);//����һ��ͼ��
	void pixel_visit_demo(Mat &image);//��д���ص�
	void operators_demo(Mat &image);//�������ص�
	void tracking_bar_demo(Mat &image);//������������������������
	void key_demo(Mat &image);//��������
	void color_style_demo(Mat &image);//OpenCV�Դ���ɫ����
	void bitwise_demo(Mat &image);//ͼ������ͻ����Լ�ͼ���λ����
	void channels_demo(Mat &image);//ͨ���ķ�����ϲ�
};