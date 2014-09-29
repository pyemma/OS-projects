#include<linux/sched.h>
#include<linux/list.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("LIST ALL PID");

static int pid;
module_param(pid,int,0644);

static int hello_init(void)
{
	printk(KERN_ALERT"NO BEGIN\n");
	struct task_struct *p;
	//pid=1;
	//for_each_process(p)
	//{
		//if(p->pid==pid)
		//{
	p=pid_task(find_get_pid(pid),PIDTYPE_PID);
	printk(KERN_ALERT"PID: %d    Parent: %s\n",p->pid,p->parent->comm);
	struct list_head *pp;
	struct task_struct * task;
	list_for_each(pp,&p->children)
	{
		task=list_entry(pp,struct task_struct, sibling);
		printk(KERN_ALERT"PID: %d    Children: %s\n",task->pid,task->comm);
	}
	list_for_each(pp,&p->sibling)
	{
		task=list_entry(pp,struct task_struct, sibling);
		printk(KERN_ALERT"PID: %d    Sibling: %s\n",task->pid,task->comm);
	}
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT"I'M LEAVING~~\n");
}

module_init(hello_init);
module_exit(hello_exit);
