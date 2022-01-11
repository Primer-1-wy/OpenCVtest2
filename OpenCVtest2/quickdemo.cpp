#include<quickjopencv.h>


void QuickDemo::colorSpace_Demo(Mat &image)
{
	Mat gray, hsv;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	cvtColor(image, gray, COLOR_BGR2GRAY);
	//色调（H），饱和度（S），明度（V）。
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
	//上面俩种方法都是把值赋值
	Mat m3 = Mat::ones(Size(8, 8), CV_8UC3);//8位Unsigned(U) char(C)  1:单通

	m3 = Scalar(127, 127, 127);

	std::cout << "width:" << m3.cols << "height:" << m3.rows << "channels:" << m3.channels() << std::endl;
	std::cout << m3 << std::endl;
	/*   测试底色   说明用=进行初始化的话 其实就是将指针指向地址 改变m3时也会改变m4
	m3 = Scalar(0, 0, 255);
	Mat m4 = m3;
	m4 = Scalar(0, 255, 255);
	imshow("图像", m3);
	*/

}

void QuickDemo::pixel_visit_demo(Mat &image)
{
	int w = image.cols;//获取图像宽度
	int h = image.rows;//获取图像高度
	int dims = image.channels();//获取通道数
	/*
	通过数组下标完成像素点的访问
	*/
	//for (int row = 0; row < h; row++)
	//{
	//	for (int col = 0; col < w; col++)
	//	{
	//		if (dims == 1)//灰度图像
	//		{
	//			int pv = image.at<uchar>(row, col);//单通道 像素值是uchar型
	//			image.at<uchar>(row, col) = 255 - pv;
	//		}
	//		if (dims == 3)//彩色图像
	//		{
	//			Vec3b bgr=image.at<Vec3b>(row, col);//返回三个值哦	可以把bgr这个结构看成数组
	//			image.at<Vec3b>(row, col)[0] = 255 - bgr[0];
	//			image.at<Vec3b>(row, col)[1] = 255 - bgr[1];
	//			image.at<Vec3b>(row, col)[2] = 255 - bgr[2];
	//		}
	//	}
	//}

	/*
	通过指针完成像素点的访问			速度稍微快一些
	*/
	for (int row = 0; row < h; row++)
	{
		uchar *current_row = image.ptr<uchar>(row);
		for (int col = 0; col < w; col++)
		{
			if (dims == 1)//灰度图像
			{
				int pv = *current_row;//单通道 像素值是uchar型
				*current_row++ = 255 - pv;
			}
			if (dims == 3)//彩色图像
			{
				*current_row++ = 255 - *current_row;//往后走三个位置（三通道）
				*current_row++ = 255 - *current_row;
				*current_row++ = 255 - *current_row;
			}
		}
	}
	imshow("像素读写演示", image);
}
void QuickDemo::operators_demo(Mat &image)
{
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	m = Scalar(50, 50, 50);
	multiply(image, m, dst);//乘法 前俩个参数是乘数 最后一个参数是输出




	//dst = image + Scalar(50, 50, 50);//每一个像素点都加50
	//imshow("加法操作", dst);
	//dst = image - Scalar(50, 50, 50);
	//imshow("减法操作",dst);
	//dst = image / Scalar(2, 2, 2);
	//imshow("除法操作",dst);

	//int w = image.cols;//获取图像宽度
	//int h = image.rows;//获取图像高度
	//int dims = image.channels();//获取通道数

	//for (int row = 0; row < h; row++)
	//{
	//	for (int col = 0; col < w; col++)
	//	{
	//		Vec3b p1 = image.at<Vec3b>(row, col);//返回三个值哦	可以把bgr这个结构看成数组
	//		Vec3b p2 = m.at<Vec3b>(row, col);
	//		dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(p1[0] + p2[0]);
	//		dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(p1[1] + p2[1]);
	//		dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(p1[2] + p2[2]);
	//	}
	//}


	//其实直接call OpenCV的API就行了
	add(image, m, dst);//加法
	//subtract(image, m, dst);//减法
	//divide(image, m, dst);//除法
	//multiply(image, m, dst);//乘法 前俩个参数是乘数 最后一个参数是输出


	imshow("加法操作", dst);

}


