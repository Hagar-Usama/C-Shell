#include "genStack.h"
#include "stack.h"
#define INFIX 64
#include "hash_lp.h"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"


// lacks verbose variable for printf

 int isOperator(char *op);
int isNumeric(char *str);
int doMath(double num1 , double num2 , char *op , double *sum);
double calcA(double num1 , double num2 , char *op);
int checkPost(char* post);
int checkValid(char* post);
void help();
void sys(char *command);
void readFile(char* path);
void readAb(char* path);
void evalIt(char *infix , char *post);
void read_s(char* path);
int str_cut(char *str, int begin, int len);
void infixToPostfix_s_label(char* infix , char* postfix , char* symbol , char* label);


int flag_sym = 2;

int evalPost( char * postfix , double *sum){

	stack s;
	initialize(&s);
	
	 double num1, num2 , calc = 0 , number ;
	 
	 
	 
		int i =0 , j =1, count = 0;
	
	while(postfix[i] != '\0')
	{
	
		if(postfix[i++] == ' ' && postfix[j]!=' ')
		count++;
		j = i+1;
	}
	
	const char sep[2] = " ";
	char *token;
	
   /* get the first token */
   token = strtok(postfix, sep);
   
   /* walk through other tokens */
   
   count++;
   
  
   
   while( count-- ) {
	   //printf("\ntoken is : %s << token\n" , token);
		
			
		
		if (isNumeric(token)){
			 
			sscanf(token , "%lf" , &number);
			//printf( " num1 Is : %lf" , num1);
			//printf("number: %lf", number);
			
			push(&s , number);
			//printf("number push to stack");
			
			//printf( " num 2 Is : %lf" , num2);
		
			//puts("Number");
			}else if (isOperator(token) == 1) {
				
				//sscanf(token, "%lf", &num1);
				//printf("num now is %lf\n", num1);
				
				num2 = pop(&s);
				//printf("number poped is %lf", num2);
				num1 = pop(&s);
				//printf("num 1 : %lf , num2: %lf", num1 , num2);
				
				//operator done
				
				calc = calcA(num1, num2, token);
				//calc = num2 + num1;
				//checkCalc = doMath(num1 , num2 , token ,&calc);
				
				//puts("summed");
				//printf(" sum = %lf", calc);
				//push result
				
				
					
						push(&s , calc);
					
				
				
			}else{
				
				puts("something else");
				}


		token = strtok(NULL, sep);
	}// end of while
	
	
	//printf("the sum finally is : %lf" , pop(&s));
	*sum = pop(&s);
	return 1;
	
	}
	
	
	
	double calcA(double num1 , double num2 , char *op){
	
	//double su;
	//sum = & su;
	
	if( op[0] == '+'){
		
			
			
			return num1 + num2;
		}
	
	else if( op[0] == '-'){
		
			
			return num1 - num2;
		}
	else if ( op[0] == '*'){
		return num1 * num2;
		}
	else if (op[0] == '/' &&  num2 != 0){
		return num1 / num2;
		}
		
	return 0;
		/*
	else if (op[0] == '%')
	return num1 % num2;
	else if (op[0] == '<')
	return num1 << num2;
    else if (op[0] == '>')
	return num1 >> num2;
	*/
	
	
	/*
	switch (op){
		
		case '+' : return num1 + num2;
		case '-' : return num1 - num2;
		case '*' : return num1 * num
		
		}
	*/
	}


int doMath(double num1 , double num2 , char *op , double *sum){
	
	double su;
	sum = & su;
	
	if( op[0] == '+'){
		
			su = num1 + num2;
			printf("calculation = %lf\n",su);
			return 1;
		}
	
	else if( op[0] == '-'){
		
			su =  num1 - num2;
			printf("calculation = %lf\n",su);
			return 1;
		}
	else if ( op[0] == '*'){
		su = num1 * num2;
		printf("calculation = %lf\n",su);
		return 1;
		}
	else if (op[0] == '/' &&  num2 != 0){
		su = num1 / num2;
		printf("calculation = %lf\n",su);
		return 1;
		}
		
	return 0;
		/*
	else if (op[0] == '%')
	return num1 % num2;
	else if (op[0] == '<')
	return num1 << num2;
    else if (op[0] == '>')
	return num1 >> num2;
	*/
	
	
	/*
	switch (op){
		
		case '+' : return num1 + num2;
		case '-' : return num1 - num2;
		case '*' : return num1 * num
		
		}
	*/
	}

