########################################
##
## Makefile
## LINUX compilation 
##
##############################################





#FLAGS
C++FLAG = -g -std=c++11

MATH_LIBS = -lm

EXEC_DIR=.


.cc.o:
	g++ $(C++FLAG) $(INCLUDES)  -c $< -o $@


#Including
INCLUDES=  -I. 

#-->All libraries (without LEDA)
LIBS_ALL =  -L/usr/lib -L/usr/local/lib 


#First Program (ListTest)

ALL_OBJ0=image.o s1.o

PROGRAM_1=s1

$(PROGRAM_1): $(ALL_OBJ0)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ0) $(INCLUDES) $(LIBS_ALL)

ALL_OBJ1=image.o s2.o

PROGRAM_2=s2

$(PROGRAM_2): $(ALL_OBJ1)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ1) $(INCLUDES) $(LIBS_ALL)

ALL_OBJ2=image.o s3.o

PROGRAM_3=s3

$(PROGRAM_3): $(ALL_OBJ2)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ2) $(INCLUDES) $(LIBS_ALL)

ALL_OBJ3=image.o s4.o

PROGRAM_4=s4

$(PROGRAM_4): $(ALL_OBJ3)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ3) $(INCLUDES) $(LIBS_ALL)


all: 
	make $(PROGRAM_1) 
	make $(PROGRAM_2)
	make $(PROGRAM_3)
	make $(PROGRAM_4)

clean:
	(rm -f *.o; rm -f $(PROGRAM_1); rm -f $(PROGRAM_2); rm -f $(PROGRAM_3); rm -f $(PROGRAM_4);)

(:
