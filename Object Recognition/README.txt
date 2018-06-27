Prob. 1
Homework 2
Computational Vision , Fall 2017 Due Date 9/26/2017
Total Points: 30
Programming Assignment
Our goal is to develop a vision system that recognizes two–dimensional objects in images (you are given gray–level PGM images that can be found in blackboard). The two objects we are interested in are shown in the image two objects.pgm. Given an image such as many objects 1.pgm, we would like our vision system to determine if the two objects are in the image and if so compute their positions and orientations. This information is valuable as it can be used by a robot to sort and assemble manufactured parts.
The task is divided into three parts, each corresponding to a program you need to write and submit. Each program must accept arguments in the format specified as
program name {1st argument} {2nd argument} . . . {Nth argument}.
Program 1 Write a program named p1 that converts a gray–level image to a binary one using
a threshold value:
p1 {input gray–level image} {input gray–level threshold} {output binary image}.
Select any threshold that results in ”clean” binary images from the gray–level ones given to you (a binary image can be saved as a PGM file with 1 as the number of colors in the header). You should be able to use the same threshold value for all images. Please, when you submit your assignment, indicate the value you used in your README file. Apply program p1 to the image two objects.pgm. (3 points)
Program 2 Write a labeling program named p2 that segments a binary image into several connected regions:
p2 {input binary image} {output labeled image}.
(TOTAL: 30 points)
     
A good choice is the sequential labeling algorithm described in the class. Note that you may have to make two passes of the image to resolve possible equivalences in the labels. In the ”labeled” output image each object region should be painted with a different gray– level: the gray–level assigned to an object is its label. The labeled image can be displayed to check the results produced by your program. To make gray–levels look significantly different, you may want to use consecutive natural numbers as labels in your output file, and set the number of colors in the PGM header to the total number of objects. Note that your program must be able to produce correct results given any binary image. You can test it on the images given to you. Apply program p2 to the binary version of image two objects.pgm. (9 points)
Program 3 Write a program named p3 that takes a labeled image as input, computes object attributes, and generates the database of the objects:
p3 {input labeled image} {output database} {output image}.
The generated object database should include a line for each of the objects with the following values: object label, row position of the center, column position of the center, the minimum moment of inertia, and the orientation (angle in degrees between the axis of minimum inertia and the vertical axis). Separate the aforementioned values with blanks. These attributes will serve as your object model database. The output image should display positions and orientations of objects in the input image using a dot for the position and a short line segment originating from the dot for the orientation. (For this, you can use the code provided to you: see handout ”Programming Assignments...”). Apply program p3 to the labeled image of two objects.pgm. (9 points)
Program 4 Now you have all the tools needed to develop the object recognition system. Write a program named p4 that recognizes objects from the database:
p4 {input labeled image} {input database} {output image}.
Your program should compare (using your own comparison criteria) the attributes of each object in a labeled image file with those from the object model database. It should pro- duce an output image which would display the positions and orientations (using dots and line segments, as before) of the objects that have been recognized. Using the object database generated from two objects.pgm, test your program on the images many objects 1.pgm and many objects 2.pgm. (9 points)

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