int priority(char *op ){
	
	switch(op[0]){
		
		case '(': case ')': 
		//puts("brackets");
		 return 6;
		case '*': case '/': case '%':
		//puts(" mul or div"); 
		return 5;
		case '+': case '-': 
		//puts("plus or minus");
		return 4;
			
		
		
		}
		
		return 0;
	}


//check if a string is a number (-ve ,decimal ....)
int isNumeric(char *str){
	 
	 if(str == NULL )
	 return 0;
	 
	 
	 char ch;
	 int dotCount = 0 , i=0;
	 
	 //-ve can only be in the first index
	 
	   if(str[0] == '-' ){
			
			if(str[1] == '\0')
			return 0;
		 
		 i=1;
		 }
		
		
	 while(str[i] != '\0'){
		 
			ch = str[i];
			
			
			 switch(ch){
				
				case '.' :
				 if(++dotCount >1) return 0;
				 break;
		
				default:
				if(ch < '0' || ch > '9')
				return 0;
				
				}
				
		 
		 i++;
		 }
	 
	 
	 
	 return 1;
	 
	 }
	 
	 
	 
	 //check if string is operator
	 int isOperator(char *op){
		 
		 if(op[1] == '\0'){
			 if(op[0] == '*' || op[0] =='/' || op[0] =='%' || op[0] =='+' || op[0] =='-')
				return 1;
			else if(op[0] =='('){
			//puts("scanned '('" );
			return 2;	
			}else if(op[0] == ')'){
				//puts("scanned ')'" );
					return 3;
				}
			
		}else if(op[2] == '\0'){
			
			if((op[0] =='>' && op[1] == '>') || (op[0] =='<' && op[1] == '<'))
			return 1; 
			
			}
		return 0;
		 }




 void infixToPostfix(char* infix , char* postfix){
	
	Stack s ;
	createStack(8 , 32,&s);
	//stackPush(&s , " #");
	int count = 0 , i=0, j=1;
	char c[20];
	char top[20];
	//int symlen = -1;
	
	//double num1 , num2;
	while(infix[i] != '\0')
	{
		
		if(infix[i++] == ' ' && infix[j]!=' ')
		count++;
		j = i+1;
	}// now I have number of terms or more :)
	
	infix[strlen(infix)-1] = '\0';
	//strcat(infix , " #");
	
	//char str[count+1][10];
	
	const char sep[2] = " ";
	char *token;
	
   /* get the first token */
   token = strtok(infix, sep);
   
   /* walk through other tokens */
   i = 0 ; j=0 ;
   //int g;
   //int pop =1;
   
   count++;
   while( count--/*token != NULL*/ ) {
	   //here token or element is in hand
	  //printf("{%s} isNumber : %d , isOp : %d[%d]\n",token,isNumeric(token),isOperator(token) , count);
	  //if numeric output it
	  if(strstr(token ,"=")){
		  //printf("%s" , token);
		  //symlen = strlen(token);
		  
		  }
	  else if(isNumeric(token)){
		  //sscanf(token , "%lf", &num1);
		  //if(num1 == 5)
		  //puts("yay");
		  //printf(" num1 = %f\n", num1);
		  
		  //printf("%s ", token);
		  strcat(postfix , token);
		  strcat(postfix , " ");
	  // if ( push it
	  }else if(isOperator(token) == 2){
			
			stackPush(&s,token);
	  // if ) pop the stack til you find its partner (
	  }else if(isOperator(token) ==3){
		  
		  //check here if () empty
		  //pop = stackPop(&s , c);
		  stackTop(&s , top);
		  while(stackTop(&s , top) && isOperator(top) != 2){
			  stackPop(&s ,c);
			  
			 // printf("%s ",c);
			  strcat(postfix ,c);
			  strcat(postfix , " ");
			  }
			//don't forget to remove the )
				//int y = stackTop(&s , top);
				//printf( " y = %d , top = %s\n" , y , top);
			//int g = stackPop(&s,c);
			//g = stackPop(&s,c);
			stackPop(&s,c);
			//printf("\npoped worked : %d    : %s ***\n ", g ,c);
	 }else if(isOperator(token) == 1){
		 if(isStackEmpty(&s)){
				stackPush(&s ,token);
				//stackPop(&s , pop);
				//printf("pop is : %s",pop);
				//exit(1); 
			 
			 }
		 
		 else{
			 // in case stack isn't empty!!
			 //stackTop(&s , top);
			 //puts("get into stack not empty");
			 while(stackTop(&s , top) && (priority(top) >= priority(token)) && isOperator(top)!=2){
				// puts("into triple");
				 stackPop(&s,c);				 
				
				// printf("%s ",c);
				 strcat(postfix , c);
				 strcat(postfix , " ");
				 
				 //stackPush(&s , token);
				 //printf(" %s" ,c);
				 
				 }
			 stackPush(&s , token);
			 }
		
	 }else{ // ay mo4kl tany
		  }
	  
	   
      token = strtok(NULL, sep);
		
	

	}// end of while
	//puts("at the end");
	while(!isStackEmpty(&s)){
		stackPop(&s , c);
		
		//printf("%s ",c);
		strcat(postfix , c);
		strcat(postfix , " ");
		}
		
		
		//str_cut(token, symlen, strlen(postfix));
		//printf("postfix is now : %srrr" , postfix);
		//stackDestroy(&s);
	
	
}

