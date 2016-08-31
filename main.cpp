#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace cv;
using namespace std;
using namespace std::chrono;

void minmax(Mat inputimage){
	 static Vec3b min(255,255,255);
	 static Vec3b max(0,0,0);
	 static float maxsub01 = 0;
	 static float maxsub02 = 0;
	 static float maxsub12 = 0;

	 static float minsub01 = 999999;
	 static float minsub02 = 999999;
	 static float minsub12 = 999999;

	 static float maxdiv01 = 0;
	 static float maxdiv02 = 0;
	 static float maxdiv12 = 0;

	 static float mindiv01 = 999999;
	 static float mindiv02 = 999999;
	 static float mindiv12 = 999999;

	 float temp;

	for (int y = 0; y < inputimage.rows; y++) {
		for (int x = 0; x < inputimage.cols; x++) {
			//cout << "???" << inputimage.at<Vec3b>(y, x) << "!!!" << endl;
			Vec3b pixel = inputimage.at<Vec3b>(y, x);
			if (pixel[0] > max[0]){
				max[0] = pixel[0];
			}
			if (pixel[1] > max[1]){
				max[1] = pixel[1];
			}
			if (pixel[2] > max[2]){
				max[2] = pixel[2];
			}
			if (pixel[0] < min[0]){
				min[0] = pixel[0];
			}
			if (pixel[1] < min[1]){
				min[1] = pixel[1];
			}
			if (pixel[2] < min[2]){
				min[2] = pixel[2];
			}



			//sub
			if (pixel[0] < pixel[1]){
				temp = pixel[1] - pixel[0];
				if (temp > maxsub01){
					maxsub01 = temp;
				}
				else if (temp < minsub01)
				{
					minsub01 = temp;
				}
			}
			else{
				temp = pixel[0] - pixel[1];
				if (temp > maxsub01){
					maxsub01 = temp;
				}
				else if (temp < minsub01)
				{
					minsub01 = temp;
				}
			}


			if (pixel[0] < pixel[2]){
				temp = pixel[2] - pixel[0];
				if (temp > maxsub02){
					maxsub02 = temp;
				}
				else if (temp < minsub02)
				{
					minsub02 = temp;
				}

			}
			else{
				temp = pixel[0] - pixel[2];
				if (temp > maxsub02){
					maxsub02 = temp;
				}
				else if (temp < minsub02)
				{
					minsub02 = temp;
				}
			}


			if (pixel[2] < pixel[1]){
				temp = pixel[1] - pixel[2];
				if (temp > maxsub12){
					maxsub12 = temp;
				}
				else if (temp < minsub12)
				{
					minsub12 = temp;
				}
			}
			else{
				temp = pixel[2] - pixel[1];
				if (temp > maxsub12){
					maxsub12 = temp;
				}
				else if (temp < minsub12)
				{
					minsub12 = temp;
				}
			}


		
			//divisons
			if (pixel[0] && pixel[1] && pixel[2]){
				if (pixel[0] < pixel[1]){
					temp = (float) pixel[1] / pixel[0];
					if (temp > maxdiv01){
						maxdiv01 = temp;
					}
					else if (temp < mindiv01)
					{
						mindiv01 = temp;
					}
				}
				else{
					temp = (float) pixel[0] / pixel[1];
					if (temp > maxdiv01){
						maxdiv01 = temp;
					}
					else if (temp < mindiv01)
					{
						mindiv01 = temp;
					}
				}



				if (pixel[0] < pixel[2]){
					temp = (float) pixel[2] / pixel[0];
					if (temp > maxdiv02){
						maxdiv02 = temp;
					}
					else if (temp < mindiv02)
					{
						mindiv02 = temp;
					}
				}
				else{
					temp = (float) pixel[0] / pixel[2];
					if (temp > maxdiv02){
						maxdiv02 = temp;
					}
					else if (temp < mindiv02)
					{
						mindiv02 = temp;
					}
				}


				if (pixel[2] < pixel[1]){
					temp = (float) pixel[1] / pixel[2];
					if (temp > maxdiv12){
						maxdiv12 = temp;
					}
					else if (temp < mindiv12)
					{
						mindiv12 = temp;
					}
				}
				else{
					temp = (float) pixel[2] / pixel[1];
					if (temp > maxdiv12){
						maxdiv12 = temp;
					}
					else if (temp < mindiv12)
					{
						mindiv12 = temp;
					}
				}
			}	
		}
	}
	cout << " MIN: " << min << " MAX: " << max << endl;
	cout << " minsub01: " << minsub01 << " maxsub01: " << maxsub01 << " minsub02: " << minsub02 << " maxsub02: " << maxsub02 << " minsub12: " << minsub12 << " maxsub12: " << maxsub12 << endl;
	cout << " mindiv01: " << mindiv01 << " maxdiv01: " << maxdiv01 << " mindiv02: " << mindiv02 << " maxdiv02: " << maxdiv02 << " mindiv12: " << mindiv12 << " maxdiv12: " << maxdiv12 << endl;
}

int main() {
	Mat inputimage;
	const char fileFormatString[] = "C:/Users/eszter.toth/Desktop/captures/road/%02d.JPG";
	char fileName[1024];
	for (int frameNum = 1;; frameNum++) {
		sprintf(fileName, fileFormatString, frameNum);
		inputimage = imread(fileName, CV_LOAD_IMAGE_COLOR);
		if (!inputimage.data)
		{
			cout << "Could not open or find the image." << std::endl;
			return -1;
		}

			cout << "RGB: " << endl;
		minmax(inputimage);
	/*cvtColor(inputimage, inputimage,CV_RGB2HSV);
		cout << "HSV: " << endl;
		minmax(inputimage);*/ 
		waitKey(1); // just to force image refresh during video saving
	}
	
		return 0;
}
