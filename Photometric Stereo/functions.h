#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "image.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdio>
#include <cmath>

using namespace std;
using namespace ComputerVisionProjects;


// Centroid and Raduis Calculations
void ComputeCentroidAndRadius(Image &an_image, int threshold, const string &out_file) {
	for(int i = 0; i < an_image.num_rows(); i++) {
		for(int j = 0; j < an_image.num_columns(); j++) {
			if(an_image.GetPixel(i,j) > threshold) {
				an_image.SetPixel(i,j,255);
			}
			else {
				an_image.SetPixel(i,j,0);
			}
		}
	}

	int x = 0;
	int y =0;
	int circle_size = 0;
	int min_x = 1000;
	int max_x = 0;
	int min_y = 1000;
	int max_y = 0;
	for(int i = 0; i < an_image.num_rows(); i++) {
		for(int j = 0; j < an_image.num_columns(); j++) {
			if(an_image.GetPixel(i,j) == 255) {
				if(i > max_x) {
					max_x = i;
				}
				if(i < min_x) {
					min_x = i;
				}
				if(j > max_y) {
					max_y = j;
				}
				if(j < min_y) {
					min_y = j;
				}
				x += i;
				y += j;
				circle_size++;
			}
		}
	}

	int x_center = x / circle_size;
	int y_center = y / circle_size;

	int horizontal_dist = max_x - min_x;
	int vertical_dist = max_y - min_y;

	int radius = (horizontal_dist + vertical_dist) / 4;

	ofstream out;
	out.open(out_file);

	out << x_center << " " << y_center << " " << radius;
	
}


// Calculate Normal Vector using equation of sphere, and orthragraphic projection
void ComputeNormalVector(Image &an_image, int x, int y, const string &input_file, const string &out_file) {
	ifstream input;
	input.open(input_file);
	int radius, x_center, y_center;

	input >> x_center >> y_center >> radius;

	int x_normal = x - x_center;
	int y_normal = y - y_center;
	double z_normal = -sqrt((radius*radius) - (x_normal*x_normal) - (y_normal*y_normal));
	int brightness = an_image.GetPixel(x,y);

	double magnitude = sqrt((x_normal*x_normal) + (y_normal*y_normal) + (z_normal*z_normal));

	double x_intensity = (x_normal * brightness)/ magnitude;
	double y_intensity = (y_normal * brightness)/ magnitude;
	double z_intensity = (z_normal * brightness)/ magnitude;

	ofstream out;
	out.open(out_file, fstream::app);

	out << x_intensity << " " << y_intensity << " " << z_intensity << endl;

	out.close();


}


// Calculate Normal Vector for the brightest pixels
void NormalForBrightestPixel(Image &an_image, const string &input_file, const string &out_file) {
	int brightest_pixel = 0;
	int brightest_x, brightest_y;
	for(int i = 0; i < an_image.num_rows(); i++) {
		for(int j = 0; j < an_image.num_columns(); j++) {
			if(an_image.GetPixel(i,j) > brightest_pixel) {
				brightest_pixel = an_image.GetPixel(i,j);
				brightest_x = i;
				brightest_y = j;
			}
		}	
	}

	//cout << brightest_x << " " << brightest_y << " " << brightest_pixel << endl;

	ComputeNormalVector(an_image, brightest_x, brightest_y, input_file, out_file);
}



