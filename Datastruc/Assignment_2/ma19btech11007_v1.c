/* 
Assignment 2
Roll Number: MA19BTECH11007 
Name: Meet Vyas

*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


struct bst_node {                                   // Defination of node 
    char str[7] ;
    struct bst_node * parent;
    struct bst_node * left ;
    struct bst_node * right ;
} ;

int compare (char str1[], char str2[]){      // if string 1 is greter, then returns 1
    for (int i = 0 ; i<6; i++){              // if string 2 is greater then returns 2
        if ((int)str1[i]>(int)str2[i])
            return 1 ;
        if ((int)str1[i]<(int)str2[i])
            return 2 ;
    }

    return 0 ;
}

struct bst_node * create_node (char str1[]){                // Creating the node    
    struct bst_node * temp ;
    temp = (struct bst_node *)malloc(sizeof(struct bst_node)) ;
    temp->left = NULL ;
    temp->right = NULL; 
    temp->parent = NULL ;
    // strcpy((temp->str),str1) ;
    // (temp->str)[6] = '\0' ;
    for (int i = 0 ; i<6 ; i++){
        (temp->str)[i] = str1[i] ;
    }
    (temp->str)[6] = '\0' ;
    return temp ;
}

struct bst_node * insert_node (char str1[], struct bst_node * Head){            // inserting the node
    struct bst_node * temp = create_node(str1) ;
    if (Head == NULL)
        return temp ;
    else {
        struct bst_node * itr = Head ;
        while (1){
            if (compare((itr->str),(temp->str)) == 1){
                if (itr->left == NULL){
                    itr->left = temp ;
                    temp->parent = itr ;
                    return Head ;
                }
                else {
                    itr = itr->left ;
                }
            }
            else {
                if (itr->right == NULL){
                    itr->right = temp ;
                    temp->parent = itr ;
                    return Head ;
                }
                else {
                    itr = itr->right ;
                }
            }
        }
    }
    
}

int existe (struct bst_node * Head, char str1[]){                       // Checking if the string exists...
    struct bst_node * itr = Head ;
    while (1){
        if (itr == NULL)
            return 0 ;
        else if (compare((itr->str),str1) == 1){
            itr = itr->left ;
        }
        else if (compare((itr->str),str1) == 2){
            itr = itr->right ;
        }
        else{
            return 1 ;
        }
    }
}

void path_print (struct bst_node * Head, char str1[]){              // If the string exists then printing the L R path
    struct bst_node * itr = Head ;
    while (1){
        if (itr == NULL)
            return ;
        else if (compare((itr->str),str1) == 1){
            itr = itr->left ;
            printf("L") ;
        }
        else if (compare((itr->str),str1) == 2){
            itr = itr->right ;
            printf("R") ;
        }
        else{
            return ;
        }
    }
}

void succ_find (struct bst_node * Head, char str1[]){                       // finding succesor
    struct bst_node * itr = Head ;                                          // itr to iterate
    while (1){
        if (itr == NULL){                                                   // If Head is NULL then it prints 0
            printf ("0\n") ;
            return ;
        }
            
        else if (compare((itr->str),str1) == 1){                            
            if (itr->left == NULL){                                         // Now if the node should be on left but it does not exist
                break ;                                                     // Then we store our hypothetical node's parent node in itr
            }
            itr = itr->left ;
        }
        else if (compare((itr->str),str1) == 2){
            if (itr->right == NULL){                                        // Now if the node should be on right but it does not exist
                break ;                                                     // Then we store our hypothetical node's parent node in itr
            }
            itr = itr->right ;
        }
        else{
            break ;
        }
    }

    if (compare(itr->str,str1) == 0 && itr->right != NULL){               // Standard procedure to find succesor when it has right child
        itr = itr->right ;
        while (itr->left != NULL){
            itr = itr->left ;
        }
        printf("%s\n",(itr->str));
        return ;
    }

    else if (compare(itr->str,str1) == 0){                               // Case when it does not have right child
        struct bst_node * itr_2 = itr ;
        while (1){
            itr_2 = itr_2->parent ;
            if (itr_2 == NULL){
                printf("0\n");
                return ;
            }
            else {
                if (compare(itr_2->str,itr->str)==2){
                    itr = itr_2 ;
                }
                else {
                    printf("%s\n", itr_2->str) ;
                    return ;
                }
            }
        }
    }

    else {                                                      // case when the node does not exist
        struct bst_node * temp_node ;                           // We create a hypothecial temp node of our numberplate 
        temp_node = create_node(str1) ;                         // and only link it to parent 
        temp_node->parent = itr ;
        struct bst_node * itr_2 = temp_node ;
        itr = temp_node ;

        while (1){                                             // Now it is case 2 
            itr_2 = itr_2->parent ;
            if (itr_2 == NULL){
                printf("0\n");
                return ;
            }
            else {
                if (compare(itr_2->str,itr->str)==2){
                    itr = itr_2 ;
                }
                else {
                    printf("%s\n", itr_2->str) ;
                    free(temp_node) ;                           // we delete temp node
                    return ;
                }
            }
        }
        
    }




}

void pred_find (struct bst_node * Head, char str1[]){               // predecessor finding
    struct bst_node * itr = Head ;                                  // itr to iterate
    while (1){
        if (itr == NULL){                                           // If Head is NULL then it prints 0
            printf ("0\n") ;
            return ;
        }
            
        else if (compare((itr->str),str1) == 1){                    // Now if the node should be on left but it does not exist
            if (itr->left == NULL){                                 // Then we store our hypothetical node's parent node in itr
                break ;                         
            }
            itr = itr->left ;
        }
        else if (compare((itr->str),str1) == 2){                    // Now if the node should be on right but it does not exist
            if (itr->right == NULL){                                // Then we store our hypothetical node's parent node in itr 
                break ;
            }
            itr = itr->right ;
        }
        else{
            break ;
        }
    }

    if (compare(itr->str,str1) == 0 && itr->left != NULL){          // Standard procedure to find succesor when it has left child
        itr = itr->left ;
        while (itr->right != NULL){
            itr = itr->right ;
        }
        printf("%s\n",(itr->str));
        return ;
    }
    else if (compare(itr->str,str1) == 0){                          // Case when it does not have left child
        struct bst_node * itr_2 = itr ;
        while (1){
            itr_2 = itr_2->parent ;
            if (itr_2 == NULL){
                printf("0\n");
                return ;
            }
            else {
                if (compare(itr_2->str,itr->str)==1){
                    itr = itr_2 ;
                }
                else {
                    printf("%s\n", itr_2->str) ;
                    return ;
                }
            }
        }
    }
    else {                                                  // case when the node does not exist
        struct bst_node * temp_node ;                       // We create a hypothecial temp node of our numberplate 
        temp_node = create_node(str1) ;                      // and only link it to parent 
        temp_node->parent = itr ;
        struct bst_node * itr_2 = temp_node ;
        itr = temp_node ;

        while (1){                                          // Now it is case 2 
            itr_2 = itr_2->parent ;
            if (itr_2 == NULL){
                printf("0\n");
                return ;
            }
            else {
                if (compare(itr_2->str,itr->str)==1){
                    itr = itr_2 ;
                }
                else {
                    printf("%s\n", itr_2->str) ;
                    free(temp_node) ;                       // we delete temp node
                    return ;
                }
            }
        }

        
    }
}

struct bst_node * deall (struct bst_node * Head){
    if (Head == NULL)
        return NULL ;
    struct bst_node * left = NULL ;
    struct bst_node * right = NULL ;
    if (Head->left != NULL){
        left = Head->left ;
    }
    if (Head->right != NULL)
        right = Head->right ;
    

    free(Head) ;
    Head = NULL ;
    deall (left) ;
    deall (right) ;
    return Head ;
}

int main(){
    struct bst_node * Head = NULL ;
  char* firstLine=NULL;
  char* inputLine=NULL;
  size_t length=0, counter=0, plateLength=6;
  char choice, numberPlate[7];

  // Fetching only the first line of input.
  length = getline(&firstLine,&length,stdin);

  // Parsing the string word by word. 
  while(counter<length){
    strncpy(numberPlate,&firstLine[counter],plateLength);
    numberPlate[plateLength] = '\0';
    counter += plateLength+1; // The +1 takes care of the space between words.

    // Call your BST Insert function here with argument: numberPlate
        Head = insert_node(numberPlate,Head) ;
    
  }

  free(firstLine) ;
  firstLine = NULL ;

  // Main input handler to serve requests.
  while(getline(&inputLine, &length, stdin) != -1){
    char * temp = inputLine ;
    sscanf(inputLine,"%c %s",&choice, numberPlate);
    if(choice=='S'){
      
      // Call your BST Search function here with argument: numberPlate
        if (existe(Head,numberPlate) == 0)
            printf("0\n") ;
        else {
            printf("1 ") ;
            path_print(Head,numberPlate) ;
            printf("\n") ;
        }
      
    }
    else if (choice=='<'){
        // predecessor
        pred_find(Head,numberPlate) ;
    }
    else if (choice== '>'){
        // successor
        succ_find(Head,numberPlate) ;
    }
    free(temp); inputLine=NULL;
    length=0;
  }
  free (inputLine) ;

  Head = deall(Head) ;
  return 0;
  
}