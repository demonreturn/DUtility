
#ifndef _D_TIME_VALUE_H_
#define _D_TIME_VALUE_H_

#include "DBase.h"
#include "DDataStructure.h"

class CDTimeValue
{
public:
	/*
	* 描述：	获得当前的时间
	* 参数：	无
	* 返回值：	CScTimeValue时间结构
	*/
	static CDTimeValue GetTimeOfDay();

	CDTimeValue();

	/*
	* 描述：	通过秒和微秒构造时间对象
	* 参数：	second [in] 秒数
	*			usecond [in] 微秒数
	*/
	CDTimeValue( LONGLONG second, long usecond = 0 );

	CDTimeValue( const struct D_TIMEVALUE& tv );

	CDTimeValue( const timeval& tv );

#ifdef D_WIN32

	/*
	* 描述：	通过Win32 FILETIME结果，构造时间，在windows下使用
	* 参数：	ft [in] FILETIME结构
	*/
	CDTimeValue( const FILETIME& ft );

#endif

	/*
	* 描述：	设置时间
	* 参数：	sencode [in] 描述
	*		useconde [in] 微秒数
	*/
	void Set( LONGLONG second, LONG usecond );

	void Set( const struct D_TIMEVALUE& tv );

	void Set( const timeval& tv );

	void Set( LONGLONG llSecond );

#ifdef D_WIN32

	void Set( const FILETIME& ft );
	
#endif

	/*
	* 描述：	获得毫秒数
	* 返回值：	毫秒数
	*/
	DWORD GetMSecond() const;

	/*
	* 描述：	获得秒数
	* 返回值：	秒数
	*/
	DWORD GetSecond() const;

	/*
	* 描述：	设置秒数
	* 参数：	second [in] 秒数
	*/
	void SetSecond( LONGLONG second );

	/*
	* 描述：	获得微秒数microseconds
	* 返回值：	微秒数
	*/
	void SetUSecond( LONG usecond );

	/*
	* 描述：	获得微秒数microseconds
	* 返回值：	微秒数
	*/
	LONG GetUSecond() const;

	/*
	* 描述：	两个CScTimeValue对象相加
	* 参数：	tv [in] CScTimeValue时间对象
	* 返回值：	CScTimeValue对象
	*/
	CDTimeValue& operator += ( const CDTimeValue& tv );

	/*
	* 描述：	CScTimeValue对象和一个LONGLONG类型相加
	* 参数：	tv [in] 秒数
	* 返回值：	CScTimeValue对象
	*/
	CDTimeValue& operator += ( LONGLONG tv );

	/*
	* 描述：	赋值
	* 参数：	tv [in] CScTimeValue时间对象
	* 返回值：	CScTimeValue对象
	*/
	CDTimeValue& operator = ( const CDTimeValue& tv );

	/*
	* 描述：	赋值
	* 参数：	tv [in] 秒数
	* 返回值：	CScTimeValue对象
	*/
	CDTimeValue& operator = ( LONGLONG tv );

	/*
	* 描述：	两个CScTimeValue对象相减
	* 参数：	tv [in] 减去的CScTimeValue时间
	* 返回值：	CScTimeValue对象引用
	*/
	CDTimeValue& operator -= ( const CDTimeValue& tv );

	/*
	* 描述：	CScTimeValue对象减一个LONGLONG类型的值
	* 参数：	tv [in] 减去的秒数
	* 返回值：	CScTimeValue对象引用
	*/
	CDTimeValue& operator -= ( LONGLONG tv );

	// 全局操作符重载.
	/*
	* 描述：	两个CScTimeValue对象相加
	* 参数：	tv1 [in] CScTimeValue时间
	*			tv2 [in] CScTimeValue时间
	* 返回值：	CScTimeValue
	*/
	friend CDTimeValue operator + ( const CDTimeValue& t1, const CDTimeValue& t2 );

	/*
	* 描述：	两个CScTimeValue对象相减，前面一个减去后面一个
	* 参数：	tv1 [in] CScTimeValue时间
	*			tv2 [in] CScTimeValue时间
	* 返回值：	CScTimeValue
	*/
	friend CDTimeValue operator - ( const CDTimeValue& t1, const CDTimeValue& t2 );

	/*
	* 描述：	如果tv1 < tv2，为TRUE, 否则为FALSE
	* 参数：	tv1 [in] CScTimeValue时间
	*			tv2 [in] CScTimeValue时间
	* 返回值：	TRUE tv1 < tv2， FALSE tv1 > tv2
	*/
	friend BOOL operator < ( const CDTimeValue& t1, const CDTimeValue& t2 );

	/*
	* 描述：	如果tv1 > tv2，为TRUE, 否则为FALSE
	* 参数：	tv1 [in] CScTimeValue时间
	*			tv2 [in] CScTimeValue时间
	* 返回值：	TRUE tv1 > tv2， FALSE tv1 < tv2
	*/
	friend BOOL operator > ( const CDTimeValue& t1, const CDTimeValue& t2 );

	/*
	* 描述：	如果tv1 <= tv2，为TRUE, 否则为FALSE
	* 参数：	tv1 [in] CScTimeValue时间
	*			tv2 [in] CScTimeValue时间
	* 返回值：	TRUE tv1 <= tv2， FALSE tv1 > tv2
	*/
	friend BOOL operator <= ( const CDTimeValue& t1, const CDTimeValue& t2 );

	/*
	* 描述：	如果tv1 >= tv2，为TRUE, 否则为FALSE
	* 参数：	tv1 [in] CScTimeValue时间
	*			tv2 [in] CScTimeValue时间
	* 返回值：	TRUE tv1 >= tv2， FALSE tv1 < tv2
	*/
	friend BOOL operator >= ( const CDTimeValue& t1, const CDTimeValue& t2 );

	/*
	* 描述：	如果tv1 == tv2，为TRUE, 否则为FALSE
	* 参数：	tv1 [in] CScTimeValue时间
	*			tv2 [in] CScTimeValue时间
	* 返回值：	TRUE tv1 == tv2， FALSE tv1 != tv2
	*/
	friend BOOL operator == ( const CDTimeValue& t1, const CDTimeValue& t2 );

private:
	void BounderCheck();

private:
	enum
	{
		/* 1秒等于1000毫秒 */
		D_ONE_SECOND_IN_MSECS = 1000,

		/* 1秒等于1000000微秒 */
		D_ONE_SECOND_IN_USECS = D_ONE_SECOND_IN_MSECS * 1000,

		/* 1秒等于1000000000纳秒 */
		D_ONE_SECOND_IN_NSECS = D_ONE_SECOND_IN_MSECS * 1000 * 1000,
	};

	D_TIMEVALUE					m_tv;
};

#endif	// _D_TIME_VALUE_H_