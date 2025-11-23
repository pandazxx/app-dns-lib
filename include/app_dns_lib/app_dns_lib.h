
#ifndef APP_DNS_LIB_H_
#define APP_DNS_LIB_H_

#include <zephyr/kernel.h>
#include <zephyr/net/net_ip.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  char host_name[256];
  bool resolved;
  struct sockaddr_storage addr;
  socklen_t addr_len;
} app_dns_record;

int app_dns_lib_init(void);

int app_dns_query(app_dns_record *dns_rec);

#ifdef __cplusplus
}
#endif

#endif
