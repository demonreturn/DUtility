

#ifndef _D_ERROR_NETWORK_DEFINE_H_
#define _D_ERROR_NETWORK_DEFINE_H_

#include "DErrorDefine.h"

enum
{
	/* socket�������� */
	ERROR_NETWORK_BASE_SOCKET_ERROR						= (long)(ERROR_NETWORK_BASE + 1),

	/* �Է��Ͽ�һ���������� */
	ERROR_NETWORK_BASE_SOCKET_RESET						= (long)(ERROR_NETWORK_BASE + 2),

	/* һ���������ӱ��ر� */
	ERROR_NETWORK_BASE_SOCKET_CLOSE						= (long)(ERROR_NETWORK_BASE + 3),

	/* �󶨵�ַ��˿�ʱ���� */
	ERROR_NETWORK_BASE_SOCKET_BIND_ERROR				= (long)(ERROR_NETWORK_BASE + 4),

	/* ���ӶԶ�ʱ���� */
	ERROR_NETWORK_BASE_CONNECT_ERROR					= (long)(ERROR_NETWORK_BASE + 5),

	/* ���ӳ�ʱ */
	ERROR_NETWORK_BASE_CONNECT_TIMEOUT					= (long)(ERROR_NETWORK_BASE + 6),

	/* DNS����ʧ�� */
	ERROR_NETWORK_BASE_DNS_FAILURE						= (long)(ERROR_NETWORK_BASE + 7),

	/* ����������޷����� */
	ERROR_NETWORK_BASE_PROXY_SERVER_UNAVAILABLE			= (long)(ERROR_NETWORK_BASE + 8),

	/* ��֪���Ĵ��� */
	ERROR_NETWORK_BASE_UNKNOWN_ERROR					= (long)(ERROR_NETWORK_BASE + 9),

	/* û��������� */
	ERROR_NETWORK_BASE_NO_SERVICE						= (long)(ERROR_NETWORK_BASE + 10),
};

#endif	// _D_ERROR_NETWORK_DEFINE_H_