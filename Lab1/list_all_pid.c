#include<linux/sched.h>
#include<linux/list.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("LIST ALL PID");

static int hello_init(void)
{
	printk(KERN_ALERT"NO BEGIN\n");
	struct task_struct *p;
	for_each_process(p)
	{
		if(p->mm==NULL)
			printk(KERN_ALERT"Process Name: %s   PID: %d   Statue:%ld\n",p->comm,p->pid,p->state);
	}
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT"I'M LEAVING~~\n");
}

module_init(hello_init);
module_exit(hello_exit);
