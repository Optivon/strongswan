/*
 * Copyright (C) 2013 Martin Willi
 * Copyright (C) 2013 revosec AG
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */

#ifndef WINDOWS_THREAD_H_
#define WINDOWS_THREAD_H_

/**
 * @defgroup windowsthread windows
 * @ingroup threading
 *
 * @defgroup threadwindows thread
 * @{ @ingroup windowsthread
 */

/**
 * MinGW seems to miss the actual struct definition
 */
typedef struct {
	PVOID Ptr;
} SRWLOCK, *PSRWLOCK, CONDITION_VARIABLE, *PCONDITION_VARIABLE;

VOID WINAPI InitializeConditionVariable(PCONDITION_VARIABLE ConditionVariable);
BOOL WINAPI SleepConditionVariableCS(PCONDITION_VARIABLE ConditionVariable,
					PCRITICAL_SECTION CriticalSection, DWORD dwMilliseconds);
BOOL WINAPI SleepConditionVariableSRW(PCONDITION_VARIABLE ConditionVariable,
						PSRWLOCK SRWLock, DWORD dwMilliseconds, ULONG Flags);
VOID WINAPI WakeAllConditionVariable(PCONDITION_VARIABLE ConditionVariable);
VOID WINAPI WakeConditionVariable(PCONDITION_VARIABLE ConditionVariable);
VOID WINAPI AcquireSRWLockExclusive(PSRWLOCK SRWLock);
VOID WINAPI AcquireSRWLockShared(PSRWLOCK SRWLock);
BOOL TryAcquireSRWLockExclusive(PSRWLOCK SRWLock);
VOID WINAPI InitializeSRWLock(PSRWLOCK SRWLock);
VOID WINAPI ReleaseSRWLockExclusive(PSRWLOCK SRWLock);
VOID WINAPI ReleaseSRWLockShared(PSRWLOCK SRWLock);

/**
 * Set active condvar of a thread before waiting in it.
 *
 * @param cv		active condition variable, NULL to unset
 */
void thread_set_active_condvar(CONDITION_VARIABLE *condvar);

/**
 * Set a thread specific value on the current thread.
 *
 * @param key		unique key specifying the TLS variable
 * @param value		value to set
 * @return			old value for key, if any
 */
void* thread_tls_put(void *key, void *value);

/**
 * Get a thread specific value from the current thread.
 *
 * @param key		unique key specifying the TLS variable
 * @return			value for key, if any
 */
void* thread_tls_get(void *key);

/**
 * Remove a thread specific value from the current thread.
 *
 * @param key		unique key specifying the TLS variable
 * @return			value for key, if any
 */
void* thread_tls_remove(void *key);

/**
 * Remove a thread specific value from all threads.
 *
 * For each found TLS value thread_tls_cleanup() is invoked.
 *
 * @param key		unique key specifying the TLS variable
 */
void thread_tls_remove_all(void *key);

/**
 * Cleanup function for thread specific value.
 *
 * This is called whenever a thread exits to clean up thread specific data.
 *
 * This function is actually implemented in thread_value.c.
 *
 * @param value		value, as passed to thread_tls_put()
 */
void thread_tls_cleanup(void *value);

#endif /** WINDOWS_THREAD_H_ @}*/
