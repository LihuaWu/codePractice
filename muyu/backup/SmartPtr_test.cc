#include <stdio.h>

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

int main() {

	int *p = new int(5);
	boost::shared_ptr<int> ip(p);
	boost::weak_ptr<int> wip(ip);

	boost::shared_ptr<int> ip2 = wip.lock();
	if (ip2) {
		printf("ip.use_count = %ld\n", ip.use_count());
		*ip2 = 9;
		ip2.reset();
		printf("ip.use_count = %ld\n", ip.use_count());
		printf("*ip = %d\n", *ip);
	}

	return 0;
}
