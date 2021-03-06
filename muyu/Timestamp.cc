#include "Timestamp.h"

#include <sys/time.h>
#include <inttypes.h>
#include <stdio.h>

#include <string>

#include <boost/static_assert.hpp>

using namespace Sync;

BOOST_STATIC_ASSERT(sizeof(Timestamp) == sizeof(int64_t));

std::string Timestamp::toString() const {
	char buf[32] = {0};
	int64_t seconds = microSecondsSinceEpoch_ / kMicroSecondsPerSecond;
	int64_t microseconds = microSecondsSinceEpoch_ % kMicroSecondsPerSecond;
	snprintf(buf, sizeof(buf) - 1, "%lld%lld", seconds, microseconds);
	return buf;
}

Timestamp Timestamp::now() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	int64_t seconds = tv.tv_sec;
	return Timestamp(seconds * kMicroSecondsPerSecond + tv.tv_usec);
}

//change seconds into local time format
std::string Timestamp::toFormattedString(bool showMicroseconds) const {
	char buf[32] = {};
	time_t seconds = static_cast<time_t>(microSecondsSinceEpoch_ / kMicroSecondsPerSecond);
	struct tm tm_time;

	gmtime_r(&seconds, &tm_time);

	if (showMicroseconds) {
		int microseconds = static_cast<int>(microSecondsSinceEpoch_ % kMicroSecondsPerSecond);
		snprintf(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d.%06d",
				tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday, tm_time.tm_hour + 8, tm_time.tm_min, tm_time.tm_sec, microseconds);
	} else {
		snprintf(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d",
				tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday, tm_time.tm_hour + 8, tm_time.tm_min, tm_time.tm_sec); 
	}
	return buf;
}