static void on_lightness(int poa, void* usrdata)//poa是你拉动滑块的值
{
	Mat image = *((Mat*)usrdata);//必须强制转化
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	addWeighted(image, 1.0, m, 0.0, poa, dst);
	imshow("亮度与对比度调整", dst);
}

static void on_contrast(int poa, void* usrdata)//poa是你拉动滑块的值
{
	Mat image = *((Mat*)usrdata);//必须强制转化
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	double contrast = poa / 100.0;
	add(image, m, dst);
	addWeighted(image, contrast, m, 0.0, 0, dst);//只调对比度
	imshow("亮度与对比度调整", dst);
}


void QuickDemo::tracking_bar_demo(Mat &image)
{
	namedWindow("亮度与对比度调整", WINDOW_AUTOSIZE);
	int max_value = 100;
	int lightness = 50;
	int contrast_value = 100;
	createTrackbar("Value Bar:", "亮度与对比度调整", &lightness, max_value, on_lightness, (void*)(&image));//关于最后一个参数 在回调函数总的第二个参数将会用到它 要保持类型一样 并且传参也一样
	createTrackbar("Contrast Bar:", "亮度与对比度调整", &contrast_value, 200, on_contrast, (void*)(&image));//对比度的值较小 0-5

	on_lightness(50, &image);//多余


}

void QuickDemo::key_demo(Mat &image)
{
	Mat dst=Mat::zeros(image.size(),image.type());
	while (true)
	{
		char c = waitKey(100);//停顿100ms  waitKey返回的是一个int型的值
		if (c == 27)	break;//返回27 就是你按下了Esc  当你按下Esc的时候就退出循环
		if (c == 49)
		{//#Key 1
			std::cout << "You enter key #1" << std::endl;//按下1的时候打印You enter key #1 并且将图像转换为灰度
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
		imshow("键盘响应", dst);
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
		imshow("颜色风格", dst);
	}
}

void QuickDemo::bitwise_demo(Mat &image)
{
	Mat m1 = Mat::zeros(Size(256, 256), CV_8UC3);
	Mat m2 = Mat::zeros(Size(256, 256), CV_8UC3);
	rectangle(m1, Rect(100, 100, 80, 80), Scalar(255, 255, 0), 2, LINE_8, 0);//倒数第三个参数-1：这个参数大于0表示绘制 小于0表示填充	
	rectangle(m2, Rect(150, 150, 80, 80), Scalar(0, 255, 255), -1, LINE_8, 0);//现在是第一个绘制（描边） 第二个填充
	imshow("m1", m1);//scalar  三个参数：Blue Green Red
	imshow("m2", m2);

	Mat dst;
	//bitwise_and(m1, m2, dst);//对m1和m2的Scalar的参数进行与操作	让后位置进行与操作
	//imshow("与操作", dst);
	//bitwise_or(m1, m2, dst);
	//imshow("或操作", dst);
	bitwise_xor(m1, m2, dst);
	imshow("异或操作", dst);
	//bitwise_not(image,dst);//取反操作	dst=~image;也可以哦
	//imshow("非操作", dst);
}

void QuickDemo::channels_demo(Mat &image)
{
	std::vector<Mat> mv;
	split(image, mv);
	imshow("蓝色", mv[0]);
	imshow("绿色", mv[1]);
	imshow("红色", mv[2]);
	//为了表示蓝色 需要把其他俩个通道的像素值改为0	   同理其他颜色亦是如此
	Mat dst;
	mv[1] = 0;
	mv[2] = 0;
	merge(mv, dst);
	imshow("蓝色", dst);

	//int from_to[] = { 0,2,1,1,2,0 };//0->2 1->1 2->0
	//mixChannels(&image,1, &dst,from_to,3);
	//imshow("通道混合", dst);

}