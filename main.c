#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int add(char* wo);


int wordcomp(char* w1, char* w2);
//returns 1 if w1>=w2, 0 if w1<w2, 2 if w1==w2. does not check for invalid characters, assumes a-z each time.

struct node
{
    int count;
    char* word;
    struct node *left;

    struct node *right;
    struct node *parent;
};

struct node head;



int main(int argc, char **argv) {

    head.left = 0;
    head.right = 0;
    head.count = 0;
    head.parent = 0;
    head.word = '\0';








    exit(0);
}


int add(char* wo)
{

    struct node* ptr = &head;
    struct node* cptr; //child pointer for creation of new node

    if (ptr->count == 0)
    {
        ptr->word = wo;
        ptr->count++;
    }
    else
    {
        ptr = (struct node*)malloc(sizeof(struct node));







    }

    int wordcomp(char* w1, char* w2)
    {
        int i = 0;
        int result = 0;
        while ((w1[i] != '\0') &&  (w2[i] != '\0'))
        {
            if (w1[i]>w2[i])
            {
                return 1;
            }
            else if (w1[i]<w2[i])
            {
                return 0;
            }
            else
            {
                i++;
            }
        }

        if ((w1[i] == '\0') &&  (w2[i] == '\0')) //if
        {
            return 2;
        }
        else if (w1[i] == '\0')
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    ;

};