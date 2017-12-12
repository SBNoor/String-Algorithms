
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>




//structures

typedef struct node {
    struct node *siblings, *children;
    int index;
    int beg;
    int end;
} node;


// global variables

char inputString[30001]; //= {'m','i','s','s','i','s','s','i','p','p','i','$'};

node *root = NULL;

int size_of_string;


int index_substring;
char subSource[30];

//int myCounter = 0;
int mySuffixLengthSoFar = 0;
int myLength = 0;

int counterForNode = 0;
int start_index = 0;

//char* inputString = 0;

//typedefs
node *make_node(int index, int beg, int end) {
    node *new_node = (node*)malloc(sizeof(node));
    new_node->siblings = NULL;
    new_node->children = NULL;
    new_node->index = index;
    new_node->beg = beg;
    new_node->end = end;
    return new_node;
}

int numberMatches(node* node, int beg, int end)
{
    int counter = 0;
    int ctrl = 0;



    int i;
    for(i= node->beg; i <= node->end; i++)
    {

        if(inputString[i] == inputString[beg + ctrl])
        {
            counter++;
            ctrl++;
        }
        else
            break;

    }



    //printf("number of matches: %d\n", counter);


    return counter;



}



int checkNextLevel(node* check, int beg, int end)
{
    int matches= numberMatches(check, beg, end);

    if(check->siblings == NULL)
        return 0;


    else if(matches == 0)
    {
        return checkNextLevel(check->siblings, beg, end);
    }

    else if(matches > 0)
        return 1;

    return 0;

}


node* create_chid(node* current_node, int new_beg, int new_end, int sizeHead){

    node *child= make_node(current_node->index, current_node->end + 1, new_end);

    //printf("the child is (%d,%d, %d)\n", child->index,child->beg, child->end);

    child->siblings = make_node(index_substring, new_beg + sizeHead, new_end);
    //printf("the sibling to the child is (%d,%d, %d)\n", child->siblings->index,child->siblings->beg, child->siblings->end);

    return child;



}

node *break_edge(node *dist, int length ){

    int i = dist->beg;
    int j = i + length;
    int k = j + 1;
    node *new_node = make_node(i,k,dist->end);

    k = dist -> end;
    return new_node;

}