void infixToPostfix_s_label(char* infix , char* postfix , char* symbol , char* label){
	
	Stack s ;
	createStack(8 , 32,&s);
	//stackPush(&s , " #");
	int count = 0 , i=0, j=1;
	char c[20];
	char top[20];
	//int symlen = -1;
	//char sym[16];
	symbol[0] = '\0';
	label[0] = '\0';
	//double num1 , num2;
	while(infix[i] != '\0')
	{
		
		if(infix[i++] == ' ' && infix[j]!=' ')
		count++;
		j = i+1;
	}// now I have number of terms or more :)
	
	infix[strlen(infix)-1] = '\0';
	//strcat(infix , " #");
	
	//char str[count+1][10];
	
	const char sep[2] = " ";
	char *token;
	
   /* get the first token */
   token = strtok(infix, sep);
   
   /* walk through other tokens */
   i = 0 ; j=0 ;
   //int g;
   //int pop =1;
   
   count++;
   while( count--/*token != NULL*/ ) {
	   //here token or element is in hand
	  //printf("{%s} isNumber : %d , isOp : %d[%d]\n",token,isNumeric(token),isOperator(token) , count);
	  //if numeric output it
	  if(strstr(token ,":")){
			printf("**%s\n" , token);
		  //symlen = strlen(token);
		  memcpy(label, token, strlen(token)+1);
		   label[strlen(label)-1] = '\0';
	  
	  }else if(strstr(token ,"=")){
		  //printf("**%s" , token);
		  //symlen = strlen(token);
		   memcpy(symbol, token, strlen(token)+1);
		   symbol[strlen(symbol)-1] = '\0';
		   
			//printf("**sm :%s**",sym);
		  }
	  else if(isNumeric(token)){
		  //sscanf(token , "%lf", &num1);
		  //if(num1 == 5)
		  //puts("yay");
		  //printf(" num1 = %f\n", num1);
		  
		  //printf("%s ", token);
		  strcat(postfix , token);
		  strcat(postfix , " ");
	  // if ( push it
	  }else if(isOperator(token) == 2){
			
			stackPush(&s,token);
	  // if ) pop the stack til you find its partner (
	  }else if(isOperator(token) ==3){
		  
		  //check here if () empty
		  //pop = stackPop(&s , c);
		  stackTop(&s , top);
		  while(stackTop(&s , top) && isOperator(top) != 2){
			  stackPop(&s ,c);
			  
			 // printf("%s ",c);
			  strcat(postfix ,c);
			  strcat(postfix , " ");
			  }
			//don't forget to remove the )
				//int y = stackTop(&s , top);
				//printf( " y = %d , top = %s\n" , y , top);
			//int g = stackPop(&s,c);
			//g = stackPop(&s,c);
			stackPop(&s,c);
			//printf("\npoped worked : %d    : %s ***\n ", g ,c);
	 }else if(isOperator(token) == 1){
		 if(isStackEmpty(&s)){
				stackPush(&s ,token);
				//stackPop(&s , pop);
				//printf("pop is : %s",pop);
				//exit(1); 
			 
			 }
		 
		 else{
			 // in case stack isn't empty!!
			 //stackTop(&s , top);
			 //puts("get into stack not empty");
			 while(stackTop(&s , top) && (priority(top) >= priority(token)) && isOperator(top)!=2){
				// puts("into triple");
				 stackPop(&s,c);				 
				
				// printf("%s ",c);
				 strcat(postfix , c);
				 strcat(postfix , " ");
				 
				 //stackPush(&s , token);
				 //printf(" %s" ,c);
				 
				 }
			 stackPush(&s , token);
			 }
		
	 }else{ // ay mo4kl tany
		  }
	  
	   
      token = strtok(NULL, sep);
		
	

	}// end of while
	//puts("at the end");
	while(!isStackEmpty(&s)){
		stackPop(&s , c);
		
		//printf("%s ",c);
		strcat(postfix , c);
		strcat(postfix , " ");
		}
		
		
		//str_cut(token, symlen, strlen(postfix));
		//printf("postfix is now : %s" , postfix);
		//stackDestroy(&s);
	
	
}


