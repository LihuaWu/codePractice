#include "Atomic.h"

#include <assert.h>
#include <stdio.h>

int main() {
	Sync::AtomicInt64 a0;

	printf("ao.get() = %lld\n", a0.get());
	printf("a0.getAndAdd(1) = %lld\n", a0.getAndAdd(1));
	printf("ao.get() = %lld\n", a0.get());

	printf("a0.addAndGet(2) = %lld\n", a0.addAndGet(2));

	printf("a0.incrementAndGet() = %lld\n", a0.incrementAndGet());

	a0.increment();
	printf("ao.get() = %lld\n", a0.get());

	printf("a0.addAndGet(-3) = %lld\n", a0.addAndGet(-3));

	printf("a0.getAndSet(100) = %lld\n",a0.getAndSet(100));
	printf("ao.get() = %lld\n", a0.get());
	printf("ao.get() = %lld\n", a0.get());
	return 0;
}
