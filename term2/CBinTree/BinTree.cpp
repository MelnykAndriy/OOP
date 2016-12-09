/************************************************************************
*file: BinTree.cpp
*purpose: BinTree interface implementation
*author: Melnyk Andriy
*written: 02/02/2014
*last modified: 11/02/2014
*************************************************************************/

#include "BinTree.h"

BinTree::BinTree(const string csvFile) : size(0) {
	ifstream f;
	root = NULL;
	f.open(csvFile);
	string buf;
	while ( f.good() ) {

		getline(f,buf,'\n');
		size_t first = buf.find_first_of(';') ,second  = buf.find_last_of(';');
		if (first == string::npos ||first == second ||
			first == 0 || second == buf.length() - 1 ||
			first == second - 1 ) continue;

		TreeNode addNode = TreeNode(atoi(buf.substr(0,first).c_str()),
								    buf.substr(first + 1,second - first - 1).c_str(),
									buf.substr(second + 1 ,buf.length() - 1).c_str());
		AddTrain(addNode);
	}

	if ( f.fail() ) throw FillingFailed(csvFile);

	f.close();
}

void BinTree::InitFromCsv(const string csvFile) {
	delete root;
	BinTree tmp = BinTree(csvFile);
	root = tmp.root;
	this->size = tmp.size;
	tmp.root = NULL;
}

BinTree& BinTree::operator=(const BinTree &tree){
	TreeNode* _root = new TreeNode(*tree.root);
	size = tree.size;
	if (root) delete root;
	root = _root;
	return *this;
}

void BinTree::AddTrain(const TreeNode &newTrains) {
	TreeNode* addNode = new TreeNode(newTrains);

	if (!root) {
		root = addNode;
		size = addNode->CalcSize();
		return;
	}

	SEARCH(root,
			if (*traverse > *addNode) {
				traverse->left = addNode;
			} else {
				traverse->right = addNode;
			}	
			size += addNode->CalcSize();
			,(*traverse < *addNode && traverse->right == NULL || 
			 *traverse > *addNode && traverse->left == NULL)
			,*addNode);
}

void BinTree::RecursivePrint(const TreeNode* prnNode) const {
	if (!prnNode) return;

	RecursivePrint(prnNode->left);
	prnNode->Print();
	RecursivePrint(prnNode->right);
}

void BinTree::PrintTree() const {
	cout << setw(15)  << "Train Number" << setw(18) << "Departure Time" << setw(15) <<  "Destination" << endl;
	RecursivePrint(root);
}

void BinTree::PrintTrainInfo(unsigned int TrainNumb) const {
	SEARCH( root,
			cout << "Train number: " << TrainNumb << " information:"<< endl;
			cout << setw(17) << "Destination - " << traverse->m_Destination << endl 
				 << setw(18) << "Departure in - " << traverse->m_DepartureTime << endl;
			,TrainNumb == traverse->m_TrainNumber,TrainNumb);
}

void BinTree::RecursiveSearchDest(TreeNode* node,const char* searchDest,vector<TreeNode*> &ret) const {
	if (node == NULL)  return;

	RecursiveSearchDest(node->right,searchDest,ret);
	RecursiveSearchDest(node->left,searchDest,ret);
	if (strcmp(searchDest,node->m_Destination) == 0) {
		ret.push_back(node);
	}
}

void BinTree::PrintDestPaths(const char* dest) const {
	vector<TreeNode*> destPaths;
	RecursiveSearchDest(root,dest,destPaths);
	sort(destPaths.begin(),destPaths.end(),
		 [](TreeNode *x,TreeNode *y)->bool {
			return 	*x < *y;} );

	if (destPaths.empty()) {
		cout << "Information about trains which follow to " << dest << " is absent." << endl;
		return;
	}

	cout << "Trains which follow to " << dest << endl;
	cout << setw(15)  << "Train Number" << setw(18) << "Departure Time" << setw(15) <<  "Destination" << endl;
	for (vector<TreeNode*>::iterator iter = destPaths.begin() ; iter != destPaths.end() ; iter++)
		(*iter)->Print();
}

#define CHECK_IF_NULL(what,traversePoint)	if (!what) { \
												tmpTraverse = traverse->traversePoint;	\
												traverse->traversePoint = NULL; \
												throw exception();}

#define SWAP(modNode,invModNd,PointNd)  tmpTraversePred = traverse->PointNd; \
                                        tmpTraverse = traverse->PointNd->modNode; \
                                        CHECK_IF_NULL(tmpTraverse,PointNd); \
                                        while (tmpTraverse->invModNd) { \
                                            tmpTraversePred = tmpTraverse; \
                                            tmpTraverse = tmpTraverse->invModNd; \
                                        } \
                                        traverse->PointNd->m_TrainNumber = tmpTraverse->m_TrainNumber; \
                                        if (traverse->PointNd == tmpTraversePred) \
                                            tmpTraversePred->modNode = tmpTraverse->modNode; \
                                        else  \
                                            tmpTraversePred->invModNd = tmpTraverse->modNode; \
                                        tmpTraverse->modNode = NULL; \

#define DEL_IN_POINT_NODE(pointNd)	if (traverse->pointNd->right->CalcSize() < traverse->pointNd->left->CalcSize()) { \
										SWAP(left,right,pointNd); \
									} else { \
										SWAP(right,left,pointNd); \
									} \
									throw exception();

bool BinTree::DelByNumb(unsigned int TrainNumb) {
	TreeNode* imagineRoot = new TreeNode();
	imagineRoot->SetLeftNode(root);
	imagineRoot->SetRightNode(root);
	SEARCH(imagineRoot,
			TreeNode* tmpTraverse;
			TreeNode* tmpTraversePred;
			try {
				if (traverse->left && traverse->left->m_TrainNumber == TrainNumb) {
					DEL_IN_POINT_NODE(left);
				} else {
					DEL_IN_POINT_NODE(right);
				}
			} catch (exception e) {
				delete tmpTraverse;
				root = imagineRoot->left;
				imagineRoot->left = imagineRoot->right = NULL;
				delete imagineRoot;
				size--;
				return true; 
			}
			, 
			  (traverse->left && traverse->left->m_TrainNumber == TrainNumb ) || 
			 (traverse->right && traverse->right->m_TrainNumber == TrainNumb)
			,TrainNumb);

	return false;
}