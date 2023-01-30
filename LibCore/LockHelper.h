#pragma once

//本类用于辅助加锁操作，只要在需要加锁的程序块中声明一个对象，即可实现加锁
class MutexHelper
{
	HANDLE mutex_;								//所用的锁
public:
	bool locked_;

	_When_(this->locked_, _Acquires_lock_(this->mutex_)) MutexHelper(HANDLE hMutex): mutex_(hMutex), locked_(false)
	{
		if(WaitForSingleObject(mutex_, INFINITE) == WAIT_OBJECT_0)
			locked_ = true;
	};
	_When_(this->locked_, _Releases_lock_(this->mutex_)) ~MutexHelper(void)
	{
		if(locked_)
			ReleaseMutex(mutex_);
	};
};

class CCriticalSectionHelper
{
	LPCRITICAL_SECTION criticalsection_;			//所用的锁
public:
	_Acquires_lock_(*this->criticalsection_) CCriticalSectionHelper(LPCRITICAL_SECTION pCriticalSection)
		: criticalsection_(pCriticalSection)
	{EnterCriticalSection(criticalsection_);};

	_Releases_lock_(*this->criticalsection_) ~CCriticalSectionHelper(void)
	{LeaveCriticalSection(criticalsection_);};
};