void infixToPostfix_s(char* infix , char* postfix , char* symbol){
	
	Stack s ;
	createStack(8 , 32,&s);
	//stackPush(&s , " #");
	int count = 0 , i=0, j=1;
	char c[20];
	char top[20];
	//int symlen = -1;
	//char sym[16];
	symbol[0] = '\0';
	//double num1 , num2;
	while(infix[i] != '\0')
	{
		
		if(infix[i++] == ' ' && infix[j]!=' ')
		count++;
		j = i+1;
	}// now I have number of terms or more :)
	
	infix[strlen(infix)-1] = '\0';
	//strcat(infix , " #");
	
	//char str[count+1][10];
	
	const char sep[2] = " ";
	char *token;
	
   /* get the first token */
   token = strtok(infix, sep);
   
   /* walk through other tokens */
   i = 0 ; j=0 ;
   //int g;
   //int pop =1;
   
   count++;
   while( count--/*token != NULL*/ ) {
	   //here token or element is in hand
	  //printf("{%s} isNumber : %d , isOp : %d[%d]\n",token,isNumeric(token),isOperator(token) , count);
	  //if numeric output it
	  if(strstr(token ,"=")){
		  //printf("**%s" , token);
		  //symlen = strlen(token);
		   memcpy(symbol, token, strlen(token)+1);
		   symbol[strlen(symbol)-1] = '\0';
		   
			//printf("**sm :%s**",sym);
		  }
	  else if(isNumeric(token)){
		  //sscanf(token , "%lf", &num1);
		  //if(num1 == 5)
		  //puts("yay");
		  //printf(" num1 = %f\n", num1);
		  
		  //printf("%s ", token);
		  strcat(postfix , token);
		  strcat(postfix , " ");
	  // if ( push it
	  }else if(isOperator(token) == 2){
			
			stackPush(&s,token);
	  // if ) pop the stack til you find its partner (
	  }else if(isOperator(token) ==3){
		  
		  //check here if () empty
		  //pop = stackPop(&s , c);
		  stackTop(&s , top);
		  while(stackTop(&s , top) && isOperator(top) != 2){
			  stackPop(&s ,c);
			  
			 // printf("%s ",c);
			  strcat(postfix ,c);
			  strcat(postfix , " ");
			  }
			//don't forget to remove the )
				//int y = stackTop(&s , top);
				//printf( " y = %d , top = %s\n" , y , top);
			//int g = stackPop(&s,c);
			//g = stackPop(&s,c);
			stackPop(&s,c);
			//printf("\npoped worked : %d    : %s ***\n ", g ,c);
	 }else if(isOperator(token) == 1){
		 if(isStackEmpty(&s)){
				stackPush(&s ,token);
				//stackPop(&s , pop);
				//printf("pop is : %s",pop);
				//exit(1); 
			 
			 }
		 
		 else{
			 // in case stack isn't empty!!
			 //stackTop(&s , top);
			 //puts("get into stack not empty");
			 while(stackTop(&s , top) && (priority(top) >= priority(token)) && isOperator(top)!=2){
				// puts("into triple");
				 stackPop(&s,c);				 
				
				// printf("%s ",c);
				 strcat(postfix , c);
				 strcat(postfix , " ");
				 
				 //stackPush(&s , token);
				 //printf(" %s" ,c);
				 
				 }
			 stackPush(&s , token);
			 }
		
	 }else{ // ay mo4kl tany
		  }
	  
	   
      token = strtok(NULL, sep);
		
	

	}// end of while
	//puts("at the end");
	while(!isStackEmpty(&s)){
		stackPop(&s , c);
		
		//printf("%s ",c);
		strcat(postfix , c);
		strcat(postfix , " ");
		}
		
		
		//str_cut(token, symlen, strlen(postfix));
		//printf("postfix is now : %s" , postfix);
		//stackDestroy(&s);
	
	
}

