#define TYPE double
#define SIZE 100

typedef struct {
	int top;
	TYPE items[SIZE];	
	} stack;
	
	
void initialize(stack *s){
	
	s->top = -1;
	
	}

	
int isEmpty(stack *s){
	
	if((s->top) > -1)
		return 0;
		
	return 1;
		
	}


	
int isFull(stack *s){
	
	if( s-> top < SIZE -1 )
	return 0;
	return 1;
	
	}
	
	
TYPE peak(stack *s){
	
	if(!isEmpty(s)){
		TYPE value = s->items[s->top];
		return value;
		
		}else
		printf("Can't get peak : stack is empty");
		return 0;
	}


void push( stack *s , TYPE value){
	
	if(!isFull(s)){
		
		s->top+=1;
		s->items[s->top] = value;
		
		}else{
			
			printf("Can't push stack is Full");
						
			}
	
	
	}
	
TYPE pop(stack *s){
	
	if(!isEmpty(s)){
		
		TYPE value = s->items[s->top];
		s->top -=1;
		return value;
		
		}else
		printf("Can't pop , stack is Empty");
		
		
		return 0;
	
	}
	
