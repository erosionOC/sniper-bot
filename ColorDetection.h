#ifndef COLORDETECTION_H
#define	COLORDETECTION_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

namespace SniperBot
{
    class ColorDetector
    {
    public:
        
        static const int ERROR_NONE = 0;
        
        static const int ERROR_CANNOT_READ_CAMERA = 1;
        
        static const long DEFAULT_WINDOW_WIDTH = 0;
        
        static const int RED = 1;
        
        static const int BLUE = 2;
        
        static const int GREEN = 3;
        
        static const int YELLOW = 4;
        
    public:
        
        static Point GetScreenSize(VideoCapture &cap);
        
        ColorDetector();
        
        int findColorFromCam(int &x, int &y, VideoCapture &cap, int color, bool showWindow = false,
            long width = ColorDetector::DEFAULT_WINDOW_WIDTH, bool drawCrosshair = true,
            bool showThreshold = false);
    };
}

#endif	/* COLORDETECTION_H */
