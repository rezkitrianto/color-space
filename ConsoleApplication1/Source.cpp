#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<math.h>
#include<iostream>
using namespace std;
using namespace cv;
int main(void)
{
	cv::Mat rawImage, imageHSV, imageHSV_splitted[3];
	rawImage = imread("lena.jpg");

	cvtColor(rawImage, imageHSV, CV_BGR2imageHSV);
	cv::split(imageHSV, imageHSV_splitted);

	cv::imshow("imageHSV(H)", imageHSV_splitted[0]);
	cv::imshow("imageHSV(S)", imageHSV_splitted[1]);
	cv::imshow("imageHSV(V)", imageHSV_splitted[2]);

	cv::Mat temp_log = imageHSV_splitted[0].clone();
	cv::Mat temp_inv = imageHSV_splitted[1].clone();

	string stringimageHSV[3] = { "H", "S", "V" };

	for (int z = 0; z<3; z++){
		Mat logx = imageHSV_splitted[z].clone();
		Mat inv_logx = imageHSV_splitted[z].clone();

		temp_log.convertTo(temp_log, CV_32FC1);
		temp_inv.convertTo(temp_inv, CV_32FC1);

		for (int i = 0; i<imageHSV_splitted[z].rows; i++)
		{
			for (int j = 0; j<imageHSV_splitted[z].cols; j++)
			{
				float d_logx = 32 * (log(logx.at<uchar>(j, i) + 1 * 1.0) / log(2.0));
				float d_inv_logx = pow(2.0, (inv_logx.at<uchar>(j, i)*1.0 / 32)) - 1;
				temp_log.at<float>(j, i) = d_logx;
				temp_inv.at<float>(j, i) = d_inv_logx;
			}
		}

		temp_log.convertTo(temp_log, CV_8UC1);
		temp_inv.convertTo(temp_inv, CV_8UC1);


		imshow("Log (" + stringimageHSV[z] + ")", temp_log);
		imshow("Inverse Log (" + stringimageHSV[z] + ")", temp_inv);



	}
	waitKey(0);
	return 0;

}

/*
#include <opencv2\core\core.hpp>
#include <highgui.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int main() {
Mat rawImage, rawImageimageHSV, rawImageimageHSVSplitted[3], rawImageimageHSVSplittedLog[3], rawImageimageHSVSplittedInvLog[3];
= imread("lena.jpg");
cv::cvtColor(rawImage, rawImageimageHSV, CV_BGR2imageHSV);
cv::split(rawImageimageHSV, rawImageimageHSVSplitted);

imshow("H", rawImageimageHSVSplitted[0]);
imshow("S", rawImageimageHSVSplitted[1]);
imshow("V", rawImageimageHSVSplitted[2]);

imwrite("H.jpg", rawImageimageHSVSplitted[0]);
imwrite("S.jpg", rawImageimageHSVSplitted[1]);
imwrite("V.jpg", rawImageimageHSVSplitted[2]);


//for (int k = 0; k < 3; k++){
rawImageimageHSVSplittedLog[0] = rawImageimageHSVSplitted[0];
rawImageimageHSVSplittedInvLog[0] = rawImageimageHSVSplitted[0];

for (int row = 0; row < rawImageimageHSV.rows; row++){
for (int col = 0; col < rawImageimageHSV.cols; col++){
double x = rawImageimageHSVSplitted[0].at<double>(row, col);
rawImageimageHSVSplittedLog[0].at<double>(row, col) = 32 * (log(x + 1) / log(2));
//rawImageimageHSVSplittedInvLog[0].at<double>(row, col) = pow(2, x / 32) - 1;
double xLog = rawImageimageHSVSplittedLog[0].at<double>(row, col);
rawImageimageHSVSplittedInvLog[0].at<double>(row, col) = pow(2, xLog / 32) - 1;
}

}

imshow(("LOG_"+(0+1)), rawImageimageHSVSplittedLog[0]);
imshow(("INV_LOG_" +(0+1)), rawImageimageHSVSplittedInvLog[0]);

//}

imwrite("LOG_H.jpg", rawImageimageHSVSplittedLog[0]);
//imwrite("LOG_S.jpg", rawImageimageHSVSplittedLog[1]);
//imwrite("LOG_V.jpg", rawImageimageHSVSplittedLog[2]);

imwrite("INV_LOG_H.jpg", rawImageimageHSVSplittedInvLog[0]);
//imwrite("INV_LOG_S.jpg", rawImageimageHSVSplittedInvLog[1]);
//imwrite("INV_LOG_V.jpg", rawImageimageHSVSplittedInvLog[2]);


waitKey(0);
return 0;
}
*/