#include "image.h"
#include "DisjointSet.h"
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;
using namespace ComputerVisionProjects;

int main(int argc, char **argv) {

	if(argc != 3) {
		cout << "Incorrect number of arguments" << endl;
		return 0;
	}

	const string input_image(argv[1]);
	const string output_image(argv[2]);

	Image binary_image;

	if (!ReadImage(input_image, &binary_image)) {
    cout <<"Can't open file " << input_image << endl;
    return 0;
  	}
  	
  	SequentialLabeling(binary_image);

  	if (!WriteImage(output_image, binary_image)){
    cout << "Can't write to file " << output_image << endl;
    return 0;
  }


}