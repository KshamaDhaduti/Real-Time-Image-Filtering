// Project 1: Task 1 to Read and Display image imgDisaply.cpp
// Created by Kshama Dhaduti on 20th Jan 2023
//
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// Driver code
int main(int argc, char** argv)
{
	// Read the image file as
	Mat image = imread("C:/Users/ksham/OneDrive/Desktop/the-starry-night.jpg",IMREAD_GRAYSCALE);

	// If image is not located
	if (image.empty()) {
		cout << "Image File "
			<< "Not Found" << endl;

		// Wait for any key press
		cin.get();
		return -1;
	}

	// Show Image inside a window 
	imshow("Window Name: Starry Nights", image);

	// See if there is a waiting keystroke
	int key = waitKey(0);
	if(key == 'q') {
		
		imwrite("Image.jepeg", image);
	}
	return 0;
}
