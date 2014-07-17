

#ifndef _D_NODE_LIST_H_
#define _D_NODE_LIST_H_

#include "DBase.h"
#include "DTrace.h"

template< class NODETYPE>
class IDNodeListT
{
public:
	virtual int GetSize() = 0;

	virtual DResult Add( NODETYPE pType ) = 0;

	virtual DResult Remove( NODETYPE pType ) = 0;

	virtual DResult InsertAtPos( NODETYPE pType, int pos ) = 0;

	virtual DResult RemoveAtPos( int pos ) = 0;

	virtual NODETYPE GetFirst() = 0;

	virtual DResult RemoveFirst() = 0;

	virtual void Clear() = 0;
};

template< class NODETYPE>
class CDNodeListT : public IDNodeListT<NODETYPE>
{
public:
	CDNodeListT();

	virtual ~CDNodeListT();

	virtual int GetSize();

	virtual DResult Add( NODETYPE pType );

	virtual DResult Remove( NODETYPE pType );

	virtual DResult InsertAtPos( NODETYPE pType, int pos );

	virtual DResult RemoveAtPos( int pos );

	virtual NODETYPE GetFirst();

	virtual DResult RemoveFirst();

	virtual void Clear();

	std::list<NODETYPE>& GetList();

	void Destory();

	void DestoryList();

private:
	std::list<NODETYPE>			m_list;
};

template< class NODETYPE>
void CDNodeListT<NODETYPE>::DestoryList()
{
	if ( 0 == this->GetSize() )
	{
		return;
	}

	std::list<NODETYPE>::iterator itorbegin = m_list.begin();
	std::list<NODETYPE>::iterator itorend = m_list.end();

	NODETYPE pNodeType = NULL;

	while( itorend != itorbegin )
	{
		pNodeType = (*itorbegin);

		pNodeType->OnDestory();

		pNodeType = NULL;

		itorbegin = m_list.erase( itorbegin );
	}
}

template< class NODETYPE>
void CDNodeListT<NODETYPE>::Destory()
{
	delete this;
}

template< class NODETYPE>
std::list<NODETYPE>& CDNodeListT<NODETYPE>::GetList()
{
	return m_list;
}

template< class NODETYPE>
void CDNodeListT<NODETYPE>::Clear()
{
	m_list.clear();
}

template< class NODETYPE>
DResult CDNodeListT<NODETYPE>::RemoveFirst()
{
	m_list.pop_front();

	return D_OK;
}

template< class NODETYPE>
NODETYPE CDNodeListT<NODETYPE>::GetFirst()
{
	if ( 0 == this->GetSize() )
	{
		return NULL;
	}

	NODETYPE pNode = *m_list.begin();

	D_ASSERT( NULL != pNode );

	return pNode;
}

template< class NODETYPE>
DResult CDNodeListT<NODETYPE>::RemoveAtPos( int pos )
{
	return D_ERROR_NOT_IMPLEMENTED;
}

template< class NODETYPE>
DResult CDNodeListT<NODETYPE>::InsertAtPos( NODETYPE pType, int pos )
{
	return D_ERROR_NOT_IMPLEMENTED;
}

template< class NODETYPE>
DResult CDNodeListT<NODETYPE>::Remove( NODETYPE pType )
{
	m_list.remove( pType );

	return D_OK;
}

template< class NODETYPE>
DResult CDNodeListT<NODETYPE>::Add( NODETYPE pType )
{
	D_ASSERT( NULL != pType );

	m_list.push_back( pType );

	return D_OK;
}

template< class NODETYPE>
int CDNodeListT<NODETYPE>::GetSize()
{
	return (int)(m_list.size());
}

template< class NODETYPE>
CDNodeListT<NODETYPE>::~CDNodeListT()
{
	this->DestoryList();
}

template< class NODETYPE>
CDNodeListT<NODETYPE>::CDNodeListT()
{

}

#endif	// _D_NODE_LIST_H_