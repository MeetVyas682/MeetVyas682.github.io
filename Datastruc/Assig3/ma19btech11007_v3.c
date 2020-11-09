/* 
Assignment 3
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

struct bst_node * existe (struct bst_node * Head, char str1[]){                       // Checking if the string exists... returns NULL if doesnt exist
    struct bst_node * itr = Head ;                                                      //Other wise pointer to the node we wanted to find
    while (1){
        if (itr == NULL)
            return itr ;
        else if (compare((itr->str),str1) == 1){
            itr = itr->left ;
        }
        else if (compare((itr->str),str1) == 2){
            itr = itr->right ;
        }
        else{
            return itr ;
        }
    }
}
void Inorder_print (struct bst_node * Head) {      // Inorder printing
    if (Head == NULL)
        return ;
    Inorder_print(Head->left) ;
    printf("%s ", Head->str) ;
    Inorder_print(Head->right) ;
}

void Post_order(struct bst_node * Head ){           // Post order printing
    if (Head == NULL)
        return ;
    Post_order(Head->left) ;
    Post_order(Head->right) ;
    printf("%s ", Head->str) ;
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

struct bst_node * succ_find (struct bst_node * Head, char str1[]){                       // finding succesor
// It return the pointer to the node of succesor
    struct bst_node * itr = Head ;                                          // itr to iterate
    while (1){
        if (itr == NULL){                                                   // If Head is NULL then it prints 0
            // printf ("0\n") ;
            return itr;
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
        // printf("%s\n",(itr->str));
        return itr;
    }

    else if (compare(itr->str,str1) == 0){                               // Case when it does not have right child
        struct bst_node * itr_2 = itr ;
        while (1){
            itr_2 = itr_2->parent ;
            if (itr_2 == NULL){
                // printf("0\n");
                return  NULL;
            }
            else {
                if (compare(itr_2->str,itr->str)==2){
                    itr = itr_2 ;
                }
                else {
                    // printf("%s\n", itr_2->str) ;
                    return itr_2 ;
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
                // printf("0\n");
                return NULL ;
            }
            else {
                if (compare(itr_2->str,itr->str)==2){
                    itr = itr_2 ;
                }
                else {
                    // printf("%s\n", itr_2->str) ;
                    free(temp_node) ;                           // we delete temp node
                    return itr_2;
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
int num_child (struct bst_node * Head){             // It return the number of immediate children
    if (Head == NULL)
        return -1 ;
    int ans = 0 ;
    if (Head->left != NULL){
        ans++;
    }
    if (Head->right != NULL)
        ans++;
    
    return ans ;
}
struct bst_node * splice (struct bst_node * Head, struct bst_node * current_node){    // Standard Splicing function, Assumption is that currrent node is not NULL
    if (current_node->parent==NULL){                                                    // Case when the current node is Head
        if (current_node->left==NULL && current_node->right==NULL){                     // Only Head case
            free(Head) ;
            return NULL ;
        }
        else if (current_node->left!=NULL){                                 // Head with left child
            struct bst_node * lef_ch = Head->left ;
            lef_ch->parent = NULL ;
            free(Head) ;
            return lef_ch ;
        }
        else {                                                              // Head with right child
            struct bst_node * rig_ch = Head->right ;
            rig_ch->parent = NULL ;
            free(Head) ;
            return rig_ch ;
        }
    }
    else {                                                      // When current node is not Head, i.e parent exist
        if(current_node->left!=NULL){                           // Left child case
            struct bst_node * pare_cur = current_node->parent ;
            struct bst_node * lef_chil = current_node->left ;
            if (compare(pare_cur->str,current_node->str) == 2){
                pare_cur->right = lef_chil ;
                lef_chil->parent = pare_cur ;
                free(current_node) ;
                return Head ;
            }
            else {
                pare_cur->left = lef_chil ;
                lef_chil->parent = pare_cur ;
                free(current_node) ;
                return Head ;
            }
        }
        if (current_node->right!=NULL){                         // Right child case
            struct bst_node * pare_cur = current_node->parent ;
            struct bst_node * rig_chil = current_node->right ;
            if (compare(pare_cur->str,current_node->str) == 2){
                pare_cur->right = rig_chil ;
                rig_chil->parent = pare_cur ;
                free(current_node) ;
                return Head ;
            }
            else {
                pare_cur->left = rig_chil ; 
                rig_chil->parent = pare_cur ;
                free(current_node) ;
                return Head ;
            }
        }   
        // No child case, i.e. leaf node
        struct bst_node * pare_cur = current_node->parent ;
        if (compare(pare_cur->str,current_node->str) == 2){
                pare_cur->right =NULL ;
                
                free(current_node) ;
                return Head ;
            }
        else {
            pare_cur->left = NULL ; 
            
            free(current_node) ;
            return Head ;
        }
    }
}

struct bst_node * delete_node (struct bst_node * Head, struct bst_node * t0_del){    // we will call delete when node exists
    if (Head == NULL)
        return NULL ;

    struct bst_node * itr = t0_del ;

    if (itr->left == NULL || itr->right == NULL){               // If the node has at max one child
        printf ("%d ",num_child(itr)) ;
        if (num_child(itr) == 0)
            printf("\n") ;
        else {
            if (itr->left != NULL){
                printf("%s\n",(itr->left)->str) ;
            }
            else {
                printf("%s\n",(itr->right)->str) ;
            }

        }
        Head = splice(Head,itr) ;
        return Head ;
    }
    else {                                                      // If the node has 2 child
        printf ("%d ",num_child(itr)) ;
        struct bst_node * add_succ = succ_find(Head,itr->str) ;
        printf("%s\n",add_succ->str) ;
        // copy string of add_suc to itr
        char temp_string[7] ;

        for (int i = 0 ; i<6 ; i++){
            temp_string[i] = (add_succ->str)[i] ;
        }
        // temp_string[6] = '\0' ;
        // printf("%s\n",itr->str) ;
        Head = splice(Head,add_succ) ;  // we can just splice since the succesor has only one child at max
        for (int i = 0 ; i<6 ; i++){
            (itr->str)[i] = temp_string[i];
        }
        // (itr->str)[6] = '\0' ;
        return Head ;
        
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
  char choice, numberPlate[7];
  _Bool requests = 0;
    
  // Fetching till we hit the first request
   while(scanf("%s",numberPlate)!=-1){
    if(!requests){
      if(strlen(numberPlate) == 1){ // Detecting start of request lines.
	choice = numberPlate[0];
	requests = 1;
      }
      else{
	// *** Call your insert function here with argument numberPlate ***
            Head = insert_node(numberPlate,Head) ;
      }
    }
    else break; // choice and numberPlate have values to be processed!!
   }
      
   do{ // Ugly do-while to process first request line before first scanf.
   
     if(choice=='S'){
      
      // Call your BST Search function here with argument: numberPlate
        if (existe(Head,numberPlate) == NULL)
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
        struct bst_node * add_suc = succ_find(Head,numberPlate) ;
        if (add_suc == NULL)
            printf("0\n") ;
        else 
            printf("%s\n",add_suc->str) ;
    }
    else if (choice == '+'){
        // Inserting function, if doesnt exist then we insert
        if (existe(Head,numberPlate) == NULL)
            Head = insert_node(numberPlate,Head) ;
    }
    else if (choice == '-'){
        //delete
        if (existe(Head,numberPlate) == NULL)
            printf("-1\n") ;
        else {
            Head = delete_node(Head,existe(Head,numberPlate)) ;
        }
    }
    else if (choice=='I'){
        //Inorder
        Inorder_print(Head) ;
        printf("\n");
    }
    else if (choice=='P'){
        //postorder 
        Post_order(Head) ;
        printf("\n");
    }




   }while(scanf("%*[\n]%c %6s",&choice, numberPlate)!=-1); 

   Head = deall(Head) ;
   return(0);  
}