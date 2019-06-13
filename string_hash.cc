/// @brief BKDR Hash Function
/// @detail 本算法由于在Brian Kernighan与Dennis Ritchie的《The C Programming Language》一书被展示而得名，是一种简单快捷的hash算法，也是Java目前采用的字符串的Hash算法（累乘因子为31）。
template<class T>
size_t BKDRHash(const T *str)
{
	register size_t hash = 0;
	while (size_t ch = (size_t)*str++)
	{		
		hash = hash * 131 + ch;   // 也可以乘以31、131、1313、13131、131313..
		// 有人说将乘法分解为位运算及加减法可以提高效率，如将上式表达为：hash = hash << 7 + hash << 1 + hash + ch;
		// 但其实在Intel平台上，CPU内部对二者的处理效率都是差不多的，
		// 我分别进行了100亿次的上述两种运算，发现二者时间差距基本为0（如果是Debug版，分解成位运算后的耗时还要高1/3）；
		// 在ARM这类RISC系统上没有测试过，由于ARM内部使用Booth's Algorithm来模拟32位整数乘法运算，它的效率与乘数有关：
		// 当乘数8-31位都为1或0时，需要1个时钟周期
		// 当乘数16-31位都为1或0时，需要2个时钟周期
		// 当乘数24-31位都为1或0时，需要3个时钟周期
		// 否则，需要4个时钟周期
		// 因此，虽然我没有实际测试，但是我依然认为二者效率上差别不大		
	}
	return hash;
}
/// @brief SDBM Hash Function
/// @detail 本算法是由于在开源项目SDBM（一种简单的数据库引擎）中被应用而得名，它与BKDRHash思想一致，只是种子不同而已。
template<class T>
size_t SDBMHash(const T *str)
{
	register size_t hash = 0;
	while (size_t ch = (size_t)*str++)
	{
		hash = 65599 * hash + ch;		
		//hash = (size_t)ch + (hash << 6) + (hash << 16) - hash;
	}
	return hash;
}
/// @brief RS Hash Function
/// @detail 因Robert Sedgwicks在其《Algorithms in C》一书中展示而得名。
template<class T>
size_t RSHash(const T *str)
{
	register size_t hash = 0;
	size_t magic = 63689;	
	while (size_t ch = (size_t)*str++)
	{
		hash = hash * magic + ch;
		magic *= 378551;
	}
	return hash;
}
/// @brief AP Hash Function
/// @detail 由Arash Partow发明的一种hash算法。
template<class T>
size_t APHash(const T *str)
{
	register size_t hash = 0;
	size_t ch;
	for (long i = 0; ch = (size_t)*str++; i++)
	{
		if ((i & 1) == 0)
		{
			hash ^= ((hash << 7) ^ ch ^ (hash >> 3));
		}
		else
		{
			hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));
		}
	}
	return hash;
}
/// @brief JS Hash Function
/// 由Justin Sobel发明的一种hash算法。
template<class T>
size_t JSHash(const T *str)
{
	if(!*str)		 // 这是由本人添加，以保证空字符串返回哈希值0
		return 0;
	register size_t hash = 1315423911;
	while (size_t ch = (size_t)*str++)
	{
		hash ^= ((hash << 5) + ch + (hash >> 2));
	}
	return hash;
}
/// @brief DEK Function
/// @detail 本算法是由于Donald E. Knuth在《Art Of Computer Programming Volume 3》中展示而得名。
template<class T>
size_t DEKHash(const T* str)
{
	if(!*str)		 // 这是由本人添加，以保证空字符串返回哈希值0
		return 0;
	register size_t hash = 1315423911;
	while (size_t ch = (size_t)*str++)
	{
		hash = ((hash << 5) ^ (hash >> 27)) ^ ch;
	}
	return hash;
}
/// @brief FNV Hash Function
/// @detail Unix system系统中使用的一种著名hash算法，后来微软也在其hash_map中实现。
template<class T>
size_t FNVHash(const T* str)
{
	if(!*str)	// 这是由本人添加，以保证空字符串返回哈希值0
		return 0;
	register size_t hash = 2166136261;
	while (size_t ch = (size_t)*str++)
	{
		hash *= 16777619;
		hash ^= ch;
	}
	return hash;
}
/// @brief DJB Hash Function
/// @detail 由Daniel J. Bernstein教授发明的一种hash算法。
template<class T>
size_t DJBHash(const T *str)
{
	if(!*str)	// 这是由本人添加，以保证空字符串返回哈希值0
		return 0;
	register size_t hash = 5381;
	while (size_t ch = (size_t)*str++)
	{
		hash += (hash << 5) + ch;
	}
	return hash;
}
/// @brief DJB Hash Function 2
/// @detail 由Daniel J. Bernstein 发明的另一种hash算法。
template<class T>
size_t DJB2Hash(const T *str)
{
	if(!*str)	// 这是由本人添加，以保证空字符串返回哈希值0
		return 0;
	register size_t hash = 5381;
	while (size_t ch = (size_t)*str++)
	{
		hash = hash * 33 ^ ch;
	}
	return hash;
}
/// @brief PJW Hash Function
/// @detail 本算法是基于AT&T贝尔实验室的Peter J. Weinberger的论文而发明的一种hash算法。
template<class T>
size_t PJWHash(const T *str)
{
	static const size_t TotalBits		= sizeof(size_t) * 8;
	static const size_t ThreeQuarters	= (TotalBits  * 3) / 4;
	static const size_t OneEighth		= TotalBits / 8;
	static const size_t HighBits		= ((size_t)-1) << (TotalBits - OneEighth);	
	
	register size_t hash = 0;
	size_t magic = 0;	
	while (size_t ch = (size_t)*str++)
	{
		hash = (hash << OneEighth) + ch;
		if ((magic = hash & HighBits) != 0)
		{
			hash = ((hash ^ (magic >> ThreeQuarters)) & (~HighBits));
		}
	}
	return hash;
}
/// @brief ELF Hash Function
/// @detail 由于在Unix的Extended Library Function被附带而得名的一种hash算法，它其实就是PJW Hash的变形。
template<class T>
size_t ELFHash(const T *str)
{
	static const size_t TotalBits		= sizeof(size_t) * 8;
	static const size_t ThreeQuarters	= (TotalBits  * 3) / 4;
	static const size_t OneEighth		= TotalBits / 8;
	static const size_t HighBits		= ((size_t)-1) << (TotalBits - OneEighth);	
	register size_t hash = 0;
	size_t magic = 0;
	while (size_t ch = (size_t)*str++)
	{
		hash = (hash << OneEighth) + ch;
		if ((magic = hash & HighBits) != 0)
		{
			hash ^= (magic >> ThreeQuarters);
			hash &= ~magic;
		}		
	}
	return hash;
}