

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
	* 描述：	减少运行次数，并返回剩余次数，如果原先是-1（标识循环执行），
	*			返回仍旧是-1。如果之前设置了轮询次数，在减少次数的同时返回剩余次数，直到0为止。
	* 参数：	无
	* 返回值：	执行次数， -1表示循环
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

	TIMETYPE					m_pTimeType;// 时间ID - CDTimer*

	TYPE						m_pType;// 处理器 - IDTimerSink*

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
	D_ASSERT( -2 < m_runtimes );		// 使用错误

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