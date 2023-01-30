#pragma once
#include <iostream>

//如果指针为空，则直接返回
#define  Check_EmptyPointer_NoReturn(data) \
if(data==NULL)\
{\
	return;\
}

//如果指针为空，则直接continue
#define  Check_EmptyPointer_Continue(data) \
if(data==NULL)\
{\
	continue;\
}

//如果指针为空，则返回指定错误编号
#define  Check_EmptyPointer(data,errorvalue) \
if(data==NULL)\
{\
	return errorvalue;\
}


//满足条件时，返回指定错误编号
#define  Check_Condition(data,errorvalue) \
if((data))\
{\
	return errorvalue;\
}

//如果小于0，则返回指定错误编号
#define   Check_LessZero(data,errorvalue) \
if(data<0)\
{\
	return errorvalue;\
}

//如果指针为空，则返回指定错误编号，并记录
#define  LogCheck_EmptyPointer(data,errorvalue,logfun,log) \
if(data==NULL)\
{\
	logfun(log);\
	return errorvalue;\
}

//满足条件时，返回指定错误编号，并记录
#define LogCheck_Condition(data,errorvalue,logfun,log) \
if((data))\
{\
	logfun(log);\
	return errorvalue;\
}

//如果小于0，则返回指定错误编号，并记录
#define   LogCheck_LessZero(data,errorvalue,logfun,log) \
if(data<0)\
{\
	logfun(log);\
	return errorvalue;\
}


#define  DestroyPointer(data)\
if(data)\
{\
	delete data;\
	data = NULL;\
}

#define  DestroyArrayPointer(data)\
if(data)\
{\
	delete [] data;\
	data = NULL;\
}


#define For_(index,begin,end) for(int index=begin;index<end;index++)

#define  ArraySize(a)  (sizeof((a))/sizeof((a[0]))) 

//将指针数据强制转换为另外一种类型指针
#define PointerToPointer(type,value) reinterpret_cast<type*>(value)

//将指针数据强制转换为另外一种类型的数据
#define PointerToValue(type,value) *reinterpret_cast<type*>(value)

#define FormatDouble(x) int(x*10000)/10000.0f
