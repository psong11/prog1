#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node node;
struct node
{
    int data;
    node *next;
};

int main()
{
    srand(time(NULL));
    cout << "hello world" << endl;

    return 0;
}