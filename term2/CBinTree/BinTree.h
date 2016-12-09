/************************************************************************
*file: BinTree.h
*purpose: BinTree class declaration
*author: Melnyk Andriy
*written: 02/02/2014
*last modified: 11/02/2014
*************************************************************************/

#pragma once

#include "TreeNode.h"
#include <vector>
#include <fstream>
#include <exception>
#include <string>
#include <algorithm>

class BinTree {

//use the variable 'traverse' in 'body' to refer to found node
#define SEARCH(startFrom,bodyIfFound,searchExpr,trnNumb)  \
							TreeNode* traverse = startFrom; \
							while (traverse) { \
								if (searchExpr) { \
									bodyIfFound\
									break; \
								} else {  \
									if (*traverse < trnNumb) \
										traverse = traverse->right; \
									else \
										traverse = traverse->left; \
								}} 

public:
	class FillingFailed : public exception {
		private:
			string msg;
		public:
			FillingFailed(const string f) : msg(string("File : ").append(f).append("\n\tFilling from the file failed.")) {
			}

			virtual const char* what() const throw() {
				return msg.c_str();
			}
	};

	BinTree() : root(NULL),size(0)	{}
	BinTree(const BinTree &tree) : size(tree.size) {
		TreeNode* _root = (tree.root)?(new TreeNode(*tree.root)):(NULL);
		root = _root;
	}
	BinTree(const TreeNode &node) : size(node.CalcSize()) {
		TreeNode* _root = new TreeNode(node);
		root = _root;
	}

	BinTree(const string csv_file);
	~BinTree() {
		delete root;
	}

	inline bool empty() const {
		return (root == NULL);
	}
	inline int GetSize() const {
		return size;
	}
	inline void Clear() {
		delete root;
		size =  0;
		root = NULL;
	}
	
	void InitFromCsv(const string csvFile);
	void AddTrain(const TreeNode &);
	void PrintTree() const;
	void PrintTrainInfo(unsigned int TrainNumb) const;
	void PrintDestPaths(const char* dest) const;

	//return value true->deleted 
	//			   false->does not exist
	bool DelByNumb(unsigned int TrainNumb);

	BinTree& operator=(const BinTree &tree);
private:
	int size;
	TreeNode* root;
	//void shake();
	void RecursiveSearchDest(TreeNode*,const char*,vector<TreeNode*> &ret) const;
	void RecursivePrint(const TreeNode* ) const;
};
