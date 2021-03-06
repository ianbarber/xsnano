/*
    Copyright (c) 2012 250bpm s.r.o.

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to
    deal in the Software without restriction, including without limitation the
    rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
    sell copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#include <string.h>

#include "../include/xs.h"
#include "err.h"
#include "ctx.h"
#include "likely.h"

#define XS_CHECK_SOCKET(s) \
    if (s > ctx.socks_num || !ctx.socks [s]) {\
        errno = EBADF;\
        return -1;\
    }

/*  Global state of the library. */
static xs_ctx ctx;

int xs_init (void)
{
    int rc;

    rc = xs_ctx_init (&ctx);
    if (unlikely (rc < 0)) {
        errno = -rc;
        return -1;
    }
    return 0;
}

int xs_term (void)
{
    int rc;

    rc = xs_ctx_term (&ctx);
    if (unlikely (rc < 0)) {
        errno = -rc;
        return -1;
    }
    return 0;
}

int xs_socket (int type)
{
    int s;

    s = xs_ctx_socket (&ctx, type);
    if (unlikely (s < 0)) {
        errno = -s;
        return -1;
    }
    return s;
    
}

int xs_close (int s)
{
    int rc;

    rc = xs_ctx_close (&ctx, s);
    if (unlikely (rc < 0)) {
        errno = -rc;
        return -1;
    }
    return 0;
}

int xs_setsockopt (int s, int level, int option, const void *optval,
    size_t optvallen)
{
    int rc;

    XS_CHECK_SOCKET (s);
    rc = ctx.socks [s]->vfptr.setopt (ctx.socks [s], level, option,
        optval, optvallen);
    if (unlikely (rc < 0)) {
        errno = -rc;
        return -1;
    }
    return 0;
}

int xs_getsockopt (int s, int level, int option, void *optval,
    size_t *optvallen)
{
    int rc;

    XS_CHECK_SOCKET (s);
    rc = ctx.socks [s]->vfptr.getopt (ctx.socks [s], level, option,
        optval, optvallen);
    if (unlikely (rc < 0)) {
        errno = -rc;
        return -1;
    }
    return 0;
}

int xs_bind (int s, const char *addr)
{
    int rc;

    XS_CHECK_SOCKET (s);
    rc = xs_sock_bind (ctx.socks [s], addr);
    if (unlikely (rc < 0)) {
        errno = -rc;
        return -1;
    }
    return rc;
}

int xs_connect (int s, const char *addr)
{
    int rc;

    XS_CHECK_SOCKET (s);
    rc = xs_sock_connect (ctx.socks [s], addr);
    if (unlikely (rc < 0)) {
        errno = -rc;
        return -1;
    }
    return rc;
}

int xs_shutdown (int s, int how)
{
    int rc;

    XS_CHECK_SOCKET (s);
    rc = xs_sock_shutdown (ctx.socks [s], how);
    if (unlikely (rc < 0)) {
        errno = -rc;
        return -1;
    }
    return 0;
}

int xs_send (int s, const void *buf, size_t len, int flags)
{
    int rc;

    XS_CHECK_SOCKET (s);
    rc = xs_sock_send (ctx.socks [s], buf, len, flags);
    if (unlikely (rc < 0)) {
        errno = -rc;
        return -1;
    }
    return rc;
}

int xs_recv (int s, void *buf, size_t len, int flags)
{
    int rc;

    XS_CHECK_SOCKET (s);
    rc = xs_sock_recv (ctx.socks [s], buf, len, flags);
    if (unlikely (rc < 0)) {
        errno = -rc;
        return -1;
    }
    return rc;
}

void xs_version (int *major, int *minor, int *patch)
{
    if (major)
        *major = XS_VERSION_MAJOR;
    if (minor)
        *minor = XS_VERSION_MINOR;
    if (patch)
        *patch = XS_VERSION_PATCH;
}

int xs_errno (void)
{
    return errno;
}

const char *xs_strerror (int errnum)
{
    return xs_err_strerror (errnum);
}

