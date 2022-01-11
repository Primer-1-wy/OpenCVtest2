#include<quickjopencv.h>


void QuickDemo::colorSpace_Demo(Mat &image)
{
	Mat gray, hsv;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	cvtColor(image, gray, COLOR_BGR2GRAY);
	//ɫ����H�������Ͷȣ�S�������ȣ�V����
	imshow("HSV", hsv);
	imshow("GRAY", gray);

	imwrite("D:/hsv.png", hsv);
	imwrite("D:/gray.png", gray);

}
void QuickDemo::mat_creation_demo(Mat &image)
{
	Mat m1, m2;
	m1 = image.clone();
	image.copyTo(m2);
	//�������ַ������ǰ�ֵ��ֵ
	Mat m3 = Mat::ones(Size(8, 8), CV_8UC3);//8λUnsigned(U) char(C)  1:��ͨ

	m3 = Scalar(127, 127, 127);

	std::cout << "width:" << m3.cols << "height:" << m3.rows << "channels:" << m3.channels() << std::endl;
	std::cout << m3 << std::endl;
	/*   ���Ե�ɫ   ˵����=���г�ʼ���Ļ� ��ʵ���ǽ�ָ��ָ���ַ �ı�m3ʱҲ��ı�m4
	m3 = Scalar(0, 0, 255);
	Mat m4 = m3;
	m4 = Scalar(0, 255, 255);
	imshow("ͼ��", m3);
	*/

}

void QuickDemo::pixel_visit_demo(Mat &image)
{
	int w = image.cols;//��ȡͼ����
	int h = image.rows;//��ȡͼ��߶�
	int dims = image.channels();//��ȡͨ����
	/*
	ͨ�������±�������ص�ķ���
	*/
	//for (int row = 0; row < h; row++)
	//{
	//	for (int col = 0; col < w; col++)
	//	{
	//		if (dims == 1)//�Ҷ�ͼ��
	//		{
	//			int pv = image.at<uchar>(row, col);//��ͨ�� ����ֵ��uchar��
	//			image.at<uchar>(row, col) = 255 - pv;
	//		}
	//		if (dims == 3)//��ɫͼ��
	//		{
	//			Vec3b bgr=image.at<Vec3b>(row, col);//��������ֵŶ	���԰�bgr����ṹ��������
	//			image.at<Vec3b>(row, col)[0] = 255 - bgr[0];
	//			image.at<Vec3b>(row, col)[1] = 255 - bgr[1];
	//			image.at<Vec3b>(row, col)[2] = 255 - bgr[2];
	//		}
	//	}
	//}

	/*
	ͨ��ָ��������ص�ķ���			�ٶ���΢��һЩ
	*/
	for (int row = 0; row < h; row++)
	{
		uchar *current_row = image.ptr<uchar>(row);
		for (int col = 0; col < w; col++)
		{
			if (dims == 1)//�Ҷ�ͼ��
			{
				int pv = *current_row;//��ͨ�� ����ֵ��uchar��
				*current_row++ = 255 - pv;
			}
			if (dims == 3)//��ɫͼ��
			{
				*current_row++ = 255 - *current_row;//����������λ�ã���ͨ����
				*current_row++ = 255 - *current_row;
				*current_row++ = 255 - *current_row;
			}
		}
	}
	imshow("���ض�д��ʾ", image);
}
void QuickDemo::operators_demo(Mat &image)
{
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	m = Scalar(50, 50, 50);
	multiply(image, m, dst);//�˷� ǰ���������ǳ��� ���һ�����������




	//dst = image + Scalar(50, 50, 50);//ÿһ�����ص㶼��50
	//imshow("�ӷ�����", dst);
	//dst = image - Scalar(50, 50, 50);
	//imshow("��������",dst);
	//dst = image / Scalar(2, 2, 2);
	//imshow("��������",dst);

	//int w = image.cols;//��ȡͼ����
	//int h = image.rows;//��ȡͼ��߶�
	//int dims = image.channels();//��ȡͨ����

	//for (int row = 0; row < h; row++)
	//{
	//	for (int col = 0; col < w; col++)
	//	{
	//		Vec3b p1 = image.at<Vec3b>(row, col);//��������ֵŶ	���԰�bgr����ṹ��������
	//		Vec3b p2 = m.at<Vec3b>(row, col);
	//		dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(p1[0] + p2[0]);
	//		dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(p1[1] + p2[1]);
	//		dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(p1[2] + p2[2]);
	//	}
	//}


	//��ʵֱ��call OpenCV��API������
	add(image, m, dst);//�ӷ�
	//subtract(image, m, dst);//����
	//divide(image, m, dst);//����
	//multiply(image, m, dst);//�˷� ǰ���������ǳ��� ���һ�����������


	imshow("�ӷ�����", dst);

}


