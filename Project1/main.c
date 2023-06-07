#include <stdio.h>
#include <stdlib.h>
#define null NULL

//implemented by:  Moath AbdAlbaqi

typedef struct subnode* subptr;
typedef struct node* ptr;

struct node{//the main node, the node which are the header of numbers
char sign;
 ptr next;
  ptr pre;
   subptr subnext;
};
struct subnode{//this node where number's digits are stored...
 int data;
  subptr next;
   subptr pre;
};

ptr last_node;
int realsize=1;
//functions prototype
ptr creation();
ptr add(ptr);
ptr sub(ptr);
ptr multi(ptr);
ptr divi(ptr);
ptr operationon(ptr, int, int);
int size(ptr);
int greaterabs(ptr, ptr);
void readfile(ptr);
void newnum(ptr);
void insert(int);
void printall(ptr);
void printres(ptr);
void menu();
void addzeros(ptr, int);
int sizeall(ptr);
void InsertNewResTomulti(ptr);
ptr rev(ptr);
int greaterdiv(ptr,ptr);
void insertres(ptr,int);
void printresfile(ptr);


int main(){
printf("****Hello****\n");

ptr list=creation();//create the main node...

     readfile(list);//read the text file.


         printall(list);
printf("\n\n");

 ptr res=(ptr)(malloc(sizeof(struct node)));res->subnext=null;//the list where the final result stored
 ptr opeon;//the list of two numbers that we need to do operations on them.

  printf("choose two numbers to do operations on them by typing the index of them:\n");
           int fir,sec;
        scanf("%d%d",&fir,&sec);

opeon=operationon(list,fir,sec);//copy the two numbers to opeon list..
 printall(opeon);

     int choice=0;
     while(choice!=8){

        menu();

      scanf("%d",&choice);
       switch(choice){
    case 1://addition..
         res=add(opeon);
 printres(res);opeon=operationon(list,fir,sec);

         break;
    case 2://subtraction..
        res=sub(opeon);
 printres(res);opeon=operationon(list,fir,sec);

         break;
    case 3://multiplication
  res= multi(opeon);
  printres(res);opeon=operationon(list,fir,sec);
         break;
    case 4://division
            printf("\nthe first num / the second num\n\n");
             if(greaterabs(opeon,opeon->next)){res=divi(opeon);printf("Result=");printres(res);opeon=operationon(list,fir,sec);}
                else printf("you must change the numbers, because in long division the first number must be greater than second one....or the result will be zeroo....");
         break;
    case 5://change the choosen number to another numbers
        printf("\n");
    printall(list);
    printf("\n");
         printf("choose two numbers to do operations on them by typing the index of them:\n");

        scanf("%d%d",&fir,&sec);
opeon=operationon(list,fir,sec);
 printf("\n");
 printall(opeon);

         break;
    case 6:
       list=creation();
         readfile(list);
         printall(list);
         printf("choose two numbers to do operations on them by typing the index of them:\n");

        scanf("%d%d",&fir,&sec);
opeon=operationon(list,fir,sec);
 printf("\n");
 printall(opeon);
         break;
    case 7://print output to text file.
        if(res->subnext==null)printf("you cant print without result in, you must do operation first");
        else
            printresfile(res);
          break;

    case 8://exiting the program......
        printf("good bye....");
         break;
    default: //if the entered choice is not from this list.
        printf("no no no you must choose from above choices");
     }

     }

return 0;
}

void menu(){//printing the main menu
    printf("\nChoose what-->\n\n1-add   2-sub   3-multi   4-div   5-change numbers   6-read file   7-write on file   8-exit.\n");
}

