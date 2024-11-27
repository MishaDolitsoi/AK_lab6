#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/ktime.h>
#include <linux/slab.h>
#include <linux/list.h>

MODULE_AUTHOR("IO-24 Dolitsoi M.V.");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

static uint repeat = 1;
module_param(repeat, uint, 0444);
MODULE_PARM_DESC(repeat, "Number of times to print 'Hello, world!' message");

struct hello_data {
    struct list_head list;
    ktime_t time;
};

static LIST_HEAD(hello_list);

static int __init hello_init(void)
{
    BUG_ON(repeat>10);
    struct hello_data *data;
    int i;
    
    for (i = 0; i < repeat; i++) {
        if (i == 2) {
            data = NULL;
        } else {
            data = kmalloc(sizeof(*data), GFP_KERNEL);
        }

        if(!data) {
		printk(KERN_ERR "Failed to allocate memory at iteration %d\n", i + 1);
		return -ENOMEM;
        }

        data->time = ktime_get();
        list_add_tail(&data->list, &hello_list);

        printk(KERN_EMERG "Hello, world!\n");
    }

    return 0;
}

static void __exit hello_exit(void)
{
    struct hello_data *data, *tmp;

    list_for_each_entry_safe(data, tmp, &hello_list, list) {
        printk(KERN_INFO "Time: %lld ns\n", ktime_to_ns(data->time));
        list_del(&data->list);
        kfree(data);
    }
}

module_init(hello_init);
module_exit(hello_exit);

