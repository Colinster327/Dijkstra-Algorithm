/*
  Colin Murphy
  CS 3610 Data Structures
  GraphMinHeap.h
*/

#ifndef GRAPH_MIN_HEAP_H
#define GRAPH_MIN_HEAP_H

#include <vector>

using namespace std;

template <typename T>
class GraphMinHeap
{
public:
  struct HeapNode
  {
    // constructor
    HeapNode(const T data, const int key, int index) : data(data), key(key), index(index) {}
    T data;
    int key;
    int index; // holds index in heap for easy lookup
  };

  // constructor
  GraphMinHeap() {}

  // destructor
  ~GraphMinHeap()
  {
    while (heap.size() > 0) // deallocate all nodes
    {
      delete heap[heap.size() - 1];
      heap.pop_back();
    }
  }

  // Inserts a value into the min heap
  // precondition: const T data -> data to be inserted
  //               const int key -> the key used to sort data
  // postcondition: returns pointer to new node and inserts the node into min heap
  HeapNode *insert(const T data, const int key);

  // Creates a min heap in linear time
  // precondition: const T inputs[]
  //               const int keys[]
  //               int numInputs (length of inputs[] and keys[])
  // postcondition: returns vector<HeapNode *> of all memory addressess of node location
  //                in min heap in order they are in inputs[]; organizes nodes into min heap
  vector<HeapNode *> heapify(const T inputs[], const int keys[], int numInputs);

  // Decrease the key value in the node
  // precondition: int index (index of the node in the heap -> must be valid)
  //               int newKey (MUST BE LESS THAN ORIGINAL)
  // postcondition: no return, bubbles up to find new position in heap
  void decreaseKey(int index, int newKey);

  // Extracts and returns first node of min heap
  // precondition: heap of at least size 1
  // postcondition: returns the first node of min heap
  T extract_min();

  // Get the size of the min heap
  // precondition: NA
  // postcondition: returns the size of the min heap
  int size() const { return heap.size(); }

private:
  vector<HeapNode *> heap;

  // Bubbles down from specified index
  // precondition: int index
  // postcondition: no return, alters heap by bubbling down node
  void bubbleDown(int index);

  // Bubbles up from specified index
  // precondition: int index
  // postcondition: no return, alters heap by bubbling up node
  void bubbleUp(int index);
};

template <typename T>
vector<typename GraphMinHeap<T>::HeapNode *> GraphMinHeap<T>::heapify(const T inputs[], const int keys[], int numInputs)
{
  vector<HeapNode *> outputs; // to store pointers
  heap.clear();               // ensure heap is empty
  for (int i = 0; i < numInputs; i++)
  {
    HeapNode *newNode = new HeapNode(inputs[i], keys[i], outputs.size());
    outputs.push_back(newNode);
    heap.push_back(newNode); // add new node
  }

  for (int i = numInputs / 2 - 1; i >= 0; i--) // bubble down from lowest node with children to first node
    bubbleDown(i);

  return outputs; // return lookup table
}

template <typename T>
typename GraphMinHeap<T>::HeapNode *GraphMinHeap<T>::insert(const T data, const int key)
{
  HeapNode *newNode = new HeapNode(data, key, heap.size());
  heap.push_back(newNode);   // add to the end
  bubbleUp(heap.size() - 1); // bubble up from last index

  return newNode;
}

template <typename T>
void GraphMinHeap<T>::decreaseKey(int index, int newKey)
{
  if (newKey > heap[index]->key)
    throw "Error: key is not less than original";

  heap[index]->key = newKey; // update key value
  bubbleUp(index);           // bubble up from index
}

template <typename T>
T GraphMinHeap<T>::extract_min()
{
  T data;

  if (heap.size() == 0) // no nodes
    throw "Error: heap is empty";

  if (heap.size() == 1) // 1 node
  {
    data = heap[0]->data; // save first node
    delete heap[0];       // deallocate memory
    heap.pop_back();      // delete the only node
  }
  else // at least 2 nodes
  {
    data = heap[0]->data;                 // save first node
    delete heap[0];                       // deallocate memory
    swap(heap[0], heap[heap.size() - 1]); // swap first and last node
    heap[0]->index = 0;                   // assign new top to index 0
    heap.pop_back();                      // delete last node

    bubbleDown(0); // bubble down from index 0
  }

  return data;
}

template <typename T>
void GraphMinHeap<T>::bubbleDown(int index)
{
  int currentIndex = index;
  int leftChildIndex = 2 * currentIndex + 1;
  int rightChildIndex = 2 * currentIndex + 2;

  while (leftChildIndex <= heap.size() - 1) // while there is a left child
  {
    if (rightChildIndex <= heap.size() - 1 && heap[leftChildIndex]->key > heap[rightChildIndex]->key) // use right child
    {
      if (heap[currentIndex]->key > heap[rightChildIndex]->key)
      {
        swap(heap[currentIndex], heap[rightChildIndex]);               // swap if current is greater
        swap(heap[currentIndex]->index, heap[rightChildIndex]->index); // swap indeces
        currentIndex = rightChildIndex;
      }
      else // else -> exit loop
        break;
    }
    else // use left child
    {
      if (heap[currentIndex]->key > heap[leftChildIndex]->key)
      {
        swap(heap[currentIndex], heap[leftChildIndex]);               // swap if current is greator
        swap(heap[currentIndex]->index, heap[leftChildIndex]->index); // swap indeces
        currentIndex = leftChildIndex;
      }
      else // else -> exit loop
        break;
    }

    // iterate to next index values
    leftChildIndex = 2 * currentIndex + 1;
    rightChildIndex = 2 * currentIndex + 2;
  }
}

template <typename T>
void GraphMinHeap<T>::bubbleUp(int index)
{
  int currentIndex = index;                    // newNode index
  double parentIndex = (currentIndex - 1) / 2; // parent index -> keep decimal for sign
  while (parentIndex >= 0)
  {
    int trueParentIndex = parentIndex; // cast parent index back to int
    if (heap[currentIndex]->key < heap[trueParentIndex]->key)
    {
      swap(heap[currentIndex], heap[trueParentIndex]);               // swap values
      swap(heap[currentIndex]->index, heap[trueParentIndex]->index); // swap index values
      currentIndex = trueParentIndex;
      parentIndex = (currentIndex - 1) / 2;
    }
    else
      break;
  }
}

#endif // GRAPH_MIN_HEAP_H