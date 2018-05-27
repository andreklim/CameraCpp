#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <thread>

using namespace cv;
using namespace std;

int main(int argc, char** argv )
{
    
time_t rawtime;
  struct tm * timeinfo;
  char buffer[80];
  Mat hsv;
/*
  time (&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(buffer,sizeof(buffer),"%d-%m-%Y %I:%M:%S",timeinfo);
  std::string str(buffer);

  std::cout << str;    
*/    
    
VideoCapture camera(0);
Mat frame;
std::this_thread::sleep_for(std::chrono::milliseconds(4000));
//camera.open("http://video1.belrts.ru:9786/cameras/4/streaming/main.flv?authorization=Basic%20d2ViOndlYg%3D%3D");
//camera.open("http://video1.belrts.ru:9786/cameras/7/streaming/sub.m3u8?authorization=Basic%20d2ViOndlYg==");
camera.open("udp://localhost:5001");
std::this_thread::sleep_for(std::chrono::milliseconds(4000));
//camera.open("1.mp4");
//camera.set(CAP_PROP_FRAME_WIDTH, 1280);  
//camera.set(CAP_PROP_FRAME_HEIGHT, 720);  
//camera.set(CV_CAP_PROP_FPS,0.1);
int k=0;
while(!camera.isOpened()) {
  camera.open("udp://localhost:5001");
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  cerr << k;
  
    k++;
}    

        if(!camera.isOpened()){  
            cout << "Error1";  
        }  
        else 
        { 
            int i=0;
			for(;;){
                i++;
                cout << "Error2";
                        //std::this_thread::sleep_for(std::chrono::milliseconds(2000));
				camera >> frame;
				if(frame.empty()) {
					break;
				}
//-------------------------------------------------
				cvtColor(frame, hsv, COLOR_BGR2HSV);

                
                
                
                    int hbins = 30, sbins = 32;
    int histSize[] = {hbins, sbins};
    // hue varies from 0 to 179, see cvtColor
    float hranges[] = { 0, 180 };
    // saturation varies from 0 (black-gray-white) to
    // 255 (pure spectrum color)
    float sranges[] = { 0, 256 };
    const float* ranges[] = { hranges, sranges };
    MatND hist;
    // we compute the histogram from the 0-th and 1-st channels
    int channels[] = {0, 1};

    calcHist( &hsv, 1, channels, Mat(), // do not use mask
             hist, 2, histSize, ranges,
             true, // the histogram is uniform
             false );
    double maxVal=0;
    minMaxLoc(hist, 0, &maxVal, 0, 0);

    int scale = 10;
    Mat histImg = Mat::zeros(sbins*scale, hbins*10, CV_8UC3);

    for( int h = 0; h < hbins; h++ )
        for( int s = 0; s < sbins; s++ )
        {
            float binVal = hist.at<float>(h, s);
            int intensity = cvRound(binVal*255/maxVal);
            rectangle( histImg, Point(h*scale, s*scale),
                        Point( (h+1)*scale - 1, (s+1)*scale - 1),
                        Scalar::all(intensity),
                        CV_FILLED );
        }
//=====================
                
                
                
                
                
                
                
                
                
                
                
				  time (&rawtime);
                    timeinfo = localtime(&rawtime);

                    strftime(buffer,sizeof(buffer),"%d-%m-%Y_%I:%M:%S",timeinfo);
                    std::string str(buffer);
                    //strcat(str,".jpg");
                    //std::cout << str;
                    //sprintf(str, "%s-%d", str, i);
				imwrite(str + std::to_string(i)  + ".jpg", frame); 
                imwrite(str + std::to_string(i) + "h"  + ".jpg",histImg);

                }
			}
			
			
		



    return 0;
}
