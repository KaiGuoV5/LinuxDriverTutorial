/*
 * helloworld demo for linux module
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("KaiGuo");
MODULE_DESCRIPTION("Register device number and implement some callback functions");
MODULE_VERSION("0.1");


/**
 * @brief This function is called when a device file is opened.
 *
 * @param device_file Pointer to the inode structure of the device file.
 * @param instance Pointer to the file structure of the device file instance.
 *
 * @return 0 on success, negative value on error.
 *
 * This function is called when a device file is opened. It prints a message to
 * the kernel log indicating that the device file has been opened.
 */
static int driver_open(struct inode *device_file, struct file *instance) {
    // Print a message to the kernel log
    printk("dev_no: Device file opened!\n");
    
    // Return 0 to indicate success
    return 0;
}

/**
 * @brief This function is called when a device file is closed.
 *
 * @param device_file Pointer to the inode structure of the device file.
 * @param instance Pointer to the file structure of the device file instance.
 *
 * @return 0 on success, negative value on error.
 *
 * This function is called when a device file is closed. It prints a message to
 * the kernel log indicating that the device file has been closed.
 */
static int driver_close(struct inode *device_file, struct file *instance) {
    // Print a message to the kernel log
    printk("dev_no: Device file closed!\n");
    
    // Return 0 to indicate success
    return 0;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = driver_open,
    .release = driver_close
};

#define DEVICE_MAJOR 80
#define DEVICE_NAME "dev_no"

/**
 * @brief The initialization function of the kernel module.
 *
 * This function is called when the module is loaded. It prints a greeting
 * message to the kernel log.
 *
 * @return 0 on success, negative value on error.
 */
static int __init ModuleInit(void) {
    printk(KERN_INFO "Hello, Kernel!\n");
    int ret = register_chrdev(DEVICE_MAJOR, DEVICE_NAME, &fops);
    if (ret < 0) {
        printk(KERN_ERR "Cannot register device major number %d!\n", DEVICE_MAJOR);
        return ret;
    }

    if (ret == 0) {
        printk("Register device major number %d, minor number 0!\n", DEVICE_MAJOR);
    } else {
        printk("Register device major number %d, minor number %d!\n", ret >> 20, ret & 0xFFFFF);
    }

    return 0;
}

/**
 * @brief The cleanup function of the kernel module.
 *
 * This function is called when the module is unloaded. It prints a goodbye
 * message to the kernel log.
 */
static void __exit ModuleExit(void) {
    unregister_chrdev(DEVICE_MAJOR, DEVICE_NAME);
    printk(KERN_INFO "Goodbye, Kernel!\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);