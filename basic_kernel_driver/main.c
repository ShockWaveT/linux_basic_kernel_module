#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/kdev_t.h>
#include<linux/uaccess.h>

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
	pr_info("pcd lseek called\n");
	return 0;
}

ssize_t pcd_read(struct file *filp, char __user *buff, size_t count, loff_t *f_pos)
{
	int ret;
	pr_info("pcd read called\n");
	
	if(count > DEV_MEM_SIZE){
		pr_info("too much data requested to pcd driver\n");
		count = DEV_MEM_SIZE;
	}
	
	ret = copy_to_user(buff, device_buffer, count);
	if(ret != 0){
		pr_info("pcd driver: could not read whole file\n");
		return -EFAULT;
	}
	pr_info("pcd: copy_to_user ret: %d\n", ret);
	return count;
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
	/*Class destroy */
	class_destroy(class_pcd);

	/*Unregister device numbers for MAX_DEVICES */
	unregister_chrdev_region(device_number, 1);
	
	pr_info("pcd platform driver unloaded\n");
}

module_init(pcd_driver_init);
module_exit(pcd_driver_cleanup);

MODULE_LICENSE("GPL");
