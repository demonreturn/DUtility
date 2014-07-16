

#ifndef _I_D_HANDLER_H_
#define _I_D_HANDLER_H_

#include "DBase.h"


/*
 * 事件派发基类
 * 提供给会产生系统事件，并需要由reactor进行事件捕获分派的对象派生
 * 对回调方法的调用，是依据向reactor注册的事件决定的
 * 对于acceptor对象 可以注册accept_mask,except_mask
 * 对于connector对象，可以注册connect_mask,except_mask
 * 对于transport对象，可以注册read_mask,write_mask,except_mask
 */
interface IDHandler
{
public:
	/*
	 * 返回对象对应的句柄，该方法主要提供给reactor使用
	 */
	virtual DHANDLE GetHandle() = 0;

	/*
	 * 可读事件回调
	 * reactor在捕获该对象句柄上有可读事件发生时，回调该方法
	 * 对于acceptor，如果注册了accept_mask事件也会回调该方法
	 * 对于connector，如果注册了connect_mask事件也会回调该方法
	 * 对于transprot，如果通讯连接发生断开，则也会回调该方法
	 */
	virtual void OnHandleInput( DHANDLE handle, int iEvent ) = 0;

	/*
	 * 可写事件回调
	 * reactor在捕获该对象句柄上有可写事件发生时，回调该方法
	 * 对于acceptor，如果只注册了accept_mask,except_mask，则不会回调该方法
	 * 对于connector，如果只注册了connect_mask,except_mask,则不会回调该方法
	 */
	virtual void OnHandleOutput( DHANDLE handle, int iEvent ) = 0;

	/*
	 * 异常事件回调
	 * reactor在捕获对象句柄事件时，如果句柄发生了异常，则回调该方法
	 */
	virtual void OnHandleClose( DHANDLE handle, int iEvent ) = 0;

};

#endif	// _I_D_HANDLER_H_