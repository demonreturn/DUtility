

#ifndef _I_D_HANDLER_H_
#define _I_D_HANDLER_H_

#include "DBase.h"


/*
 * �¼��ɷ�����
 * �ṩ�������ϵͳ�¼�������Ҫ��reactor�����¼�������ɵĶ�������
 * �Իص������ĵ��ã���������reactorע����¼�������
 * ����acceptor���� ����ע��accept_mask,except_mask
 * ����connector���󣬿���ע��connect_mask,except_mask
 * ����transport���󣬿���ע��read_mask,write_mask,except_mask
 */
interface IDHandler
{
public:
	/*
	 * ���ض����Ӧ�ľ�����÷�����Ҫ�ṩ��reactorʹ��
	 */
	virtual DHANDLE GetHandle() = 0;

	/*
	 * �ɶ��¼��ص�
	 * reactor�ڲ���ö��������пɶ��¼�����ʱ���ص��÷���
	 * ����acceptor�����ע����accept_mask�¼�Ҳ��ص��÷���
	 * ����connector�����ע����connect_mask�¼�Ҳ��ص��÷���
	 * ����transprot�����ͨѶ���ӷ����Ͽ�����Ҳ��ص��÷���
	 */
	virtual void OnHandleInput( DHANDLE handle, int iEvent ) = 0;

	/*
	 * ��д�¼��ص�
	 * reactor�ڲ���ö��������п�д�¼�����ʱ���ص��÷���
	 * ����acceptor�����ֻע����accept_mask,except_mask���򲻻�ص��÷���
	 * ����connector�����ֻע����connect_mask,except_mask,�򲻻�ص��÷���
	 */
	virtual void OnHandleOutput( DHANDLE handle, int iEvent ) = 0;

	/*
	 * �쳣�¼��ص�
	 * reactor�ڲ���������¼�ʱ���������������쳣����ص��÷���
	 */
	virtual void OnHandleClose( DHANDLE handle, int iEvent ) = 0;

};

#endif	// _I_D_HANDLER_H_