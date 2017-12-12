//
//  main.c
//  FinalSuffixTree
//
//  Created by Bakhtawar Noor on 19/04/2017.
//  Copyright � 2017 Bakhtawar Noor. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<math.h>



//structures

typedef struct node {
    struct node *siblings, *children;
    int index;
    int beg;
    int end;
    int beg_interval;
    int end_interval;
} node;
/*
typedef struct node1
{
    struct node1 *next;
    int index_i;
    int len_dv;
} node1;

node1 *start = NULL;
*/

// global variables


int** minus_dv;

int** plus_dv;

char* inputString; //= {'m','i','s','s','i','s','s','i','p','p','i','$'};

node *root = NULL;

int size_of_string;


int index_substring;
char subSource[30];

//int myCounter = 0;
int mySuffixLengthSoFar = 0;
int myLength = 0;

int counterForNode = 0;
int start_index = 0;
int dfo;
int* look_up;
int branching = 0;
int non_branching = 0;
int count_per_lvl = 0;






int ctrl = 0;

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
                  // ,current_node->children->index, current_node->children->beg, current_node->children->end );
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

            else if(size_head > ((current_node->end - current_node->beg) + 1))
            {   //printf("TRUE TRUE TRUE TRUE TRUE TRUE\n");
                //current_node->siblings = add_on_tree(current_node->children->siblings, new_begin+((current_node->end - current_node->beg) + 1), new_end);
                //printf("Updating. Size of the head > node. we are at (%d,%d,%d)\n",current_node->index, current_node->beg, current_node->end);
                newChild = make_node(current_node->index, current_node->end + 1, new_end);

                //newChild->children = current_node->children;
                newChild->siblings = make_node(index_substring, new_begin + size_head, new_end);

                //printf("the child after updating is (%d,%d, %d)\n",newChild->index, newChild->beg, newChild->end);
                //current_node->end = current_node->beg + size_head -1;
                current_node ->children->siblings = newChild;
                //printf("the sibling after updating is (%d,%d, %d)\n",newChild->siblings->index, newChild->siblings->beg, newChild->siblings->end);
                //printf("the papa after updating is (%d,%d, %d)\n",current_node->index, current_node->beg, current_node->end);
                current_node->index=-1;
                //return current_node;*/
                return current_node;

            }

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
                        if(size_head > ((current_node->end - current_node->beg) + 1)){

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
                        }

                        else if (size_head == ((current_node->end - current_node->beg) + 1)){
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
            /////////////////////////////////////////////////////////////////////////////////////////////////////
            /* flag = checkNextLevel(current_node->children, new_begin, new_end);

             if(flag == 1)
             {
             printf("go to the child. we are at (%d,%d,%d)\n",current_node->index, current_node->beg, current_node->end);

             current_node->children = add_on_tree(current_node->children, new_begin + size_head, new_end);
             return current_node;
             }
             else if(flag == 0)
             {

             if (new_begin +1 != size_of_string) {
             printf("Updating. we are at (%d,%d,%d)\n",current_node->index, current_node->beg, current_node->end);
             newChild = make_node(current_node->index, current_node->beg + size_head, current_node->end);

             newChild->children = current_node->children;
             newChild->siblings = make_node(index_substring, new_begin + size_head, new_end);

             printf("the child after updating is (%d,%d, %d)\n",newChild->index, newChild->beg, newChild->end);
             current_node->end = current_node->beg + size_head -1;
             current_node ->children = newChild;
             printf("the simbling after updating is (%d,%d, %d)\n",newChild->siblings->index, newChild->siblings->beg, newChild->siblings->end);
             printf("the papa after updating is (%d,%d, %d)\n",current_node->index, current_node->beg, current_node->end);

             return current_node;
             }
             else{
             current_node->children = add_on_tree(current_node->children, new_begin + size_head, new_end);
             return current_node;
             }



             }*/
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
}


int traversingSibling(node* root)
{

    int a = -2;

    if(root != NULL)
    {
        if(root->siblings != NULL)
        {
            a = traversingSibling(root->siblings);
        }
        else
            a = root->end_interval;
    }


    return a;

}

void pre_order_traversal(node* root) {




    if(root != NULL) {

        pre_order_traversal(root->children);






        if( root->children ==NULL) //root->index  != -1)
        {
            //printf("the suffix start in: %d in node: (%d,%d)\n", root->index, root->beg, root->end);
            root->beg_interval = dfo;
            root->end_interval = dfo;
            look_up[dfo] = root->index;
            dfo++;
        }
        else
        {
            root->beg_interval = root->children->beg_interval;
            root->end_interval = traversingSibling(root->children);;

        }

        pre_order_traversal(root->siblings);


    }
}

