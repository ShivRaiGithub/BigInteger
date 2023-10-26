#ifndef BIGINTEGER_H
#define BIGINTEGER_H

struct node {
    int data;
    struct node* next;
};

struct BigInteger {
    struct node* L;
    int sign;
    int size;
    int dig;
};

 struct BigInteger* initialize(char* s);
 void display(struct BigInteger* a);
 struct node *createNode(int data);
int getNumber(struct node *head);
struct node *createList(int num);
void displayList(struct node *head);
void displayStr(struct BigInteger *d);
struct node *reverse(struct node *head);
void changeSign(struct node *head);
int negativeSign(struct node *head);
struct node *addLists(struct node *first, struct node *second);
struct node *subtractLists(struct node *first, struct node *second);
int multiply(int num1, int num2) ;
int divide(int num1, int num2) ;
int modulus(int num1, int num2) ;
struct node *multiplyLists(struct node *first, struct node *second);
struct node *divideLists(struct node *first, struct node *second);
struct node *modulusLists(struct node *first, struct node *second);
 struct BigInteger* add(struct BigInteger* a, struct BigInteger* b);
 struct BigInteger* sub(struct BigInteger* a, struct BigInteger* b);
 struct BigInteger* mul(struct BigInteger* a, struct BigInteger* b);
 struct BigInteger* div1(struct BigInteger* a, struct BigInteger* b);
 struct BigInteger* mod(struct BigInteger* a, struct BigInteger* b);
int compare(struct BigInteger *a, struct BigInteger *b);
 

#endif
