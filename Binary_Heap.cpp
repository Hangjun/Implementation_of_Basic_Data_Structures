/* Implementation of a Binary Heap with Nodes Integers. 
** One can specify whether a max or a min hep needs to be constructed.
** By default, a max heap will be constructed.
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
        
        /* Build a heap from a given vector: O(n) Time */
        Heap (vector<int> &values, bool isMax = true) {
            int size = values.size();
            nodes.resize(size);
            isMaxHeap = isMax;
            for (int i = 0; i < size; i++)
                nodes[i] = values[i];
            // adjust to maintain heap condition
            for (int i = size/2; i >= 0; i--)
                percolateDown(i);
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
        
        void printHeapVals () {
            if (isEmpty())  return;
            for (int i = 0; i < nodes.size(); i++)
                cout << nodes[i] << "  ";
            cout << endl;
        }
        
        bool isEmpty () {
            return nodes.size() == 0;
        }
        
        int size () {
            return nodes.size();
        }
        
        /* Insertion: Return true/false to indicate if insertion is successful */
        void push (int val) {
            // need to throw an exception if memory alloc fails
            nodes.push_back(val); // insert at the end first
            // check heap condition recursively on its parent node
            int curIndex = nodes.size()-1;
                percolateUp(curIndex);
        }
        
        /* Remove the top node */
        int pop () {
            if (isEmpty())  return INT_MIN;
            int rootVal = nodes[0];
            swap (0, nodes.size()-1);
            nodes.pop_back();
            // adjust new root
            if (!nodes.empty() > 0)
                percolateDown(0);
            return rootVal;
        }
        
        int top () {
            if (isEmpty())  return INT_MIN;
            return nodes[0];
        }
        
        int find(int value) {
            for (int i = 0; i < nodes.size(); i++) {
                if (nodes[i] == value) {
                    return i;
                }
            }
            return -1; // not found
        }
        
        /* Delete the node of the give value: O(n) Time */
        void deleteNode (int value) {
            // scan the heap to locate the requested node
            int curIndex = find (value);
            if (curIndex == -1)  return; // requested node not found
            swap (curIndex, nodes.size()-1);
            nodes.pop_back();
            int parentIndex = (curIndex-1)/2;
            if (isMaxHeap) {
                if (nodes[curIndex] > nodes[parentIndex])
                    percolateUp(curIndex);
                else
                    percolateDown(curIndex);
            } else {
                if (nodes[curIndex] < nodes[parentIndex])
                    percolateUp(curIndex);
                else
                    percolateDown(curIndex);
            }
        }
        
    private:
        void swap (int indx, int indy) {
            int tmp = nodes[indx];
            nodes[indx] = nodes[indy];
            nodes[indy] = tmp;
        }
        
        void percolateUp (int curIndex) {
            int parentIndex = (curIndex-1)/2;
            while (parentIndex >=0 && ((isMaxHeap && nodes[parentIndex] < nodes[curIndex]) || (!isMaxHeap && nodes[parentIndex] > nodes[curIndex]))) {
                // swap to maintain the heap condition
                swap(curIndex, parentIndex);
                curIndex = parentIndex;
                parentIndex = (curIndex-1)/2;
            }
        }
        
        void percolateDown (int curIndex) {
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



/* Tested on LintCode Problem 81: Data Stream Median */
class Solution {
public:
    /**
     * @param nums: A list of integers.
     * @return: The median of numbers
     */
    vector<int> medianII(vector<int> &nums) {
        // min queue size <= max queue size + 1
        vector<int> result;
        if (nums.empty())  return result;
        int median = nums[0];
        result.push_back(median);
        Heap maxHeap(true);
        // change default max heap setting to min heap
        Heap minHeap(false);
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] >= median) 
                minHeap.push(nums[i]);
            else
                maxHeap.push(nums[i]);
            // rebalance the two heaps
            if (maxHeap.size() > minHeap.size()) {
                minHeap.push(median);
                median = maxHeap.top();
                maxHeap.pop();
            }
            if (maxHeap.size() + 1 < minHeap.size()) {
                maxHeap.push(median);
                median = minHeap.top();
                minHeap.pop();
            }
            result.push_back(median);
        }
        return result;
    }
};



        
        

