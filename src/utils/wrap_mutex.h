//  $Id: wrap_mutex.h 379 2014-04-14 23:14:15Z serge $

#ifndef WRAP_MUTEX_H
#define WRAP_MUTEX_H

#define CPP_MUTEX(_x)           boost::mutex _x
#define CPP_COND(_x)
#define CPP_INIT_COND(_x)
#define CPP_BROADCAST_COND(_x)
#define SCOPE_LOCK(_x)          boost::mutex::scoped_lock _scoped_lock##_x(_x)
#define THREAD_SLEEP_MS(_x)     boost::this_thread::sleep( boost::posix_time::milliseconds( _x ) )

#endif // WRAP_MUTEX_H
