#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include "opencv2/aruco.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"

#define UPDATE_PERIOD 50

using namespace cv;
using cv::aruco::Dictionary;

Point2f getAverageTagCoordinateFromCorners(const std::vector<Point2f> &corners) {  //gets coordinate of center of tag
    // RETURN:
    // Point2f object containing the average location of the 4 corners
    // of the passed-in tag
    Point2f avgCoord;
    for (auto &corner : corners) {
        avgCoord.x += corner.x;
        avgCoord.y += corner.y;
    }
    avgCoord.x /= corners.size();
    avgCoord.y /= corners.size();
    return avgCoord;
}

std::vector<cv::Point> contoursConvexHull(std::vector<std::vector<cv::Point>> contours) {
    std::vector<Point> result;
    std::vector<Point> pts;
    for (size_t i = 0; i < contours.size(); i++)
        for (size_t j = 0; j < contours[i].size(); j++)
            pts.push_back(contours[i][j]);
    convexHull(pts, result);
    return result;
}

int main() {
    //ensure file is present before continuing
    cv::FileStorage fsr("alvar_dict.yml", cv::FileStorage::READ);
    if (!fsr.isOpened()) {
        std::cerr << "ERR: \"alvar_dict.yml\" does not exist! Create it before running main\n";
        return 1;
    }

    //read dictionary from file
    int mSize, mCBits;
    cv::Mat bits;
    fsr["MarkerSize"] >> mSize;
    fsr["MaxCorrectionBits"] >> mCBits;
    fsr["ByteList"] >> bits;
    fsr.release();
    Ptr<Dictionary> alvarDict = new Dictionary(bits, mSize, mCBits);

    //initialize detector parameters that we need to detect Alvar
    Ptr<cv::aruco::DetectorParameters> alvarParams = new cv::aruco::DetectorParameters();
    alvarParams->markerBorderBits = 2;

    //store tags and locations here so we don't need to reinitialize/resize each loop
    std::vector<int> ids;
    std::vector<std::vector<cv::Point2f>> corners;
    std::vector<std::vector<cv::Point2f>> rejected;
    cv::Mat image;

    //contour stuff
    Mat canny_output;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<std::vector<cv::Point>> accepted;
    std::vector<Vec4i> hierarchy;
    Mat greyscale;
    int thresh = 100;

    //Grab each frame and detect tags that may be present
    cv::VideoCapture inputVideo;
    inputVideo.open(0);
    while (inputVideo.grab()) {
        //clear ids and corners vectors for next iteration
        ids.clear();
        corners.clear();

        //grab frame from video
        inputVideo.retrieve(image);
        cv::aruco::detectMarkers(image, alvarDict, corners, ids, alvarParams, rejected);

        //increase contrast
        //image.convertTo(image, -1, 1.5, -50);

        // if (ids.size() == 0) {
        //SECONDARY DETECTION
        // Detect edges using canny
        cvtColor(image, greyscale, cv::COLOR_RGB2GRAY);
        Canny(greyscale, canny_output, thresh, thresh * 2.2, 3);
        /// Find contours
        findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

        // Filter contours
        std::vector<std::vector<Point>>poly(contours.size());
        for (int i = 0; i < contours.size(); ++i) {
            cv::approxPolyDP(Mat(contours[i]), poly[i], 3, true);
            if (poly[i].size() < 20 && contourArea(contours[i]) > 75) {
                accepted.push_back(contours[i]);
            }
            // }
        }

        // Draw contours
        Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
        for (int i = 0; i < accepted.size(); i++) {
            Scalar color = Scalar(0, 0, 255);
            drawContours(drawing, accepted, i, color, 2, 8, hierarchy, 0, Point());
        }
        imshow("Contours", drawing);

        imshow("contoursConvexHull", canny_output);
        accepted.clear();

        /// Show in a window
        namedWindow("Contours", CV_WINDOW_AUTOSIZE);
        //imshow("Contours", drawing);
        namedWindow("Canny", CV_WINDOW_AUTOSIZE);

        cv::imshow("out", image);

        //exit once ESC is pressed
        char key = (char)cv::waitKey(UPDATE_PERIOD);
        if (key == 27) {
            break;
        }
    }
}