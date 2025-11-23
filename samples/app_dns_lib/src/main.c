#include <app_dns_lib/app_dns_lib.h>
#include <zephyr/kernel.h>

int main(void) {
  app_dns_lib_init();

  int result = app_dns_lib_do_something(21);
  printk("Result = %d\n", result);

  while (1) {
    k_sleep(K_SECONDS(1));
  }
}
