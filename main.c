#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct node //not sure if this needs to be defined before functions
{
    int count;
    char* word;
    struct node *left;

    struct node *right;
    struct node *parent;
};

const int chunksize = 10;

struct node* addword(struct node* nod, char* wo); //adds word to given tree. assumes head passed in.
struct node* createchild(struct node* par, char* wo); //creates a child node with parent, 'par', passed in.
int wordcomp(char* w1, char* w2);//returns 1 if w1>w2, 0 if w1<w2, 2 if w1==w2. does not check for invalid characters, assumes a-z each time.
int readtotree(FILE* fi, struct node* nod);
void printtree(struct node *nod);





int main(int argc, char **argv)
{

    struct node* head = (struct node*)malloc(sizeof(struct node));
    head->left = NULL;
    head->right = NULL;
    head->count = 0;
    head->parent = NULL;
    head->word = '\0';

    FILE *inp;
    inp = fopen("input01.txt", "r");

    readtotree(inp,head);
    printtree(head);




    //tests

//    //test of wordcomp:
//    char* test1 = "a";
//    char* test2 = "b";
//    char* test3 = "abc";
//    char* test4 = "abb";
//    char* test5 = "abc";
//
//    printf("should display 010122: %i%i%i%i%i%i", wordcomp(test1,test2), wordcomp(test2,test1), wordcomp(test1,test3), wordcomp(test3,test1),
//           wordcomp(test3, test5),wordcomp(test1,test1));

    //tests of addword





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
                return nod->left;
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
                return nod->right;
            }
            else
            {
                nod = nod->right;
            }
        }
        else
        {
            printf("\nsomething went wrong in addword while loop when trying to add: %s.",wo);
        }
    }

    printf("\nsomething went wrong after addword while loop (should not be possible) when trying to add: %s.\",wo");
    return nod;
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

struct node *createchild(struct node* par, char *wo)
{

    struct node* nod = (struct node*)malloc(sizeof(struct node));
    nod->left = NULL;
    nod->right = NULL;
    nod->count = 1;
    nod->parent = par;
    nod->word = wo;
    return nod;
}

int readtotree(FILE *fi, struct node *nod)
{
    size_t nread;
    char* chunk[chunksize];//should read in 16 bytes at a time
    char* wo;
    char* wotest;
    char* wocat;
    int cont = 0; //used if word was not completed in chunk
    if (fi)
    {

        while ((nread = fread(chunk, 1, sizeof chunk, fi)) > 0)
        {


            if (!cont) //if we are not continuing a possible broken word
            {
                wotest = strtok (chunk," ,.-");//probably don't need all of these characters yet.. oh well
//                printf("%s",wotest);

                if (chunk[nread-1] == ' ') //if we are not going to be cutting a word off in this chunk
                {
                    printf("test1");
                    cont = 0;


                    while (wotest != NULL)
                    {
                        addword(nod, wotest);
                        wotest = strtok (NULL, " ,.-");
                    }
                }
                else //if we will be cutting off a word, we want to keep the first part of it for later
                {
                    cont = 1;


                    while (wotest != NULL)
                    {
                        wo = wotest;
                        wotest = strtok (NULL, " ,.-");
                        if (wotest != NULL)
                        {
                            addword(nod, wo);
                        }
                        //stopping here, wo will continue to hold last piece
                    }
                }
            }
            else //if we need to potentially continue a word from previous
            {
                wotest = strtok (chunk," ,.-");

                if (chunk[nread-1] == ' ')
                {
                    cont = 0;

                    if (chunk[0] == ' ') //we don't actually need to continue previous word
                    {
                        addword(nod, wo); //add wo as it is as it hasn't been added yet
                        addword(nod,wotest);

                        wotest = strtok (NULL, " ,.-");
                        while (wotest != NULL)
                        {
                            addword(nod, wotest);
                            wotest = strtok (NULL, " ,.-");
                        }
                    }
                    else
                    {
                        wocat = malloc(strlen(wo)+strlen(wotest)+1);
                        strcat(wocat,wo);
                        strcat(wocat,wotest);
                        addword(nod,wocat);

                        wotest = strtok (NULL, " ,.-");
                        while (wotest != NULL)
                        {
                            addword(nod, wotest);
                            wotest = strtok (NULL, " ,.-");
                        }
                    }
                }
                else
                {
                    cont = 1;

                    if (chunk[0] == ' ') //we don't actually need to continue previous word
                    {
                        addword(nod, wo); //add wo as it is as it hasn't been added yet
                        addword(nod, wotest);

                        wotest = strtok (NULL, " ,.-");

                        while (wotest != NULL)
                        {
                            wo = wotest;
                            wotest = strtok (NULL, " ,.-");
                            if (wotest != NULL)
                            {
                                addword(nod, wo);
                            }
                            //stopping here, wo will continue to hold last piece
                        }


                    }
                    else
                    {
                        wocat = malloc(strlen(wo)+strlen(wotest)+1);
                        strcat(wocat,wo);
                        strcat(wocat,wotest);
                        addword(nod,wocat);

                        wotest = strtok (NULL, " ,.-");

                        while (wotest != NULL)
                        {
                            wo = wotest;
                            wotest = strtok (NULL, " ,.-");
                            if (wotest != NULL)
                            {
                                addword(nod, wo);
                            }
                            //stopping here, wo will continue to hold last piece
                        }
                    }


                }

            }




        }

        if (cont == 1)
        {
            printf(wo);
            addword(nod, wo);
        }


        if (ferror(fi)) {
            printf("\nThere was an error reading in the file");
        }
        fclose(fi);




    }
    else
    {
        printf("\nFile does not exist");
    }

    return 0;
}

void printtree(struct node *nod)
{
    if (nod != NULL) {
        printtree(nod->left);
        printf(nod->word);
        printf("\n %s: %i\n", nod->word, nod->count);
        printtree(nod->right);
    }
}
