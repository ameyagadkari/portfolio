#ifndef bit_array_h
#define bit_array_h

#if defined _WIN64
#define ENV64
#else
#define ENV32 
#endif //_WIN64

#include <cassert>
#include <malloc.h>
#include <memory>
#include <cstdint>

namespace Engine
{
	namespace Containers
	{
		extern void bit_array_UnitTest(void);
		class bit_array
		{
		public:

#if defined ENV32
			typedef	 uint32_t integer;
#else
			typedef	 uint64_t integer;
#endif

			bit_array(integer i_numBits, bool i_startClear = true);
			bit_array(const bit_array& other);
			virtual ~bit_array(void);

			void Clear(void)const;
			void Set(void)const;

			bool IsEmpty(void)const;
			bool IsFull(void)const;

			inline bool IsBitSet(const integer i_bitNumber)const;
			inline bool IsBitClear(const integer i_bitNumber)const;

			inline void SetBit(const integer i_bitNumber)const;
			inline void ClearBit(const integer i_bitNumber)const;

			bool GetFirstClearBit(integer & o_bitNumber)const;
			bool GetFirstSetBit(integer & o_bitNumber)const;

			inline bool operator[](integer i_index)const;
			inline bit_array& operator=(const bit_array &other);
			
			inline bit_array & operator&=(const bit_array &other);
			inline bit_array & operator|=(const bit_array &other);
			inline bit_array & operator^=(const bit_array &other);
			inline bit_array & operator<<=(const unsigned int lShift);
			inline bit_array & operator>>=(const unsigned int rShift);

			inline friend bit_array operator ~(const bit_array &other);
			inline friend bit_array operator &(const bit_array &lhs, const bit_array &rhs);
			inline friend bit_array operator |(const bit_array &lhs, const bit_array &rhs);
			inline friend bit_array operator ^(const bit_array &lhs, const bit_array &rhs);
			inline friend bit_array operator<<(const bit_array &other, const unsigned int lShift);
			inline friend bit_array operator>>(const bit_array &other, const unsigned int rShift);
			
			inline friend bool operator==(const bit_array &lhs, const bit_array &rhs);
			inline friend bool operator!=(const bit_array &lhs, const bit_array &rhs);

		private:

			unsigned char *			m_pBitMemory;
			integer	m_numBits;
			static const unsigned char maskLookUp[];
		};
	}
}
#include"bit_array_inl.h"
#endif // !bit_array_h