ptr add (ptr list){//addition function
ptr result;//the list where the result stored
   result=(ptr)(malloc(sizeof(struct node)));
    result->next=null;
     result->pre=null;
      result->sign='+';
       result->subnext=null;

ptr sign1,sign2;
sign1=list; //locating the first number with its sign
 sign2=list->next;//locating the second number with its sign
 subptr num1,num2;
 num1=sign1->subnext;//locating the first number
  num2=sign2->subnext;//locating the second number

int sum,carry;
 sum=0;carry=sum;
//now i need to check the sign for each number then do the needed;
   if((sign1->sign=='+')&& (sign2->sign=='+')){
       while(num1!=null || num2!= null){
            sum=0;carry=0;
        if(num1!=null)sum+=num1->data;
         if(num2!=null)sum+=num2->data;
          carry=sum/10;
           sum=sum%10;
             insertres(result,sum);
               if(num1!=null)num1=num1->next;
               if(num2!=null)num2=num2->next;
            if(carry!=0){
                if(num1)num1->data+=carry;
                 else if(num2)num2->data+=carry;
                 else {
                    insertres(result,carry);
                 }
            }
   }
   result->sign='+';//when add two positive number the res will be positive
   }

   else if((sign1->sign=='+')&& sign2->sign=='-'){
     // here i will send it to the subtraction function, cuz it will be subtraction, the first - the second
     sign2->sign='+';
     result=sub(list);sign2->sign='-';
   }
   else if(sign1->sign=='-' &&(sign2->sign=='+')){
     //this also will be a subtraction, the second - the first

      sign1->sign='+';ptr temp=list;list=list->next;list->next=temp;
      result=sub(list);temp=list->next;list->next=list;list=temp;
      sign1->sign='-';
   }
   else if(sign1->sign=='-' && sign2->sign=='-'){
      //this will be addition but at the end we will put - sign;
      while(num1!=null || num2!= null){
            sum=0;carry=0;
        if(num1!=null)sum+=num1->data;
         if(num2!=null)sum+=num2->data;
          carry=sum/10;
           sum=sum%10;
             insertres(result,sum);
               if(num1!=null)num1=num1->next;
               if(num2!=null)num2=num2->next;
            if(carry!=0){
                if(num1)num1->data+=carry;
                 else if(num2)num2->data+=carry;
                 else {
                    insertres(result,carry);
                 }
            }
   }
   result->sign='-';
   }

   subptr t=result->subnext;
     while(t->next!=null){t=t->next;}
    while(1){if(t->data!=0)break; t=t->pre;}
     t->next=null;//to delete the zeros in last of the result

return result;
}

ptr sub(ptr list){ // in subtraction we always have to sub the smaller from the larger e.g 98-2...
ptr result=(ptr)(malloc(sizeof(struct node)));
  result->next=null;
   result->pre=null;
    result->sign='+';
     result->subnext=null;

ptr sign1,sign2;
sign1=list;
 sign2=list->next;

 subptr num1,num2;
 num1=sign1->subnext;

  num2=sign2->subnext;


int sub=0;
 if((sign1->sign=='+')&& (sign2->sign=='+')){//done

       //normal subtraction but if the second is bigger then the sign will be minus
        if(greaterabs(sign2,sign1)){result->sign='-';subptr temp= num1;num1=num2;num2=temp;}//Values assigned to each others
                  //10   //15
    while(num1||num2){
        sub=0;
    if(num1)sub+=num1->data;
     if(num2)sub-=num2->data;
    if(sub<0){sub=0;(num1->next->data)--;num1->data+=10;if(num2)sub=num1->data-num2->data;else sub=num1->data;}
    insertres(result,sub);

      if(num1) num1=num1->next;if(num2)num2=num2->next;
                        }
  subptr temp= num2;num2=num1;num1=temp;//reset as they were
   }

   else if((sign1->sign=='+')&& sign2->sign=='-'){//155--458745 --> 155+458745
       sign2->sign='+';result=add(list);sign2->sign='-';
   }
   else if(sign1->sign=='-' &&(sign2->sign=='+')){
sign1->sign='+';result=add(list);result->sign='-';sign1->sign='-';
   }
   else if(sign1->sign=='-' && sign2->sign=='-'){
       sign2->sign='+';
       result=add(list);
       sign2->sign='-';
    }

    subptr t=result->subnext;
     while(t->next!=null){t=t->next;}
    while(1){if(t->data!=0)break; t=t->pre;}
     t->next=null;//to delete the zeros in last of the result

return result;
}

