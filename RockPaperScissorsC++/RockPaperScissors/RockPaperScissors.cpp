#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
using namespace cv;
using namespace std;

void main() {

    string choice = "Rock";
	Mat img;
	VideoCapture cap(0);
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
		
        rockCascade.detectMultiScale(img, rock, 1.2, 5);  //I had to tinker with these values to balance optimisation of performance with accuracy.
        paperCascade.detectMultiScale(img, paper, 1.3, 5);
        scissorsCascade.detectMultiScale(img, scissors, 1.1, 15);  //"Scissors" is the most volatile and random, while paper and rock are fairly accurate as long as you give the correct gesture.
        


        //Changes the values choice depending on which gesture you do.
		for (int i = 0; i < rock.size(); i++)
		{
			rectangle(img, rock[i].tl(), rock[i].br(), Scalar(255, 0, 255),
				3);
            choice = "rock";
		}
        for (int i = 0; i < paper.size(); i++)
        {
         
            rectangle(img, paper[i].tl(), paper[i].br(), Scalar(255, 0, 255),
                3);
            choice = "paper";
        }
        for (int i = 0; i < scissors.size(); i++)
        {
            rectangle(img, scissors[i].tl(), scissors[i].br(), Scalar(255, 0, 255),
                3);
            choice = "scissors";
        }

		imshow("RockPaperScissors", img);
		waitKey(1);
	}
}

/*Using Haar cascades
Sources:

For "fist.xml": https://github.com/Sandeep-Sthapit/HandGestureDetection/tree/master
For "palm.xml": https://github.com/Aravindlivewire/Opencv/tree/master/haarcascade
For "V.xml":  https://github.com/Tejas-Nanaware/Haar-Cascades-for-Sign-Language/tree/master/Haar%20Cascades
*/