static void on_lightness(int poa, void* usrdata)//poa�������������ֵ
{
	Mat image = *((Mat*)usrdata);//����ǿ��ת��
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	addWeighted(image, 1.0, m, 0.0, poa, dst);
	imshow("������Աȶȵ���", dst);
}

static void on_contrast(int poa, void* usrdata)//poa�������������ֵ
{
	Mat image = *((Mat*)usrdata);//����ǿ��ת��
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	double contrast = poa / 100.0;
	add(image, m, dst);
	addWeighted(image, contrast, m, 0.0, 0, dst);//ֻ���Աȶ�
	imshow("������Աȶȵ���", dst);
}


void QuickDemo::tracking_bar_demo(Mat &image)
{
	namedWindow("������Աȶȵ���", WINDOW_AUTOSIZE);
	int max_value = 100;
	int lightness = 50;
	int contrast_value = 100;
	createTrackbar("Value Bar:", "������Աȶȵ���", &lightness, max_value, on_lightness, (void*)(&image));//�������һ������ �ڻص������ܵĵڶ������������õ��� Ҫ��������һ�� ���Ҵ���Ҳһ��
	createTrackbar("Contrast Bar:", "������Աȶȵ���", &contrast_value, 200, on_contrast, (void*)(&image));//�Աȶȵ�ֵ��С 0-5

	on_lightness(50, &image);//����


}

void QuickDemo::key_demo(Mat &image)
{
	Mat dst=Mat::zeros(image.size(),image.type());
	while (true)
	{
		char c = waitKey(100);//ͣ��100ms  waitKey���ص���һ��int�͵�ֵ
		if (c == 27)	break;//����27 �����㰴����Esc  ���㰴��Esc��ʱ����˳�ѭ��
		if (c == 49)
		{//#Key 1
			std::cout << "You enter key #1" << std::endl;//����1��ʱ���ӡYou enter key #1 ���ҽ�ͼ��ת��Ϊ�Ҷ�
			cvtColor(image, dst, COLOR_BGR2GRAY);
		}
		if (c == 50)
		{//#Key 2
			std::cout << "You enter key #2" << std::endl;
			cvtColor(image, dst, COLOR_BGR2HSV);

		}
		if (c == 51)
		{//#Key 3
			std::cout << "You enter key #3" << std::endl;
			dst = Scalar(5, 5, 5);
			add(image, dst, dst);
		}
		imshow("������Ӧ", dst);
	}
}