int main(){
	

//to store postfix & infix exp

char post[20] ,infix[INFIX+1] , in[INFIX+1];
char command[16];
int indx;
char symbol[16];

double val;
double res;


     for(int i = 0 ; i<SIZE ; i++){
			hash_table[i].value = INT_MIN;
			
			}

read_s("eval.txt");
//readAb("simpleEval.txt");


//insert("x", 52.25);
//s= get("x", &indx);
//printf("getting value = %0.2lf", s);


while(1){
	
	if(flag_sym)	
	printf(">> ");
	
	
	
	
	//readFile("simpleEval.txt");
// scan infix expression from terminal 
	fgets(infix , INFIX , stdin);
	if(strlen(infix) <=1)
	{
		
	}else if(strstr(infix , "exit")){
		flag_sym =1;
		break;
		}else if(strstr(infix , "help")){
			help();
			
			
	}else if(strstr(infix , "terminal -c")){
		flag_sym =1;
		fgets(command, sizeof(command)-1 , stdin);
		sys(command);
		
		
	}else if(strstr(infix , "read file -a")){
		flag_sym =1;
		printf("Path: ");
		scanf("%s", command);
		//scanf("\n");
		//readAb("eval.txt");
		read_s(command);
		
		
	}else if(!strcmp(infix , "get value\n")){
		flag_sym =1;
		printf("enter variable: ");
		scanf("%s", command);
		
		val = get(command , &indx);
		
		if(val != INT_MIN){
			
			printf("%s = %lf\n",command , val);
			
			}
	}else if(strstr(infix , "get value by label")){
		flag_sym =1;
		printf("enter label: ");
		scanf("%s", command);
		
		val = get_by_label(command , symbol);
		
		if(val != INT_MIN){
			
			printf("%s: %s = %lf\n",command,symbol , val);
			
			}else{
				puts("Label not found");
				
				}
		
		
		
		}else if(strstr(infix , "eval")){
			flag_sym =1;
			puts("Enter Expression");
			fgets(infix, sizeof(infix)-1 , stdin);
			evalIt(infix , post);
			
			
		
		}else if(!strcmp(infix , "if\n")){
			flag_sym =1;

			printf("#Condition : ");
			fgets(infix, sizeof(infix)-1 , stdin);
			evalIt(infix , post);
			val = evalPost(post , &res);
			
			puts("#ELSE :");
			fgets(in , sizeof(in)-1 , stdin);
			
			if(val){
				printf("condition is valid\n");
				puts("#Then : GO TO ");
				scanf("%s", command);
				val = get_by_label(command , symbol);
				if( val != INT_MIN){
					
					printf("%s: %s = %lf\n", command , symbol , val);
					
					}
				
				}else{
					
					evalIt(in , post);
					val = evalPost(in , &res);
					if(val){
						puts("#Then : GO TO ");
						scanf("%s", command);
						val = get_by_label(command , symbol);
						if( val != INT_MIN){
					
					printf("%s: %s = %lf\n", command , symbol , val);
					
					}
						
						}
					}
						//puts("Enter Expression");
			
			
			
			
			
			}else{
		
			
		 if(strlen(command) <= 20 && flag_sym!=1)
		 printf(">> ");
		 flag_sym =0;
		
		
		}
    
	
	
	
	
	/*
		
	//printf("infix = %s\n" , infix);
	post[0] = '\0';
	//printf("postfix = %s\n" , post);
	
// covert expression into postfix
	//printf( "is valid : %d", checkPost(infix));
	
			if(checkPost(infix)){
	
		infixToPostfix(infix , post);	
		post[strlen(post)-1] = '\0';
	
	// printf postfix expression
		printf("postfix is :\n%s",post);
	
	
	// 
		double result ;
		if(evalPost(post , &result)){
		printf("\nResult is %lf\n", result);
		}else
		puts("invalid expression");
		
		
		
		
		} // end of if checkPost
		
	
	*/
	}
	
return 0;	
}


