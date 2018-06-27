
Sample code that reads/writes pgm images and that draws lines on the images is provided.

image.* : Image class (2-D array of integers, along with size, number of colors)
                      (For our purposes the number of colors is 256)

image_demo.cc : Sample main() function for testing.

----------------------
To compile in Linux:
----------
 
   make all

To run:
---------

./image_demo objects.pgm output.pgm

This will open image objects.pgm, will draw a line on the image, and will save resulting image to file output.pgm

Used equation of sphere to find normal vector

Used S inverse times I to get N
Albedo is magnitude of N

Step for s3 is around 7-8, while threshold for s3 and s4 is around 100.

-----------