// We find the normals for thresholded pixels using a step, and map them into needle map.
void CalculateNormal(Image &an_image_1, Image &an_image_2, Image &an_image_3, const string &input_file, int threshold, int step, const string &output_image) {
	double matrix[3][3];
	ifstream input;
	input.open(input_file);

	Image copy_image(an_image_1);

	double x1, x2, x3, y1, y2, y3, z1, z2, z3;

	input >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3;

	matrix[0][0] = x1;
	matrix[0][1] = y1;
	matrix[0][2] = z1;
	matrix[1][0] = x2;
	matrix[1][1] = y2;
	matrix[1][2] = z2;
	matrix[2][0] = x3;
	matrix[2][1] = y3;
	matrix[2][2] = z3;

	//Calculate inverse of 3x3 matrix

	// Determinent
	double det = matrix[0][0] * ((matrix[1][1] * matrix[2][2]) - (matrix[1][2] * matrix[2][1])) 
				- matrix[0][1] * ((matrix[1][0] * matrix[2][2]) - (matrix[1][2] * matrix[2][0]))
				+ matrix[0][2] * ((matrix[1][0] * matrix[2][1]) - (matrix[1][1] * matrix[2][0]));
	double x = 1 / det;

	double inverseMatrix[3][3];

	inverseMatrix[0][0] = x * ((matrix[1][1] * matrix[2][2]) - (matrix[1][2] * matrix[2][1]));
	inverseMatrix[0][1] = x * ((matrix[0][2] * matrix[2][1]) - (matrix[0][1] * matrix[2][2]));
	inverseMatrix[0][2] = x * ((matrix[0][1] * matrix[1][2]) - (matrix[0][2] * matrix[1][1]));
	inverseMatrix[1][0] = x * ((matrix[1][2] * matrix[2][0]) - (matrix[1][0] * matrix[2][2]));
	inverseMatrix[1][1] = x * ((matrix[0][0] * matrix[2][2]) - (matrix[0][2] * matrix[2][0]));
	inverseMatrix[1][2] = x * ((matrix[0][2] * matrix[1][0]) - (matrix[0][0] * matrix[1][2]));
	inverseMatrix[2][0] = x * ((matrix[1][0] * matrix[2][1]) - (matrix[1][1] * matrix[2][0]));
	inverseMatrix[2][1] = x * ((matrix[0][1] * matrix[2][0]) - (matrix[0][0] * matrix[2][1]));
	inverseMatrix[2][2] = x * ((matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]));

	for(int i = 0; i < an_image_1.num_rows(); i += step) {
		for(int j = 0; j < an_image_1.num_columns(); j += step) {
			if(an_image_1.GetPixel(i,j) > threshold and an_image_2.GetPixel(i,j) > threshold and an_image_3.GetPixel(i,j) > threshold) {
				double x = (inverseMatrix[0][0] * an_image_1.GetPixel(i,j)) + (inverseMatrix[0][1] * an_image_2.GetPixel(i,j)) + (inverseMatrix[0][2] * an_image_3.GetPixel(i,j));
				double y = (inverseMatrix[1][0] * an_image_1.GetPixel(i,j)) + (inverseMatrix[1][1] * an_image_2.GetPixel(i,j)) + (inverseMatrix[1][2] * an_image_3.GetPixel(i,j));
				double z = (inverseMatrix[2][0] * an_image_1.GetPixel(i,j)) + (inverseMatrix[2][1] * an_image_2.GetPixel(i,j)) + (inverseMatrix[2][2] * an_image_3.GetPixel(i,j));
				DrawLine(i, j, (i+(10*x)), (j +(10*y)), 255, &copy_image);
			}
		}
	}
	if (!WriteImage(output_image, copy_image)){
    cout << "Can't write to file " << output_image << endl;
    return;
  }
}


