
// Class for representing a 2D gray-scale image,
// with support for reading/writing pgm images.
// To be used in Computer Vision class.

#include "image.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

namespace ComputerVisionProjects {

Image::Image(const Image &an_image){
  AllocateSpaceAndSetSize(an_image.num_rows(), an_image.num_columns());
  SetNumberGrayLevels(an_image.num_gray_levels());

  for (size_t i = 0; i < num_rows(); ++i)
    for (size_t j = 0; j < num_columns(); ++j){
      SetPixel(i,j, an_image.GetPixel(i,j));
    }
}

Image::~Image(){
  DeallocateSpace();
}

void
Image::AllocateSpaceAndSetSize(size_t num_rows, size_t num_columns) {
  if (pixels_ != nullptr) DeallocateSpace();
  pixels_ = new int*[num_rows];
  for (size_t i = 0; i < num_rows; ++i)
    pixels_[i] = new int[num_columns];

  num_rows_ = num_rows;
  num_columns_ = num_columns;
}

void
Image::DeallocateSpace() {
  for (size_t i = 0; i < num_rows_; i++)
    delete pixels_[i];
  delete pixels_;
  pixels_ = nullptr;
  num_rows_ = 0;
  num_columns_ = 0;
}

bool ReadImage(const string &filename, Image *an_image) {  
  if (an_image == nullptr) abort();
  FILE *input = fopen(filename.c_str(),"rb");
  if (input == 0) {
    cout << "ReadImage: Cannot open file" << endl;
    return false;
  }
  
  // Check for the right "magic number".
  char line[1024];
  if (fread(line, 1, 3, input) != 3 || strncmp(line,"P5\n",3)) {
    fclose(input);
    cout << "ReadImage: Expected .pgm file" << endl;
    return false;
  }
  
  // Skip comments.
  do
    fgets(line, sizeof line, input);
  while(*line == '#');
  
  // Read the width and height.
  int num_columns,num_rows;
  sscanf(line,"%d %d\n", &num_columns, &num_rows);
  an_image->AllocateSpaceAndSetSize(num_rows, num_columns);
  

  // Read # of gray levels.
  fgets(line, sizeof line, input);
  int levels;
  sscanf(line,"%d\n", &levels);
  an_image->SetNumberGrayLevels(levels);

  // read pixel row by row.
  for (int i = 0; i < num_rows; ++i) {
    for (int j = 0;j < num_columns; ++j) {
      const int byte=fgetc(input);
      if (byte == EOF) {
        fclose(input);
        cout << "ReadImage: short file" << endl;
        return false;
      }
      an_image->SetPixel(i, j, byte);
    }
  }
  
  fclose(input);
  return true; 
}

bool WriteImage(const string &filename, const Image &an_image) {  
  FILE *output = fopen(filename.c_str(), "w");
  if (output == 0) {
    cout << "WriteImage: cannot open file" << endl;
    return false;
  }
  const int num_rows = an_image.num_rows();
  const int num_columns = an_image.num_columns();
  const int colors = an_image.num_gray_levels();

  // Write the header.
  fprintf(output, "P5\n"); // Magic number.
  fprintf(output, "#\n");  // Empty comment.
  fprintf(output, "%d %d\n%03d\n", num_columns, num_rows, colors);

  for (int i = 0; i < num_rows; ++i) {
    for (int j = 0; j < num_columns; ++j) {
      const int byte = an_image.GetPixel(i , j);
      if (fputc(byte,output) == EOF) {
	    fclose(output);
            cout << "WriteImage: could not write" << endl;
	    return false;
      }
    }
  }

  fclose(output);
  return true; 
}

// Implements the Bresenham's incremental midpoint algorithm;
// (adapted from J.D.Foley, A. van Dam, S.K.Feiner, J.F.Hughes
// "Computer Graphics. Principles and practice", 
// 2nd ed., 1990, section 3.2.2);  
void
DrawLine(int x0, int y0, int x1, int y1, int color,
	 Image *an_image) {  
  if (an_image == nullptr) abort();

#ifdef SWAP
#undef SWAP
#endif
#define SWAP(a,b) {a^=b; b^=a; a^=b;}

  const int DIR_X = 0;
  const int DIR_Y = 1;
  
  // Increments: East, North-East, South, South-East, North.
  int incrE,
    incrNE,
    incrS,
    incrSE,
    incrN;     
  int d;         /* the D */
  int x,y;       /* running coordinates */
  int mpCase;    /* midpoint algorithm's case */
  int done;      /* set to 1 when done */
  
  int xmin = x0;
  int xmax = x1;
  int ymin = y0;
  int ymax = y1;
  
  int dx = xmax - xmin;
  int dy = ymax - ymin;
  int dir;

  if (dx * dx > dy * dy) {  // Horizontal scan.
    dir=DIR_X;
    if (xmax < xmin) {
      SWAP(xmin, xmax);
      SWAP(ymin , ymax);
    } 
    dx = xmax - xmin;
    dy = ymax - ymin;

    if (dy >= 0) {
      mpCase = 1;
      d = 2 * dy - dx;      
    } else {
      mpCase = 2;
      d = 2 * dy + dx;      
    }

    incrNE = 2 * (dy - dx);
    incrE = 2 * dy;
    incrSE = 2 * (dy + dx);
  } else {// vertical scan.
    dir = DIR_Y;
    if (ymax < ymin) {
      SWAP(xmin, xmax);
      SWAP(ymin, ymax);
    }
    dx = xmax - xmin;
    dy = ymax-ymin;    

    if (dx >=0 ) {
      mpCase = 1;
      d = 2 * dx - dy;      
    } else {
      mpCase = 2;
      d = 2 * dx + dy;      
    }

    incrNE = 2 * (dx - dy);
    incrE = 2 * dx;
    incrSE = 2 * (dx + dy);
  }
  
  /// Start the scan.
  x = xmin;
  y = ymin;
  done = 0;

  while (!done) {
    an_image->SetPixel(x,y,color);
  
    // Move to the next point.
    switch(dir) {
    case DIR_X: 
      if (x < xmax) {
	      switch(mpCase) {
	      case 1:
		if (d <= 0) {
		  d += incrE;  
		  x++;
		} else {
		  d += incrNE; 
		  x++; 
		  y++;
		}
		break;
  
            case 2:
              if (d <= 0) {
                d += incrSE; 
		x++; 
		y--;
              } else {
                d += incrE;  
		x++;
              }
	      break;
	      } 
      } else {
	done=1;
      }     
      break;

    case DIR_Y: 
        if (y < ymax) {
          switch(mpCase) {
	  case 1:
	    if (d <= 0) {
	      d += incrE;  
	      y++;
	    } else {
	      d += incrNE; 
	      y++; 
	      x++;
	    }
            break;
  
	  case 2:
	    if (d <= 0) {
                d += incrSE; 
		y++; 
		x--;
              } else {
                d += incrE;  
		y++;
	    }
            break;
	  } // mpCase
        } // y < ymin 
        else {
	  done=1;
	}
	break;    
    }
  }
}

// Database for object
void Database(Image &an_image, const std::string &file_name) {

  //Create a map which pairs label value greyscale to a vector of all coordinates i and k with that siad label
  std::map<int, std::vector <std::pair<int, int> > > area_map;
    for(int i= 0; i < an_image.num_rows(); i++) {
      for(int k = 0; k < an_image.num_columns(); k++) {
        std::pair<int, int> coordinates(i,k);
        area_map[an_image.GetPixel(i,k)].push_back(coordinates);
      }
    }
    ofstream out;
    out.open(file_name);
    int x = 0;
    int y = 0;

    // Iterate through map for calculations
    for(auto &it : area_map) {
      for(auto &it2 : it.second) {

        //Assume a object has at least 1000 pixels in area
        if(it.first != 0 and it.second.size() > 1000) {
          x += it2.first;
          y += it2.second;
        }
      }

      // Compute centers
      if(it.first != 0 and it.second.size() > 1000) {
      int avgX = x / it.second.size();
      int avgY = y / it.second.size();

      //a, b, c variables in order to compute theta and inertia
      int a = 0;
      int b = 0;
      int c = 0; 
      for(auto &it3 : it.second) {
        int x_prime = it3.first - avgX;
        int y_prime = it3.second - avgY;
        a += (x_prime * x_prime);
        b += (x_prime * y_prime);
        c += (y_prime * y_prime);
      }
      b *= 2;

      //Compute theta
      double theta = 0.5 * atan2(b, a - c);

      //Inertia using formula for E
      double inertia = (a * sin(theta)* sin(theta) ) - (b * sin(theta) * cos(theta)) + (c * cos(theta) * cos(theta) );

      //Find 
      int p = (avgY * cos(theta)) - (avgX * sin(theta));
      int x_point = avgX + cos(theta)*50;
      int y_point = avgY + sin(theta)*50;
      DrawLine(avgX, avgY, avgX, avgY, 0, &an_image);
      DrawLine(avgX, avgY, x_point, y_point, 0, &an_image);

      out << it.first << " " << avgX << " " << avgY << " " << inertia << " " << theta << std::endl;
      x = 0;
      y = 0;
      a = 0;
      b = 0;
      c = 0;
      }
    }
}

void DetectObject(Image &an_image, const std::string &file_name) {
  ifstream input;
  input.open(file_name);
  int label;
  int row_pos;
  int col_pos;
  double inertia;
  double theta;
  string line;
  while(input >> label >> row_pos >> col_pos >> inertia >> theta) {
    cout << label << " " << row_pos << " " << col_pos << " " << inertia << " " << theta << endl;
  }
}

void SequentialLabeling(Image &an_image) {
    //Label starts at 254
    int label = 254;

    //Check for the leftmost pixel, if it is 255, we label it
    if(an_image.GetPixel(0, 0) == 255) {
      an_image.SetPixel(0, 0, label);
      label--;
    }

    //Check for the first row of pixels labeling them
    for(int i = 1; i < an_image.num_columns(); i++) {
      if(an_image.GetPixel(0, i) == 255) {
        if(an_image.GetPixel(0, i-1) > 0) {
          an_image.SetPixel(0, i, an_image.GetPixel(0, i-1));
        }
        else an_image.SetPixel(0, i, label--);
    }
  }

    //Check for first column of pixels labeling them
    for(int i = 1; i < an_image.num_rows(); i++) {
      if(an_image.GetPixel(i, 0) == 255) {
        if(an_image.GetPixel(i-1, 0) > 0) {
          an_image.SetPixel(i, 0, an_image.GetPixel(i-1, 0));
        }
        else an_image.SetPixel(i, 0, label--);
    }
  }

    //Disjoint Set needed to union two neigbors
    DisjointSet d(256);


    //Standard Labeling checking top and left neighbors
    for(int i = 1; i < an_image.num_rows(); i++) {
      for(int k = 1; k < an_image.num_columns(); k++) {
        if(an_image.GetPixel(i, k) == 255) {

          //If Left is labeled and Top is not
          if(an_image.GetPixel(i-1, k) > 0 and an_image.GetPixel(i, k-1) == 0) {
            an_image.SetPixel(i, k, an_image.GetPixel(i-1, k));
          }

          //If Top is labeled but left is not
          else if(an_image.GetPixel(i, k-1) > 0 and an_image.GetPixel(i-1, k) == 0) {
            an_image.SetPixel(i, k, an_image.GetPixel(i, k-1));
          }

          //If both are labeled, we will need to union them for later
          else if(an_image.GetPixel(i, k-1) > 0 and an_image.GetPixel(i-1, k) > 0) {
            an_image.SetPixel(i, k, an_image.GetPixel(i-1, k));
            d.unionSet(an_image.GetPixel(i, k-1), an_image.GetPixel(i-1, k));
          }

          //If both neighbors are unlabeled, we create new label
          else if(an_image.GetPixel(i, k-1) == 0 and an_image.GetPixel(i-1, k) == 0) {
            an_image.SetPixel(i, k, label--);
          }
        }
      }
    }

    // Second Pass unioning every label
    for(int i = 0; i < an_image.num_rows(); i++) {
      for(int k = 0; k < an_image.num_columns(); k++) {
        an_image.SetPixel(i, k, d.find(an_image.GetPixel(i, k)));
      }
    }
  }

}  // namespace ComputerVisionProjects







