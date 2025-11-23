
#include <app_dns_lib/app_dns_lib.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(app_dns_lib, LOG_LEVEL_INF);

int app_dns_lib_init(void) {
  LOG_INF("app_dns_lib init");
  return 0;
}

int app_dns_lib_do_something(int value) {
  LOG_INF("Doing something with %d", value);
  return value * 2;
}
