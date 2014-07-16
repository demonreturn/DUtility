
#ifndef _D_EVENT_NODE_T_H_
#define _D_EVENT_NODE_T_H_

#include "DBase.h"
#include "DAutoEvent.h"

#include "DTrace.h"

// Ͷ������
enum POSTSEND_TYPE
{
	POSTEVENT = 0,
	SENDEVENT = 1
};

// �¼����ȼ�
enum EVENT_PRIOTIRY
{
	LOW = 0,
	NORMAL = 1,
	HIGH = 2
};

class CDSyncAutoEvent
{
public:
	CDSyncAutoEvent( CDAutoEvent* pAutoEvent )
		: m_pAutoEvent( pAutoEvent )
		, m_DResult( D_ERROR_FAILURE )
	{
	}
	~CDSyncAutoEvent()
	{
	}

	void Signal( BOOL bSuccess )
	{
		if ( bSuccess == TRUE )
		{
			m_DResult = D_OK;
		}
		else
		{
			m_DResult = D_ERROR_FAILURE;
		}

		m_pAutoEvent->Signal();
	}

	DResult GetResult()
	{
		return m_DResult;
	}

private:
	CDAutoEvent*					m_pAutoEvent;
	DResult							m_DResult;
};

template< class TYPE>
class CDEventNodeT
{
public:
	CDEventNodeT();

	virtual ~CDEventNodeT();

	DResult SetEventNode( TYPE pType, POSTSEND_TYPE ps );

	DResult SetSyncEvent( CDSyncAutoEvent* pSyncAutoEvent = NULL );

	virtual DResult OnEvent();

	virtual DResult OnDestory();

	virtual int GetPriority();

	virtual DResult SetPriority( int nPriority );

	virtual BOOL operator < ( const CDEventNodeT<TYPE>& right );

	virtual BOOL operator > ( const CDEventNodeT<TYPE>& right );

private:
	DResult SignalSyncEvent( BOOL bSuccess );

	TYPE						m_pType;
	int							m_nPriority;
	POSTSEND_TYPE				m_ps;

	// �Զ��¼�������¼���������SendEvent�ȴ������ã�ͬ��
	CDSyncAutoEvent				m_pSyncAutoEvent;

	// ���˱���OnEventִ�еĽ����������SendDataʱ����Ҫ����OnEvent�ķ���ֵ
	// ����ʾ���ݷ����Ƿ�ɹ�����ǰ��ֵֻ��������;����ֵ��ͬ���������ʱ��
	// �����ж�����ͬ���Ժ�Ľ��Ϊ0-�ɹ�������-ʧ��
	int								m_EventRetValue; 
};

template< class TYPE>
DResult CDEventNodeT<TYPE>::SignalSyncEvent( BOOL bSuccess )
{
	switch ( m_ps )
	{
	case SENDEVENT:
		{
			if ( NULL == m_pSyncAutoEvent )
			{
				return -1;
			}

			m_pSyncAutoEvent->Signal( bSuccess );

			break;
		}
	case POSTEVENT:
	default:
		break;
	}
}

template< class TYPE>
BOOL CDEventNodeT<TYPE>::operator>( const CDEventNodeT<TYPE>& right )
{
	return this->m_nPriority > right.m_nPriority;
}

template< class TYPE>
BOOL CDEventNodeT<TYPE>::operator<( const CDEventNodeT<TYPE>& right )
{
	return this->m_nPriority < right.m_nPriority;
}

template< class TYPE>
DResult CDEventNodeT<TYPE>::SetPriority( int nPriority )
{
	m_nPriority = nPriority;

	return D_OK;
}

template< class TYPE>
int CDEventNodeT<TYPE>::GetPriority()
{
	return m_nPriority;
}

template< class TYPE>
DResult CDEventNodeT<TYPE>::OnDestory()
{
	D_CHECK_EX( NULL != m_pType, "", return D_ERROR_NULL_POINTER );

	m_pType->OnDestory();

	m_pType = NULL;

	DResult dRet = D_OK;
	if ( 0 == m_EventRetValue )
	{
		dRet = this->SignalSyncEvent( TRUE );
	}
	else
	{
		dRet = this->SignalSyncEvent( FALSE );
	}

	delete this;

	return dRet;
}

template< class TYPE>
DResult CDEventNodeT<TYPE>::OnEvent()
{
	D_CHECK_EX( NULL != m_pType, "", return D_ERROR_NULL_POINTER );

	m_EventRetValue = m_pType->OnEvent();

	return D_OK;
}

template< class TYPE>
DResult CDEventNodeT<TYPE>::SetSyncEvent( CDSyncAutoEvent* pSyncAutoEvent /*= NULL */ )
{
	D_CHECK_EX( NULL != pSyncAutoEvent, "", return D_ERROR_NULL_POINTER );

	m_pSyncAutoEvent = pSyncAutoEvent;

	return D_OK;
}

template< class TYPE>
DResult CDEventNodeT<TYPE>::SetEventNode( TYPE pType, POSTSEND_TYPE ps )
{
	D_CHECK_EX( NULL != pType, "", return D_ERROR_NULL_POINTER );

	m_pType = pType;
	m_ps = ps;

	return D_OK;
}

template< class TYPE>
CDEventNodeT<TYPE>::~CDEventNodeT()
{

}

template< class TYPE>
CDEventNodeT<TYPE>::CDEventNodeT()
	: m_pType( NULL )
	, m_nPriority( NORMAL )
	, m_ps( POSTEVENT )
	, m_pSyncAutoEvent( NULL )
	, m_EventRetValue( -1 )
{

}

#endif	// _D_EVENT_NODE_T_H_

