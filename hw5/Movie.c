/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Winter 2024                   */
/* Movie.c: source file for basic movie manipulations                */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include "Movie.h"

/*
typedef struct {
        ILIST *Frames; // Pointer to the frame list
} Movie;
*/


/* Allocate the memory space for the movie and the memory space */
/* for the frame list. Return the pointer to the movie. */
Movie *CreateMovie(void)
{
        Movie *M;
        M = (Movie *)malloc(sizeof(Movie));
        assert(M); // error check for malloc

        M->Frames = CreateImageList();
        assert(M->Frames);

        return M;  
}

/* Release the memory space for the frame list. */
/* Release the memory space for the movie. */
void DeleteMovie(Movie *movie)
{
        assert(movie);
        if (movie->Frames){
                DeleteImageList(movie->Frames); 
        }
        free(movie);
}

/* Convert a YUV movie to a RGB movie */
void YUV2RGBMovie(Movie *movie)
{
        assert(movie);
        IENTRY *current = movie->Frames->First;

        while(current != NULL){

                YUVImage *YUVcurrent = (YUVImage *)current->image;
                Image *newImageRGB = CreateImage(ImageWidth(YUVcurrent), ImageHeight(YUVcurrent));

                for(int j = 0; j < ImageHeight(YUVcurrent); j++){
                        for(int i = 0; i < ImageWidth(YUVcurrent); i++){
                                int Y = GetPixelY(YUVcurrent, i, j);
                                int U = GetPixelU(YUVcurrent, i, j);
                                int V = GetPixelV(YUVcurrent, i, j);

                                int C = Y - 16;
                                int D = U - 128;
                                int E = V - 128;
                
                                int R = clip((298 * C + 409 * E + 128) >> 8);
                                int G = clip((298 * C- 100 * D - 208 * E + 128) >> 8);
                                int B = clip((298 * C + 516 * D + 128) >> 8);
                
                                SetPixelR(newImageRGB, i, j, (unsigned char)R);
                                SetPixelG(newImageRGB, i, j, (unsigned char)G);
                                SetPixelB(newImageRGB, i, j, (unsigned char)B);
                        }
                }
                DeleteYUVImage(YUVcurrent);
                current->image = newImageRGB;
                current = current->Next;
        }
}

/* Convert a RGB movie to a YUV movie */
void RGB2YUVMovie(Movie *movie)
{
        assert(movie);
        IENTRY *current = movie->Frames->First;

        while(current != NULL){

                Image *RGBcurrent = (Image *)current->image;
                YUVImage *newImageYUV = CreateYUVImage(ImageWidth(RGBcurrent), ImageHeight(RGBcurrent));

                for(int j = 0; j < ImageHeight(RGBcurrent); j++){
                        for(int i = 0; i < ImageWidth(RGBcurrent); i++){
                                int R = GetPixelR(RGBcurrent, i, j);
                                int G = GetPixelG(RGBcurrent, i, j);
                                int B = GetPixelB(RGBcurrent, i, j);

                                int Y = clip(((66 * R + 129 * G + 25 * B + 128) >> 8) + 16);
                                int U = clip(((-38 * R- 74 * G + 112 * B + 128) >> 8) + 128);
                                int V = clip(((112 * R- 94 * G- 18 * B + 128) >> 8) + 128);
                
                                SetPixelY(newImageYUV, i, j, (unsigned char)Y);
                                SetPixelU(newImageYUV, i, j, (unsigned char)U);
                                SetPixelV(newImageYUV, i, j, (unsigned char)V);
                        }
                }
                DeleteImage(RGBcurrent);
                current->image = newImageYUV;
                current = current->Next;
        }
}

/* EOF */