ptr multi(ptr list){//done
ptr result=(ptr)(malloc(sizeof(struct node)));
  result->next=null;
   result->pre=null;
    result->sign='+';
     result->subnext=null;

ptr sign1=list;
ptr sign2=list->next;
//the signs here doesn't need alot of attention cuz of we have one minus then the res will be minus then if two minus then the res is positive and so on...

    if(size(sign1)<size(sign2)){subptr temp= sign1;sign1=sign2;sign2=temp;}//to save as many lists as we can


int ZeroToAdd=0;
 subptr large=sign1->subnext,small=sign2->subnext;//located the first number and second number;

ptr t=result;int mu=0,carry=0;
while(small!=null){
addzeros(t,ZeroToAdd);
 large=sign1->subnext;
    while(large!=null){
         //addzeros(t,ZeroToAdd);

    mu=small->data;
     mu*=large->data;
      int res=mu;
    res+=carry;
     mu=res;
     carry=0;
    if(res>=10){
        res=mu%10;

         insertres(t,res);
          carry=(mu/10);
    }
    else{
         insertres(t,res);
    }
if(large->next==null&&carry!=0){insertres(t,carry);carry=0;}

        large=large->next;
    }

 small=small->next;ZeroToAdd++;if(small){InsertNewResTomulti(result);t=t->next;}
}
int positive=0,negative=0;
 if((sign1->sign=='+'&&sign2->sign=='+')||(sign1->sign=='-'&&sign2->sign=='-'))positive=1;
  else if((sign1->sign=='+'&&sign2->sign=='-')||(sign1->sign=='-'&&sign2->sign=='+'))negative=1;
//the result list is ready, now i have to add them all;
if(sizeall(result)==1){
        if(positive)result->sign='+';
        else result->sign='-';
        return result;}
else{
        ptr first=result;
     while(first->next !=null)first=first->next;//final res;
ptr second=first->pre;

        if(sizeall(result)==2){
                ptr f=add(second);
        if(positive)f->sign='+';
        else f->sign='-';
            return f;
        }

 ptr re=add(second);

int s=sizeall(result)-2;
 while(s--){//to always add the results to find the true result...
         second=second->pre;
          second->next=re;
           re->next=null;
            re=add(second);
 }
 if(positive)re->sign='+';
        else re->sign='-';
 return re;
}
}

ptr divi(ptr list){

ptr result=(ptr)(malloc(sizeof(struct node)));
 result->next=null;
  result->pre=null;
   result->subnext=null;
ptr sign1=list,sign2=list->next;
//the first number is greater than second, so now we should do the work;;;;;;;
   //55555                  //1234

ptr rem=(ptr)(malloc(sizeof(struct node)));
 rem->next=null;
  rem->pre=null;
   rem->subnext=null;rem->sign='+';char sign=sign2->sign;sign2->sign='+';
   sign1=rev(sign1);
    sign2=rev(sign2);
subptr num1=sign1->subnext,num2=sign2->subnext;

rem->next=sign2;
int i=1;
while(num1!=null){int resdiv=0; // until you reach the final digit in the bigger number
   while(!(greaterdiv(rem,sign2))&&num1!=null){//until the rem get bigger than the second number.
    insertres(rem,num1->data);if((!(greaterdiv(rem,sign2)))&&i==0){insertres(result,0);i=0;}
     num1=num1->next;
   }
                  //46   //15

   while(greaterdiv(rem,sign2)){//to calculate the division result by subtraction until its get smaller than the second number.
        ptr one=rev(rem),two=rev(sign2);one->next=two;
     ptr r=sub(one);rem=rev(r); rem->next=sign2;resdiv++;
   }//rem=1
   insertres(result,resdiv);
}


sign1->next=sign2;
sign2->next=null;
sign1->pre=null;
 sign2->pre=sign1;//to be sure that all thing are all right
rem->next=null;



result=rev(result);
subptr t=result->subnext;
     while(t->next!=null){t=t->next;}
    while(1){if(t->data!=0)break; t=t->pre;}
     t->next=null;//to delete the zeros in last of the result


printf("Remainder =");printres(rem);

if((sign1->sign=='+'&&sign=='+')||(sign1->sign=='-'&&sign=='-'))result->sign='+';
 else if((sign1->sign=='+'&&sign=='-')||(sign1->sign=='-'&&sign=='+'))result->sign='-';

return result;
}

