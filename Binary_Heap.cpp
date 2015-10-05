/* Implementation of a Binary Heap with Nodes Integers. 
** One can specify whether a max or a min hep needs to be constructed.
** By default, a max heap will be constructed.
** We assume that there are no duplicates in the heap.
** 
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;

class Heap {
    public:
        Heap(int sz, bool isMax = true) {
            nodes.resize(sz);
            isMaxHeap = isMax;
        }
        
        Heap(bool isMax = true) {
            isMaxHeap = isMax;
        }
        
        Heap (vector<int> &values, bool isMax = true) {
            int size = values.size();
            nodes.resize(size);
            isMaxHeap = isMax;
            for (int i = 0; i < size; i++)
                nodes[i] = values[i];
            // adjust to maintain heap condition
            for (int i = size/2; i >= 0; i--)
                shiftDown(i);
        }
        
        ~Heap() {
            if (nodes.size() != 0)
                nodes.clear();
        }
        
        void getNodesValues (vector<int> &values) {
            if (values.size() != nodes.size())  return;
            for (int i = 0; i < nodes.size(); i++)
                values[i] = nodes[i];
        }
        
        bool isEmpty () {
            return nodes.size() == 0;
        }
        
        int getHeapRootValue () {
            if (isEmpty())  return INT_MIN;
            return nodes[0];
        }
        
        /* Insertion: Return true/false to indicate if insertion is successful*/
        bool push (int val) {
            // need to throw an exception if memory alloc fails
            nodes.push_back(val); // insert at the end first
            // check heap condition recursively on its parent node
            int curIndex = nodes.size()-1;
            int parentIndex = (curIndex-1)/2;
            while (parentIndex >= 0 && (isMaxHeap && nodes[parentIndex] < nodes[curIndex] || !isMaxHeap && nodes[parentIndex] > nodes[curIndex])) {
                // swap to maintain the heap condition
                swap(curIndex, parentIndex);
                curIndex = parentIndex;
                parentIndex = (curIndex-1)/2;
            }
            return true;
        }
        
        int pop () {
            if (isEmpty())  return INT_MIN;
            int rootVal = nodes[0];
            swap (0, nodes.size()-1);
            // adjust new root
            if (!nodes.empty() > 0)
                shiftDown(0);
            return rootVal;
        }
        
    private:
        void swap (int indx, int indy) {
            int tmp = nodes[indx];
            nodes[indx] = nodes[indy];
            nodes[indy] = tmp;
        }
        
        void shiftDown (int curIndex) {
            int size = nodes.size();
            int leftChild = curIndex*2+1;
            int rightChild = curIndex*2+2;
            while (leftChild < size || rightChild < size) {
                if (isMaxHeap) {
                    int leftValue = (leftChild < size) ? nodes[leftChild] : INT_MIN;
                    int rightValue = (rightChild < size) ? nodes[rightChild] : INT_MIN;
                    int maxChild = (leftValue < rightValue) ? rightChild : leftChild;
                    // check if swap is needed
                    if (nodes[curIndex] > nodes[maxChild])  break;
                    swap (curIndex, maxChild);
                    curIndex = maxChild;
                    leftChild = curIndex*2+1;
                    rightChild = curIndex*2+2;
                } else {
                    int leftValue = (leftChild < size) ? nodes[leftChild] : INT_MAX;
                    int rightValue = (rightChild < size) ? nodes[rightChild] : INT_MAX;
                    int minChild = (leftValue < rightValue) ? leftChild : rightChild;
                    // check if swap is needed
                    if (nodes[curIndex] < nodes[minChild])  break;
                    swap (curIndex, minChild);
                    curIndex = minChild;
                    leftChild = curIndex*2+1;
                    rightChild = curIndex*2+2;
                }
            }
        }
        
        // private members
        vector<int> nodes;
        bool isMaxHeap;
};



/* Tested on LintCode Problem 130: Heapify */
class Solution {
public:
    /**
     * @param A: Given an integer array
     * @return: void
     */
    void heapify(vector<int> &nums) {
        Heap minHeap(nums, false);
        minHeap.getNodesValues(nums);
    }
};
