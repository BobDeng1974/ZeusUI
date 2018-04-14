#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_platform.h>

//#include <asm/arch/regs-gpio.h>
//#include <asm/hardware.h>

#define  LED_ALL_OFF  0x00
#define  LED1_ON      0x11
#define  LED1_OFF     0x10
#define  LED2_ON      0x21
#define  LED2_OFF     0x20

static struct class *firstdrv_class;
static struct class_device	*firstdrv_class_dev;

volatile unsigned long *gpfcon = NULL;
volatile unsigned long *gpfdat = NULL;


static int first_drv_open(struct inode *inode, struct file *file)
{
	//printk("first_drv_open\n");
	/* ����GPF4,5,6Ϊ��� */
	//*gpfcon &= ~((0x3<<(4*2)) | (0x3<<(5*2)) | (0x3<<(6*2)));
	//*gpfcon |= ((0x1<<(4*2)) | (0x1<<(5*2)) | (0x1<<(6*2)));
	//*gpfdat |= (1<<4) ;// �ر�led1
	//*gpfdat |= (1<<5) ;// �ر�led2
	return 0;
}

static ssize_t first_drv_write(struct file *file, const char __user *buf, size_t count, loff_t * ppos)
{
	int val;

	//printk("first_drv_write\n");

	copy_from_user(&val, buf, count); //	copy_to_user();
/*
	if (val == 1)
	{
		// ���
		*gpfdat &= ~((1<<4) | (1<<5) | (1<<6));
	}
	else
	{
		// ���
		*gpfdat |= (1<<4) | (1<<5) | (1<<6);
	}
*/
	if (val == LED1_ON){
		*gpfdat &= ~(1<<4) ;// ��led1
	}
	else  if(val == LED1_OFF){
		*gpfdat |= (1<<4) ;// �ر�led1
	}
	else  if(val == LED2_ON){
		*gpfdat &= ~(1<<5) ;// ��led2
	}
	else  if(val == LED2_OFF){
		*gpfdat |= (1<<5) ;// �ر�led2
	}
	else{}

	return 0;
}

static struct file_operations first_drv_fops = {
    .owner  =   THIS_MODULE,    /* ����һ���꣬�������ģ��ʱ�Զ�������__this_module���� */
    .open   =   first_drv_open,     
	.write	=	first_drv_write,	   
};


int major;
static int first_drv_init(void)
{
	major = register_chrdev(0, "first_drv", &first_drv_fops); // ע��, �����ں�

	firstdrv_class = class_create(THIS_MODULE, "firstdrv");

	firstdrv_class_dev = device_create(firstdrv_class, NULL, MKDEV(major, 0), NULL, "xyz"); /* /dev/xyz */

	gpfcon = (volatile unsigned long *)ioremap(0x56000050, 16);
	gpfdat = gpfcon + 1;

	/* ����GPF4,5,6Ϊ��� */
	*gpfcon &= ~((0x3<<(4*2)) | (0x3<<(5*2)) | (0x3<<(6*2)));
	*gpfcon |= ((0x1<<(4*2)) | (0x1<<(5*2)) | (0x1<<(6*2)));
	*gpfdat |= (1<<4) ;// �ر�led1
	*gpfdat |= (1<<5) ;// �ر�led2
	
	return 0;
}

static void first_drv_exit(void)
{
	unregister_chrdev(major, "first_drv"); // ж��

	device_destroy(firstdrv_class,  MKDEV(major, 0));
	class_destroy(firstdrv_class);
	iounmap(gpfcon);
}

module_init(first_drv_init);
module_exit(first_drv_exit);


MODULE_LICENSE("GPL");

