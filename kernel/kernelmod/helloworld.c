#include <linux/kernel.h>
#include <linux/module.h>
static int __init helloworld_init(void)
{
    printk("<0>""helloworld!\n");
    return 0;
}
static void __exit helloworld_exit(void)
{
    printk("<0>""byebye!\n");
}
module_init(helloworld_init);
module_exit(helloworld_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("haoning");
