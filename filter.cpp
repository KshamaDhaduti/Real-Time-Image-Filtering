//Project 1
//  filter.cpp
//  CV
//
//  Created by Kshama Dhaduti on 23rd January 2023
//
#include "filter.hpp"
#include <stdio.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int, char**) {

    string image_path = ("C:/Users/ksham/OneDrive/Desktop/PRCV/screenshots/the-starry-night.jpg");
    Mat img, dst;
    Mat3s tmp, tmp2, mag;
    img = imread(image_path, IMREAD_COLOR);
    if (img.empty())
    {
        cout << "Could not access the image" << endl;
        return 1;
    }
    img.copyTo(dst);
    img.copyTo(tmp);
    img.copyTo(tmp2);
    img.copyTo(mag);
    imshow("Original image", img);

    //Alternate_Grey_scale
    alt_greyscale(img, dst);
    imshow("Grayscale", dst);

    img.copyTo(dst);

    //Blur
    blur5x5(img, dst);
    imshow("Blur", dst);

    img.copyTo(dst);

    //Sobel
    sobelX3x3(img, tmp);
    sobelY3x3(img, tmp2);
    magnitude(tmp, tmp2, mag);
    convertScaleAbs(mag, dst);
    imshow("Magnitude", dst);

    img.copyTo(dst);

    //Sketch
    sketch(img, dst);
    imshow("Sketch", dst);

    img.copyTo(dst);

    //BlurQuantize
    blurQuantize(img, dst, 10);
    imshow("BlurQuant", dst);

    img.copyTo(dst);

    //cartoonization
    cartoon(img, dst, 10, 20);
    imshow("Cartoon", dst);

    img.copyTo(dst);

    //negative
    negative(img, dst);
    imshow("Negative", dst);

    img.copyTo(dst);

    //mirror
    flip(img, dst);
    imshow("Mirror", dst);

    img.copyTo(dst);

    //color_pop
    color_pop(img, dst);
    imshow("Color pop", dst);
    waitKey(0);
    return 0;
}
