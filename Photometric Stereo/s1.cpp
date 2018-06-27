#include "image.h"
#include "functions.h"

#include <iostream>
#include <string>
#include <cstdio>

using namespace std;
using namespace ComputerVisionProjects;

//s1 where we compute centroid and raduis
int main(int argc, char **argv) {

	if(argc != 4) {
		cout << "Incorrect number of arguments" << endl;
		return 0;
	}

	const string input_image(argv[1]);
	int grayscale_threshold = atoi(argv[2]);
	const string output_file(argv[3]);

	Image an_image;

	if (!ReadImage(input_image, &an_image)) {
    	cout <<"Can't open file " << input_image << endl;
    	return 0;
  	}

  	ComputeCentroidAndRadius(an_image, grayscale_threshold, output_file);

}