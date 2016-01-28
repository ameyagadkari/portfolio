#include"bit_array.h"
namespace Engine
{
	namespace Containers
	{
		const unsigned char bit_array::maskLookUp[] = { 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff };
		/** Constructor, copy constructor and destructor */
		bit_array::bit_array(integer i_numBits, bool i_startClear) :m_numBits(i_numBits)
		{
			assert(i_numBits);

			integer bytesNeeded = (i_numBits + (8 - 1)) / 8;

			integer adjustment = bytesNeeded * 8 - i_numBits;

			unsigned char mask = maskLookUp[8 - adjustment];

			m_pBitMemory = reinterpret_cast<unsigned char *>(_aligned_malloc(bytesNeeded, sizeof(integer)));

			assert(m_pBitMemory);

			int initValue = i_startClear ? 0 : ~0;

			memset(m_pBitMemory, initValue, bytesNeeded);

			m_pBitMemory[bytesNeeded - 1] &= mask;

			//m_numBits = i_numBits;
		}

		bit_array::bit_array(const bit_array& other) :m_numBits(other.m_numBits)
		{
			integer bytesNeeded = (other.m_numBits + (8 - 1)) / 8;

			m_pBitMemory = reinterpret_cast<unsigned char *>(_aligned_malloc(bytesNeeded, sizeof(integer)));

			bit_array::integer byte = 0;

			while (byte < bytesNeeded)
			{
				*(m_pBitMemory + byte) = *(other.m_pBitMemory + byte);
				byte++;
			}

			//m_numBits = other.m_numBits;
		}
		
		bit_array::~bit_array(void)
		{
			assert(m_pBitMemory);

			_aligned_free(m_pBitMemory);
		}

		/** Other non-inlined methods */
		void bit_array::Clear(void)const
		{
			memset(m_pBitMemory, 0, (m_numBits + (7 - 1)) / 8);
		}

		void bit_array::Set(void)const
		{
			memset(m_pBitMemory, ~0, (m_numBits + (7 - 1)) / 8);

			integer bytesNeeded = (m_numBits + (8 - 1)) / 8;

			integer adjustment = bytesNeeded * 8 - m_numBits;

			unsigned char mask = maskLookUp[8 - adjustment];

			m_pBitMemory[bytesNeeded - 1] &= mask;
		}

		bool bit_array::IsEmpty(void)const
		{
			integer i_dummyBit;

			return GetFirstSetBit(i_dummyBit) == false;
		}

		bool bit_array::IsFull(void)const
		{
			integer i_dummyBit;

			return GetFirstClearBit(i_dummyBit) == false;
		}

		bool bit_array::GetFirstClearBit(integer & o_bitNumber)const
		{
			integer allSet = 0xff;

			integer numBytes = (m_numBits + (8 - 1)) / 8;
			integer byte = 0;

			while ((static_cast<integer>(m_pBitMemory[byte]) == allSet) && (byte < numBytes))
				byte++;

			if (byte == numBytes)
				return false;

			integer bit = 0;
			unsigned char bit_mask = 0x80;

			while ((m_pBitMemory[byte] & bit_mask) != 0)
			{
				bit_mask >>= 1;
				bit++;
			}

			integer bitNumber = (byte * 8) + bit;

			if (bitNumber < m_numBits)
			{
				o_bitNumber = bitNumber;
				return true;
			}
			else
				return false;
		}

		bool bit_array::GetFirstSetBit(integer & o_bitNumber)const
		{
			integer allClear = 0;

			integer numBytes = (m_numBits + (8 - 1)) / 8;
			integer byte = 0;

			while ((static_cast<integer>(m_pBitMemory[byte]) == allClear) && (byte < numBytes))
				byte++;

			if (byte == numBytes)
				return false;

			integer bit = 0;
			unsigned char bit_mask = 0x80;

			while ((m_pBitMemory[byte] & bit_mask) == 0)
			{
				bit_mask >>= 1;
				bit++;
			}

			integer bitNumber = (byte * 8) + bit;

			if (bitNumber < m_numBits)
			{
				o_bitNumber = bitNumber;
				return true;
			}
			else
				return false;
		}
	}
}