#include "image.h"
#include "functions.h"
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;
using namespace ComputerVisionProjects;


//h2 where we threshold our grey level to binary
int main(int argc, char **argv) {

	if(argc != 4) {
		cout << "Incorrect number of arguments" << endl;
		return 0;
	}

	const string input_image(argv[1]);
	int grayscale_threshold = atoi(argv[2]);
	const string output_image(argv[3]);

	Image an_image;

	if (!ReadImage(input_image, &an_image)) {
    cout <<"Can't open file " << input_image << endl;
    return 0;
  	}

  	ConvertBinary(an_image, grayscale_threshold);

  	if (!WriteImage(output_image, an_image)){
    cout << "Can't write to file " << output_image << endl;
    return 0;
  }


}
