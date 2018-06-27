#include "image.h"
#include "DisjointSet.h"
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;
using namespace ComputerVisionProjects;

int main(int argc, char **argv) {

	if(argc != 4) {
		cout << "Incorrect number of arguments" << endl;
		return 0;
	}

	const string input_image(argv[1]);
	const string output_database(argv[2]);
	const string output_image(argv[3]);

	Image labeled_image;

	if (!ReadImage(input_image, &labeled_image)) {
    cout <<"Can't open file " << input_image << endl;
    return 0;
  	}

  	Database(labeled_image, output_database);

  	if (!WriteImage(output_image, labeled_image)){
    cout << "Can't write to file " << output_image << endl;
    return 0;
  }


}