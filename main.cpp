#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <string>

void composite(cv::Mat &base,
	       const cv::Point &top_left,
	       const int width,
	       const int height,
    	       const cv::Mat &over)
{
    //overを必要なサイズにリサイズする
    cv::Mat resized;
    cv::resize(over,resized,cv::Size(width,height));

    for(int i = 0;i<width;i++){
	for(int j = 0;j<height;j++){
	    resized.row(j).col(i).copyTo(base.row(top_left.y + j).col(top_left.x + i));	    
	}
    }
}

int main(int argc, char** argv)
{
    const std::string filename = (argc > 1)? argv[1] : "";
    auto img = cv::imread(filename,1);
    if(img.empty()){
	std::cerr << "faild to open image file" << std::endl;
	return -1;
    }
    
    //グレースケールにしないと認識に使えないっぽい
    cv::Mat gray;
    cv::cvtColor(img,gray,CV_BGR2GRAY);
    
    //分類器
    const std::string cascade_name = "/usr/share/opencv/haarcascades/haarcascade_frontalface_alt.xml";
    cv::CascadeClassifier cascade;
    cascade.load(cascade_name);

    //顔の座標を検出、保存
    std::vector<cv::Rect> faces;
    cascade.detectMultiScale(gray,
			     faces,
			     1.1,2,
			     CV_HAAR_SCALE_IMAGE,
			     cv::Size(30,30));
    //サスケェ
    const auto sasuke = cv::imread("./sasukee.png");
    if(sasuke.empty()){
	std::cerr << "faild to open SASUKE image file\n"
		  << "make sure that sasukee.png in this directory" << std::endl;
	return -1;
    }
    const cv::Mat cropped_sasuke(sasuke,cv::Rect(60,0,393,320));
    
    for(auto r : faces){
	cv::Point top_left;
	top_left.x = cv::saturate_cast<int>(r.x);
	top_left.y = cv::saturate_cast<int>(r.y);

	composite(img , top_left, r.width,r.height,cropped_sasuke);
    }
    
//表示
    cv::namedWindow("result",CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
    cv::imshow("result",img);
    cv::waitKey(0);   
}





