#pragma once

// hijacked from log4cxx.
// see apache-log4cxx-x.y.z/src/main/include/log4cxx/spi/location/locationinfo.h
#if !defined(WLOG_LOCATION)
#if defined(_MSC_VER)
#if _MSC_VER >= 1300
#define __WLOG_FUNC__ __FUNCSIG__
#endif
#else
#if defined(__GNUC__)
#define __WLOG_FUNC__ __PRETTY_FUNCTION__
#endif
#endif
#if !defined(__WLOG_FUNC__)
#define __WLOG_FUNC__ ""
#endif
#define WLOG_LOCATION __FILE__,__WLOG_FUNC__,__LINE__
#endif
