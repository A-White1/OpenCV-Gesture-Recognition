#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
using namespace cv;
using namespace std;

VideoCapture cap;
//extern "C" int __declspec(dllexport) __stdcall  Load(bool showFrame) {
void main() {

	cap.open(0);
    int choice = 0;
	Mat img;
	CascadeClassifier rockCascade;
	rockCascade.load("fist.xml"); 
    CascadeClassifier paperCascade;
    paperCascade.load("palm.xml");
    CascadeClassifier scissorsCascade;
    scissorsCascade.load("V.xml"); //Couldn't find a scissors cascade so I used the letter V in sign language which looks like a "peace" or scissors sign.
    


	vector<Rect> rock;
    vector<Rect> paper;
    vector<Rect> scissors;
	while (true) {

       	cap.read(img);


		//Resizing and scaling for performance
        Mat grayscale;
        cvtColor(img, grayscale, COLOR_BGR2GRAY);
        Mat gray;
        resize(grayscale, gray, Size(img.cols / 1, img.rows / 1));
        equalizeHist(gray, gray);
		
        rockCascade.detectMultiScale(gray, rock, 3, 5);  //I had to tinker with these values to balance optimisation of performance with accuracy.
        paperCascade.detectMultiScale(gray, paper, 2, 5);
        scissorsCascade.detectMultiScale(gray, scissors, 2, 15);  //"Scissors" is the most volatile and random, while paper and rock are fairly accurate as long as you give the correct gesture.
        

        //Changes the values choice depending on which gesture you do.
		for (int i = 0; i < rock.size(); i++)
		{
			rectangle(img, rock[i].tl(), rock[i].br(), Scalar(0, 0, 255),
				3);
            putText(img, "Rock", Point(10, img.rows / 2), FONT_HERSHEY_DUPLEX, 1, Scalar(255, 0, 255));
            choice = 0;
		}
        for (int i = 0; i < paper.size(); i++)
        {
         
            rectangle(img, paper[i].tl(), paper[i].br(), Scalar(255, 0, 0),
                3);
            putText(img, "Paper", Point(10, img.rows / 2), FONT_HERSHEY_DUPLEX, 1, Scalar(255, 0, 255));
            choice = 1;
        }
        for (int i = 0; i < scissors.size(); i++)
        {
            rectangle(img, scissors[i].tl(), scissors[i].br(), Scalar(255, 0, 255),
                3);
            putText(img, "Scissors", Point(10, img.rows / 2), FONT_HERSHEY_DUPLEX, 1, Scalar(255, 0, 255));
            choice = 2;
        }

        char c = (char)waitKey(25);
        if (c == 13) //esc
            break;

		imshow("RockPaperScissors", img);
		waitKey(1);
		
	}
	// When everything done, release the video capture object
	cap.release();

	// Closes all the frames
	destroyAllWindows();
    //return choice;
}

/*extern "C" void __declspec(dllexport) __stdcall  Close()
{
    cap.release();
}*/
/*Using Haar cascades
Sources:

For "fist.xml": https://github.com/Sandeep-Sthapit/HandGestureDetection/tree/master
For "palm.xml": https://github.com/Aravindlivewire/Opencv/tree/master/haarcascade
For "V.xml":  https://github.com/Tejas-Nanaware/Haar-Cascades-for-Sign-Language/tree/master/Haar%20Cascades
*/