node* add_on_tree(node* current_node, int new_begin, int new_end)
{
    int size_head = numberMatches(current_node, new_begin, new_end);
    int flag;
    node *newChild;


    if(current_node->beg == -1){
            if(current_node->children == NULL)
            {
                current_node->children = make_node(index_substring,new_begin, new_end);
                //printf("Adding child to the root. we are at (%d,%d,%d)\n",current_node->children->index, new_begin, new_end);
                return current_node;
            }
            else
            {
                //printf("root. we are at (%d,%d,%d)\n", current_node->index, current_node->beg, current_node->end);
                current_node->children = add_on_tree(current_node->children, new_begin, new_end);
                return current_node;
            }

    }
    else if(new_begin == size_of_string && new_end == size_of_string){

        if(current_node->beg == new_begin && current_node->end == new_end){
            return current_node;
        }

        else if(current_node->siblings == NULL){
            current_node->siblings = make_node(index_substring, new_begin, new_end);
            //printf("sibling in (%d,%d), the new_node is: (%d,%d, %d)\n", current_node->beg, current_node->end,current_node->siblings->index,new_begin, new_end);
            return current_node;
        }
        else{
            //printf("go to next sibling. we are at (%d,%d,%d)\n",current_node->index, current_node->beg, current_node->end);
            current_node->siblings =add_on_tree(current_node->siblings, new_begin, new_end);
            return current_node;
        }
    }
    else if(size_head == 0){
        if(current_node->siblings == NULL){
            current_node->siblings = make_node(index_substring, new_begin, new_end);
            //printf("sibling in (%d,%d), the new_node is: (%d,%d, %d)\n", current_node->beg, current_node->end, current_node->siblings->index,new_begin, new_end);
            return current_node;
        }
        else{
            //printf("go to next sibling. we are at (%d,%d,%d)\n",current_node->index, current_node->beg, current_node->end);
            current_node->siblings =add_on_tree(current_node->siblings, new_begin, new_end);
            return current_node;
        }
    }
    else if (size_head > 0)
    {
        if (current_node->children == NULL) {
            current_node->end = current_node->beg + size_head -1;
            //printf("create a child. we are at (%d,%d,%d)\n",current_node->index, current_node->beg, current_node->end);
            current_node->children = create_chid(current_node, new_begin, new_end, size_head);
            current_node->index=-1;
            //printf("child created. the parent is (%d,%d,%d), the child is (%d,%d,%d) \n",current_node->index, current_node->beg, current_node->end
            //       ,current_node->children->index, current_node->children->beg, current_node->children->end );
            return current_node;
        }
        else{
            if(size_head < ((current_node->end - current_node->beg) + 1))
            {
                //printf("Updating. Size of the head < node. we are at (%d,%d,%d)\n",current_node->index, current_node->beg, current_node->end);
                newChild = make_node(current_node->index, current_node->beg + size_head, current_node->end);

                newChild->children = current_node->children;
                newChild->siblings = make_node(index_substring, new_begin + size_head, new_end);

                //printf("the child after updating is (%d,%d, %d)\n",newChild->index, newChild->beg, newChild->end);
                current_node->end = current_node->beg + size_head -1;
                current_node ->children = newChild;
                //printf("the sibling after updating is (%d,%d, %d)\n",newChild->siblings->index, newChild->siblings->beg, newChild->siblings->end);
                //printf("the papa after updating is (%d,%d, %d)\n",current_node->index, current_node->beg, current_node->end);

                return current_node;

            }
            else if (size_head == ((current_node->end - current_node->beg) + 1)){
                current_node->children = add_on_tree(current_node->children, new_begin+size_head, new_end);
                //printf()
                return current_node;


            }

            /*else if(size_head > ((current_node->end - current_node->beg) + 1))
                {   printf("TRUE TRUE TRUE TRUE TRUE TRUE\n");
                    //current_node->siblings = add_on_tree(current_node->children->siblings, new_begin+((current_node->end - current_node->beg) + 1), new_end);
                    printf("Updating. Size of the head > node. we are at (%d,%d,%d)\n",current_node->index, current_node->beg, current_node->end);
                    newChild = make_node(current_node->index, current_node->end + 1, new_end);

                    //newChild->children = current_node->children;
                    newChild->siblings = make_node(index_substring, new_begin + size_head, new_end);

                    //printf("the child after updating is (%d,%d, %d)\n",newChild->index, newChild->beg, newChild->end);
                    //current_node->end = current_node->beg + size_head -1;
                    current_node ->children->siblings = newChild;
                    //printf("the sibling after updating is (%d,%d, %d)\n",newChild->siblings->index, newChild->siblings->beg, newChild->siblings->end);
                    //printf("the papa after updating is (%d,%d, %d)\n",current_node->index, current_node->beg, current_node->end);
                    current_node->index=-1;
                    //return current_node;
                    return current_node;

                }*/

                else {

                    flag = checkNextLevel(current_node->children, new_begin, new_end);

                    if(flag == 1)
                    {
                        //printf("go to the child. we are at (%d,%d,%d)\n",current_node->index, current_node->beg, current_node->end);

                        current_node->children = add_on_tree(current_node->children, new_begin + size_head, new_end);
                        return current_node;
                    }


                    else if(flag == 0)
                    {

                        if (new_begin +1 != size_of_string) {
                            /*if(size_head > ((current_node->end - current_node->beg) + 1)){
                                printf("TRUE TRUE TRUE TRUE TRUE TRUE\n");
                                //printf("Updating. Size of the head > node. we are at (%d,%d,%d)\n",current_node->index, current_node->beg, current_node->end);
                                newChild = make_node(current_node->index, current_node->end + 1, new_end);

                                //newChild->children = current_node->children;
                                newChild->siblings = make_node(index_substring, new_begin + size_head, new_end);

                                //printf("the child after updating is (%d,%d, %d)\n",newChild->index, newChild->beg, newChild->end);
                                //current_node->end = current_node->beg + size_head -1;
                                current_node ->children->siblings = newChild;
                                current_node->index=-1;
                                //printf("the sibling after updating is (%d,%d, %d)\n",newChild->siblings->index, newChild->siblings->beg, newChild->siblings->end);
                                //printf("the papa after updating is (%d,%d, %d)\n",current_node->index, current_node->beg, current_node->end);

                                //current_node->end=new_begin
                                //current_node->siblings = add_on_tree(current_node->children->siblings, new_begin+((current_node->end - current_node->beg) + 1), new_end);
                                //return current_node;

                                return current_node;
                            }*/

                             if (size_head == ((current_node->end - current_node->beg) + 1)){
                                current_node->children = add_on_tree(current_node->children, new_begin+size_head, new_end);
                                return current_node;


                                }

                               else{
                                   //printf("Updating. Did not find the kids. we are at (%d,%d,%d)\n",current_node->index, current_node->beg, current_node->end);
                                   newChild = make_node(current_node->index, current_node->beg + size_head, current_node->end);

                                   newChild->children = current_node->children;
                                   newChild->siblings = make_node(index_substring, new_begin + size_head, new_end);

                                   //printf("the child after updating is (%d,%d, %d)\n",newChild->index, newChild->beg, newChild->end);
                                   current_node->end = current_node->beg + size_head -1;
                                   current_node ->children = newChild;
                                   //printf("the sibling of after updating is (%d,%d, %d)\n",newChild->siblings->index, newChild->siblings->beg, newChild->siblings->end);
                                   //printf("the papa after updating is (%d,%d, %d)\n",current_node->index, current_node->beg, current_node->end);

                                   return current_node;
                               }
                            }
                            else{
                            current_node->children = add_on_tree(current_node->children, new_begin + size_head, new_end);
                            return current_node;
                    }



                }

            }

        }

    }



    return current_node;

}





