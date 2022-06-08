#include <linux/config.h>    /*头文件及变量等定义*/
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>       /* printk() */
#include <linux/fs.h>                /* everything... */
#include <linux/errno.h>         /* error codes */
#include <linux/types.h>         /* size_t */
#include <linux/proc_fs.h>
#include <linux/fcntl.h>            /* O_ACCMODE */
#include <linux/poll.h>             /* COPY_TO_USER */
#include <asm/system.h>       /* cli(), *_flags */


#define DEVICE_NAME	  "demo"
#define demo_MAJOR        249
#define demo_MINOR        0
#define MAX_BUF_LEN       20
static char drv_buf[20];


/* *****************************************************************/

static int demo_open(struct inode *inode, struct file *file)      {
	MOD_INC_USE_COUNT;
	sprintf(drv_buf,"device open sucess!\n");
	printk("device open sucess!\n");
	return 0;
}
static int  demo_release(struct inode *inode, struct file *filp)  {
	MOD_DEC_USE_COUNT;
	printk("device release\n");
	return 0;
}

/********************************************************************/

static ssize_t  demo_read(struct file *filp, char *buffer, size_t count, loff_t *ppos)	{
	if(count > MAX_BUF_LEN)
		count=MAX_BUF_LEN;
	copy_to_user(buffer, drv_buf,count);
	printk("user read data from driver\n");
	return count;
}
static ssize_t  demo_write(struct file *filp,const char *buffer, size_t count)	{ 
	copy_from_user(drv_buf , buffer, count);
	printk("user write data to driver\n");
	//your code here
	return count;
}


/******************************************************************/

static int demo_ioctl(struct inode *inode, struct file *file, 
                 unsigned int cmd, unsigned long arg)
{
	switch(cmd){
		case 1:{printk("ioctl runing  \n");
                        printk("runing command 1 \n");
                        break;}
		case 2:{printk("ioctl runing  \n");
                        printk("runing command 2 \n");
                        break;}
		default:
			printk("error cmd number\n");break;
	}
	return 0;
}



/*******************************************************************/

static struct file_operations demo_fops = {
	owner:	THIS_MODULE,
	write:	demo_write,	
	read:	demo_read,	
	ioctl:	demo_ioctl,
	open:	demo_open,
	release:	demo_release,
}; 

/*******************************************************************/



static int __init demo_init(void)	{
    int result;
    SET_MODULE_OWNER(&demo_fops);
    result = register_chrdev(demo_MAJOR, "demo", &demo_fops);
    if (result < 0) return result;
	printk(DEVICE_NAME " initialized\n");
	return 0;
} 

static void __exit  demo_exit(void)	{
    unregister_chrdev(demo_MAJOR, "demo");
	printk(DEVICE_NAME " unloaded\n");
} 



/******************************************************************/
module_init(demo_init);
module_exit(demo_exit);





