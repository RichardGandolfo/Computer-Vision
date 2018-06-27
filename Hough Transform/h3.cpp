#include "image.h"
#include "functions.h"
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;
using namespace ComputerVisionProjects;


//run hough transform on binary image producing database and hough image
int main(int argc, char **argv) {

	if(argc != 4) {
		cout << "Incorrect number of arguments" << endl;
		return 0;
	}

	const string input_image(argv[1]);
	const string hough_image(argv[2]);
	const string hough_file(argv[3]);

	Image an_image;

	if (!ReadImage(input_image, &an_image)) {
    cout <<"Can't open file " << input_image << endl;
    return 0;
  	}

  	HoughTransform(an_image, hough_image, hough_file);


}
