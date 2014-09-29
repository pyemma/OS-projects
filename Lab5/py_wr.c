#include<linux/module.h>
#include<linux/kernel.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h> /* for copy_from_user */
#include<linux/sched.h>

#define PROCFS_MAX_SIZE 4096
#define PROCFS_NAME1 "task_info"
#define PROCFS_NAME2 "pid"

MODULE_LICENSE("GPL");

static struct proc_dir_entry *New_dir, *task_info_file, *pid_file;
static char procfs_buffer[PROCFS_MAX_SIZE];
static char procfs_bufferr[PROCFS_MAX_SIZE];
static unsigned long procfs_buffer_size = 0;
static unsigned long procfs_bufferr_size = 0;

static int pid_read(char *buffer,char **buffer_location,
		off_t offset, int buffer_length, int *eof,void *data)
{
	int ret;
	printk(KERN_INFO "procfile_read (/proc/%s) called\n", PROCFS_NAME2);
	if (offset > 0) {
		ret = 0;
	} else {
		memcpy(buffer, procfs_buffer, procfs_buffer_size);
		ret = procfs_buffer_size;
	}
	return ret;
}

static int pid_write(struct file *file, const char *buffer, unsigned long count,void *data)
{
	procfs_buffer_size = count;
	if (procfs_buffer_size > PROCFS_MAX_SIZE ) {
		procfs_buffer_size = PROCFS_MAX_SIZE;
	}
	if ( copy_from_user(procfs_buffer, buffer,procfs_buffer_size)){
		return EFAULT;
	}
	struct task_struct *task;
	int pid = -1;
	char temp[50]=" ";
	char str[100] = "The name of the process is: ";
	char str1[100] = "The pid of the process is: ";
	char str2[50] = "State: ";
	if(procfs_buffer[0] != '-')
	{
		pid = 0;
		int i;
		for(i=0;i<procfs_buffer_size-1;i++)
		{
			pid = pid * 10;
			pid = pid + procfs_buffer[i] - '0';
		}
		printk("The len is %d\n", procfs_buffer_size);
		printk("The pid is :%d\n", pid);
		task = pid_task(find_get_pid(pid),PIDTYPE_PID);
		i = 0;
		printk("%s",temp);
		while(pid!=0)
		{
			printk("%d",pid);
			temp[i] = pid%10 + '0';
			i++; pid = pid/10;
		}
		printk("%s",temp);
		strcat(str1, temp);
		printk("The pid is :%d the name is :%s\n", task->pid, task->comm);
		int len;
		len = strlen(task->comm);
		printk("The len is:%d\n", len);
		strcat(str, task->comm);
		int cnt = 0;
		strcat(str,"   ");
		//strcat(str, str1);
		len = strlen(str);
		printk("%s\n", str);
		for(i=0;i<len;i++)
		{
			procfs_bufferr[cnt] = str[i];
			cnt++;
		}
		len = strlen(str1);
		for(i=0;i<len;i++)
		{
			procfs_bufferr[cnt] = str1[i];
			cnt++;
		}
		procfs_bufferr[cnt] = '\r';
		cnt++;
		procfs_bufferr[cnt] = '\n';
		cnt++;
		procfs_bufferr_size = cnt;
	}
	else 
	{
		int cnt = 0;
		for_each_process(task)
		{
			int len,i;
			len = strlen(task->comm);
			for(i=0;i<len;i++)
			{
				procfs_bufferr[cnt] = task->comm[i];
				cnt++;
			}
			procfs_bufferr[cnt]='\t';
			cnt++;
			len = strlen(str2);
			for(i=0;i<len;i++)
			{
				procfs_bufferr[cnt] = str2[i];
				cnt++;
			}
			procfs_bufferr[cnt]=task->state + '0';
			cnt++;
			procfs_bufferr[cnt]='\r';
			cnt++;
			procfs_bufferr[cnt]='\n';
			cnt++;
		}
		procfs_bufferr_size = cnt;
	}	
	return procfs_buffer_size;
}

static int task_info_read(char *buffer,char **buffer_location,
		off_t offset, int buffer_length, int *eof,void *data)
{
	int ret;
	printk(KERN_INFO "procfile_read (/proc/task_info/%s) called\n", PROCFS_NAME1);
	memcpy(buffer, procfs_bufferr, procfs_bufferr_size + 2);
	ret = procfs_bufferr_size;
	printk("The length of the task_info is: %d", ret); 
	return ret;
}

static int rw_proc_init(void)
{
	New_dir = proc_mkdir("task_info",NULL);
	task_info_file = create_proc_entry(PROCFS_NAME1, 0444, New_dir);
	if (task_info_file == NULL) {
		remove_proc_entry(PROCFS_NAME1, NULL);
		printk(KERN_ALERT "Error: Could not initialize /proc/task_info/%s\n",PROCFS_NAME1);
	return ENOMEM;
	}
	task_info_file->read_proc = task_info_read;
	task_info_file->mode = S_IFREG | S_IRUGO;
	task_info_file->uid = 0;
	task_info_file->gid = 0;
	task_info_file->size = 37;
	printk(KERN_INFO "/proc/task_info/%s created\n", PROCFS_NAME1);
	pid_file = create_proc_entry(PROCFS_NAME2, 0644, New_dir);
	if (pid_file == NULL) {
		remove_proc_entry(PROCFS_NAME2, NULL);
		printk(KERN_ALERT "Error: Could not initialize /proc/task_info/%s\n",PROCFS_NAME2);
	return ENOMEM;
	}
	pid_file->read_proc = pid_read;
	pid_file->write_proc = pid_write;
	//Our_Proc_File->owner = THIS_MODULE;
	pid_file->mode = S_IFREG | S_IRUGO;
	pid_file->uid = 0;
	pid_file->gid = 0;
	pid_file->size = 37;
	printk(KERN_INFO "/proc/task_info/%s created\n", PROCFS_NAME2);
return 0;
}

static void rw_proc_exit(void)
{
	remove_proc_entry("task_info", NULL);
	printk(KERN_INFO "/proc/%s removed\n", "task_info");
}
module_init(rw_proc_init);
module_exit(rw_proc_exit);

