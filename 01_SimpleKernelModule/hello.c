/*
 * helloworld demo for linux module
 */
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("KaiGuo");
MODULE_DESCRIPTION("A simple Hello World Kernel Module for Raspberry Pi");
MODULE_VERSION("0.1");

static int __init hello_init(void) {
    printk(KERN_INFO "Hello, World from the Raspberry Pi Kernel Module!\n");
    return 0;
}

static void __exit hello_exit(void) {
    printk(KERN_INFO "Goodbye, World from the Raspberry Pi Kernel Module!\n");
}

module_init(hello_init);
module_exit(hello_exit);