/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Winter 2024                   */
/* ImageList.c: source file for image list manipulations             */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include "ImageList.h"

/* Create a new image list */
ILIST *CreateImageList(void)
{
        ILIST *L;
        L = malloc(sizeof(ILIST));
        assert(L); // error check for malloc
        L->Length = 0;
        L->First = NULL;
        L->Last = NULL;

        return L;
}

/* Delete an image list (and all entries) */
void DeleteImageList(ILIST *list)
{
        assert(list);
        IENTRY *current = list->First;
        IENTRY *next;

        while(current != NULL){
                next = current->Next;
                if (current->image != NULL){
                        DeleteImage((Image *)current->image);
                        //DeleteYUVImage((YUVImage *)current->image);
                }
                free(current);
                current = next;
        }
        free(list);
}

/* Insert a RGB image to the image list at the end */
void AppendRGBImage(ILIST *list, Image *RGBimage)
{
        assert(list);
        assert(RGBimage);

        IENTRY *newEntry = (IENTRY *)malloc(sizeof(IENTRY));
        assert(newEntry);

        // update IENTRY
        newEntry->List = list;
        newEntry->Next = NULL;
        newEntry->Prev = list->Last;
        newEntry->image = RGBimage;

        if (list->Last){ // list with elements case
                // update ILIST
                list->Last->Next = newEntry;
                list->Last = newEntry;
        }
        else{ // empty list case
                // update ILIST
                list->First = newEntry;
                list->Last = newEntry;
        }
        list->Length++;
}

/* Insert a YUV image to the image list at the end */
void AppendYUVImage(ILIST *list, YUVImage *YUVimage)
{
        assert(list);
        assert(YUVimage);

        IENTRY *newEntry = (IENTRY *)malloc(sizeof(IENTRY));
        assert(newEntry);

        // update IENTRY
        newEntry->List = list;
        newEntry->Next = NULL;
        newEntry->Prev = list->Last;
        newEntry->image = YUVimage;

        if (list->Last){ // list with elements case
                // update ILIST
                list->Last->Next = newEntry;
                list->Last = newEntry;
        }
        else{ // empty list case
                // update ILIST
                list->First = newEntry;
                list->Last = newEntry;
        }
        list->Length++;
}

/* Crop an image list */
void CropImageList(ILIST *list, unsigned int start, unsigned int end)
{
        // check inputs
        assert(list);
        assert(start <= end);
        assert(end <= list->Length);  
    
        // temps for list traversal
        IENTRY *current = list->First;
        IENTRY *next;
        int index = 0;
    
        // traverse list and check each element
        while (current != NULL){
            next = current->Next;
    
            if (index < start || index >= end){
                if (current->Prev){
                    current->Prev->Next = current->Next;
                } 
                else {
                    list->First = current->Next;
                }
                if (current->Next){
                } 
                else{
                    list->Last = current->Prev;
                }
    
                DeleteImage((Image *)current->image);
                free(current);
                list->Length--;
            }
            current = next;
            index++;
        }
}

/* Fast forward an image list */
void FastImageList(ILIST *list, unsigned int factor)
{
        // check inputs
        assert(list);
        assert(factor <= list->Length);
        assert(factor > 0);

        // temps for list traversal
        IENTRY *current = list->First;
        IENTRY *next;
        unsigned int index = 0;

        // traverse list and check each element
        while(current != NULL){
                next = current->Next;

                // if element is not supposed to be in updated list:
                if(index % factor != 0){
                        // update pointers

                        // not the first element in a list case
                        if (current->Prev) {
                                current->Prev->Next = current->Next;
                        } 
                        // current is the first node
                        else {
                                list->First = current->Next;
                        }

                        // not the last element in a list case
                        if (current->Next) {
                                current->Next->Prev = current->Prev;
                        } 
                        // current is the last node
                        else {
                                list->Last = current->Prev;
                        }

                        // delete entry from list
                        DeleteImage((Image *)current->image);
                        free(current);
                        list->Length--;
                }
                current = next;
                index++;
        }
}

/* Reverse an image list */
void ReverseImageList(ILIST *list)
{
        // check input
        assert(list);

        // temps for list traversal and swapping
        IENTRY *current = list->First;
        IENTRY *temp = NULL;

        // traverse list and swap entry values
        while(current != NULL){
                temp = current->Next;
                current->Next = current->Prev;
                current->Prev = temp;
                current = temp;
        }

        // swap list entires
        temp = list->First;
        list->First = list->Last;
        list->Last = temp;
}

/* Insert a RGB image to the image list in the front */
void PrependRGBImage(ILIST *list, Image *RGBimage)
{
        // check inputs
        assert(list);
        assert(RGBimage);

        // new list entry 
        IENTRY *front = (IENTRY *)sizeof(IENTRY);
        assert(front);

        // set entry fields
        front->List = list;
        front->Prev = NULL;
        front->Next = list->First;
        front->image = RGBimage;

        // set list fields
        if(list->First){ // list with elements case
                list->First->Prev = front;
                list->First = front;
        }
        else { // list with no elements case
                list->First = front;
                list->Last = front;
        }       
        list->Length++;
}

/* EOF */