int checkPost(char* post){
	
	if( strstr(post , "()")){
			
			//puts("() entered");
			return 0;
		}
	
	else if( strstr(post , "( )")){
		//puts("() entered");
		return 0;
		
		}

	
	return 1;
	}


void help(){
	
	//system("clear");
	printf(RED "Here you can find all the info you need about this shell\n" RESET);
	printf(YEL "Info not provided yet\n" RESET);
    printf(GRN "Copyright Hagar Osama\n" RESET);
  /*
  printf(YEL "yellow\n" RESET);
  printf(BLU "blue\n" RESET);
  printf(MAG "magenta\n" RESET);
  printf(CYN "cyan\n" RESET);
  printf(WHT "white\n" RESET);
	*/
	
	
	}
	
void sys(char *command){
	
	system(command);
	
	}

void readFile(char* path){
	
	 FILE *fp ;
	 //int slots =0 , i= 0;
	
	 //char var[50];
	 
	 char infix[64];
	 char post[64];
	 
	 fp = fopen (path, "r");

	  if(fp == NULL)
   {
       puts("Error! .. Can't Find File!");
       exit(1);
   } else{
	   
	   //post[0] = '\0';
	   
	   while( fgets(infix , 60 , fp) ){
			post[0] = '\0';
			//printf("infix= %s, length = %ld\n", infix , strlen(infix));
			//printf("infix= %s, length = %ld\n", infix , strlen(infix));
					if(checkPost(infix)){
				//puts("valid exp");
		
				infixToPostfix(infix, post);	
				post[strlen(post)-1] = '\0';
		
		//printf("post is : %s",post);
	// printf postfix expression
				printf("postfix is :\n%s",post);
	
	
	// 
		double result ;
			if(evalPost(post , &result)){
			printf("\nResult is %lf\n", result);
		}
		//else
		//puts("invalid expression");
		
		
		
		
		} // end of if checkPost
	   }//END OF WHILE
	   
	   
	   
	   
	   }//end of else
	     
	   
	   
		
		
		
		fclose(fp);
   
	 } // END OF FUN

	
	
