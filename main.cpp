#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/aruco.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"

#define UPDATE_PERIOD 50

using namespace cv;
using cv::aruco::Dictionary;

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
    std::vector<std::vector<cv::Point2f> > corners;
    cv::Mat image;

    //Grab each frame and detect tags that may be present
    cv::VideoCapture inputVideo;
    inputVideo.open(0);
    while (inputVideo.grab()) {
        //clear ids and corners vectors for next iteration
        ids.clear();
        corners.clear();

        //grab frame from video
        inputVideo.retrieve(image);
        cv::aruco::detectMarkers(image, alvarDict, corners, ids, alvarParams);

        // if at least one marker detected, draw it on frame
        if (ids.size() > 0) {
            cv::aruco::drawDetectedMarkers(image, corners, ids);
        }
        cv::imshow("out", image);

        //exit once ESC is pressed
        char key = (char)cv::waitKey(UPDATE_PERIOD);
        if (key == 27) {
            break;
        }
    }
}