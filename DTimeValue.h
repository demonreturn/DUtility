
#ifndef _D_TIME_VALUE_H_
#define _D_TIME_VALUE_H_

#include "DBase.h"
#include "DDataStructure.h"

class CDTimeValue
{
public:
	/*
	* ������	��õ�ǰ��ʱ��
	* ������	��
	* ����ֵ��	CScTimeValueʱ��ṹ
	*/
	static CDTimeValue GetTimeOfDay();

	CDTimeValue();

	/*
	* ������	ͨ�����΢�빹��ʱ�����
	* ������	second [in] ����
	*			usecond [in] ΢����
	*/
	CDTimeValue( LONGLONG second, long usecond = 0 );

	CDTimeValue( const struct D_TIMEVALUE& tv );

	CDTimeValue( const timeval& tv );

#ifdef D_WIN32

	/*
	* ������	ͨ��Win32 FILETIME���������ʱ�䣬��windows��ʹ��
	* ������	ft [in] FILETIME�ṹ
	*/
	CDTimeValue( const FILETIME& ft );

#endif

	/*
	* ������	����ʱ��
	* ������	sencode [in] ����
	*		useconde [in] ΢����
	*/
	void Set( LONGLONG second, LONG usecond );

	void Set( const struct D_TIMEVALUE& tv );

	void Set( const timeval& tv );

	void Set( LONGLONG llSecond );

#ifdef D_WIN32

	void Set( const FILETIME& ft );
	
#endif

	/*
	* ������	��ú�����
	* ����ֵ��	������
	*/
	DWORD GetMSecond() const;

	/*
	* ������	�������
	* ����ֵ��	����
	*/
	DWORD GetSecond() const;

	/*
	* ������	��������
	* ������	second [in] ����
	*/
	void SetSecond( LONGLONG second );

	/*
	* ������	���΢����microseconds
	* ����ֵ��	΢����
	*/
	void SetUSecond( LONG usecond );

	/*
	* ������	���΢����microseconds
	* ����ֵ��	΢����
	*/
	LONG GetUSecond() const;

	/*
	* ������	����CScTimeValue�������
	* ������	tv [in] CScTimeValueʱ�����
	* ����ֵ��	CScTimeValue����
	*/
	CDTimeValue& operator += ( const CDTimeValue& tv );

	/*
	* ������	CScTimeValue�����һ��LONGLONG�������
	* ������	tv [in] ����
	* ����ֵ��	CScTimeValue����
	*/
	CDTimeValue& operator += ( LONGLONG tv );

	/*
	* ������	��ֵ
	* ������	tv [in] CScTimeValueʱ�����
	* ����ֵ��	CScTimeValue����
	*/
	CDTimeValue& operator = ( const CDTimeValue& tv );

	/*
	* ������	��ֵ
	* ������	tv [in] ����
	* ����ֵ��	CScTimeValue����
	*/
	CDTimeValue& operator = ( LONGLONG tv );

	/*
	* ������	����CScTimeValue�������
	* ������	tv [in] ��ȥ��CScTimeValueʱ��
	* ����ֵ��	CScTimeValue��������
	*/
	CDTimeValue& operator -= ( const CDTimeValue& tv );

	/*
	* ������	CScTimeValue�����һ��LONGLONG���͵�ֵ
	* ������	tv [in] ��ȥ������
	* ����ֵ��	CScTimeValue��������
	*/
	CDTimeValue& operator -= ( LONGLONG tv );

	// ȫ�ֲ���������.
	/*
	* ������	����CScTimeValue�������
	* ������	tv1 [in] CScTimeValueʱ��
	*			tv2 [in] CScTimeValueʱ��
	* ����ֵ��	CScTimeValue
	*/
	friend CDTimeValue operator + ( const CDTimeValue& t1, const CDTimeValue& t2 );

	/*
	* ������	����CScTimeValue���������ǰ��һ����ȥ����һ��
	* ������	tv1 [in] CScTimeValueʱ��
	*			tv2 [in] CScTimeValueʱ��
	* ����ֵ��	CScTimeValue
	*/
	friend CDTimeValue operator - ( const CDTimeValue& t1, const CDTimeValue& t2 );

	/*
	* ������	���tv1 < tv2��ΪTRUE, ����ΪFALSE
	* ������	tv1 [in] CScTimeValueʱ��
	*			tv2 [in] CScTimeValueʱ��
	* ����ֵ��	TRUE tv1 < tv2�� FALSE tv1 > tv2
	*/
	friend BOOL operator < ( const CDTimeValue& t1, const CDTimeValue& t2 );

	/*
	* ������	���tv1 > tv2��ΪTRUE, ����ΪFALSE
	* ������	tv1 [in] CScTimeValueʱ��
	*			tv2 [in] CScTimeValueʱ��
	* ����ֵ��	TRUE tv1 > tv2�� FALSE tv1 < tv2
	*/
	friend BOOL operator > ( const CDTimeValue& t1, const CDTimeValue& t2 );

	/*
	* ������	���tv1 <= tv2��ΪTRUE, ����ΪFALSE
	* ������	tv1 [in] CScTimeValueʱ��
	*			tv2 [in] CScTimeValueʱ��
	* ����ֵ��	TRUE tv1 <= tv2�� FALSE tv1 > tv2
	*/
	friend BOOL operator <= ( const CDTimeValue& t1, const CDTimeValue& t2 );

	/*
	* ������	���tv1 >= tv2��ΪTRUE, ����ΪFALSE
	* ������	tv1 [in] CScTimeValueʱ��
	*			tv2 [in] CScTimeValueʱ��
	* ����ֵ��	TRUE tv1 >= tv2�� FALSE tv1 < tv2
	*/
	friend BOOL operator >= ( const CDTimeValue& t1, const CDTimeValue& t2 );

	/*
	* ������	���tv1 == tv2��ΪTRUE, ����ΪFALSE
	* ������	tv1 [in] CScTimeValueʱ��
	*			tv2 [in] CScTimeValueʱ��
	* ����ֵ��	TRUE tv1 == tv2�� FALSE tv1 != tv2
	*/
	friend BOOL operator == ( const CDTimeValue& t1, const CDTimeValue& t2 );

private:
	void BounderCheck();

private:
	enum
	{
		/* 1�����1000���� */
		D_ONE_SECOND_IN_MSECS = 1000,

		/* 1�����1000000΢�� */
		D_ONE_SECOND_IN_USECS = D_ONE_SECOND_IN_MSECS * 1000,

		/* 1�����1000000000���� */
		D_ONE_SECOND_IN_NSECS = D_ONE_SECOND_IN_MSECS * 1000 * 1000,
	};

	D_TIMEVALUE					m_tv;
};

#endif	// _D_TIME_VALUE_H_