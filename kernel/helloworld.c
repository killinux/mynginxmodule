#include <linux/init.h>
#include <linux/module.h>
static int hello_init(void)
{
    printk(KERN_INFO "hello world haohao enter\n");
    return 0;
}
static void hello_exit(void)
{
    printk(KERN_INFO "hello world exit\n");
}
module_init(hello_init);
module_exit(hello_exit);

MODULE_AUTHOR("haoning <haoningabc@163.com>");
MODULE_LICENSE("Dual BSD/GPL");
MOUDULE_DESCRIPTION(" a helloworld haoning");
MOUDULE_ALIAS("a simplest moudle");
