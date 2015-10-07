#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
// #include <opencv2/cv.h>
// #include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// void renderMode(char *chunk, char *duplicate, uchar render);

int main(int argc, char const *argv[])
{
  if (argc != 2)
  {
    cout << "Usage: [program] path/to/video" << endl;
    return -1;
  }

  // Mat img, img2;
  // img = imread(argv[1], CV_LOAD_IMAGE_COLOR);

  VideoCapture cap(argv[1]);
  if (!cap.isOpened()) {
    cout << "!!! Failed to open file: " << argv[1] << endl;
    return -1;
  }

  //  VideoCapture cap2(argv[1]);
  // if (!cap2.isOpened()) {
  //   cout << "!!! Failed to open temporary buffer file: "<< argv[1] << endl;
  //   return -1;
  // }

  // VideoWriter ouptput;
  // ouptput.open("output-video.avi", CV_FOURCC('D', 'I', 'V', 'X', Size(1200, 1600), true));
  
  VideoWriter output_capture("smoshed.mov",
    // CV_FOURCC('D', 'I', 'V', 'X'), 
    CV_FOURCC('m','p','4', 'v'),
    cap.get(CV_CAP_PROP_FPS),
    cv::Size(cap.get(CV_CAP_PROP_FRAME_WIDTH),
      cap.get(CV_CAP_PROP_FRAME_HEIGHT))
    );

  if (!output_capture.isOpened()) {
    cout << "!!! Output video could not be opened " << endl;
    return -1;
  }

  cout << "Starting the process... "  << endl;
 
  Mat frame, frame2;

  for (;;) {
    if (!cap.read(frame))
      break;
    frame2 = frame.clone();
    size_t h = frame.rows;
    size_t w = frame.cols;
    uchar red, green, blue; 
    int value;
    // cout << "Starting the main loop" << endl;
      for (int i = 0; i < h; ++i)
      {
          cv::Vec3b* pixel = frame.ptr<cv::Vec3b>(i); // point to first pixel in row
          cv::Vec3b* other = frame2.ptr<cv::Vec3b>(i);
          for (int j = 0; j < w; ++j)
          {
              red   = pixel[j][2];
              green = pixel[j][1];
              blue  = pixel[j][0];
              value = (int) red + (int) green + (int) blue;

              
            if (value > 100 && (j > 20) && (j + 22) < w ) {
              other[j][2] = pixel[j-19][1];
              other[j][1] = pixel[j+20][2];
              other[j][0] = pixel[j-4 ][0];
            } else if (value > 50 && j > 15 && (j+16) < w) {
              other[j][2] = pixel[j-13][2];
              other[j][1] = pixel[j+15][0];
              other[j][0] = pixel[j+4 ][1];
            } else if (j > 11 && ( j+5 < w) ) {
              other[j][2] = pixel[j-7 ][2];
              other[j][1] = pixel[j+4 ][0];
              other[j][0] = pixel[j-10][1];
            } else {
              other[j][2] = pixel[j][2];
              other[j][1] = pixel[j][0];
              other[j][0] = pixel[j][1];
            }

            if (j % (w-1) == 0 ) {
              other[j][2] = red;
              other[j][1] = green;
              other[j][0] = blue;
            }

          }
      }

    //   for ( int i = 0; i < h; i++) {
    //       cv::Vec3b* pixel = frame.ptr<cv::Vec3b>(i);
    //       cv::Vec3b* other = frame2.ptr<cv::Vec3b>(i);
    //       for ( int j = 0; j < w; j++) {
    //         pixel[j][2] = other[j][2];
    //         pixel[j][1] = other[j][1];
    //         pixel[j][0] = other[j][0];
    //       }

    // }
    frame2.copyTo(frame);
    output_capture.write(frame);
    frame.release();
    frame2.release();
  }
  cap.release();
  // cap2.release();
  output_capture.release();

  // namedWindow("Original image", WINDOW_AUTOSIZE);

  // imshow("Original image", dupBuffer);

  // waitKey(0);
  // destroyAllWindows();

  // cout << "Writing image..."<< endl;
  // if (! imwrite("imagecopy.tif", img)  ) {
  //   fprintf(stderr, "failed to write image file\n");
  // }

  return 0;
}