node* getLargestLL(node* nd, node* large)
{
    int max2 = 0;
    int max = large->end_interval - large->beg_interval;


    if(nd->siblings != NULL)
        max2 = nd->siblings->end_interval - nd->siblings->beg_interval;


    if(max2 > max)
        large=nd->siblings;


    if (nd->siblings) {
        large = getLargestLL(nd->siblings,large);
    }



    return large;




}

int check_realLand(int real_j, int beg, int end)
{
    int flag = 0;
    
    for(int i=beg;i<=end;i++)
    {
        if(look_up[i] == real_j)
        {
            flag = 1;
        }
    }
    return flag;
}

void traversingTest2(node* nd, int beg_j, int end_j,int big_beg,int big_end,int dv)
{
    int patrol;
    
    if(nd->siblings != NULL && nd->index == -2)
    {
        traversingTest2(nd->siblings,beg_j,end_j,big_beg,big_end,dv);
    }
    else
    {
        int beg_i = nd->beg_interval;
        int end_i = nd->end_interval;
        int real_i, real_j;
        
        for(int i=beg_i;i<=end_i;i++)
        {
            
            real_i = look_up[i];
            real_j = real_i + dv;
            
            //int look_up_j = look_up[real_j];
            
            patrol = check_realLand(real_j, beg_j, end_j);
            
            if(patrol == 1)
            {
                if(inputString[real_i] != inputString[real_i + 2*dv])
                {
                    //if(plus_dv[real_i][real_i + 2*dv] == 0)
                    //{
                    printf("Branching\n");
                    printf("(i,d(v),2) (%d,%d,%d)\n" ,(real_i),dv,2);
                    branching++;
                    //plus_dv[real_i][real_i + 2*dv] = 1;
                    if(inputString[real_i-1] == inputString[real_i + 2*dv - 1])
                    {
                        int non_branch_i = real_i;
                        //if(plus_dv[real_i-1][real_i + 2*dv-1] == 0)
                        //{
                        printf("nonBranching\n");
                        non_branching++;
                        non_branch_i--;
                        //plus_dv[real_i-1][real_i + 2*dv-1] = 1;
                        printf("(i,d(v),2) (%d,%d,%d)\n" ,(real_i-1),dv,2);
                        //}
                        while(inputString[non_branch_i-1] == inputString[non_branch_i + 2*dv - 1])
                        {
                            if(non_branch_i > 0)
                            {
                                //if(plus_dv[non_branch_i -1][non_branch_i + 2*dv-1] == 0)
                                //{
                                printf("nonBranching\n");
                                non_branching++;
                                // plus_dv[non_branch_i -1][non_branch_i + 2*dv -1] = 1;
                                printf("(i,d(v),2) (%d,%d,%d)\n" ,(non_branch_i-1),dv,2);
                                //continue;
                                //}
                                non_branch_i--;
                            }
                            else
                            {
                                break;
                            }
                        }
                        
                    }
                    //}
                }
                
            } // end of outer most if.
            
            
        } // end of for loop
        
        
        for(int i=big_beg;i<=big_end;i++)
        {
            real_i = look_up[i];
            real_j = real_i - dv;
            
            //int look_up_j = look_up[i];
            
            patrol = check_realLand(real_j,big_beg,big_end);
            
            if(patrol == 1)
            {
                //if(plus_dv[real_i][real_i + 2*dv] == 0)
                // {
                printf("Branching\n");
                branching++;
                plus_dv[real_i][real_i + 2*dv] = 1;
                printf("(i,d(v),2) (%d,%d,%d)\n" ,(real_i),dv,2);
                if(inputString[real_i - 1] == inputString[real_i + 2*dv - 1])
                {
                    int non_branch_i = real_i;
                    //if(plus_dv[real_i-1][real_i + 2*dv-1] == 0)
                    //{
                    printf("nonBranching\n");
                    non_branching++;
                    non_branch_i--;
                    //plus_dv[real_i-1][real_i + 2*dv-1] = 1;
                    printf("(i,d(v),2) (%d,%d,%d)\n" ,(real_i-1),dv,2);
                    //}
                    while(inputString[non_branch_i -1] == inputString[non_branch_i + 2*dv - 1])
                    {
                        if(non_branch_i > 0)
                        {
                            //if(plus_dv[non_branch_i -1][non_branch_i + 2*dv-1] == 0)
                            //{
                            printf("nonBranching\n");
                            non_branching++;
                            // plus_dv[non_branch_i -1][non_branch_i + 2*dv -1] = 1;
                            printf("(i,d(v),2) (%d,%d,%d)\n" ,(non_branch_i-1),dv,2);
                            //continue;
                            //}
                            non_branch_i--;
                        }
                        else
                        {
                            break;
                        }
                    }
                    
                }
                //   }
            }
            
            
        }
        
        if(nd->siblings != NULL)
            traversingTest2(nd->siblings,beg_j,end_j,big_beg,big_end,dv);
        
    }
}



