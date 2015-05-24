bin_PROGRAMS=
noinst_PROGRAMS=test_kdb testThread testBlockingQueue Timestamp_test Mutex_test Atomic_test smartptr_test Exception_test Thread_bench ThreadPool_test

AM_CPPFLAGS=-Wall -g -D_FILE_OFFSET_BITS=64

INCLUDES=-I.-I/usr/include/  -I/usr/local/include/boost-1_34/
bindir=$(prefix)

testThread_SOURCES=Thread_test.cc Thread.cc
testThread_LDADD=-lboost_thread-gcc41-mt-1_34 -lpthread
testThread_DEPENDENCIES=

Thread_bench_SOURCES=Thread_bench.cc Thread.cc Timestamp.cc
Thread_bench_LDADD=-lboost_thread-gcc41-mt-1_34 -lpthread
Thread_bench_DEPENDENCIES=

testBlockingQueue_SOURCES=testBlockingQueue.cc Thread.cc CountDownLatch.cc
testBlockingQueue_LDADD= -lboost_thread-gcc41-mt-1_34 -lpthread
testBlockingQueue_DEPENDENCIES=

Timestamp_test_SOURCES=Timestamp.cc Timestamp_test.cc 
Timestamp_test_LDADD=
Timestamp_test_DEPENDENCIES=

Mutex_test_SOURCES=Mutex_test.cc Thread.cc Timestamp.cc
Mutex_test_LDADD=-lpthread -lboost_thread-gcc41-mt-1_34
Mutex_test_DEPENDENCIES=

Atomic_test_SOURCES=Atomic_test.cc
Atomic_test_LDADD=
Atomic_test_DEPENDENCIES=

smartptr_test_SOURCES=SmartPtr_test.cc
smartptr_test_LDADD=
smartptr_test_DEPENDENCIES=

Exception_test_SOURCES=Exception_test.cc Exception.cc
Exception_test_LDADD=
Exception_test_DEPENDENCIES=

ThreadPool_test_SOURCES=ThreadPool_test.cc ThreadPool.cc Thread.cc CountDownLatch.cc Exception.cc
ThreadPool_test_LDADD=-lpthread
ThreadPool_test_DEPENDENCIES=

test_kdb_SOURCES=test_kdb.cc
test_kdb_LDADD=
test_kdb_DEPENDENCIES=
