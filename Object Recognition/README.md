Sample code that reads/writes pgm images and that draws lines on the images is provided.

image.* : Image class (2-D array of integers, along with size, number of colors)
                      (For our purposes the number of colors is 256)

Project was completed entirely
Program 1 converts Greyscale to Binary Image, using Threshold of 120
Program 2 labels the image
Program 3 creates database
Program 4 recognizes objects in said database onto labeled image

----------------------
To compile in Linux:
----------
 
   make all

To run:
---------

Run the correct Program, along with correct input and output arguments. Program 4 must use a labeled image, so you must run program 1, 2, 3 on two_objects to create database, and then run Program1, and Program2 to label many objects, before running Program 4.

-----------