void QuickDemo::color_style_demo(Mat &image)
{
	int colormap[] = {
	COLORMAP_AUTUMN , //!< ![autumn](pics/colormaps/colorscale_autumn.jpg)
	COLORMAP_BONE , //!< ![bone](pics/colormaps/colorscale_bone.jpg)
	COLORMAP_JET , //!< ![jet](pics/colormaps/colorscale_jet.jpg)
	COLORMAP_WINTER , //!< ![winter](pics/colormaps/colorscale_winter.jpg)
	COLORMAP_RAINBOW , //!< ![rainbow](pics/colormaps/colorscale_rainbow.jpg)
	COLORMAP_OCEAN , //!< ![ocean](pics/colormaps/colorscale_ocean.jpg)
	COLORMAP_SUMMER , //!< ![summer](pics/colormaps/colorscale_summer.jpg)
	COLORMAP_SPRING , //!< ![spring](pics/colormaps/colorscale_spring.jpg)
	COLORMAP_COOL , //!< ![cool](pics/colormaps/colorscale_cool.jpg)
	COLORMAP_HSV , //!< ![HSV](pics/colormaps/colorscale_hsv.jpg)
	COLORMAP_PINK , //!< ![pink](pics/colormaps/colorscale_pink.jpg)
	COLORMAP_HOT , //!< ![hot](pics/colormaps/colorscale_hot.jpg)
	COLORMAP_PARULA , //!< ![parula](pics/colormaps/colorscale_parula.jpg)
	COLORMAP_MAGMA , //!< ![magma](pics/colormaps/colorscale_magma.jpg)
	COLORMAP_INFERNO, //!< ![inferno](pics/colormaps/colorscale_inferno.jpg)
	COLORMAP_PLASMA, //!< ![plasma](pics/colormaps/colorscale_plasma.jpg)
	COLORMAP_VIRIDIS, //!< ![viridis](pics/colormaps/colorscale_viridis.jpg)
	COLORMAP_CIVIDIS , //!< ![cividis](pics/colormaps/colorscale_cividis.jpg)
	COLORMAP_TWILIGHT , //!< ![twilight](pics/colormaps/colorscale_twilight.jpg)
	COLORMAP_TWILIGHT_SHIFTED  //!< ![twilight shifted](pics/colormaps/colorscale_twilight_shifted.jpg
	};
	Mat dst;
	int index = 0;
	while (true)
	{
		int c = waitKey(2000);//2s
		if (c == 27)	break;

		applyColorMap(image, dst, colormap[index % 19]);
		index++;
		imshow("��ɫ���", dst);
	}
}

void QuickDemo::bitwise_demo(Mat &image)
{
	Mat m1 = Mat::zeros(Size(256, 256), CV_8UC3);
	Mat m2 = Mat::zeros(Size(256, 256), CV_8UC3);
	rectangle(m1, Rect(100, 100, 80, 80), Scalar(255, 255, 0), 2, LINE_8, 0);//��������������-1�������������0��ʾ���� С��0��ʾ���	
	rectangle(m2, Rect(150, 150, 80, 80), Scalar(0, 255, 255), -1, LINE_8, 0);//�����ǵ�һ�����ƣ���ߣ� �ڶ������
	imshow("m1", m1);//scalar  ����������Blue Green Red
	imshow("m2", m2);

	Mat dst;
	//bitwise_and(m1, m2, dst);//��m1��m2��Scalar�Ĳ������������	�ú�λ�ý��������
	//imshow("�����", dst);
	//bitwise_or(m1, m2, dst);
	//imshow("�����", dst);
	bitwise_xor(m1, m2, dst);
	imshow("������", dst);
	//bitwise_not(image,dst);//ȡ������	dst=~image;Ҳ����Ŷ
	//imshow("�ǲ���", dst);
}

void QuickDemo::channels_demo(Mat &image)
{
	std::vector<Mat> mv;
	split(image, mv);
	imshow("��ɫ", mv[0]);
	imshow("��ɫ", mv[1]);
	imshow("��ɫ", mv[2]);
	//Ϊ�˱�ʾ��ɫ ��Ҫ����������ͨ��������ֵ��Ϊ0	   ͬ��������ɫ�������
	Mat dst;
	mv[1] = 0;
	mv[2] = 0;
	merge(mv, dst);
	imshow("��ɫ", dst);

	//int from_to[] = { 0,2,1,1,2,0 };//0->2 1->1 2->0
	//mixChannels(&image,1, &dst,from_to,3);
	//imshow("ͨ�����", dst);

}