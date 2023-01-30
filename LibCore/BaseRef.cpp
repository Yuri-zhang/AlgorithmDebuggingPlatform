#include "pch.h"
#include "BaseRef.h"
#include <windows.h>
#include "LockHelper.h"
BaseRef::BaseRef()
{
	refcount_ = 0;
	mutex_ = CreateMutex(NULL, FALSE, NULL);
}

BaseRef::~BaseRef()
{
	if (mutex_)
	{
		CloseHandle(mutex_);
		mutex_ = NULL;
	}
}

long BaseRef::callref()
{
	MutexHelper mutxt(mutex_);
	refcount_++;
	return refcount_;
}

long BaseRef::uncallref()
{
	MutexHelper mutxt(mutex_);
	if (refcount_ == 0)
	{
		return 0;
	}
	refcount_--;
	return refcount_;
}

const long BaseRef::getrefcount() const
{
	MutexHelper mutxt(mutex_);
	return refcount_;
}