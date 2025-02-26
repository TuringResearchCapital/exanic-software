#include "common.h"

#include <netinet/tcp.h>
#include <netinet/ip.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>
#include <sched.h>
#include <time.h>

#include "kernel/consts.h"
#include "kernel/structs.h"
#include "lock.h"
#include "rwlock.h"
#include "structs.h"
#include "checksum.h"
#include "ip.h"
#include "tcp_buffer.h"
#include "tcp.h"

struct exa_hashtable __exa_tcp_sockfds;

struct exa_tcp_state* exasock_get_tcp_state(int fd) {
    // Look up the socket based on its file descriptor.
    struct exa_socket *sock = exa_socket_get(fd);
    if (sock == NULL) {
        return NULL;
    }
    // Return a pointer to the TCP state inside the socket's state.
    return &sock->state->p.tcp;
}

__attribute__((constructor))
void
__exa_tcp_init(void)
{
    exa_hashtable_init(&__exa_tcp_sockfds);
}
