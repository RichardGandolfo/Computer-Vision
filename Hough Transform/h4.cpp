#include "image.h"
#include "functions.h"
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;
using namespace ComputerVisionProjects;

//Detect lines using the parameter lines we computed
int main(int argc, char **argv) {

	if(argc != 5) {
		cout << "Incorrect number of arguments" << endl;
		return 0;
	}

	const string input_image(argv[1]);
	const string hough_file(argv[2]);
	int threshold = atoi(argv[3]);
	const string output_image(argv[4]);

	Image an_image;

	if (!ReadImage(input_image, &an_image)) {
    cout <<"Can't open file " << input_image << endl;
    return 0;
  	}

  	LineDetection(an_image, hough_file, threshold, output_image);

  	if (!WriteImage(output_image, an_image)) {
    	cout << "Can't write to file " << output_image << endl;
	}


}
