#######################################################################
# Homework Assignment 5, for EECS 22, Winter 2024
#
# Initial author: Tim Schmidt
#
# Makefile: Makefile for HW 5
#
#######################################################################

FLAGS = -Wall -std=c11
OBJ = Movie.o ImageList.o Image.o DIPs.o FileIO.o MovieLab.o

######################### Generate object files #######################
# Target for MovieLab.o
MovieLab.o: FileIO.h DIPs.h Movie.h Constants.h Image.h ImageList.h MovieLab.c
	gcc -c MovieLab.c $(FLAGS)
# Target for FileIO.o
FileIO.o: Constants.h FileIO.h Image.h FileIO.c 
	gcc -c FileIO.c $(FLAGS)	
# Target for DIPs.o
DIPs.o: DIPs.h Constants.h string.h math.h Image.h DIPs.c
	gcc -c DIPs.c $(FLAGS)
# Target for Image.o
Image.o: Image.h Image.c
	gcc -c Image.c $(FLAGS)
# Target for ImageList.o
ImageList.o: ImageList.h Image.h ImageList.c
	gcc -c ImageList.c $(FLAGS)
# Target for Movie.o
Movie.o: Movie.h ImageList.h Image.h Movie.c
	gcc -c Movie.c $(FLAGS)

######################### Generate the executable #####################
# Target for MovieLab
MovieLab: $(OBJ) 
	gcc $(OBJ) $(FLAGS) -lm -o MovieLab

###############################  others  ##############################
# Target for clean-up
clean:
	rm -f MovieLab out.yuv $(OBJ) 

# Target for all

all: MovieLab
