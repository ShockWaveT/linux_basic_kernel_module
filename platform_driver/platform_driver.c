#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/kdev_t.h>
#include<linux/uaccess.h>
#include<linux/platform_device.h>

#define DEV_MEM_SIZE 512

/* psuedo device's memory */
char device_buffer[DEV_MEM_SIZE] = "Hello World\n";

/* will hold the device major and minor numbers*/
dev_t device_number;

/* cdev variable */
struct cdev pcd_cdev;
struct class *class_pcd;
struct device *device_pcd;


loff_t pcd_lseek(struct file *filp, loff_t off, int whence)
{
	pr_info("platform_driver: pcd lseek called\n");
	return 0;
}

ssize_t pcd_read(struct file *filp, char __user *buff, size_t count, loff_t *f_pos)
{

	pr_info("platform_driver: pcd_read called\n");
	return count;
}

ssize_t pcd_write(struct file *filp, const char __user *buff, size_t count, loff_t *f_pos)
{
	pr_info("platform_driver: pcd_write called\n");
	return -ENOMEM;
}

int pcd_open(struct inode *inode, struct file *filp)
{
	pr_info("platform_driver: pcd_open called\n");
	return 0;
}

int pcd_release(struct inode *inode, struct file *filp)
{
	pr_info("platform_driver: pcd_release called\n");
	return 0;
}

/* file operations of the driver */
struct file_operations pcd_fops = 
{
	.open = pcd_open,
	.write = pcd_write,
	.read = pcd_read,
	.llseek = pcd_lseek,
	.owner = THIS_MODULE

};

/* gets called when matching platform device is found */
int pcd_platform_driver_probe(struct platform_device *pdev)
{
	pr_info("platform_driver: a device is detected\n");
	return 0;
}

/* gets called when device is removed from sthe system */
int pcd_platform_driver_remove(struct platform_device *pdev)
{
	pr_info("platform_driver: device was removed\n");
	return 0;
}

struct platform_driver pcd_platform_driver = {
	.probe = pcd_platform_driver_probe,
	.remove = pcd_platform_driver_remove,
	.driver = {
		//This name should be exactly same as the device name
		.name = "pseudo-char-device"
	}
};

static int __init pcd_driver_init(void)
{
	platform_driver_register(&pcd_platform_driver);
	pr_info("platform_driver: device setup module is loaded\n");
	
	return 0;
}

static void __exit pcd_driver_cleanup(void)
{
	platform_driver_unregister(&pcd_platform_driver);
	pr_info("platform_driver: device setup module is unloaded\n");
}

module_init(pcd_driver_init);
module_exit(pcd_driver_cleanup);

MODULE_LICENSE("GPL");