void traversing(node* nd, int beg_j, int end_j, int dv){

    int i,j;

    if(nd->siblings != NULL && nd->index == -2)
    {
        traversing(nd->siblings,beg_j,end_j,dv);
    }

//////////////////////////////////////////
    else{


        int beg_i = nd->beg_interval;
        int end_i = nd->end_interval;
        int real_i, real_j;

       for(i=beg_i;i<=end_i;i++)
       {
            for(j=beg_j;j<=end_j;j++)
            {
                    real_i = look_up[i];
                    real_j = look_up[j];
                    if(real_j == real_i + dv)
                    {
                        if(inputString[real_i] != inputString[real_i + 2*dv])
                        {
                            if(plus_dv[real_i][real_i + 2*dv] == 0)
                            {
                                printf("branching\t");
                                printf("(%d,%d,%d)\n" ,(real_i),dv,2);
                                branching++;
                                plus_dv[real_i][real_i + 2*dv] = 1;
                            }
                            if(inputString[real_i - 1] == inputString[real_i + 2*dv - 1])
                            {
                                int non_branch_i = real_i;
                                if(plus_dv[real_i-1][real_i + 2*dv-1] == 0){
                                    non_branching++;
                                    non_branch_i--;
                                    printf("non-branching\t");
                                    printf("(%d,%d,%d)\n" ,(real_i-1),dv,2);
                                    plus_dv[real_i-1][real_i + 2*dv-1] = 1;

                                }

                                while(inputString[non_branch_i - 1] == inputString[non_branch_i + 2*dv -1])
                                {
                                    if(non_branch_i >= 0)
                                    {
                                        if(plus_dv[non_branch_i -1][non_branch_i + 2*dv-1] == 0)
                                        {
                                            non_branching++;

                                            printf("non-branching\t");
                                            printf("(%d,%d,%d)\n" ,(non_branch_i-1),dv,2);


                                            plus_dv[non_branch_i -1][non_branch_i + 2*dv -1] = 1;

                                        }
                                        non_branch_i--;
                                    }
                                }
                            }
                        } // end of if-statement (for checking if its branching)


                    } // end of if -statement (for real_j = real_i + dv)
             //   } // end of if -statement for (plus_dv[i][j] == 0)

            }// end of inner for loop

        } // end of outer for loop

        for(j = beg_i;j<=end_i;j++)
        {
            for(i=beg_j;i<=end_j;i++)
            {

                    real_i = look_up[i];
                    real_j = look_up[j];
                    if(real_i == real_j - dv)
                    {
                        if(inputString[real_i] != inputString[real_i + 2*dv])
                        {
                            if(plus_dv[real_i][real_i + 2*dv] == 0)
                            {
                                printf("branching\t");
                                printf("(%d,%d,%d)\n" ,(real_i),dv,2);
                                branching++;
                                plus_dv[real_i][real_i + 2*dv] = 1;

                            }

                            if(inputString[real_i - 1] == inputString[real_i + 2*dv - 1])
                            {
                                int non_branch_i = real_i;
                                if(plus_dv[real_i-1][real_i + 2*dv -1]==0){
                                    printf("non-branching\t");
                                    printf("(%d,%d,%d)\n" ,(real_i-1),dv,2);
                                    plus_dv[real_i - 1][real_i + 2*dv -1] = 1;
                                    non_branching++;
                                    non_branch_i--;

                                }

                                while(inputString[non_branch_i - 1] == inputString[non_branch_i + 2*dv -1])
                                {
                                    if(non_branch_i >= 0)
                                    {
                                        if(plus_dv[non_branch_i -1][non_branch_i + 2*dv -1] ==0)
                                        {
                                            printf("non-branching\t");
                                            printf("(%d,%d,%d)\n" ,(non_branch_i-1),dv,2);
                                            non_branching++;

                                            plus_dv[non_branch_i -1][non_branch_i + 2*dv -1] = 1;

                                        }
                                    non_branch_i--;


                                    }
                                }

                            }
                        } // end of if-statement (checing for branching)

                    } // end of if-statement(real_i == real_j - dv)

////////////////////////////////////////////////////////////////////////////////////////////
            } // end of inner for loop
        } // end of outer for loop


        if(nd->siblings != NULL)
            traversing(nd->siblings,beg_j,end_j,dv);
        /////////////////////////////////////
    } // end of else statement
    //////////////////////////////////////////////////////////////////////////////////////

}