void readAb(char* path){
	
	 FILE *fp ;
	 
	 
	 char infix[64];
	 char post[64];
	 
	 fp = fopen (path, "r");

	  if(fp == NULL)
   {
       puts("Error! .. Can't Find File!");
       return;
       //exit(1);
   } else{
	   
	   //post[0] = '\0';
	   
	   while( fgets(infix , 60 , fp) ){
			post[0] = '\0';
			//printf("infix= %s, length = %ld\n", infix , strlen(infix));
			//printf("infix= %s, length = %ld\n", infix , strlen(infix));
					if(checkPost(infix)){
				//puts("valid exp");
				//printf("strlen** = %ld**", strlen(infix));
				infixToPostfix(infix, post);	
				post[strlen(post)-1] = '\0';
		
			//printf("post is : %s",post);
			// printf postfix expression
				printf("postfix is :\n%s",post);
	
	
	// 
		double result ;
			if(evalPost(post , &result)){
			printf("\nResult is %lf\n", result);
		}
		//else
		//puts("invalid expression");
		
		
		
		
		} // end of if checkPost
	   }//END OF WHILE
	   
	   
	   
	   
	   }//end of else
	     
	   
	   
		
		
		
		fclose(fp);
   
	 } // END OF FUN

	
void read_s_label(char* path){
	
	 FILE *fp ;
	 
	 //char infix[64];
	 char post[64];
	 //char symbol[8];
	 char exp[128];
	 
	 //const char sep[2] = " ";
	 //char *token;
	 
	 //puts("enterd fun read_s");
	 fp = fopen (path, "r");

	  if(fp == NULL)
   {
       puts("Error! .. Can't Find File!");
       return;
       //exit(1);
   } else{
	   
	   post[0] = '\0';
	   
	   while( fgets(exp , 127 , fp) ){
			
			//printf("exp is %s",exp);
			evalIt(exp , post);
			
					 // end of if checkPost
	   }//END OF WHILE
	   
	   
	   
	   
	   }//end of else
	     
	   
	   
		
		
		
		fclose(fp);
   
	 } // END OF FUN
	

	
void read_s(char* path){
	
	 FILE *fp ;
	 
	 //char infix[64];
	 char post[64];
	 //char symbol[8];
	 char exp[128];
	 
	 //const char sep[2] = " ";
	 //char *token;
	 
	 //puts("enterd fun read_s");
	 fp = fopen (path, "r");

	  if(fp == NULL)
   {
       puts("Error! .. Can't Find File!");
       return;
       //exit(1);
   } else{
	   
	   post[0] = '\0';
	   
	   while( fgets(exp , 127 , fp) ){
			
			//printf("exp is %s",exp);
			evalIt(exp , post);
			
					 // end of if checkPost
	   }//END OF WHILE
	   
	   
	   
	   
	   }//end of else
	     
	   
	   
		
		
		
		fclose(fp);
   
	 } // END OF FUN
	
	
void evalIt(char *infix , char *post){
	
	char symbol[16];
	char label[16];
	symbol[0] ='\0';
	label[0] ='\0';
	post[0] = '\0';
					if(checkPost(infix)){
				//puts("valid exp");
		
				infixToPostfix_s_label(infix, post,symbol,label);
				//printf("symbol in eval %s",symbol);
				
				
				post[strlen(post)-1] = '\0';
		
			//printf("post is : %s",post);
			// printf postfix expression
				printf(GRN"postfix is :\n%s"RESET,post);
	
		//printf(RED "Here you can find all the info you need about this shell\n" RESET);
	//printf(YEL "Info not provided yet\n" RESET);
	 
		double result ;
			if(evalPost(post , &result)){
			//printf("strlen of sym = %ld**",strlen(symbol));
			if(strlen(symbol)> 0){
				
				//printf("\n**%s =***",symbol);
				printf(YEL"\n%s = %lf\n"RESET,symbol , result);
				insert(symbol , label, result);
				}else{
					printf(YEL"\nResult is %lf\n"RESET, result);
						
					}
							
			
		}
		
		
		
		
		}
	
	
	
	
	}
