
#include <app_dns_lib/app_dns_lib.h>
#include <string.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/net/dns_resolve.h>

LOG_MODULE_REGISTER(app_dns_lib, LOG_LEVEL_INF);

#define DNS_TIMEOUT (2 * MSEC_PER_SEC)
int app_dns_lib_init(void) {
  LOG_INF("app_dns_lib init");
  return 0;
}

void dns_result_cb(enum dns_resolve_status status, struct dns_addrinfo *info,
                   void *user_data) {
  char hr_addr[NET_IPV6_ADDR_LEN];
  char *hr_family;
  void *addr;

  switch (status) {
  case DNS_EAI_CANCELED:
    LOG_INF("mDNS query was canceled");
    return;
  case DNS_EAI_FAIL:
    LOG_INF("mDNS resolve failed");
    return;
  case DNS_EAI_NODATA:
    LOG_INF("Cannot resolve address using mDNS");
    return;
  case DNS_EAI_ALLDONE:
    LOG_INF("mDNS resolving finished");
    return;
  case DNS_EAI_INPROGRESS:
    break;
  default:
    LOG_INF("mDNS resolving error (%d)", status);
    return;
  }

  if (!info) {
    return;
  }

  app_dns_record *dns_rec = (app_dns_record *)user_data;
  memcpy(&dns_rec->addr, &info->ai_addr, info->ai_addrlen);
  dns_rec->addr_len = info->ai_addrlen;
  dns_rec->resolved = true;

  // if (info->ai_family == NET_AF_INET) {
  //   hr_family = "IPv4";
  //   addr = &net_sin(&info->ai_addr)->sin_addr;
  // } else if (info->ai_family == NET_AF_INET6) {
  //   hr_family = "IPv6";
  //   addr = &net_sin6(&info->ai_addr)->sin6_addr;
  // } else {
  //   LOG_ERR("Invalid IP address family %d", info->ai_family);
  //   return;
  // }
  //
  // LOG_INF("%s %s address: %s", user_data ? (char *)user_data : "<null>",
  //         hr_family,
  //         net_addr_ntop(info->ai_family, addr, hr_addr, sizeof(hr_addr)));
}

int app_dns_query(app_dns_record *dns_rec) {
  int ret;
  ret = dns_get_addr_info(dns_rec->host_name, DNS_QUERY_TYPE_A, NULL,
                          dns_result_cb, dns_rec, DNS_TIMEOUT);

  return ret;
}
