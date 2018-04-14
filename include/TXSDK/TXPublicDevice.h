#ifndef __TX_PUBLIC_DEVICE_H_
#define __TX_PUBLIC_DEVICE_H_

#include "TXSDKCommonDef.h"

CXX_EXTERN_BEGIN

//        �����豸��ؽӿ�


///////////////////////////////////////////////////////////////////////////
//
//                          ����QQ����ŷ���ģ����Ϣ��
//
///////////////////////////////////////////////////////////////////////////
//
//   ģ����Ϣ���ڹ����豸��QQ����ŷ�����Ϣ���������û�֪ͨ�����豸�ķ�����Ϣ
//   ģ����Ϣ��һ��JSON��ʽ�����ݰ�
//   �����豸���밴��һ����JSON��ʽģ�壬��д���ݣ����ܳɹ��Ľ�ģ����Ϣ�ʹ�QQ�����
//

//callback: ����ȷ����Ϣ�Ƿ��ʹ���QQ������̨������
typedef void (*on_send_template_msg_ret)(unsigned int cookie, int err_code);

/**
 * �ӿ�˵������QQ����ŷ���ģ����Ϣ
 * ����˵����
 *  msg_data                  ��Ϣ���ݣ�JSON��ʽ���ַ�������\0��β��
 *  ret_callback            ���ͽ���ص�
 *  cookie                  ��sdk�ڲ�����Ψһֵ�������ڷ��ͽ���ص�ʱ�ش�������Ψһ��ʶ��ǰ����
 */
SDK_API void tx_send_template_msg(char *msg_data, on_send_template_msg_ret ret_callback, unsigned int *cookie);


CXX_EXTERN_END


#endif /* __TX_PUBLIC_DEVICE_H_ */
