// Huffman Coding using minheaps
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//caluculating maximum height of huffman tree
#define MAX_TREE_HT 100
//declaring a huffman tree node
struct MinHNode {
  char item;
  unsigned freq;
  struct MinHNode *left, *right;
};
//Minheap-group of huffman tree nodes/min heaps
struct MinHeap {
  unsigned size;
  unsigned capacity;
  struct MinHNode **array;
};
// Create nodes by allotting a min heap with given character and frequency
struct MinHNode *newNode(char item, unsigned freq) {
//creating a min heap temp
  struct MinHNode *temp = (struct MinHNode *)malloc(sizeof(struct MinHNode));
  temp->left = temp->right = NULL;
  temp->item = item;
  temp->freq = freq;

  return temp;
}

// Create min heap and assigning size,capacity
struct MinHeap *createMinH(unsigned capacity) {
  struct MinHeap *minHeap = (struct MinHeap *)malloc(sizeof(struct MinHeap));

  minHeap->size = 0;

  minHeap->capacity = capacity;

  minHeap->array = (struct MinHNode **)malloc(minHeap->capacity * sizeof(struct MinHNode *));
  return minHeap;
}

// Function to swap two min heap nodes
void swapMinHNode(struct MinHNode **a, struct MinHNode **b) {
  struct MinHNode *t = *a;
  *a = *b;
  *b = t;
}

// Heapify function
void minHeapify(struct MinHeap *minHeap, int idx) {
  int smallest = idx;
  int left = 2 * idx + 1;
  int right = 2 * idx + 2;

  if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
    smallest = left;

  if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
    smallest = right;

  if (smallest != idx) {
    swapMinHNode(&minHeap->array[smallest], &minHeap->array[idx]);
    minHeapify(minHeap, smallest);
  }
}

// veifying whether size if 1
int checkSizeOne(struct MinHeap *minHeap) {
  return (minHeap->size == 1);
}

// Extract min value node from heap
struct MinHNode *extractMin(struct MinHeap *minHeap) {
  struct MinHNode *temp = minHeap->array[0];
  minHeap->array[0] = minHeap->array[minHeap->size - 1];

  --minHeap->size;
  minHeapify(minHeap, 0);

  return temp;
}
// Inserting new node to Min heap
void insertMinHeap(struct MinHeap *minHeap, struct MinHNode *minHeapNode) {
  ++minHeap->size;
  int i = minHeap->size - 1;

  while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
    minHeap->array[i] = minHeap->array[(i - 1) / 2];
    i = (i - 1) / 2;
  }
  minHeap->array[i] = minHeapNode;
}
//function for building minimum heap
void buildMinHeap(struct MinHeap *minHeap) {
  int n = minHeap->size - 1;
  int i;

  for (i = (n - 1) / 2; i >= 0; --i)
    minHeapify(minHeap, i);
}
//function to check whether it is leaf or not
int isLeaf(struct MinHNode *root) {
  return !(root->left) && !(root->right);
}

struct MinHeap *createAndBuildMinHeap(char item[], int freq[], int size) {
  struct MinHeap *minHeap = createMinH(size);

  for (int i = 0; i < size; ++i)
    minHeap->array[i] = newNode(item[i], freq[i]);

  minHeap->size = size;
  buildMinHeap(minHeap);

  return minHeap;
}
//main function that builds the huffman tree
struct MinHNode *buildHuffmanTree(char item[], int freq[], int size) {
  struct MinHNode *left, *right, *top;
  struct MinHeap *minHeap = createAndBuildMinHeap(item, freq, size);

  while (!checkSizeOne(minHeap)) {
    left = extractMin(minHeap);
    right = extractMin(minHeap);

    top = newNode('$', left->freq + right->freq);

    top->left = left;
    top->right = right;

    insertMinHeap(minHeap, top);
  }
  return extractMin(minHeap);
}
// Print the array by transversing
void printArray(int arr[], int n) {
  int i;
  for (i = 0; i < n; ++i)
    printf("%d", arr[i]);

  printf("\n");
}
void spacer(int x){
  if(x>9 && x<100){
         //printf(" |");
     }
    if(x<10){
         //printf("  |");
     }
     if(x>100){
        // printf("|");
     }   
}
int ark[1251];
int check(int arr[],int x){
    if(arr[x]==0){
        return x;
    }
     x=x+1;
     check(arr,x);
}

//prints huffman codes from the roots of huffman tree
void printHCodes(struct MinHNode *root, int arr[], int top) {
  if (root->left) {
    arr[top] = 0;
    printHCodes(root->left, arr, top + 1);
  }
  if (root->right) {
    arr[top] = 1;
    printHCodes(root->right, arr, top + 1);
  }
  if (isLeaf(root)) {
    //printf("  %c   | ", root->item);
     //printf("  %d   ", root->freq);
     int x=root->freq;
     int y=x*top;
     x=check(ark,x);
     ark[x]=y;
     spacer(x);
     //printf("  %d  |",top);
     //printf("  %d  ",y);
     //spacer(y);
     //printf("  ");
    //printArray(arr, top);
  }
}

// Wrapper function
void HuffmanCodes(char item[], int freq[], int size) {
  struct MinHNode *root = buildHuffmanTree(item, freq, size);

  int arr[MAX_TREE_HT], top = 0;

  printHCodes(root, arr, top);
}
void printsum(int arr[]){
    float sum=0;
    for(int i=0;i<131;i++){
        sum=sum+arr[i];
    }
    //sum=sum/10000;
    printf("Expected code length=%f",sum);
}
int main() {
    for(int i=0;i<200;i++){
    int lower = 1, upper = 36;
        int num = (rand() % (upper - lower + 1)) + lower;
        char* arr;
        int* freq;
     char ar[] = {'A', 'B', 'C', 'D', 'E', 'F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j'};
       arr = calloc(num, sizeof(char) ); 
       freq = calloc(num, sizeof(int));
        for(int j=0;j<num;j++){
            arr[j]=ar[j];
        }
  for(int l=0;l<num;l++){
    int lowr = 1, uppr = 500;
        freq[l] = (rand() % (uppr - lowr + 1)) + lowr;  
  }
  
  clock_t t;
    t = clock();
  //printf("letter|frequency|Huffman code ");
  //printf("\n------------------------\n");
  HuffmanCodes(arr, freq, num);
   t = clock() - t;
    double time_taken = (((double)t)/CLOCKS_PER_SEC)*1000000;
    
    printf("%d,",num);
     printf("%.f\n", time_taken);
  //printsum(ark);
   }
}