// Albedo calculations, scaled with max albedo and drawn to copy image
void CalculateAlbedo(Image &an_image_1, Image &an_image_2, Image &an_image_3, const string &input_file, int threshold, const string &output_image) {
	double matrix[3][3];
	ifstream input;
	input.open(input_file);

	Image copy_image(an_image_1);

	double x1, x2, x3, y1, y2, y3, z1, z2, z3;

	input >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3;

	matrix[0][0] = x1;
	matrix[0][1] = y1;
	matrix[0][2] = z1;
	matrix[1][0] = x2;
	matrix[1][1] = y2;
	matrix[1][2] = z2;
	matrix[2][0] = x3;
	matrix[2][1] = y3;
	matrix[2][2] = z3;

	double det = matrix[0][0] * ((matrix[1][1] * matrix[2][2]) - (matrix[1][2] * matrix[2][1])) 
				- matrix[0][1] * ((matrix[1][0] * matrix[2][2]) - (matrix[1][2] * matrix[2][0]))
				+ matrix[0][2] * ((matrix[1][0] * matrix[2][1]) - (matrix[1][1] * matrix[2][0]));
	double x = 1 / det;

	double inverseMatrix[3][3];

	inverseMatrix[0][0] = x * ((matrix[1][1] * matrix[2][2]) - (matrix[1][2] * matrix[2][1]));
	inverseMatrix[0][1] = x * ((matrix[0][2] * matrix[2][1]) - (matrix[0][1] * matrix[2][2]));
	inverseMatrix[0][2] = x * ((matrix[0][1] * matrix[1][2]) - (matrix[0][2] * matrix[1][1]));
	inverseMatrix[1][0] = x * ((matrix[1][2] * matrix[2][0]) - (matrix[1][0] * matrix[2][2]));
	inverseMatrix[1][1] = x * ((matrix[0][0] * matrix[2][2]) - (matrix[0][2] * matrix[2][0]));
	inverseMatrix[1][2] = x * ((matrix[0][2] * matrix[1][0]) - (matrix[0][0] * matrix[1][2]));
	inverseMatrix[2][0] = x * ((matrix[1][0] * matrix[2][1]) - (matrix[1][1] * matrix[2][0]));
	inverseMatrix[2][1] = x * ((matrix[0][1] * matrix[2][0]) - (matrix[0][0] * matrix[2][1]));
	inverseMatrix[2][2] = x * ((matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]));

	double max_albedo = 0;

	for(int i = 0; i < an_image_1.num_rows(); i++) {
		for(int j = 0; j < an_image_1.num_columns(); j++) {
			if(an_image_1.GetPixel(i,j) > threshold and an_image_2.GetPixel(i,j) > threshold and an_image_3.GetPixel(i,j) > threshold) {
				double x = (inverseMatrix[0][0] * an_image_1.GetPixel(i,j)) + (inverseMatrix[0][1] * an_image_2.GetPixel(i,j)) + (inverseMatrix[0][2] * an_image_3.GetPixel(i,j));
				double y = (inverseMatrix[1][0] * an_image_1.GetPixel(i,j)) + (inverseMatrix[1][1] * an_image_2.GetPixel(i,j)) + (inverseMatrix[1][2] * an_image_3.GetPixel(i,j));
				double z = (inverseMatrix[2][0] * an_image_1.GetPixel(i,j)) + (inverseMatrix[2][1] * an_image_2.GetPixel(i,j)) + (inverseMatrix[2][2] * an_image_3.GetPixel(i,j));
				double albedo = sqrt((x*x) + (y*y) + (z*z));
				if(albedo > max_albedo) {
					max_albedo = albedo;
				}

			}
		}
	}

	for(int i = 0; i < an_image_1.num_rows(); i++) {
		for(int j = 0; j < an_image_1.num_columns(); j++) {
			if(an_image_1.GetPixel(i,j) > threshold and an_image_2.GetPixel(i,j) > threshold and an_image_3.GetPixel(i,j) > threshold) {
				double x = (inverseMatrix[0][0] * an_image_1.GetPixel(i,j)) + (inverseMatrix[0][1] * an_image_2.GetPixel(i,j)) + (inverseMatrix[0][2] * an_image_3.GetPixel(i,j));
				double y = (inverseMatrix[1][0] * an_image_1.GetPixel(i,j)) + (inverseMatrix[1][1] * an_image_2.GetPixel(i,j)) + (inverseMatrix[1][2] * an_image_3.GetPixel(i,j));
				double z = (inverseMatrix[2][0] * an_image_1.GetPixel(i,j)) + (inverseMatrix[2][1] * an_image_2.GetPixel(i,j)) + (inverseMatrix[2][2] * an_image_3.GetPixel(i,j));
				double albedo = sqrt((x*x) + (y*y) + (z*z));
				albedo = (albedo * 255)/max_albedo;
				copy_image.SetPixel(i, j, albedo);
			}
			else {
				copy_image.SetPixel(i, j, 0);
			}
		}
	}

	if (!WriteImage(output_image, copy_image)){
    cout << "Can't write to file " << output_image << endl;
    return;
  }
}


#endif