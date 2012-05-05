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

#include "../include/xs.h"

#include "xpub.h"
#include "likely.h"

/*  Prototype of virtual functions implementations. */
static int xs_xpub_term (xs_sock *sock);

int xs_xpub_init (xs_xpub *self)
{
    int rc;

    rc = xs_sock_init (&self->sock);
    if (unlikely (rc < 0))
        return rc;

    /*  Initialise virtual function pointers. */
    self->sock.vfptr.term = xs_xpub_term;
    self->sock.type = XS_XPUB;

    /*  TODO  */

    return 0;
}

static int xs_xpub_term (xs_sock *sock)
{
    int rc;
    xs_xpub *self = (xs_xpub*) sock;
    
    /*  TODO  */

    rc = xs_sock_term (&self->sock);
    if (unlikely (rc < 0))
        return rc;

    return 0;    
}
