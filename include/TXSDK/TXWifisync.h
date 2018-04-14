#ifndef __TX_WIFI_SYNC_H__
#define __TX_WIFI_SYNC_H__

#include "TXSDKCommonDef.h"

CXX_EXTERN_BEGIN

/*
 *                      SmartLink API���
 * SmartLink API�����׽ӿڣ�Ŀǰ�Ƽ�ʹ��2.0�ӿڣ�2.0�ӿڼ򵥣�1.0�ӿ�ʹ�ø��Ӳ��Ƽ�ʹ�ã�
 * �����ֹ��ɣ�common API���������֣�1.0��2.0�ӿھ�ʹ�ã�
             2.0�ӿ�API��2.0�ӿڲ��֣�
             1.0�ӿ�API��1.0�ӿڲ��֣�
 */

////////////////////////////////////////////////////////////////////////////////////////
//     
//        			    			common API
//
////////////////////////////////////////////////////////////////////////////////////////

/** init_wifi_sync & start_smartlink�ķ���ֵʹ�ô�enum����
 */
enum wifisyncerror {
	QLERROR_INIT_SUCCESS        = 0,         //suc
	QLERROR_MEMORY_ALLOC  		= 1,        //�ڴ����ʧ��
	QLERROR_NOTIFY_NULL		  	= 2,        //FUNC_NOTIFY�ص�����Ϊ��
	QLERROR_PARAM_KEY       	= 3,        //key����ΪNULL
	QLERROR_PARAM_KEY_LEN   	= 4,        //key���Ȳ��Ϸ�
	QLERROR_OPENSSL_LOAD_FAILED = 5,        //����openssl��ʧ��
	QLERROR_HOP_NULL			= 6,		//��Ƶ�ص�����Ϊ��
	QLERROR_SZIFNAME_INVALID	= 7,		//szifname���Ϸ�
	QLERROR_WIFICHIP_NOTSUPPORT = 8,		//��WIFI CHIP 2.0�ӿڲ�֧��
	QLERROR_INIT_OTHER		    = 9,		//��������
};

/** fill_80211_frame�ķ���ֵʹ�ô�enum����
 */
enum fill80211relust {
	QLERROR_SUCCESS 		= 0,		//�����ɹ�
	QLERROR_HOP				= 1,		//�յ��˷���ֵ��ʾ��ǰ�ŵ��������������л���һ���ŵ�
	QLERROR_LOCK    		= 2,        //�յ��˷���ֵ��ʾ�ǵ�ǰ�ŵ�������

	//������Щ����ֵ������ʹ�ã����ŵ������ŵ�������������ֵȷ��,BCAST��ʾBraodcast��MCAST��ʾMulticast
	QLERROR_OTHER			= 3,    //��������
	QLERROR_DECRYPT_FAILED  = 4,    //���ܳ���
	QLERROR_NEED_INIT     	= 5,    //wifi syncû�г�ʼ��
	QLERROR_VERSION        	= 6,    //SDK�汾����Ӧ
	QLERROR_START_FRAME     = 7, 	//��Ч�İ�

    //Broadcast relative
    QLERROR_BCAST_NOT_FRAME	= 8, 	//���ǹ㲥��
    QLERROR_BCAST_CALC_C	= 9,	//�ɹ�����Cֵ
    QLERROR_BCAST_ONE_DATA	= 10,	//������һ���㲥����

    //Multicast relative
    QLERROR_MCAST_NOT_FRAME	= 11,  //�����鲥��
    QLERROR_MCAST_ONE_DATA	= 12,  //������һ���鲥����
};

#define QLMAX_SSID_LEN      128
#define QLMAX_PSWD_LEN      128
#define QLMAX_IP_LEN        16

typedef struct
{
	char                sz_ssid[QLMAX_SSID_LEN];      // AP�˺�����
	char                sz_password[QLMAX_PSWD_LEN];  // AP����
    char                sz_ip[QLMAX_IP_LEN];          // ���Ͷ�IP��ַ���豸����AP���������Ͷ�ackʱ�õ�
    unsigned short      sh_port;                      // ���Ͷ˶˿ڣ�  �豸����AP���������Ͷ�ackʱ�õ�
    unsigned char       sz_bssid[6];                  // AP��48λMAC��ַ�� ��Ҫ������������SSID�㲥��AP�����̿ɸ���ʵ�����ѡ���Ƿ�ʹ��
	                                                  // ����豸����ɨ�赽beacon֡��ͨ��beancon�е���Ϣ����AP��ɺ��Դ˳�Ա
} tx_wifi_sync_param;


/**  ��