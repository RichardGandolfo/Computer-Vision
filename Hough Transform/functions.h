#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;
using namespace ComputerVisionProjects;


//Sobel Edge Detector using sobel masks
void SobelEdgeDetector(Image &an_image) {

	// We need a copy of image to compute convolutions
	Image new_image;
	new_image.AllocateSpaceAndSetSize(an_image.num_rows(), an_image.num_columns());
	new_image.SetNumberGrayLevels(255);
	for (size_t i = 0; i < new_image.num_rows(); ++i) {
    	for (size_t j = 0; j < new_image.num_columns(); ++j){
      		new_image.SetPixel(i,j, an_image.GetPixel(i,j));
    	}
    }

    // We need to figure out max gradient value to find proportional pixel values 
	int x = 0;
	int y = 0;
	int max_gradient = 0;

	//Compute the convotutions with 8 neighbors
	for(int i = 0; i < new_image.num_rows(); i++) {
		for(int j = 0; j < new_image.num_columns(); j++) {
			if(i > 0 and i < new_image.num_rows()-1 and j > 0 and j < new_image.num_columns()-1) {
				x = (-1 * new_image.GetPixel(i-1,j-1)) + (-2 * new_image.GetPixel(i-1,j)) + (-1 * new_image.GetPixel(i-1,j+1)) +
					new_image.GetPixel(i+1,j-1) + (2 * new_image.GetPixel(i+1,j)) + new_image.GetPixel(i+1,j+1);

				y = (-1 * new_image.GetPixel(i-1,j+1)) + (-2 * new_image.GetPixel(i,j+1)) + (-1 * new_image.GetPixel(i+1,j+1)) +
					new_image.GetPixel(i-1,j-1) + (2 * new_image.GetPixel(i,j-1)) + new_image.GetPixel(i+1,j-1);

					int gradient = sqrt((x * x) + (y * y));
					an_image.SetPixel(i, j, gradient);
					if(gradient > max_gradient) max_gradient = gradient;
			}

			else {
				an_image.SetPixel(i,j, 0);
			}
		}
	}


	// We set the pixel value in proportion with gradient intensity
	for(int i = 0; i < an_image.num_rows(); i++) {
		for(int j = 0; j < an_image.num_columns(); j++) {
			int intensity = (an_image.GetPixel(i,j)*255)/max_gradient;
			an_image.SetPixel(i,j,intensity);
		}
	}
}

// Convert grey scale to binary using threshold
void ConvertBinary(Image &an_image, int threshold) {
	for(int i = 0; i < an_image.num_rows(); i++) {
		for(int j = 0; j < an_image.num_columns(); j++) {
			if(an_image.GetPixel(i,j) > threshold) {
				an_image.SetPixel(i, j, 255);
			}
			else {
				an_image.SetPixel(i, j, 0);
			}
		}
	}
}


// Hough Transform algorithm
void HoughTransform(Image &an_image, const string &output_image, const string &hough_database) {

	// Max distance for r
	int diagnal = sqrt((an_image.num_rows()*an_image.num_rows()) + (an_image.num_columns()*an_image.num_columns()));

	// Hough Array
	int accu_array[diagnal][180];

	// Initilize to 0
	for(int i = 0; i < diagnal; i++) {
		for(int j = 0; j < 180; j++) {
			accu_array[i][j] = 0;
		}
	}

	const double pi = 3.1415926535897;

	// We use dp of 1, dtheta of pi/180
	// Compute r, if r is in domain we increment in hough array
	for(int x = 0; x < an_image.num_rows(); x++) {
		for(int y = 0; y < an_image.num_columns(); y++) {
			if(an_image.GetPixel(x,y) == 255) {
				for(int h = 0; h < 180; h++) {
					double theta = h * (pi/180);
					int r = (x * cos(theta)) + (y * sin(theta));
					if(r >= 0 and r < diagnal) accu_array[r][h]++;
				}
			}
		}
	}

	// Find max votes for proportional hough space image
	int max = 0;
	for(int i = 0; i < diagnal; i++) {
		for(int j = 0; j < 180; j++) {
			if(accu_array[i][j] > max) {
				max = accu_array[i][j];
			}
		}
	}

	

	// Create Hough space image using proportion, more brightness means more votes
	Image hough_image;
	hough_image.AllocateSpaceAndSetSize(diagnal, 180);
	hough_image.SetNumberGrayLevels(255);
	for(int i = 0; i < diagnal; i++) {
		for(int j = 0; j < 180; j++) {
			hough_image.SetPixel(i, j, ((255*accu_array[i][j])/max));
		}
	}

	if (!WriteImage(output_image, hough_image)) {
    	cout << "Can't write to file " << output_image << endl;
	}	

	// Create representation of array in file
    ofstream out;
    out.open(hough_database);

    for(int i = 0; i < diagnal; i++) {
		for(int j = 0; j < 180; j++) {
			out << i << " " << j << " " << accu_array[i][j] << endl;
		}
	}
}


// Detect the Lines and draw them 
void LineDetection(Image &an_image, const string &hough_database, int threshold, const string &output_image) {
	ifstream in;
	in.open(hough_database);

	int diagnal = sqrt((an_image.num_rows()*an_image.num_rows()) + (an_image.num_columns()*an_image.num_columns()));

	int accu_array[diagnal][180];

	int r, theta, votes;
	while(in >> r >> theta >> votes) {
		accu_array[r][theta] = votes;
	}

	// Vector containing all possible lines with parameters theta and r after using threshold

	vector <std::pair<int, int> > line_vec;
	for(int i = 0; i < diagnal; i++) {
		for(int j = 0; j < 180; j++) {
			if(accu_array[i][j] > threshold) {
				std::pair<int, int> line_param(i,j);
				line_vec.push_back(line_param);
			}
		}
	}

	const double pi = 3.1415926535897;

	// Iterate through each possible parameter of lines, and figure out the endpoints of the lines
	for(int i = 0; i < line_vec.size(); i++) {
		int r = line_vec[i].first;
		double theta = line_vec[i].second * (pi/180);
		vector <int> x_points;
		vector <int> y_points;
		for(int x = 0; x < an_image.num_rows(); x++) {
			for(int y = 0; y < an_image.num_columns(); y++) {
				int r2 = (x*cos(theta)) + (y*sin(theta));

				// find the solution to r = xcos(theta) + ysin(theta), put them into vector
				if(r == r2) {
					x_points.push_back(x);
					y_points.push_back(y);
				}
			}
		}

		// x1 and y1 are starting points, x2 and y2 are the ending points of line
		int x1 = x_points[0];
		int y1 = y_points[0];
		int x2 = x_points[x_points.size()-1];
		int y2 = y_points[y_points.size()-1];
		DrawLine(x1, y1, x2, y2, 255, &an_image);
	}

	

}


#endif
