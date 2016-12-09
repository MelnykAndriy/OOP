/************************************************************************
*file: TreeNode.h
*purpose: TreeNode class declaration
*author: Melnyk Andriy
*written: 02/02/2014
*last modified: 11/02/2014
*************************************************************************/

#pragma once
#pragma warning (disable : 4996)
#include <string.h>
#include <iostream>
#include <iomanip>

using namespace std;

class TreeNode {
friend class BinTree;
#define RECURSIVE_COPY(from)if (from.left) { \
								TreeNode* leftNew = new TreeNode(*from.left); \
								left = leftNew; } else left = NULL; \
							if (from.right) { \
								TreeNode* rightNew = new TreeNode(*from.right); \
								right = rightNew; 	} else right = NULL;
public:
	TreeNode();
	TreeNode(unsigned short numb,const char* dest,const char* departure);
	TreeNode(const TreeNode &);
	~TreeNode();
	
	TreeNode& operator=(const TreeNode&);
	inline bool TreeNode::operator<(const TreeNode &node){
		return (m_TrainNumber < node.m_TrainNumber)?(true):(false);
	}

	inline bool operator>(const TreeNode &node){
		return (m_TrainNumber > node.m_TrainNumber)?(true):(false);
	}

	inline bool operator<(int val){
		return (m_TrainNumber < val)?(true):(false);
	}

	inline bool operator>(int val){
		return (m_TrainNumber > val)?(true):(false);
	}

	inline unsigned short GetTrainNumber() const {
		return m_TrainNumber;
	}

	int CalcSize() const;

	inline char* GetDestination() const {
		return (m_Destination)?(strcpy(new char[strlen(m_Destination)+1],m_Destination)):(NULL);
	}

	inline char* GetDeparture() const {
		return (m_DepartureTime)?(strcpy(new char[strlen(m_DepartureTime)+1],m_DepartureTime)):(NULL);
	}

	inline TreeNode* GetLeftNode() {
		return left;
	}

	inline TreeNode* GetRightNode() {
		return right;
	}
	
	inline void SetLeftNode(TreeNode* node) {
		if (left) delete left; 
		left = node;
	}

	inline 	void SetRightNode(TreeNode* node) {
		if (right) delete right;
		right = node;
	}

	inline void Print () const {
		cout << setw(15)  << m_TrainNumber << setw(18) << m_DepartureTime << setw(15) << m_Destination << endl;
	}
	
private:
	TreeNode* left;
	TreeNode* right;
	unsigned short m_TrainNumber;
	char* m_Destination;
	char* m_DepartureTime;
};

#pragma warning (default : 4996)