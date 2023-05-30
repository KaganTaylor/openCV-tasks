#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
    // Open default camera
    VideoCapture cap(0);

    // Check successful camera opening
    if (!cap.isOpened()){
        std::cout << "Error opening video stream" << std::endl;
        return -1;
    }

    // Continuously capture frames
    while (true){
        Mat frame;
        cap >> frame;

        // Check for empty matrix before continuing
        if (frame.empty()){
            break;
        }

        // Convert from BGR to HSV to get yellow more easily
        Mat hsv_frame;
        cvtColor(frame, hsv_frame, COLOR_BGR2HSV);

        // Define bounds for yellow color in HSV
        Scalar lower_yellow(20, 100, 100);
        Scalar upper_yellow(30, 255, 255);

        // Threshold the HSV image to get only yellow colors
        Mat mask;
        inRange(hsv_frame, lower_yellow, upper_yellow, mask);

        // bitwise_and the frame and mask to obtain the result
        Mat result;
        bitwise_and(hsv_frame, hsv_frame, result, mask);

        // Display the result
        imshow("Result", result);

        // Break if q is pressed
        if (waitKey(1) == 'q'){
            break;
        }
    }

    // Release the video capture object
    cap.release();
    destroyAllWindows();

    return 0;
}