#include <linux/module.h>
#include <linux/platform_device.h>

struct pcdev_platform_data
{
	int size;
	int perm;
	const char *serial_number;
};

#define RDWR 0x11
#define RDONLY 0x01
#define WRONLY 0x10


// creating two platform data
struct pcdev_platform_data pcdev_platform_data[2] = {
	[0] = { .size = 512, .perm = RDWR, .serial_number = "PCDSER1234"},
	[1] = { .size = 1024, .perm = RDWR, .serial_number = "PCDSER5678"}
};


//creating two platform devices
struct platform_device pcd_platform_dev1 = {
	.name = "psuedo-char-device-1",
	.id = 0
};

struct platform_device pcd_platform_dev2 = {
	.name = "psuedo-char-device-2",
	.id = 1
};

static int __init pcdev_platform_init(void)
{
	//register platform device
	platform_device_register(&pcd_platform_dev1);
	platform_device_register(&pcd_platform_dev2);
	
	return 0;
	
}

static void __exit pcdev_platform_exit(void)
{
	platform_device_unregister(&pcd_platform_dev1);
	platform_device_unregister(&pcd_platform_dev2);
}

module_init(pcdev_platform_init);
module_exit(pcdev_platform_exit);

MODULE_LICENSE("GPL");