int stoyeAndGusfield(node* root, int dv)
{

    node* large = (node*)malloc(sizeof(node));
    int current_size = root->end - root->beg + 1;


    if(root->beg== -1){

        large = root->children;
        large = getLargestLL(root->children, large);
        large->index = -2;
        traversing(root->children, root->beg_interval, root->end_interval, 0);
        root->index = -3;
        large->index = -1;
        stoyeAndGusfield(root->children,0);



    }
    else{

            if(root->index == -3 && root->siblings != NULL){
                stoyeAndGusfield(root->siblings,dv);
                return 1;

            }
            else{

                if(root->children != NULL && root->index <= -1)
                {
                    large = root->children;
                    large = getLargestLL(root->children, large);


                        large->index = -2;

                    traversing(root->children,root->beg_interval,root->end_interval,dv + current_size);

                    root->index = -3;
                    if(large->beg_interval != large->end_interval)
                        large->index = -1;


                    count_per_lvl = 0;
                    stoyeAndGusfield(root->children,dv + current_size);
                }





            }








            if(root->siblings != NULL)
                stoyeAndGusfield(root->siblings,dv);

    }





    free(large);

    return 1;

}




int patternMatching(int beg, int end, char* substring)
{
    int myBeg = 0;
    int myCounter = 0;
    int activeLength = 0;

    int i;
    for(i=mySuffixLengthSoFar;i<strlen(substring);i++)
    {
        if(myBeg <= ((end-beg)))
        {
            int temp = beg + myBeg;
            if(substring[i] == inputString[temp])
            {
                myCounter++;
                myBeg++;
                mySuffixLengthSoFar++;
                printf("Input String %c\n",inputString[temp]);
                printf("Substring %c\n",substring[i]);
                myLength = myCounter;
                //activeLength++;
                //break;
            }
            else{
                myLength = myCounter;
                myCounter = 0;
                //activeLength = 1;
                printf("My Matches for this node %d\n", myLength);
                if(temp<= end)
                    myLength = 0;
                break;
            }
        }
        else{
            myLength = myCounter;
            break;
        }
    }

    printf("My suffix length so far : %d\n",mySuffixLengthSoFar);
    return activeLength;

}




int patternMatching2(int beg,int end, char* substring, int start_index, int end_index)
{

    int match = 0;
    int i=0;
    int index=beg;

    while ((start_index+i< strlen(substring)) && start_index+i<end_index){
        printf("substring i: %c\n ", substring[i+start_index]);
        printf("inputstring i: %c\n ", inputString[index]);

        if(substring[start_index+i] == inputString[index])
        {
            match++;
            printf("Substring index: %d match= %d \n ", i+start_index, match);
        }
        else{

            match = -1;
            break;
        }
        index++;
        i++;

    }


    printf("%d\n", match);
    printf("out of while\n");


    return match;
}




int main(int argc, const char * argv[]) {

    clock_t begin, end;
    // insert code here...
    FILE *fptr;
    char inputFile[50];
    int i = 0;
    char temp;

    strcpy(inputFile,argv[1]);
    fptr = fopen(inputFile,"r+");

    if (fptr == NULL)
    {
        printf("No such file found");
        return 1;
    }


    inputString = (char*)malloc((1+i)*sizeof(char));


    do {
        temp = fgetc(fptr);
        inputString[i] = temp;
        i++;
        inputString = (char*)realloc(inputString, (i+1)*sizeof(char));
    } while (!feof(fptr));


    root = initialize();


    inputString[i-1] = '$';
    size_of_string = i-1;
    create_tree(inputString, i);




    look_up = (int*) malloc(sizeof(int)*size_of_string);
    dfo = 0;
    pre_order_traversal(root);
    node* large;






    plus_dv = (int**)calloc(dfo,sizeof(int*));


    for(i = 0; i<=dfo; i++)
    {
        plus_dv[i] = (int *)calloc(dfo,sizeof(int));
    }

    begin = clock();
    int num = stoyeAndGusfield(root->children, 0);
    end = clock();

    double total = (double)(end-begin)/CLOCKS_PER_SEC;

    printf("log-number %f\n",  total);
    printf("size of the string: %d\n", size_of_string);
    printf("Non-branching : (%d)\n", non_branching);
    printf("Branching : (%d)\n", branching);



    return 0;
}

