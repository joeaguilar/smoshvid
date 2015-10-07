#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int main(int argc, char const *argv[])
{
  if (argc != 2)
  {
    cout << "Usage: [program] path/to/video" << endl;
    return -1;
  }


  VideoCapture cap(argv[1]);
  if (!cap.isOpened()) {
    cout << "!!! Failed to open file: " << argv[1] << endl;
    return -1;
  }


  VideoWriter output_capture("smoshed.mov",
    // CV_FOURCC('D', 'I', 'V', 'X'), // activate this for non-mac platforms 
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
    frame2 = frame.clone(); // copy frame to keep color "accurate"
    size_t h = frame.rows;
    size_t w = frame.cols;
    uchar red, green, blue; 
    int value;

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

    frame2.copyTo(frame); // copy frame back;
    output_capture.write(frame); // Write to video

    // FREE ALL THE MEMORY!
    frame.release();
    frame2.release();
  }

  cap.release();
  output_capture.release();

  return 0;
}








