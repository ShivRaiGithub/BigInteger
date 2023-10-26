
#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *next;
};

struct BigInteger{
    struct node *L;
    int sign;
    int size;
    int dig;
};



struct node *createNode(int data) {
  struct node *newNode = (struct node *)malloc(sizeof(struct node));
  if (!newNode) {
    printf("Memory error\n");
    return NULL;
  }
  newNode->data = data;
  newNode->next = NULL;
  return newNode;
}

int getNumber(struct node *head) {
  int num = 0;
  while (head != NULL) {
    num = num * 10 + head->data;
    head = head->next;
  }
  return num;
}

struct node *createList(int num) {
  struct node *head = NULL;
  struct node *temp = NULL;
  do {
    int digit = num % 10;
    num /= 10;
    struct node *newNode = createNode(digit);
    if (head == NULL) {
      head = newNode;
      temp = newNode;
    } else {
      temp->next = newNode;
      temp = newNode;
    }
  } while (num > 0);
  return head;
}

void displayList(struct node *head) {
  if (head == NULL) {
    return;
  }
  displayList(head->next);
  printf("%d", head->data);
}

void displayStr(struct BigInteger *d){
    displayList(d->L);
    printf("\n");
}

struct node *reverse(struct node *head) {
  struct node *prev = NULL;
  struct node *current = head;
  struct node *next = NULL;
  while (current != NULL) {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }
  head = prev;
  return head;
}

void changeSign(struct node *head) {
  if (head == NULL) {
    return;
  }
  while (head->next) {
    head = head->next;
  }
  head->data = -(head->data);
}

int negativeSign(struct node *head) {
  if (head == NULL) {
    return 0;
  }
  while (head->next) {
    head = head->next;
  }
  return ((head->data) < 0) ? 1 : 0;
}

struct node *addLists(struct node *first, struct node *second) {
  struct node *result = NULL;
  struct node **temp = &result;
  int carry = 0;
  while (first != NULL || second != NULL) {
    int sum = carry;
    if (first != NULL) {
      sum += first->data;
      first = first->next;
    }
    if (second != NULL) {
      sum += second->data;
      second = second->next;
    }
    carry = (sum >= 10) ? 1 : 0;
    sum = sum % 10;
    *temp = (struct node *)malloc(sizeof(struct node));
    (*temp)->data = sum;
    (*temp)->next = NULL;
    temp = &((*temp)->next);
  }
  if (carry > 0) {
    *temp = (struct node *)malloc(sizeof(struct node));
    (*temp)->data = carry;
    (*temp)->next = NULL;
  }
  return result;
}

struct node *subtractLists(struct node *first, struct node *second) {
  struct node *result = NULL;
  struct node **temp = &result;
  int borrow = 0;
  while (first != NULL || second != NULL) {
    int diff = (first != NULL ? first->data : 0) -
               (second != NULL ? second->data : 0) - borrow;
    if (diff < 0) {
      diff += 10;
      borrow = 1;
    } else {
      borrow = 0;
    }
    *temp = (struct node *)malloc(sizeof(struct node));
    (*temp)->data = diff;
    (*temp)->next = NULL;
    temp = &((*temp)->next);
    if (first != NULL)
      first = first->next;
    if (second != NULL)
      second = second->next;
  }
  return result;
}


int multiply(int num1, int num2) { return num1 * num2; }
int divide(int num1, int num2) { return num1 / num2; }
int modulus(int num1, int num2) { return num1 % num2; }

struct node *multiplyLists(struct node *first, struct node *second) {
  first = reverse(first);
  second = reverse(second);
  int num1 = getNumber(first);
  int num2 = getNumber(second);
  int product = multiply(num1, num2);
  return createList(product);
}

struct node *divideLists(struct node *first, struct node *second) {
  first = reverse(first);
  second = reverse(second);
  int num1 = getNumber(first);
  int num2 = getNumber(second);
  int product = divide(num1, num2);
  return createList(product);
}

struct node *modulusLists(struct node *first, struct node *second) {
  first = reverse(first);
  second = reverse(second);
  int num1 = getNumber(first);
  int num2 = getNumber(second);
  int product = modulus(num1, num2);
  return createList(product);
}


