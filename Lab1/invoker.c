#include <linux/module.h>
#include <linux/kernel.h>
extern void my_print(char * str);
MODULE_LICENSE("GPL");
static int invoker_init(void)
{
printk(KERN_ALERT " Hello world, I'm invoker module\n");
my_print(" Called by invoker module");
return 0;
}
void invoker_exit(void)
{
printk(KERN_ALERT " Invoker module: Goodbye, I'm leaving~~\n");
}
module_init(invoker_init);
module_exit(invoker_exit);

