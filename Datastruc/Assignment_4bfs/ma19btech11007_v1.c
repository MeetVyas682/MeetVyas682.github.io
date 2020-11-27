/* 
Assignment 4
Roll Number: MA19BTECH11007
Name: Meet Vyas

*/
#include<stdio.h>
#include <stdlib.h>

struct data_node {                                                          // Structure to create a node for storing data
    int vertice_id ;
    struct data_node * nxt_ptr;
};

struct data_node * Create_data_node (int vertice_id) {                      // Creating a node with the passed value
    struct data_node * temp ;
    temp = (struct data_node *)malloc(sizeof(struct data_node)) ;
    temp->vertice_id = vertice_id ;
    temp->nxt_ptr = NULL ;

    return temp;
}

struct data_node * find_data_node (struct data_node * Head, int value){     // Returns the node having the passed value, otherwise NULL
    if (Head == NULL)
        return NULL ;
    
    while(Head != NULL){
        if (Head->vertice_id == value)
            return Head ;
        else
            Head = Head->nxt_ptr ;
    }

    return NULL ;
}

void add_edge (struct data_node * Head, int value ){
    struct data_node * newNode = Create_data_node(value) ;
    if (Head->nxt_ptr == NULL)
        Head->nxt_ptr = newNode;
    else {
        struct data_node *bc_ptr = Head ;
        struct data_node * tmpPtr = Head->nxt_ptr;
        
        while(tmpPtr != NULL && tmpPtr->vertice_id<value){
            bc_ptr = tmpPtr ;
            tmpPtr =tmpPtr->nxt_ptr ;
        }

        bc_ptr->nxt_ptr = newNode ;
        newNode->nxt_ptr = tmpPtr ;
        
    }

    return;
}

void debug_graph_printer (struct data_node * arr[],int N){
    for (int i = 0 ; i<N;i++){
        struct data_node * tmp = arr[i] ;
        while (tmp!=NULL){
            printf("%d ",tmp->vertice_id) ;
            tmp = tmp->nxt_ptr ;
        }
        printf("\n") ;
    }
}

int main(){
  char choice;
  int numberOfVertices, startVertex, endVertex;
  
  // Fetching number of vertices
  scanf("%d",&numberOfVertices);
  // Create your adjacency list's array of head vertices here.
    struct data_node * array[numberOfVertices];                             // Creating the array of Heads
    for (int i = 0 ; i<numberOfVertices;i++)
        array[i] = Create_data_node(i) ;                                    // Creates Head having value i same as that of vertice


  while(scanf(" %c",&choice)!=-1){
     if(choice == 'N'){
       char delimiter;
       scanf("%d", &startVertex);     
       while(scanf("%d%c", &endVertex, &delimiter)){

	 // Add the edge (startVertex, endVertex) to your graph here.
            if (startVertex != endVertex && find_data_node(array[startVertex]->nxt_ptr,endVertex) == NULL){
                add_edge(array[startVertex],endVertex);
                add_edge(array[endVertex], startVertex);
            }
                
	 
	 if(delimiter == '\n') break; // Detecting end of line.
       }
       debug_graph_printer(array,numberOfVertices) ;
     }
     else if(choice == 'B'){
       scanf("%d",&startVertex);
       // Call BFS on your graph starting from startVertex here.
     }
   }

    


   return(0);  
}
