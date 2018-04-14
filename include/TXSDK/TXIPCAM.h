#ifndef __IPCAMERA_H__
#define __IPCAMERA_H__

#include "TXSDKCommonDef.h"
#include "TXDeviceSDK.h"

CXX_EXTERN_BEGIN


/////////////////////////////////////////////////////////////////
//
//         ����ͷ �����ȵ��� & ��̨���� 
//
/////////////////////////////////////////////////////////////////


// ��Ƶ������ ����
enum definition {
	def_low		= 1,	//��
	def_middle	= 2,	//��
	def_high	= 3,	//��
};


// ��̨(PTZ)��ת����
enum rotate_direction {
	rotate_direction_left	= 1,	//��
	rotate_direction_right	= 2,	//��
	rotate_direction_up		= 3,	//��
	rotate_direction_down	= 4,	//��
};

// ��̨(PTZ)��ת�Ƕȷ�Χ
enum rotate_degree {
	//ˮƽ�Ƕȷ�Χ
	rotate_degree_h_min = 0,
	rotate_degree_h_max = 360,

	//��ֱ�Ƕȷ�Χ
	rotate_degree_v_min = 0,
	rotate_degree_v_max = 180,
};

// �ص�����������Ҫ����ʵ�֡�
typedef struct _tx_ipcamera_notify {
	/**
	 * �ӿ�˵��:	ipcamera�����ȵ����ص������ú󷵻�����ͷ�ĵ�ǰ�ֱ���
	 * param : definition :  Ҫ�����������ȣ�����ȡֵ�μ� enum definition
	 * param : cur_definition����ʱ������û���õ�
	 * param : cur_definition_length : ��ʱ������û���õ���
	*/
	int (*on_set_definition)(int definition, char *cur_definition, int cur_definition_length);

	/**
	 * �ӿ�˵����ipcamera��̨���ƻص�
	 * param ��rotate_direction : ��̨�������򣬾���ȡֵ���Բμ� enum rotate_direction
	 * param ��rotate_degree �� ��̨�����Ƕȣ�����ȡֵ���Բμ� enum rotate_degree
	 * return : 0�������ʧ�ܣ� ��0��������ɹ���
	*/
	int (*on_control_rotate)(int rotate_direction, int rotate_degree);

	/**
	 * �ӿ�˵����ipcamera�䱶���ƻص�
	 * param zoom			 :  �Ŵ������С, ��ֵ����С����ֵ����Ŵ�
	 * return : 0�������ʧ�ܣ� ��0��������ɹ���
	*/
	int (*on_control_zoom)(int zoom);
} tx_ipcamera_notify;


/**
 * �ӿ�˵���� ����ipcamera��صĻص�
 * param: notify IPCamera�����ص�����
 */
SDK_API int tx_ipcamera_set_callback(tx_ipcamera_notify *notify);



/////////////////////////////////////////////////////////////////
//
//         ipcamera������ؽӿ�: ��ʷ��Ƶ�ؿ�
//
/////////////////////////////////////////////////////////////////

/**
  *  QQ������ʷ��Ƶ�ؿ�������
  *
  *      |-----------|                                        |