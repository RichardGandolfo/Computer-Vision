#include "image.h"
#include "functions.h"

#include <iostream>
#include <string>
#include <cstdio>

using namespace std;
using namespace ComputerVisionProjects;

//s3 where we compute the normals for visible pixels and map them
int main(int argc, char **argv) {

	if(argc != 8) {
		cout << "Incorrect number of arguments" << endl;
		return 0;
	}

	const string input_file(argv[1]);
	const string input_image_1(argv[2]);
	const string input_image_2(argv[3]);
	const string input_image_3(argv[4]);
	int step = atoi(argv[5]);
  int threshold = atoi(argv[6]);
  const string output_image(argv[7]);

	Image an_image_1, an_image_2, an_image_3;

	if (!ReadImage(input_image_1, &an_image_1)) {
    	cout <<"Can't open file " << input_image_1 << endl;
    	return 0;
  	}

  	if (!ReadImage(input_image_2, &an_image_2)) {
    	cout <<"Can't open file " << input_image_2 << endl;
    	return 0;
  	}

  	if (!ReadImage(input_image_3, &an_image_3)) {
    	cout <<"Can't open file " << input_image_3 << endl;
    	return 0;
  	}

    CalculateNormal(an_image_1,an_image_2, an_image_3 , input_file, threshold, step, output_image);

}