#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct node* addword(struct node* nod, char* wo); //adds word to given tree. assumes head passed in.
struct node* createchild(struct node* par, char* wo); //creates a child node with parent, 'par', passed in.
int wordcomp(char* w1, char* w2);//returns 1 if w1>w2, 0 if w1<w2, 2 if w1==w2. does not check for invalid characters, assumes a-z each time.

struct node
{
    int count;
    char* word;
    struct node *left;

    struct node *right;
    struct node *parent;
};

struct node head;



int main(int argc, char **argv)
{

    struct node* head = (struct node*)malloc(sizeof(struct node));
    head->left = NULL;
    head->right = NULL;
    head->count = 0;
    head->parent = NULL;
    head->word = '\0';



    //tests

    //test of wordcomp:
//    char* test1 = "a";
//    char* test2 = "b";
//    char* test3 = "abc";
//    char* test4 = "abb";
//    char* test5 = "abc";
//
//    printf("should display 010122: %i%i%i%i%i%i", wordcomp(test1,test2), wordcomp(test2,test1), wordcomp(test1,test3), wordcomp(test3,test1),
//           wordcomp(test3, test5),wordcomp(test1,test1));




    exit(0);
}


struct node* addword(struct node* nod, char* wo)
{

    int test = 3; //something other than 0, 1 or 2
    struct node* cptr = nod->left; //child pointer for creation of new node

    if (nod->count == 0) //handles case where head is empty
    {
        nod->word = wo;
        nod->count++;
        return nod;
    }
    while (nod != NULL)
    {
        test = wordcomp(wo,nod->word);
        if (test == 2)
        {
            nod->count++;
            return nod;
        }
        else if (test == 0)
        {
            if (nod->left == NULL)
            {
                nod->left = createchild(nod, wo);
                return nod ->left;
            }
            else
            {
                nod = nod->left;
            }
        }
        else if (test == 1)
        {
            if (nod->right == NULL)
            {
                nod->right = createchild(nod, wo);
                return nod ->right;
            }
            else
            {
                nod = nod->right;
            }
        }
        else
        {
            printf("something went wrong in addword while loop");
        }
    }

    printf("something went wrong after addword while loop (should not be possible)");
    return 0;


    cptr = (struct node*)malloc(sizeof(struct node));



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

struct node *createchild(struct node* par, char *wo) {

    struct node* nod = (struct node*)malloc(sizeof(struct node));
    nod->left = NULL;
    nod->right = NULL;
    nod->count = 1;
    nod->parent = par;
    nod->word = wo;
    return nod;
}