ptr rev(ptr list){//reverse lists function
 ptr res=(ptr)(malloc(sizeof(struct node)));
  res->next=null;
   res->pre=null;
    res->subnext=null;res->sign='+';

subptr t=list->subnext;
while(t->next!=null)t=t->next;
insertres(res,t->data);
while(t->pre!=list){
   t=t->pre; insertres(res,t->data);
}

return res;

}


int sizeall(ptr res){//get the bigger list size
  ptr t=res;int size=1;
   while(t->next!=null){size++;t=t->next;}
return size;
}

void InsertNewResTomulti(ptr res){//insert new number node not digit node
     ptr t=res;
      while(t->next!=null)t=t->next;
ptr temp=(subptr)(malloc(sizeof(struct subnode)));
 temp->next=null;
  temp->pre=t;
   t->next=temp;
    temp->sign='+';
     temp->subnext=null;

}


void addzeros(ptr res,int times){//this function is to add zeros to the first of new result in mult operation
if (times==0) return;
else{
        ptr t=res;
        subptr temp=(subptr)(malloc(sizeof(struct subnode)));
         temp->data=0;
          temp->next=null;
   t->subnext=temp;
 temp->pre=t;


        times--;
   subptr tt=t->subnext;
    while(tt->next!=null)tt=tt->next;
     while(times--){
        subptr temp=(subptr)(malloc(sizeof(struct subnode)));
         temp->data=0;
          temp->next=null;
           tt->next=temp;
            temp->pre=tt;
    tt=tt->next;
     }
}

}

int size(ptr list){//get the digits size from specific list
  if(list->subnext==null)return 0;
 int s=1;
  ptr t=list;
   if(t->subnext!=null){
     subptr r=t->subnext;
      while(r->next!=null){s++;r=r->next;}

   }

return s;
}
                 //101    //100
int greaterabs(ptr glist,ptr slist){//check if the first list is bigger than the second or not (in reverse lists such as result not like number is div)

int sizeg=size(glist);

 int sizes=size(slist);



 if(sizeg>sizes){return 1;}
  else if(sizeg<sizes){return 0;}
else{

subptr t=glist->subnext;
subptr tt=slist->subnext;

  int sizef=sizes;
  while(t->next!= null){t=t->next;}
  while(tt->next)tt=tt->next;


  while(sizef--){
    if((t->data)>(tt->data)){return 1;}
     else if((t->data)<(tt->data)){return 0;}
      t=t->pre;tt=tt->pre;
}return 1;}
}
                          //sum

int greaterdiv(ptr glist,ptr slist){//to check if it bigger or not for div operation

int sizeg=size(glist);

 int sizes=size(slist);

 if(sizeg>sizes){return 1;}
  else if(sizeg<sizes){return 0;}
   else if(glist->subnext==null && slist->subnext==null)return 0;
    else if(glist->subnext==null && slist->subnext!=null)return 0;
     else if(glist->subnext!=null && slist->subnext==null) return 1;
else{

subptr t=glist->subnext;
subptr tt=slist->subnext;

  int sizef=sizes;

  while(sizef--){
    if((t->data)>(tt->data)){return 1;}
     else if((t->data)<(tt->data)){return 0;}
      t=t->next;tt=tt->next;
 // }

}return 1;}
}

void readfile(ptr list){
FILE* read;
   read=fopen("input.txt","r");
    char a;
    printf("Reading from file.....\n\n");
     while(fscanf(read,"%c",&a)!=EOF){
        if(a=='\n'){realsize++;newnum(list);}
         else if(a=='+'||a=='-'){
            last_node->sign=a;
         }else {
            insert(a-'0');
            }
       }
       fclose(read);
       printf("Reading done....\n\n\n");
}

ptr creation(){//create the main list node
   ptr list=(ptr)(malloc(sizeof(struct node)));//the first node, I don't want it to be a header to list of lists;
    list->next=null;
     list->pre=null;
      list->subnext=null;
       list->sign='+';
last_node=list;// this pointer is to make newnum function O(1)
return list;
}

