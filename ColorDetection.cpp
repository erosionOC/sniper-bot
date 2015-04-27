#include "ColorDetection.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

namespace SniperBot
{
    ColorDetector::ColorDetector() //: ColorDetector::ColorDetector(ColorDetector::DEFAULT_COLOR)
    {
        
    }
    
    static Point getScreenSize(VideoCapture &cap)
    {
        Mat frame;
        bool bSuccess = cap.read(frame); // read a new frame from video

        if (!bSuccess) //if not success, return 0
            return Point(0, 0);
        else
            return Point(frame.cols, frame.rows);
    }

    int ColorDetector::findColorFromCam(int &x, int &y, VideoCapture &cap, int color, bool showWindow,
            long width, bool drawCrosshair, bool showThreshold)
    {
        int iLastX = -1;
        int iLastY = -1;
        
        Mat imgOriginal;
        Mat overlay;

        bool bSuccess = cap.read(imgOriginal); // read a new frame from video

        if (!bSuccess) //if not success, return error
            return ERROR_CANNOT_READ_CAMERA;
        
        if(width > 0)
            resize(imgOriginal, imgOriginal,
                    Size(width, (int)(imgOriginal.rows * (width / (float)imgOriginal.cols))));
        
        Mat imgHSV;
        
        cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
        
        Mat imgThresholded;
        // This needs to be tested in a control environment to acquire predefined colors and their values. Colors can be selected selected from switch case.
        switch(color)
        {
            case 1:
                inRange(imgHSV, Scalar(170, 150, 60), Scalar(179, 255, 255), imgThresholded); //Threshold the image
                break;
            case 2:
                inRange(imgHSV, Scalar(72, 63, 28), Scalar(179, 255, 255), imgThresholded); //Threshold the image
                break;
            case 3:
                inRange(imgHSV, Scalar(55, 114, 0), Scalar(86, 255, 255), imgThresholded); //Threshold the image
                break;
            case 4:
                inRange(imgHSV, Scalar(19, 0, 169), Scalar(44, 255, 255), imgThresholded); //Threshold the image
                break;
        }
        
        //morphological opening (removes small objects from the foreground)
        erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
        dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

        //morphological closing (removes small holes from the foreground)
        dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
        erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
        
        //Calculate the moments of the thresholded image
        Moments oMoments = moments(imgThresholded);

        double dM01 = oMoments.m01;
        double dM10 = oMoments.m10;
        double dArea = oMoments.m00;
        
        // if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero
        if (dArea > 10000)
        {
            //calculate the position of the object
            int posX = dM10 / dArea;
            int posY = dM01 / dArea;
            x = posX;
            y = posY;
            
            if(drawCrosshair)
            {
                circle(imgOriginal, Point(posX, posY), 15, Scalar(0, 255, 0));
                line(imgOriginal, Point(posX, posY - 20), Point(posX, posY - 5), Scalar(0, 255, 0));
                line(imgOriginal, Point(posX, posY + 20), Point(posX, posY + 5), Scalar(0, 255, 0));
                line(imgOriginal, Point(posX - 20, posY), Point(posX - 5, posY), Scalar(0, 255, 0));
                line(imgOriginal, Point(posX + 20, posY), Point(posX + 5, posY), Scalar(0, 255, 0));
            }
            
            //overlay = Mat::zeros(imgOriginal.size(), CV_8UC3);
            //imgOriginal = imgOriginal + overlay;
        }
        else
        {
            x = -1;
            y = -1;
        }
        
        if(showWindow) imshow("Original", imgOriginal); //show the original image
        
        if(showThreshold) imshow("Threshold", imgThresholded);
        
        //cout << imgOriginal.cols << " x " << imgOriginal.rows << endl;
        
        return ERROR_NONE;
    }
}
