#ifndef __TX_AUDIO_VIDEO_H__
#define __TX_AUDIO_VIDEO_H__

#include "TXSDKCommonDef.h"

CXX_EXTERN_BEGIN


/**
 *
 * ����Ƶ��ؽӿ�
 *
 */

//��Ƶ����
enum audio_format {
	audio_format_amr  = 1,
	audio_format_aac  = 2, //˫����Ŀǰ��֧��48KHz������, �������Բ�����û������
    audio_format_g711 = 6,
};

/**
 * �շ���Ƶ������ʱ�Ĳ���
 * head_length   : �ṹ��ĳ���.
 * audio_format  ����ʾ��Ƶ����ĸ�ʽ��Ҳ������Ƶѹ���㷨���������ֻ�QQ��װ����������ƣ�Ŀǰֻ֧�̶ֹ�ֵ�� 1
 * encode_param  ���������ʽΪAMRʱ����ʾ��Ƶѹ���㷨�ľ������������ֵ�� 7���������ʽΪAACʱ��1���������ʽΪG711ʱ��0����Alaw, 1����uLaw��
 * frame_per_pkg ����Ƶ������һ�����ݰ�һ�����ݰ����͵��ֻ��˵ģ����һ֡��Ƶ���ݺ�С����ô�������ݰ��п���װn����Ƶ����֡�������������ָ��n������ֵ��8
 * sampling_info ���������������ڽ���ͨ��GET_SIMPLING_INFO��GET_AMR_SIMPLING_INFO�����ֵ
 *                 ע  �������� = 8000��8K�� ���˴�����������8 �� ������  48000��48K�� �˴���48�� �Դ����ơ�
 *                 ע  ������ϵͳ��little-endian
 *                 ע  �������AMR��ʽ��ʹ��GET_AMR_SIMPLING_INFO
 * reserved      �������ֶ�
 */
typedef struct _tx_audio_encode_param
{
	unsigned char head_length;
	unsigned char audio_format;
	unsigned char encode_param;
	unsigned char frame_per_pkg;
	unsigned int  sampling_info;
	unsigned int  reserved;

} tx_audio_encode_param;


/**
* ����ĺ�������������һ���������� tx_audio_encode_param - sampling_info �е���ֵ
*  param�� channel ��������
*  param�� sampling �����ʣ������� = 8000��8K�� ���˴�����������8 �� ������  48000��48K�� �˴���48�� �Դ����ơ�
*  param��bit λ��ȡ 8 �� 16���Ƽ�16
*/
#define GET_SIMPLING_INFO(channel, sampling, bit)  ((channel << 24) | (sampling << 16) | (bit << 8) | 0x00)

/**
*  AMR��Ƶ��ʽ����sampling_info��ֵ�ĺ�
*/
#define GET_AMR_SIMPLING_INFO(channel, sampling, bit)  ((bit << 24) | (sampling << 16) | (channel << 8) | 0x00)


/**
 * AV SDK -> Device �ص��ӿ�
 *
 * on_start_camera ֪ͨ����ͷ��Ƶ��·�Ѿ�����������ͨ�� tx_set_video_data �ӿ��� AV SDK ���ɼ�������Ƶ����
 *
 * on_stop_camera  ֪ͨ����ͷ��Ƶ��·�Ѿ��Ͽ������Բ����ټ����ɼ���Ƶ����
 *
 * on_set_bitrate  ��Ƶ������ζ��1s�����������ݣ������������������ʹ��ֱ����ء�
 *                 AV SDK ����ݵ�ǰ�����������Qos��Ϣ�����������bitrate���ϲ�Ӧ�ÿ��Ը����������ֵ����Camera�ĸ��������
 *                 ��֡�ʡ��ֱ��ʣ����������ȣ��Ӷ���ú��ʵ�����
 *
 * on_start_mic    ֪ͨ��˷���Ƶ��·�Ѿ�����������ͨ�� tx_set_audio_data �ӿ��� AV SDK ���ɼ�������Ƶ����
 *
 * on_stop_mic     ֪ͨ����ͷ��Ƶ��·�Ѿ��Ͽ������Բ����ټ����ɼ���Ƶ����
 *
 * on_recv_audiodata ֪ͨ�����豸������Ƶ���ݵ���
*/
typedef struct _tx_av_callback
{
    //�����豸��Ϊ����Ƶ�ķ��ͷ�������ص����ڲɼ�����Ƶ����
    bool (*on_start_camera)();
    bool (*on_stop_camera)();

    bool (*on_set_bitrate)(int bit_rate);

    bool (*on_start_mic)();
    bool (*on_stop_mic)();

    /**
     * �����豸��Ϊ����Ƶ�Ľ��շ�������ص����ڽ�������Ƶ����
     * param��param on_recv_audiodata�ص�������tx_audio_encode_param���������������Ƶ�ı������
	 * param��pcEncData �յ�����Ƶ����
	 * param��nEncDataLen �յ�����Ƶ���ݳ��ȣ���λ���ֽ�
     */
    void (*on_recv_audiodata)(tx_audio_encode_param *param, unsigned char *pcEncData, int nEncDataLen);

    /**
    * ǿ�Ʊ�I֡�����������Ƶ�£�����뷿��Ļ����ӳٴ�����⡣
    */
    void (*on_force_iframe)();
    
} tx_av_callback;


/**
* �ӿ�˵������������Ƶ��ط��񣬸÷�����Ҫ��¼�ɹ�����ܵ��ã�������д����뷵��
* ����˵����callback  ����Ƶ�ص��ӿ�
* ����ֵ  �������루��ȫ�ִ������
*/
SDK_API int tx_start_av_service( tx_av_callback *callback);


/**
* �ӿ�˵�����˳�����SDK����Ƶ��ص��߼�
* ����ֵ  �������루��ȫ�ִ������
*/
SDK_API int tx_stop_av_service();


/**
 * ��SDK�����Ƶ����
 * nGopIndex:Gop��index
 * nFrameIndex:��ǰ֡������gop�е�index
 * nTotalIndex:��ǰ֡���ܱ�������е�index
 */
SDK_API void tx_set_video_data(unsigned char *pcEncData, int nEncDataLen,
        int nFrameType, int nTimeStamps, int nGopIndex, int nFrameIndex, int nTotalIndex, int nAvgQP);


/**
 * ��SDK�����Ƶ����
 * param��param ��Ƶ�������
 * param��pcEncData ��������Ƶ����
 * param: nEncDataLen �������Ƶ���ݳ���
 */
SDK_API void tx_set_audio_data(tx_audio_encode_param *param, unsigned char *pcEncData, int nEncDataLen, int nTimeStamps);


CXX_EXTERN_END

#endif // __TX_AUDIO_VIDEO_H__
