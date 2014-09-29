#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x78c14ddb, "module_layout" },
	{ 0x64063398, "remove_proc_entry" },
	{ 0x829b533d, "create_proc_entry" },
	{ 0x84e19b66, "proc_mkdir" },
	{ 0x362ef408, "_copy_from_user" },
	{ 0x61651be, "strcat" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x921a2879, "pid_task" },
	{ 0x27e6be88, "find_get_pid" },
	{ 0xd0d8621b, "strlen" },
	{ 0x4539439c, "init_task" },
	{ 0x2e60bace, "memcpy" },
	{ 0x50eedeb8, "printk" },
	{ 0xb4390f9a, "mcount" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "66DA5CB66164058DC860C55");
