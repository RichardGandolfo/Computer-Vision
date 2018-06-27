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

ALL_OBJ0=Program1.o image.o

PROGRAM_1=Program1

$(PROGRAM_1): $(ALL_OBJ0)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ0) $(INCLUDES) $(LIBS_ALL)

ALL_OBJ1=Program2.o image.o

PROGRAM_2=Program2

$(PROGRAM_2): $(ALL_OBJ1)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ1) $(INCLUDES) $(LIBS_ALL)

ALL_OBJ2=Program3.o image.o

PROGRAM_3=Program3

$(PROGRAM_3): $(ALL_OBJ2)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ2) $(INCLUDES) $(LIBS_ALL)

ALL_OBJ3=Program4.o image.o

PROGRAM_4=Program4

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
