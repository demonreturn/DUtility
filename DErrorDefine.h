
/*
	������붨��
*/

#ifndef _D_ERROR_DEFINE_H_
#define _D_ERROR_DEFINE_H_


#define ERROR_BASE					10000
#define ERROR_NETWORK_BASE			20000
#define ERROR_OPERATOR_BASE			30000

enum enum_D_ERROR
{
	// �ɹ�
	D_OK							= (long)0,

	// ʧ��
	D_ERROR_FAILURE					= (long)(ERROR_BASE + 1 ),

	// û�г�ʼ��
	D_ERROR_NOT_INIT				= (long)(ERROR_BASE + 2 ),

	// �Ѿ���ʼ��
	D_ERROR_ALREADY_INIT			= (long)(ERROR_BASE + 3 ),

	// û��ʵ��
	D_ERROR_NOT_IMPLEMENTED			= (long)(ERROR_BASE + 4 ),

	// ��ָ��
	D_ERROR_NULL_POINTER			= (long)(ERROR_BASE + 5 ),

	// �ڴ治��
	D_ERROR_OUT_OF_MEMORY			= (long)(ERROR_BASE + 6 ),

	// ��������
	D_ERROR_INVALID_PARAM			= (long)(ERROR_BASE + 7 ),

	// ����������
	D_ERROR_OPER_NOT_ALLOWED		= (long)(ERROR_BASE + 8 ),

	// ������
	D_ERROR_NOT_FOUND				= (long)(ERROR_BASE + 9 ),

	// �Ѿ�����
	D_ERROR_ALREADY_EXISTS			= (long)(ERROR_BASE + 10 ),

	// ���ݲ�����
	D_ERROR_PARTIAL_DATA			= (long)(ERROR_BASE + 11 ),

	// ��ʱ
	D_ERROR_TIMEOUT					= (long)(ERROR_BASE + 12 ),
};

#endif	// _D_ERROR_DEFINE_H_