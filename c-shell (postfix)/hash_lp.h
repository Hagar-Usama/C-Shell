
#include <stdio.h>
#include <limits.h>
#include <string.h>
#define HASH_SIZE 64
 
 typedef struct hash {
	 
	 char sym[16];
	 char label[16];
	 double value;
	 
	 } hash;
	 
	 
	hash hash_table[64];
  
  double get(char* symbol , int *index);
  int hashCode(char* symbol);
  void insert(char* symbol , char* label, double res);  
  double get_by_label(char* label , char* symbol );
 
 
int hashCode(char* symbol){
	
	int sum=0;
	int i=0;
	while(symbol[i] != '\0'){
		sum+=symbol[i++];
		
		}
	
		return sum;
	
	}
	
	
	
void insert(char* symbol , char* label , double res){
    
    int pos,n=0;
	
    
	int h = hashCode(symbol);
    pos = h%HASH_SIZE;
	
	int index ;
	
	// fisrt check if item already exists
	int found = get(symbol , &index);
	if( found != INT_MIN){
		
		//puts("element already found");
		//puts("updating..");
		//no effect!!!
		hash_table[index].value = res;
		return;
		
		}else{
		
		//puts("entered else");
	while(hash_table[pos].value!= INT_MIN) {  
        
            
        pos = (pos+1)%HASH_SIZE;
        n++;
        
        if(n==HASH_SIZE)
        break;
    }
 
    if(n== HASH_SIZE)
        printf("Full hash Table\n");
    else{
		
		hash_table[pos].value = res;
		memcpy(hash_table[pos].sym , symbol , 8 );
		memcpy(hash_table[pos].label, label , 8 );
		printf("inserted in index : %d\n", pos);
		}
	
		
		}
    

//puts("inserted");        
}


 
void delete(char * symbol){
    
    
 
 
 
}
 
 
double get(char* symbol , int *index){
    
    int pos;
    int in;
    index = &in; // index points to in
 
    //printf("Enter element you want to search\n");
    //scanf("%d",&element);
 

    pos = hashCode(symbol)% HASH_SIZE;
		//search using hashCode if you find it return it else linear search
	if(!strcmp(hash_table[pos].sym , symbol)){
		*(index) = pos;
		//printf("content of index = %d", *(index));
		//printf("pos = %d\n" , pos);
		return hash_table[pos].value;
		
		}else {
			
			for(int i=0 ; i<HASH_SIZE ; i++){
				
				if(!strcmp(hash_table[i].sym , symbol)){
					return hash_table[i].value; 
					
					}
				
				}
				//if for ended and found nothing return INT_MIN
			return INT_MIN;
			
			}
	

}


double get_by_label(char* label , char* symbol ){
	
	
	for(int i=0 ; i< HASH_SIZE ; i++){
		
		//printf("hash label is : %s\n" , hash_table[i].label);
		if(!strcmp(hash_table[i].label , label)){
			
			memcpy(symbol , hash_table[i].sym , 8);
			//memccpy(label , hash_table.label , 8);
			return hash_table[i].value;
			}
		
		
		
		}
	
		return INT_MIN;
	
	}
