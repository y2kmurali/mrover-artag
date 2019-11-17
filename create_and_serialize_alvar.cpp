#include <iostream>
#include <opencv2/aruco.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using cv::aruco::Dictionary;

int main() {
    Ptr<Dictionary> alvarDict = new Dictionary;
    alvarDict->markerSize = 5;
    alvarDict->maxCorrectionBits = 5;

    //tag 0
    unsigned char tag0[5][5] = {{1, 1, 0, 1, 1},
                                {1, 1, 0, 1, 1},
                                {1, 0, 1, 0, 1},
                                {1, 1, 1, 1, 1},
                                {1, 1, 1, 1, 1}};
    Mat tag0_mat = Mat(5, 5, CV_8UC1);
    std::memcpy(tag0_mat.data, tag0, 5 * 5 * sizeof(unsigned char));
    Mat tag0_compressed = alvarDict->getByteListFromBits(tag0_mat);
    alvarDict->bytesList.push_back(tag0_compressed);

    //tag 1
    unsigned char tag1[5][5] = {{1, 1, 0, 1, 1},
                                {1, 1, 0, 1, 1},
                                {1, 0, 1, 0, 1},
                                {0, 0, 1, 1, 0},
                                {1, 1, 1, 0, 1}};
    Mat tag1_mat = Mat(5, 5, CV_8UC1);
    std::memcpy(tag1_mat.data, tag1, 5 * 5 * sizeof(unsigned char));
    Mat tag1_compressed = alvarDict->getByteListFromBits(tag1_mat);
    alvarDict->bytesList.push_back(tag1_compressed);

    //tag 2
    unsigned char tag2[5][5] = {{1, 1, 0, 1, 1},
                                {1, 1, 0, 1, 1},
                                {1, 0, 1, 0, 1},
                                {1, 0, 1, 1, 0},
                                {1, 0, 1, 1, 0}};
    Mat tag2_mat = Mat(5, 5, CV_8UC1);
    std::memcpy(tag2_mat.data, tag2, 5 * 5 * sizeof(unsigned char));
    Mat tag2_compressed = alvarDict->getByteListFromBits(tag2_mat);
    alvarDict->bytesList.push_back(tag2_compressed);

    //tag 3
    unsigned char tag3[5][5] = {{1, 1, 0, 1, 1},
                                {1, 1, 0, 1, 1},
                                {1, 0, 1, 0, 1},
                                {0, 1, 1, 1, 1},
                                {1, 0, 1, 0, 0}};
    Mat tag3_mat = Mat(5, 5, CV_8UC1);
    std::memcpy(tag3_mat.data, tag3, 5 * 5 * sizeof(unsigned char));
    Mat tag3_compressed = alvarDict->getByteListFromBits(tag3_mat);
    alvarDict->bytesList.push_back(tag3_compressed);

    //tag 4
    unsigned char tag4[5][5] = {{1, 1, 0, 1, 1},
                                {1, 1, 0, 1, 1},
                                {1, 0, 1, 0, 1},
                                {0, 1, 1, 1, 0},
                                {0, 1, 1, 1, 0}};
    Mat tag4_mat = Mat(5, 5, CV_8UC1);
    std::memcpy(tag4_mat.data, tag4, 5 * 5 * sizeof(unsigned char));
    Mat tag4_compressed = alvarDict->getByteListFromBits(tag4_mat);
    alvarDict->bytesList.push_back(tag4_compressed);

    //tag 5
    unsigned char tag5[5][5] = {{1, 1, 0, 1, 1},
                                {1, 1, 0, 1, 1},
                                {1, 0, 1, 0, 1},
                                {1, 0, 1, 1, 1},
                                {0, 1, 1, 0, 0}};
    Mat tag5_mat = Mat(5, 5, CV_8UC1);
    std::memcpy(tag5_mat.data, tag5, 5 * 5 * sizeof(unsigned char));
    Mat tag5_compressed = alvarDict->getByteListFromBits(tag5_mat);
    alvarDict->bytesList.push_back(tag5_compressed);

    //tag 6
    unsigned char tag6[5][5] = {{1, 1, 0, 1, 1},
                                {1, 1, 0, 1, 1},
                                {1, 0, 1, 0, 1},
                                {0, 0, 1, 1, 1},
                                {0, 0, 1, 1, 1}};
    Mat tag6_mat = Mat(5, 5, CV_8UC1);
    std::memcpy(tag6_mat.data, tag6, 5 * 5 * sizeof(unsigned char));
    Mat tag6_compressed = alvarDict->getByteListFromBits(tag6_mat);
    alvarDict->bytesList.push_back(tag6_compressed);

    //tag 7
    unsigned char tag7[5][5] = {{1, 1, 0, 1, 1},
                                {1, 1, 0, 1, 1},
                                {1, 0, 1, 0, 1},
                                {1, 1, 1, 1, 0},
                                {0, 0, 1, 0, 1}};
    Mat tag7_mat = Mat(5, 5, CV_8UC1);
    std::memcpy(tag7_mat.data, tag7, 5 * 5 * sizeof(unsigned char));
    Mat tag7_compressed = alvarDict->getByteListFromBits(tag7_mat);
    alvarDict->bytesList.push_back(tag7_compressed);

    //tag 8
    unsigned char tag8[5][5] = {{1, 1, 0, 1, 1},
                                {1, 1, 0, 1, 1},
                                {1, 0, 1, 0, 1},
                                {0, 0, 1, 0, 1},
                                {1, 1, 1, 1, 0}};
    Mat tag8_mat = Mat(5, 5, CV_8UC1);
    std::memcpy(tag8_mat.data, tag8, 5 * 5 * sizeof(unsigned char));
    Mat tag8_compressed = alvarDict->getByteListFromBits(tag8_mat);
    alvarDict->bytesList.push_back(tag8_compressed);

    //Now that we have all tags in dict, serialize them to a file
    cv::Mat store = alvarDict->bytesList;
    cv::FileStorage fs("alvar_dict.yml", cv::FileStorage::WRITE);
    fs << "MarkerSize" << alvarDict->markerSize;
    fs << "MaxCorrectionBits" << alvarDict->maxCorrectionBits;
    fs << "ByteList" << alvarDict->bytesList;
    fs.release();
}