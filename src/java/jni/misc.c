/*
 * Copyright (c) 2014 Charles University in Prague
 * Copyright (c) 2014 Vojtech Horky
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * - The name of the author may not be used to endorse or promote products
 *   derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "papi_Wrapper.h"
#include "papijava.h"

#include <stdlib.h>
#include <pthread.h>
#include <papi.h>

JNIEXPORT jint JNICALL Java_papi_Wrapper_initLibrary
		(JNIEnv UNUSED_ARG(*env), jclass UNUSED_ARG(self), jint versionj) {
	int version = (versionj);
	if (version != PAPI_VER_CURRENT) {
		return PAPI_ENOSUPP;
	}
	return PAPI_library_init(PAPI_VER_CURRENT);
}

JNIEXPORT jint JNICALL Java_papi_Wrapper_initThread
		(JNIEnv UNUSED_ARG(*env), jclass UNUSED_ARG(self)) {

  return PAPI_thread_init(pthread_self);
}
