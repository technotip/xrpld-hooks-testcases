#define ASSERT(cond)\
{\
	if (!(cond))\
		rollback(0,0,__LINE__);\
}