node* initialize(){
    node* initNode = make_node(-1, -1, -1);

    return initNode;
}



void create_tree(char* var, int size)
{
    int max = size;
    int min, i,k;
    char substring[strlen(inputString)];

    clock_t begin, end;
    begin=clock();
    for(min = 0; min < max; min++){


        k=0;

        for(i = min; i < max; i++){
            substring[k] = var[i];
            k++;
        }
        substring[k] = '\0';
        //printf("%s\n", substring);
        index_substring=min;
    //    printf("index of the substring : %d\n",index_substring);

        root = add_on_tree(root, min, max-1);
    }



        end = clock();
        printf("the running time to build is: %lf \n", (double)(end - begin)/CLOCKS_PER_SEC);
}


void pre_order_traversal(node* root) {
    if(root != NULL) {


        if( root->children ==NULL) //root->index  != -1)
        {
            printf("%d ", root->index+1);
        }

        pre_order_traversal(root->siblings);
        pre_order_traversal(root->children);
    }
}






int patternMatching2(int beg,int end, char* substring, int start_index, int end_index)
{

    int match = 0;
    int i=0;
    int index=beg;

    while ((start_index+i< strlen(substring)) && start_index+i<end_index){
        //printf("substring i: %c\n ", substring[i+start_index]);
        //printf("inputstring i: %c\n ", inputString[index]);

        if(substring[start_index+i] == inputString[index])
        {
            match++;
            //printf("Substring index: %d match= %d \n ", i+start_index, match);
        }
        else{

            match = -1;
            break;
        }
        index++;
        i++;

    }


    //printf("%d\n", match);
    //printf("out of while\n");


    return match;
}

void search_tree2(node* node, char* source)
{
    //printf("Current node (%d,%d)\n", node->beg,node->end);
    int size_head = node->end - node->beg + 1; //size of the hEAD
    //printf("size_head %d\n", size_head);

    int end_index = start_index + size_head; //comeco do loop mto loko
    //printf("start_index %d\n", start_index);
    int match;
    //printf("end_index %d\n", end_index);
    //printf("size of the substring %ld\n",strlen(source));

    if(node->beg == -1)
    {
        search_tree2(node->children, source);
    }
    else {
        match = patternMatching2(node->beg, node->end, source, start_index,end_index);

        if(match > 0 )
        {
            start_index = start_index + size_head;
            //printf("start = %d\n", start_index);

            if (match==strlen(source) || start_index==strlen(source)){
                if(node->index == -1)
                {
                    pre_order_traversal(node->children);
                }
                else{
                    printf("%d ",node->index+1);
                }


            }else{
                if (node->children!=NULL && start_index <= strlen(source) ){
                        //printf("I am moving towards the child\n");
                        search_tree2(node->children, source);
                }else{
                    if(node->index == -1)
                    {
                        pre_order_traversal(node->children);
                    }
                    else{
                        printf("%d ",node->index+1);
                        }
                }
            }
        }
        else if(match == -1)
        {
            if(node->siblings == NULL ){
                printf("nao eh brinquedo nao, not a suffix/substring\n");
                }
                else if(node->siblings != NULL){
                    //printf("I am moving towards the sibling\n");
                    search_tree2(node->siblings, source);
                }
        }
    }





}




int main(int argc, const char * argv[]) {
    // insert code here...
    FILE *fptr;


    int i = 0;
    char temp;
    fptr = fopen(argv[1],"r+");

        if (fptr == NULL)
     {
     printf("No such file found");
     return 1;
     }



     do {
     temp = fgetc(fptr);
     inputString[i] = temp;
     i++;
     } while (!feof(fptr) && i < 30000);




    root = initialize();

    inputString[i-1] = '$';
    size_of_string = i-1;

    create_tree(inputString, i);


    clock_t begin, end;
    char substring[30];
    strcpy(substring, argv[2]);
    //search_tree1(root, substring);
    begin = clock();
    search_tree2(root, substring);
    end = clock();
    printf("\nthe running time to search is: %lf \n", ((double)(end - begin)/CLOCKS_PER_SEC)/1000);
    //printf(" int %ld\n", sizeof(int));
    //printf(" node %ld\n", sizeof(node));
    //printf(" node pointer  %ld\n", sizeof(node*));
    return 0;
}