void newnum(ptr list){

    ptr temp=(ptr)(malloc(sizeof(struct node)));
     temp->next=null;
      temp->subnext=null;
       temp->sign='+';
    ptr t=list;
     while(t->next !=null)t=t->next;
    t->next=temp;
     temp->pre=t;last_node=temp;

}

void insert(int data){
              // to add the number from the file to first of linked list;
  ptr t=last_node;
   subptr temp=(subptr)(malloc(sizeof(struct subnode)));
    temp->data=data;
     temp->next=t->subnext;
      if(t->subnext!=null)
         t->subnext->pre=temp;
     t->subnext=temp;
      temp->pre=t;
}

void printall(ptr list){
int s=1;
    ptr t=list;
   while(t->next!=null){
     printf("%d\) %c",s++,t->sign);
      subptr tt=t->subnext;
          while(tt->next!=null)tt=tt->next;
    while(1){
        printf("%d",tt->data);
    if(tt->pre == t){break;}
         tt=tt->pre;
   }
   printf("\n");t=t->next;
   }

    printf("%d\) %c",s,t->sign);

         subptr tt=t->subnext;
          while(tt->next!=null)tt=tt->next;
          while(1){
              printf("%d",tt->data);
               if(tt->pre == t){break;}
               tt=tt->pre;
          }
        printf("\n");
}

void printres(ptr list){

    ptr res=list;
     printf("%c",res->sign);
      subptr t=res->subnext;
       while(t->next!=null)t=t->next;
    while(1){

        printf("%d",t->data);
    if(t->pre == list){break;}
         t=t->pre;
   }
     printf("\n");
}

void insertres(ptr result,int data){//to insert digit to last of the list

    subptr temp=(subptr)(malloc(sizeof(struct subnode)));
     temp->data=data;
      temp->next=null;temp->pre=null;
    ptr t=result;
     subptr tt=t->subnext;
      if(tt == null){
        t->subnext=temp;
        temp->pre=t;
      }else{
        while(tt->next !=null)tt=tt->next;// to locate the last node in this list
    tt->next=temp;
     temp->pre=tt;
       }
}



 /*void inop(ptr oop,int data){
   subptr temp=(subptr)(malloc(sizeof(struct subnode)));
    temp->data=data;
temp->next=null;
 temp->pre=null;

if(oop->subnext==null){

        oop->subnext=temp;
  temp->next=null;
   temp->pre=oop;}
   else{
       subptr t=oop->subnext;
 while(t->next!=null){t=t->next;}

 t->next=temp;
  temp->next=null;
   temp->pre=t;
   }
}
*/
ptr operationon(ptr list,int i1,int i2){//to make opeon list which contain the two numbers that we need to do operations on them
    ptr oop;
oop=(ptr)(malloc(sizeof(struct node)));
 oop->subnext=null;
      oop->pre=null;
       oop->next=null;
ptr temp=(ptr)(malloc(sizeof(struct node)));
 oop->next=temp;
  temp->pre=oop;
   temp->subnext=null;
   temp->next=null;

  i1--;i2--;
ptr t=list;
 while(i1--){
    t=t->next;
 }//first num to do operations on it
oop->sign=t->sign;
 subptr y=t->subnext;

  while(1){
        insertres(oop,y->data);
        if(y->next==null)break;
        y=y->next;
  }

t=list;
 while(i2--){
    t=t->next;
 }//second num to do operations on it
    oop->next->sign=t->sign;
  y=t->subnext;
  while(1){
        insertres(oop->next,y->data);
        if(y->next==null)break;
        y=y->next;
  }

return oop;
}

void printresfile(ptr list){//this function do the file print work...
FILE* wr;
 wr=fopen("output.txt","w");
    ptr res=list;
     fprintf(wr,"%c",res->sign);
      subptr t=res->subnext;
       while(t->next!=null)t=t->next;
    while(1){

        fprintf(wr,"%d",t->data);
    if(t->pre == list){break;}
         t=t->pre;
   }
     fprintf(wr,"\n");fclose(wr);
}
