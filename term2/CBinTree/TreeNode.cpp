/************************************************************************
*file: TreeNode.cpp
*purpose: TreeNode interface implementation
*author: Melnyk Andriy
*written: 02/02/2014
*last modified: 11/02/2014
*************************************************************************/

#include "TreeNode.h"
#pragma warning (disable : 4996)

TreeNode::TreeNode(void){
	m_DepartureTime = NULL;
	m_Destination = NULL;
	left = NULL;
	right = NULL;
	m_TrainNumber = 0;

}

TreeNode::~TreeNode(void){
	delete[] m_DepartureTime;
	delete[] m_Destination;
	delete left;
	delete right;
}

TreeNode::TreeNode(unsigned short numb,const char* dest,const char* departure) : m_TrainNumber(numb),
				m_Destination((dest)?(strcpy(new char[strlen(dest)+1],dest)):(NULL)),
				m_DepartureTime((departure)?(strcpy(new char[strlen(departure)+1],departure)):(NULL)) {
	left = NULL;
	right = NULL;
}

TreeNode::TreeNode(const TreeNode &copy) {
	m_TrainNumber = copy.m_TrainNumber;
	m_Destination = copy.GetDestination();
	m_DepartureTime = copy.GetDeparture();
	RECURSIVE_COPY(copy);
}

TreeNode& TreeNode::operator=(const TreeNode &copy){
	m_TrainNumber = copy.m_TrainNumber;
	m_Destination = copy.GetDestination();
	m_DepartureTime = copy.GetDeparture();
	RECURSIVE_COPY(copy);
	
	return *this;
}

int TreeNode::CalcSize() const {
	if (this == NULL) return 0;
	return 1 + left->CalcSize() + right->CalcSize();
}


#pragma warning (default : 4996)