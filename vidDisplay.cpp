//Project 1: vidDisplay.cpp
//
//Created by Kshama Dhaduti on 22nd January 2023
//
//
#include <stdio.h>
#include "filter.hpp"
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int, char**) {

    //Video capture 
    VideoCapture* capdev;

    //Open the video device
    capdev = new VideoCapture(0);
    if (!capdev->isOpened()) {
        printf("Unable to open video device\n");
        return(-1);
    }

    // get some properties of the image
    //Size refS( (int) capdev->get(cv::CAP_PROP_FRAME_WIDTH ),
     //              (int) capdev->get(cv::CAP_PROP_FRAME_HEIGHT));
    int frame_width = capdev->get(cv::CAP_PROP_FRAME_WIDTH);
    int frame_height = capdev->get(cv::CAP_PROP_FRAME_HEIGHT);

    VideoWriter video("C:/Users/ksham/OneDrive/Desktop/PRCV/screenshots/output.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, Size(frame_width, frame_height));


    //Variables used
    Mat frame, filter;
    Mat3s sob_x, sob_y, mag;
    int count = 1;
    int flag = 0;
    int levels = 1;
    int threshold = 255;
    string str = "";
    //---------------------------------------------------------------

   //Video display
    for (;;) {
        //get a new frame from the camera in the form of a stream 
        *capdev >> frame; 
        if (frame.empty()) {
            printf("frame is empty\n");
            continue; //replaced the break to continue, as it lead to unexpected exiting the executions
        }

        //Test-to check if code was going past this point 
        std::cout << frame.cols;

        frame.copyTo(filter);

        //Filters executed 

        if (flag == 1) {
            //Grey_scale
            cvtColor(frame, filter, COLOR_RGB2GRAY);
        }
        else if (flag == 2) {
            //Alternate_Grey_scale
            alt_greyscale(frame, filter);
        }
        else if (flag == 3) {
            //Blurr
            blur5x5(frame, filter);
        }
        else if (flag == 4) {
            //Sobelx
            frame.copyTo(sob_x);
            sobelX3x3(frame, sob_x);
            convertScaleAbs(sob_x, filter);
        }
        else if (flag == 5) {
            //Sobely
            frame.copyTo(sob_y);
            sobelY3x3(frame, sob_y);
            convertScaleAbs(sob_y, filter);
        }
        else if (flag == 6) {
            //Gradiant_magnitude
            frame.copyTo(sob_x);
            frame.copyTo(sob_y);
            frame.copyTo(mag);
            sobelX3x3(frame, sob_x);
            sobelY3x3(frame, sob_y);
            magnitude(sob_x, sob_y, mag);
            convertScaleAbs(mag, filter);
        }
        else if (flag == 7) {
            //Blur_Quantization
            blurQuantize(frame, filter, levels);
        }
        else if (flag == 8) {
            //Cartoonization
            cartoon(frame, filter, levels, threshold);
        }
        else if (flag == 9) {
            //Negative
            negative(frame, filter);
        }
        else if (flag == 10) {
            //Flip
            flip(frame, filter);
        }
        else if (flag == 12) {
            //RGB_filtre
            rbg_filter(frame, filter, str);
        }
        else if (flag == 13) {
            //Sketch
            sketch(frame, filter);
        }
        else if (flag == 14) {
            //Red_colour_pop
            color_pop(frame, filter);
        }

        video.write(filter);
        imshow("Video", filter);


        //-----------------------------------------------------------------

        //keypress
        char key = cv::waitKey(10);

        //grayscale
        if (key == 'g') {
            flag = 1;
        }

        //alternate grayscale
        if (key == 'a') {
            flag = 2;
        }

        //Gaussian blur
        if (key == 'b') {
            flag = 3;
        }

        //sobelx
        if (key == 'x') {
            flag = 4;
        }

        //sobely
        if (key == 'y') {
            flag = 5;
        }

        //gradient magnitude
        if (key == 'm') {
            flag = 6;
        }

        //Blur and quantize
        if (key == 'j') {
            //take levels input from stdin
            cout << "Quantization level required.?" << endl;
            cin >> levels;
            flag = 7;
        }

        //cartoon
        if (key == 'c') {
            cout << "Quantization level required.?" << endl;
            cin >> levels;
            cout << "Threshold level required.?" << endl;
            cin >> threshold;
            flag = 8;

        }

        //negative
        if (key == 'n') {
            flag = 9;
        }

        //flipped
        if (key == 'f') {
            flag = 10;
        }

        //revert
        if (key == 'r') {
            flag = 0;
        }

        //rbg filter
        if (key == 'd') {
            cout << "Enter filter colour (red/blue/green)" << endl;
            cin >> str;
            flag = 12;
        }

        //sketch
        if (key == 'k') {
            flag = 13;
        }

        //quit
        if (key == 'q') {
            break;
        }

        //colour_pop
        if (key == 'e') {
            flag = 14;
        }


        //screenshot
        if (key == 's') {
         string str = "C:/Users/ksham/OneDrive/Desktop/PRCV/screenshots/vid_image" + to_string(count) + ".jpg";
         if (flag != 0) {
         imwrite(str, filter);
            }
          else {
               imwrite(str, frame);
            }
           count++;
}
    }
    video.release();
    delete capdev;
    return 0;
}
