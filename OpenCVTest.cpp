#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace cv;
using namespace std;

//Mat loadAndResize(const string& imagePath) {
//    Mat img = imread(imagePath);
//    if (img.empty()) {
//        cerr << "Failed to read image: " << imagePath << endl;
//        return Mat();
//    }
//    resize(img, img, Size(1024, 768));
//    return img;
//}
//
//Mat preprocessImage(const Mat& img) {
//    Mat gray, blurred, binary;
//    cvtColor(img, gray, COLOR_BGR2GRAY);
//    GaussianBlur(gray, blurred, Size(5, 5), 4);
//    threshold(blurred, binary, 0, 255, THRESH_BINARY + THRESH_OTSU);
//    return binary;
//}
//
//Mat applyMorphology(const Mat& binary) {
//    Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
//    Mat closed, opened, dilated;
//    morphologyEx(binary, closed, MORPH_CLOSE, kernel, Point(-1, -1), 2);
//    morphologyEx(closed, opened, MORPH_OPEN, kernel, Point(-1, -1), 2);
//    dilate(opened, dilated, kernel, Point(-1, -1), 3);
//    return dilated;
//}
//
//Mat drawLegs(Mat& img, const Mat& mask) {
//    vector<vector<Point>> contours;
//    findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
//
//    Mat boxedImg = img.clone();
//    int legId = 1;
//    int cx = img.cols / 2;
//    int cy = img.rows / 2;
//
//    for (const auto& cnt : contours) {
//        double area = contourArea(cnt);
//        if (area > 500 && area < 15000) {
//            Rect rect = boundingRect(cnt);
//            double aspect = static_cast<double>(rect.height) / rect.width;
//            double dist = sqrt(pow(rect.x + rect.width / 2.0 - cx, 2) +
//                pow(rect.y + rect.height / 2.0 - cy, 2));
//
//            if (aspect > 0.2 && aspect < 2.5 && dist > 150 && dist < 250) {
//                rectangle(boxedImg, rect, Scalar(0, 255, 0), 2);
//                putText(boxedImg, "Leg " + to_string(legId), Point(rect.x, rect.y - 10),
//                    FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0), 1);
//                legId++;
//            }
//        }
//    }
//
//    return boxedImg;
//}
//
//void processImage(const string& imagePath, const string& outputPath) {
//    Mat img = loadAndResize(imagePath);
//    if (img.empty()) return;
//
//    Mat binary = preprocessImage(img);
//    Mat mask = applyMorphology(binary);
//    Mat result = drawLegs(img, mask);
//
//    imwrite(outputPath, result);
//    cout << "Saved result to " << outputPath << endl;
//}
//
//int main() {
//    vector<string> imagePaths = { "1.jpg", "2.jpg", "3.jpg", "4.jpg" };
//    vector<string> outputPaths = { "out_1.jpg", "out_2.jpg", "out_3.jpg", "out_4.jpg" };
//
//    for (size_t i = 0; i < imagePaths.size(); ++i) {
//        processImage(imagePaths[i], outputPaths[i]);
//    }
//
//    return 0;
//}

Mat darkenCenterRegion(Mat& img, int radius = 260) {
    Mat darkened = img.clone();
    int h = img.rows;
    int w = img.cols;
    int cx = w / 2;
    int cy = h / 2;

    Mat mask = Mat::zeros(h, w, CV_8UC1);
    circle(mask, Point(cx, cy), radius, Scalar(255), -1);

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            if (mask.at<uchar>(y, x) == 255) {
                for (int c = 0; c < 3; ++c) {
                    darkened.at<Vec3b>(y, x)[c] = static_cast<uchar>(darkened.at<Vec3b>(y, x)[c] * 0.6);
                }
            }
        }
    }

    return darkened;
}

void debugContours(const Mat& img, const string& outputPath) {
    Mat gray, blurred, binary, closed, opened, dilated;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    GaussianBlur(gray, blurred, Size(5, 5), 4);
    threshold(blurred, binary, 0, 255, THRESH_BINARY + THRESH_OTSU);

    Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
    morphologyEx(binary, closed, MORPH_CLOSE, kernel, Point(-1, -1), 2);
    morphologyEx(closed, opened, MORPH_OPEN, kernel, Point(-1, -1), 2);
    dilate(opened, dilated, kernel, Point(-1, -1), 3);

    vector<vector<Point>> contours;
    findContours(dilated, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    Mat debugImg = img.clone();
    int legId = 1;
    cout << "Area\tAspectRatio\tBox(x,y,w,h)" << endl;

    for (const auto& cnt : contours) {
        double area = contourArea(cnt);
        Rect rect = boundingRect(cnt);
        double aspect = static_cast<double>(rect.height) / rect.width;

        if (area > 200 && area < 20000 && aspect > 0.1 && aspect < 5.0) {
            rectangle(debugImg, rect, Scalar(0, 255, 0), 2);
            putText(debugImg, to_string(legId), Point(rect.x, rect.y - 5),
                FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 255, 0), 1);
            cout << area << "\t" << aspect << "\t(" << rect.x << "," << rect.y << "," << rect.width << "," << rect.height << ")" << endl;
            legId++;
        }
    }

    imwrite(outputPath, debugImg);
    cout << "Saved debug output to " << outputPath << endl;
}

int main() {
    string imagePath = "1.jpg";
    string outputPath = "debug_output.jpg";

    Mat img = imread(imagePath);
    if (img.empty()) {
        cerr << "Failed to load image: " << imagePath << endl;
        return -1;
    }

    resize(img, img, Size(1024, 768));
    Mat darkened = darkenCenterRegion(img);

    debugContours(darkened, outputPath);

    return 0;
}
