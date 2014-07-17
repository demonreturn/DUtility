

#ifndef _D_TIMER_NODE_T_H_
#define _D_TIMER_NODE_T_H_

#include "DBase.h"
#include "DTimeValue.h"
#include "DThread.h"

template< class TIMETYPE, class TYPE >
class CDTimeNodeT
{
public:
	CDTimeNodeT();

	virtual ~CDTimeNodeT();

	virtual DResult OnTimer();

	virtual DResult OnDestory();

	DResult SetTimerNode( 
		TIMETYPE pTimeType,
		TYPE pType,
		INT64 timeTick,
		INT64 timeTickInterval,
		int runtimes = -1 );

	INT64 GetTimeTick();

	void SetTimeTick( INT64 timecount );

	INT64 GetIntervalTickCount();

	/*
	* ������	�������д�����������ʣ����������ԭ����-1����ʶѭ��ִ�У���
	*			�����Ծ���-1�����֮ǰ��������ѯ�������ڼ��ٴ�����ͬʱ����ʣ�������ֱ��0Ϊֹ��
	* ������	��
	* ����ֵ��	ִ�д����� -1��ʾѭ��
	*/
	int DecreaseRunTimes();

	TIMETYPE GetTimerType();

	virtual BOOL operator < ( const CDTimeNodeT<TIMETYPE,TYPE>& right ) const;

	virtual BOOL operator > ( const CDTimeNodeT<TIMETYPE,TYPE>& right ) const;

	virtual BOOL operator <= ( const CDTimeNodeT<TIMETYPE,TYPE>& right ) const;

	virtual BOOL operator >= ( const CDTimeNodeT<TIMETYPE,TYPE>& right ) const;

private:
	CDTimeNodeT( const CDTimeNodeT<TIMETYPE,TYPE>& tNode );

	CDTimeNodeT& operator = ( const CDTimeNodeT<TIMETYPE,TYPE>& tNode );

	TIMETYPE					m_pTimeType;// ʱ��ID - CDTimer*

	TYPE						m_pType;// ������ - IDTimerSink*

	INT64						m_timeTick;

	INT64						m_timeTickInterval;

	int							m_runtimes;
};

template< class TIMETYPE, class TYPE >
BOOL CDTimeNodeT<TIMETYPE, TYPE>::operator>=( const CDTimeNodeT<TIMETYPE,TYPE>& right ) const
{
	return m_timeTick >= right.m_timeTick;
}

template< class TIMETYPE, class TYPE >
BOOL CDTimeNodeT<TIMETYPE, TYPE>::operator<=( const CDTimeNodeT<TIMETYPE,TYPE>& right ) const
{
	return m_timeTick <= right.m_timeTick;
}

template< class TIMETYPE, class TYPE >
BOOL CDTimeNodeT<TIMETYPE, TYPE>::operator>( const CDTimeNodeT<TIMETYPE,TYPE>& right ) const
{
	return m_timeTick < right.m_timeTick;
}

template< class TIMETYPE, class TYPE >
BOOL CDTimeNodeT<TIMETYPE, TYPE>::operator<( const CDTimeNodeT<TIMETYPE,TYPE>& right ) const
{
	return m_timeTick < right.m_timeTick;
}

template< class TIMETYPE, class TYPE >
TIMETYPE CDTimeNodeT<TIMETYPE, TYPE>::GetTimerType()
{
	return m_pTimeType;
}

template< class TIMETYPE, class TYPE >
int CDTimeNodeT<TIMETYPE, TYPE>::DecreaseRunTimes()
{
	D_ASSERT( -2 < m_runtimes );		// ʹ�ô���

	if ( 0 == m_runtimes || m_runtimes == -1 )
	{
		return m_runtimes;
	}

	--m_runtimes;

	return m_runtimes;
}

template< class TIMETYPE, class TYPE >
INT64 CDTimeNodeT<TIMETYPE, TYPE>::GetIntervalTickCount()
{
	return m_timeTickInterval;
}

template< class TIMETYPE, class TYPE >
void CDTimeNodeT<TIMETYPE, TYPE>::SetTimeTick( INT64 timecount )
{
	m_timeTick = timecount;
}

template< class TIMETYPE, class TYPE >
INT64 CDTimeNodeT<TIMETYPE, TYPE>::GetTimeTick()
{
	return m_timeTick;
}

template< class TIMETYPE, class TYPE >
DResult CDTimeNodeT<TIMETYPE, TYPE>::SetTimerNode( 
	TIMETYPE pTimeType,
	TYPE pType,
	INT64 timeTick,
	INT64 timeTickInterval,
	int runtimes /*= -1 */ )
{
	D_CHECK_EX( NULL != pType && NULL != pTimeType, "pTimeType or pType is null", D_ERROR_NULL_POINTER );

	m_pType = pType;

	m_pTimeType = pTimeType;

	m_timeTick = timeTick;

	timeTickInterval = timeTickInterval;

	m_runtimes = runtimes;

	return D_OK;
}

template< class TIMETYPE, class TYPE >
DResult CDTimeNodeT<TIMETYPE, TYPE>::OnDestory()
{
	m_pType = NULL;

	m_pTimeType = NULL;

	delete this;

	return D_OK;
}

template< class TIMETYPE, class TYPE >
DResult CDTimeNodeT<TIMETYPE, TYPE>::OnTimer()
{
	D_CHECK_EX( NULL != m_pType, "", return D_ERROR_NULL_POINTER );

	DResult dRet = D_OK;

	m_pType->OnTimer( m_pTimeType );

	return dRet;
}

template< class TIMETYPE, class TYPE >
CDTimeNodeT<TIMETYPE, TYPE>::~CDTimeNodeT()
{

}

template< class TIMETYPE, class TYPE >
CDTimeNodeT<TIMETYPE, TYPE>::CDTimeNodeT()
	: m_pTimeType( NULL )
	, m_pType( NULL )
	, m_runtimes( -1 )
{

}


#endif	// _D_TIMER_NODE_T_H_