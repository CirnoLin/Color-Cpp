#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	VideoCapture cap(0); //capture the video from web cam

	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the web cam" << endl;
		return -1;
	}

	namedWindow("control", 1);
	int ctrl = 0;
	createTrackbar("ctrl", "control", &ctrl, 7);

	while (true)
	{
		Mat imgOriginal;

		bool bSuccess = cap.read(imgOriginal); // read a new frame from video
		if (!bSuccess) //if not success, break loop
		{
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}

		// imgOriginal = imread("4.jpg");

		Mat imgHSV, imgBGR;
		Mat imgThresholded;

		if (0)
		{
			vector<Mat> hsvSplit;   //�����������������HSV����ͨ������
			cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
			split(imgHSV, hsvSplit);			//����ԭͼ���HSV��ͨ��
			equalizeHist(hsvSplit[2], hsvSplit[2]);    //��HSV������ͨ������ֱ��ͼ����
			merge(hsvSplit, imgHSV);				   //�ϲ�����ͨ��
			cvtColor(imgHSV, imgBGR, COLOR_HSV2BGR);    //��HSV�ռ�ת����RGB�ռ䣬Ϊ����������ɫʶ����׼��
		}
		else
		{
			imgBGR = imgOriginal.clone();
		}



		switch (ctrl)
		{
		case 0:
		{
			inRange(imgBGR, Scalar(128, 0, 0), Scalar(255, 127, 127), imgThresholded); //��ɫ
			break;
		}
		case 1:
		{
			inRange(imgBGR, Scalar(128, 128, 128), Scalar(255, 255, 255), imgThresholded); //��ɫ
			break;
		}
		case 2:
		{
			inRange(imgBGR, Scalar(128, 128, 0), Scalar(255, 255, 127), imgThresholded); //��ɫ
			break;
		}
		case 3:
		{
			inRange(imgBGR, Scalar(128, 0, 128), Scalar(255, 127, 255), imgThresholded); //��ɫ
			break;
		}
		case 4:
		{
			inRange(imgBGR, Scalar(0, 128, 128), Scalar(127, 255, 255), imgThresholded); //��ɫ
			break;
		}
		case 5:
		{
			inRange(imgBGR, Scalar(0, 128, 0), Scalar(127, 255, 127), imgThresholded); //��ɫ
			break;
		}
		case 6:
		{
			inRange(imgBGR, Scalar(0, 0, 128), Scalar(127, 127, 255), imgThresholded); //��ɫ
			break;
		}
		case 7:
		{
			inRange(imgBGR, Scalar(0, 0, 0), Scalar(127, 127, 127), imgThresholded); //��ɫ
			break;
		}
		}

		imshow("��̬ѧȥ����ǰ", imgThresholded);

		Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
		morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);
		morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);

		imshow("Thresholded Image", imgThresholded); //show the thresholded image
		imshow("ֱ��ͼ�����Ժ�", imgBGR);
		imshow("Original", imgOriginal); //show the original image

		char key = (char)waitKey(300);
		if (key == 27)
			break;
	}

	return 0;

}
