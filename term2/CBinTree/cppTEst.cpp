

				if (traverse->right->right->CalcSize() < traverse->right->left->CalcSize()) {
					tmpTraversePred = traverse->right;
					tmpTraverse = traverse->right->left;
					CHECK_IF_NULL(tmpTraverse,right);
					while (tmpTraverse->right) {
						tmpTraversePred = tmpTraverse;
						tmpTraverse = tmpTraverse->right;
					}
					traverse->right->m_TrainNumber = tmpTraverse->m_TrainNumber;
					if (traverse->right == tmpTraversePred)
						tmpTraversePred->left = tmpTraverse->left;
					else
						tmpTraversePred->right = tmpTraverse->left;
					tmpTraverse->left = NULL;
                    
                    
                    
				} else {
                
                
                
					tmpTraversePred = traverse->right;
					tmpTraverse = traverse->right->right;
					CHECK_IF_NULL(tmpTraverse,right);
					while (tmpTraverse->left) {
						tmpTraversePred = tmpTraverse;
						tmpTraverse = tmpTraverse->left;
					}
					traverse->right->m_TrainNumber = tmpTraverse->m_TrainNumber;
					if (traverse->right == tmpTraversePred)
						tmpTraversePred->right = tmpTraverse->right;
					else
						tmpTraversePred->left = tmpTraverse->right;
					tmpTraverse->right = NULL;
				}
                
                
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
                                            
                                            
                                            
                                            
                                            
                                                
                                            

//SWAP without MACRO SWAP

				//if (traverse->right->right->CalcSize() < traverse->right->left->CalcSize()) {
				//	tmpTraversePred = traverse->right;
				//	tmpTraverse = traverse->right->left;
				//	CHECK_IF_NULL(tmpTraverse,right);
				//	while (tmpTraverse->right) {
				//		tmpTraversePred = tmpTraverse;
				//		tmpTraverse = tmpTraverse->right;
				//	}
				//	traverse->right->m_TrainNumber = tmpTraverse->m_TrainNumber;
				//	if (traverse->right == tmpTraversePred)
				//		tmpTraversePred->left = tmpTraverse->left;
				//	else
				//		tmpTraversePred->right = tmpTraverse->left;
				//	tmpTraverse->left = NULL;
				//} else {
				//	tmpTraversePred = traverse->right;
				//	tmpTraverse = traverse->right->right;
				//	CHECK_IF_NULL(tmpTraverse,right);
				//	while (tmpTraverse->left) {
				//		tmpTraversePred = tmpTraverse;
				//		tmpTraverse = tmpTraverse->left;
				//	}
				//	traverse->right->m_TrainNumber = tmpTraverse->m_TrainNumber;
				//	if (traverse->right == tmpTraversePred)
				//		tmpTraversePred->right = tmpTraverse->right;
				//	else
				//		tmpTraversePred->left = tmpTraverse->right;
				//	tmpTraverse->right = NULL;
				//}

	//expanded
	//TreeNode* traverse = imagineRoot; 
	//while (traverse) { 
	//	if ((traverse->left && traverse->left->m_TrainNumber == TrainNumb ) || 
	//		 (traverse->right && traverse->right->m_TrainNumber == TrainNumb)) { 
	//		TreeNode* tmpTraverse;
	//		TreeNode* tmpTraversePred;
	//		try {
	//			if (traverse->left && traverse->left->m_TrainNumber == TrainNumb) {
	//				DEL_IN_POINT_NODE(left);
	//			} else {
	//				DEL_IN_POINT_NODE(right);
	//			}
	//		} catch (exception e) {
	//			delete tmpTraverse;
	//			root = imagineRoot->left;
	//			imagineRoot->left = imagineRoot->right = NULL;
	//			delete imagineRoot;
	//			size--;
	//			return true; 
	//		}
	//	} else {  
	//		if (*traverse < TrainNumb) 
	//			traverse = traverse->right; 
	//		else 
	//			traverse = traverse->left; 
	//	}
	//} 
    
    
    
    
    #define ROOT_DEL(moveTo,rev)	ptrToDel = root;	\
								root = root->moveTo;	\
								if (root->rev)  AddTrain(*(root->rev));	\
								ptrToDel->moveTo = NULL;
    
    	//if (root->m_TrainNumber == TrainNumb) {
	//	TreeNode* ptrToDel;
	//	if (root->left->CalcSize() < root->right->CalcSize() ) {
	//		ROOT_DEL(right,left);
	//	} else {
	//		ROOT_DEL(left,right);
	//	}
	//	delete ptrToDel;
	//	return true;
	//}
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
template <typename T> class _iterator {
	template <typename U> friend class List;
private:
	T* ptr;
public:
	_iterator() { ptr = NULL; }
	_iterator(T* _ptr) { ptr = _ptr; }
	~_iterator() {}
	//typedef T value_type;
	typedef _iterator<T> it_type;
	T& operator *();
	void operator++();
	void operator--();
	int  operator-(const it_type &_iter) const;
	it_type operator+(int numb) const {
		int i = 0;
		_iterator<T>::it_type retIter = this;
		while (retIter.ptr->next != NULL && i++ != numb)
			retIter++;
		return retIter;
	}	

	it_type &operator=(const it_type &_iter) {
		this->ptr = _iter.ptr;
		return *this;
	}


	//dummy operator to keep compiler quiet
	void operator++(int);

	bool operator==(const it_type &_iter) const;
	bool operator!=(const it_type &_iter) const;
	bool empty() { return ptr == NULL;}
};

template <typename T> T& _iterator<T>::operator *() {
	return ptr;;
}

template <typename T> void _iterator<T>::operator++() {
	ptr = ptr->next;
}

template <typename T> void _iterator<T>::operator++(int) {
	ptr = ptr->next;
}
template <typename T> bool _iterator<T>::operator ==(const it_type &_iter) const {
	return (ptr == _iter.ptr);
}

template <typename T> bool _iterator<T>::operator!=(const it_type &_iter) const {
	return !(*this == _iter);
}
                                            