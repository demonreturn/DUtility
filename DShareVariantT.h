
#ifndef _D_SHARE_VARIANT_H_
#define _D_SHARE_VARIANT_H_

#include "DBase.h"
#include "DOSShareMemory.h"
#include "DShareMemory.h"
#include "DMutexGuardT.h"
#include "DMutex.h"

template< typename TVar>
class CDShareVariantT
{
public:
	explicit CDShareVariantT( const char* szName,
		const TVar& defaultValue )
		: m_bFirstOpen( false )
		, m_mutex( NULL )
		, m_shareMemory( NULL )
	{
		Open( szName, defaultValue );
	}
	~CDShareVariantT()
	{
		Close();
	}

	CDShareVariantT& operator = ( const TVar& val )
	{
		Set( val );

		return *this;
	}

	operator TVar() const
	{
		if ( Good() )
		{
			return *(TVar*)m_shareMemory->GetHeadPointer();
		}

		return TVar(0);
	}

	bool Set( const TVar& val );

	bool Get( TVar& val ) const;

	bool IsFirstOpen() const
	{
		return m_bFirstOpen;
	}

	bool Good() const
	{
		return NULL != m_shareMemory && NULL != m_mutex;
	}

private:
	bool Open( const char* pName,
		const TVar& defaultVale );

	void Close();

private:
	CDShareVariantT( const CDShareVariantT& );

	void operator = ( const CDShareVariantT& );

	bool						m_bFirstOpen;

	mutable CDMutex*			m_mutex;
	mutable CDShareMemory*		m_shareMemory;
};

template< typename TVar>
void CDShareVariantT<TVar>::Close()
{
	if ( NULL != m_shareMemory )
	{
		m_shareMemory->Close();

		D_DELETE( m_shareMemory );
	}

	D_DELETE( m_mutex );
}

template< typename TVar>
bool CDShareVariantT<TVar>::Open( const char* pName, const TVar& defaultVale )
{
	if ( NULL == pName 
		|| 0 == strcmp(pName, "" ))
	{
		return false;
	}

	if ( NULL == m_mutex )
	{
		CDString mutexName = pName;
		mutexName += "_MUTEX_VARIANT_";

		m_mutex = new CDMutex( MUTEX_PROCESS, mutexName.c_str() );
	}

	if ( NULL == m_shareMemory )
	{
		m_shareMemory = new CDShareMemory();
	}

	CDMutexGuardT<CDMutex> guard( m_mutex );
	CDString strSharenameTemp = pName;
	strSharenameTemp += "_SM_VARIANT_";

	int iRet = m_shareMemory->Open( 
		strSharenameTemp.c_str(),
		sizeof(TVar) );

	if ( D_OK != iRet )
	{
		iRet = m_shareMemory->Open(
			strSharenameTemp.c_str(),
			sizeof(TVar),
			CDShareMemory::OM_CREATE );

		if ( D_OK != iRet )
		{
			Close();

			return false;
		}

		m_bFirstOpen = true;

		m_shareMemory->Write( (const char*)&defaultVale, sizeof(TVar) );
	}

	return true;
}

template< typename TVar>
bool CDShareVariantT<TVar>::Get( TVar& val ) const
{
	if ( !Good() )
	{
		return false;
	}

	DWORD dwActualRead = 0;
	int iRet = D_ERROR_FAILURE;
	{
		CDMutexGuardT<DMutex> guard( m_mutex );

		m_shareMemory->Seek( 0, D_SEEK_BEGIN );
		iRet = m_shareMemory->Read(
			(char*)&val,
			sizeof(TVar),
			dwActualRead );
	}

	if ( D_OK == iRet 
		&& dwActualRead == sizeof(TVar) )
	{
		return true;
	}

	return false;
}

template< typename TVar>
bool CDShareVariantT<TVar>::Set( const TVar& val )
{
	if ( !Good() )
	{
		return false;
	}

	CDMutexGuardT<CDMutex> guard( m_mutex );

	m_shareMemory->Seek( 0, D_SEEK_BEGIN );
	int iRet = m_shareMemory->Write( (const char*)&val, sizeof(TVar) );

	return (D_OK == iRet);
}

#endif // _D_SHARE_VARIANT_H_
