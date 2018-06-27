#include "image.h"
#include "functions.h"

#include <iostream>
#include <string>
#include <cstdio>

using namespace std;
using namespace ComputerVisionProjects;

//h1 where we run sobel edge detection on hough image
int main(int argc, char **argv) {

	if(argc != 3) {
		cout << "Incorrect number of arguments" << endl;
		return 0;
	}

	const string input_image(argv[1]);
	const string output_image(argv[2]);

	Image an_image;

	if (!ReadImage(input_image, &an_image)) {
    	cout <<"Can't open file " << input_image << endl;
    	return 0;
  	}

  	SobelEdgeDetector(an_image);


  	if (!WriteImage(output_image, an_image)){
    cout << "Can't write to file " << output_image << endl;
    return 0;
  }

}