struct BigInteger* initialize(char* s){
    struct BigInteger *b=(struct BigInteger*)malloc(sizeof(struct BigInteger));
    b->dig=0;
    b->size=0;
    b->sign = 1;

    int i=0;
    if(*s=='-'){
        b->sign=-1;
        s++;
    }
    else if (*s=='+'){
        s++;
    }

    for(i;*(s+i)!='\0';i++){
        if(*(s+i)<'0' || *(s+i)>'9'){
            printf("Invalid Input");
            b->sign = 0;
            return b;
        }
        else {
            (b->dig)*=10;
            (b->dig)+=(*(s+i)-'0');

        }
        b->size++;

        }
        b->L=createList(b->dig);
        return b;

    }

void display(struct BigInteger *a){
    if(a->sign==0){
        printf("Invalid");
        return;
    }
    if(a->sign==-1){
        printf("-");
    }
    printf("%d\n",a->dig);
}

struct BigInteger* add(struct BigInteger *a, struct BigInteger *b){
    int number=0;
    struct BigInteger *c=(struct BigInteger*)malloc(sizeof(struct BigInteger));
    c->dig = (a->sign * a->dig) + (b->sign * b->dig);
    if(c->dig<0){
        c->sign=-1;
        c->dig*=-1;
    }
    else{
        c->sign=1;
    }
    c->L=addLists((a->L),(b->L));
    return c;   


}

struct BigInteger* sub(struct BigInteger *a, struct BigInteger *b){
    int number=0;
    struct BigInteger *c=(struct BigInteger*)malloc(sizeof(struct BigInteger));
    c->dig = (a->sign * a->dig) - (b->sign * b->dig);
    if(c->dig<0){
        c->sign=-1;
        c->dig*=-1;
    }
    else{
        c->sign=1;
    }
    c->L=subtractLists((a->L),(b->L));
    return c;   


}

struct BigInteger* mul(struct BigInteger *a, struct BigInteger *b){
    int number=0;
    struct BigInteger *c=(struct BigInteger*)malloc(sizeof(struct BigInteger));
    c->dig = (a->sign * a->dig) * (b->sign * b->dig);
    if(c->dig<0){
        c->sign=-1;
        c->dig*=-1;
    }
    else{
        c->sign=1;
    }
    c->L=multiplyLists((a->L),(b->L));
    return c;   


}


struct BigInteger* div1(struct BigInteger *a,struct  BigInteger *b){
    int number=0;
    struct BigInteger *c=(struct BigInteger*)malloc(sizeof(struct BigInteger));
    if (b->dig == 0) {
        printf("Division by zero is not allowed.\n");
        c->sign = 0;
        c->dig = 0;
        return c;
    }    
    c->dig = (a->sign * a->dig) / (b->sign * b->dig);
    if(c->dig<0){
        c->sign=-1;
        c->dig*=-1;
    }
    else{
        c->sign=1;
    }
    c->L=divideLists((a->L),(b->L));
    return c;   


}

struct BigInteger* mod(struct BigInteger *a,struct  BigInteger *b){
    int number=0;
    struct BigInteger *c=(struct BigInteger*)malloc(sizeof(struct BigInteger));
     if (b->dig == 0) {
        c->dig = 0;
    } else {
        c->dig = a->dig % b->dig;
    }
    if (c->sign==-1){
      c->sign=1;
    }
    c->L=modulusLists((a->L),(b->L));
    return c;   


}



int compare(struct BigInteger *a, struct BigInteger *b){
    if(a->sign==1 && b->sign==-1){
        return 1;
    }
    if(a->sign==-1 && b->sign==1){
        return -1;
    }
    if(a->sign==1 && b->sign==1){
        if(a->size>b->size){
            return 1;
        }
        else if(a->size<b->size){
            return -1;
        }
        else{
            struct node *temp1=a->L;
            struct node *temp2=b->L;
            while(temp1!=NULL){
                if(temp1->data>temp2->data){
                    return 1;
                }
                else if(temp1->data<temp2->data){
                    return -1;
                }
                temp1=temp1->next;
                temp2=temp2->next;
            }
            return 0;
        }
    }    }
    