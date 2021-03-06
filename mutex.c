/*
 * Copyright (c) 2015 Josef 'Jeff' Sipek <jeffpc@josefsipek.net>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>
#include <assert.h>

#include "mutex.h"

void mxinit(pthread_mutex_t *m)
{
	assert(!pthread_mutex_init(m, NULL));
}

void mxdestroy(pthread_mutex_t *m)
{
	assert(!pthread_mutex_destroy(m));
}

void mxlock(pthread_mutex_t *m)
{
	assert(!pthread_mutex_lock(m));
}

void mxunlock(pthread_mutex_t *m)
{
	assert(!pthread_mutex_unlock(m));
}

void rwinit(pthread_rwlock_t *l)
{
	assert(!pthread_rwlock_init(l, NULL));
}

void rwdestroy(pthread_rwlock_t *l)
{
	assert(!pthread_rwlock_destroy(l));
}

void rwlock(pthread_rwlock_t *l, bool wr)
{
	if (wr)
		assert(!pthread_rwlock_wrlock(l));
	else
		assert(!pthread_rwlock_rdlock(l));
}

void rwunlock(pthread_rwlock_t *l)
{
	assert(!pthread_rwlock_unlock(l));
}

void condinit(pthread_cond_t *c)
{
	assert(!pthread_cond_init(c, NULL));
}

void conddestroy(pthread_cond_t *c)
{
	assert(!pthread_cond_destroy(c));
}

void condwait(pthread_cond_t *c, pthread_mutex_t *m)
{
	assert(!pthread_cond_wait(c, m));
}

int condreltimedwait(pthread_cond_t *c, pthread_mutex_t *m,
		     const struct timespec *reltime)
{
	struct timespec abstime;
	struct timespec now;
	int ret;

	clock_gettime(CLOCK_REALTIME, &now);

	if ((now.tv_nsec + reltime->tv_nsec) >= 1000000000) {
		now.tv_sec++;
		now.tv_nsec -= 1000000000;
	}

	abstime.tv_sec  = now.tv_sec  + reltime->tv_sec;
	abstime.tv_nsec = now.tv_nsec + reltime->tv_nsec;

	ret = pthread_cond_timedwait(c, m, &abstime);
	if ((ret != 0) || (ret != ETIMEDOUT))
		assert(0);

	return ret;
}

void condsig(pthread_cond_t *c)
{
	assert(!pthread_cond_signal(c));
}

void condbcast(pthread_cond_t *c)
{
	assert(!pthread_cond_broadcast(c));
}
