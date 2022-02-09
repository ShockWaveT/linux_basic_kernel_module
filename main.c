#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/kdev_t.h>

#define DEV_MEM_SIZE 512

/* psuedo device's memory */
char device_buffer[DEV_MEM_SIZE];

/* will hold the device major and minor numbers*/
dev_t device_number;

/* cdev variable */
struct cdev pcd_cdev;
struct class *class_pcd;
struct device *device_pcd;


loff_t pcd_lseek(struct file *filp, loff_t off, int whence)
{
	pr_info("pcd lseek called\n");
	return 0;
}

ssize_t pcd_read(struct file *filp, char __user *buff, size_t count, loff_t *f_pos)
{
	pr_info("pcd read called\n");
	return 0;
}

ssize_t pcd_write(struct file *filp, const char __user *buff, size_t count, loff_t *f_pos)
{
	pr_info("pcd write called\n");
	return 0;
}

int pcd_open(struct inode *inode, struct file *filp)
{
	pr_info("pcd open called\n");
	return 0;
}

int pcd_release(struct inode *inode, struct file *filp)
{
	pr_info("pcd release called\n");
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

static int __init pcd_driver_init(void)
{
	/* dynamically allocate a device major number and range of minor number*/
	alloc_chrdev_region(&device_number, 0, 1, "pcd_devices");
	
	pr_info("device number <MAJOR>:<MINOR> %d:%d\n", MAJOR(device_number), MINOR(device_number));
	
	cdev_init(&pcd_cdev, &pcd_fops);
	
	/* initialize the cdev structure with fops */
	pcd_cdev.owner = THIS_MODULE;	
	
	/* Register a device (cdev structure with VFS) */
	cdev_add(&pcd_cdev, device_number, 1);
	
	/* create device class number under /sys/class */
	class_pcd = class_create(THIS_MODULE, "pcd_class");
	
	/* populate the sysfs with device information */
	device_pcd = device_create(class_pcd, NULL, device_number, NULL, "pcd");
	
	pr_info("module init was successful\n");
	
	return 0;
}

static void __exit pcd_driver_cleanup(void)
{

}

module_init(pcd_driver_init);
module_exit(pcd_driver_cleanup);

MODULE_LICENSE("GPL");
