#include <cstdlib>
#include<cstdint>
#define ROUND_UP(addr,align) (((addr) + (align - 1)) & (~(align - 1)))
#define ROUND_DOWN(addr,align) ((addr) & (~(align - 1)))
class HeapManager
{
public:
	static HeapManager * Create(void * pHeapMemory, size_t sizeHeap);
	void * myAlloc(size_t chunkSize);
	bool myFree(void * pPtr);
	void myCollect();

private:
	typedef struct MemBlockDescriptor
	{
		
		size_t fullSize;
		size_t userSize;
		void * userStart;
		MemBlockDescriptor * next;
		bool isInUse;
	}MemBlockDesc;

	uint8_t * startOfHeap;
	uint8_t * currentPosOfHeap;
	uint8_t * endOfHeap;

	static MemBlockDesc * memoryList;
	static MemBlockDesc * head;
	static HeapManager * heapManager;
};