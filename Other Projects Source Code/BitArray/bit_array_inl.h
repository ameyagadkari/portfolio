#ifndef bit_array_inl_h
#define bit_array_inl_h

namespace Engine
{
	namespace Containers
	{
		/** Small inlined methods */
		inline bool bit_array::IsBitSet(const integer i_bitNumber)const
		{
			assert(i_bitNumber < m_numBits);
			integer byte = i_bitNumber / 8;
			integer bit = i_bitNumber % 8;
			unsigned char bit_mask = 0x80;

			return(m_pBitMemory[byte] & (bit_mask >> bit)) != 0;
		}

		inline bool bit_array::IsBitClear(const integer i_bitNumber)const
		{
			return !IsBitSet(i_bitNumber);
		}

		inline void bit_array::SetBit(const integer i_bitNumber)const
		{
			assert(i_bitNumber < m_numBits);
			integer byte = i_bitNumber / 8;
			integer bit = i_bitNumber % 8;
			unsigned char bit_mask = 0x80;

			m_pBitMemory[byte] = m_pBitMemory[byte] | (bit_mask >> bit);
		}

		inline void bit_array::ClearBit(const integer i_bitNumber)const
		{
			assert(i_bitNumber < m_numBits);
			integer byte = i_bitNumber / 8;
			integer bit = i_bitNumber % 8;
			unsigned char bit_mask = 0x80;

			m_pBitMemory[byte] = m_pBitMemory[byte] & ~(bit_mask >> bit);
		}

		/** Inlined operators overloaded as members of the class */
		inline bool bit_array::operator[](integer i_index)const
		{
			integer byte = i_index / 8;
			integer bit = i_index % 8;
			unsigned char bit_mask = 0x80;

			return (m_pBitMemory[byte] & (bit_mask >> bit)) != 0 ? true : false;
		}

		inline bit_array& bit_array::operator =(const bit_array& other)
		{
			if (this != &other)
			{
				integer numBytes = (other.m_numBits + (8 - 1)) / 8;
				integer byte = 0;

				while (byte < numBytes)
				{
					*(m_pBitMemory + byte) = *(other.m_pBitMemory + byte);
					byte++;
				}
				m_numBits = other.m_numBits;
			}

			return *this;
		}

		inline bit_array & bit_array::operator&=(const bit_array &other)
		{
			assert(m_numBits == other.m_numBits);
			integer numBytes = (m_numBits + (8 - 1)) / 8;
			integer byte = 0;

			while (byte < numBytes)
			{
				m_pBitMemory[byte] &= other.m_pBitMemory[byte];
				byte++;
			}
			return *this;
		}

		inline bit_array & bit_array::operator|=(const bit_array &other)
		{
			assert(m_numBits == other.m_numBits);
			bit_array::integer numBytes = (m_numBits + (8 - 1)) / 8;
			bit_array::integer byte = 0;

			while (byte < numBytes)
			{
				m_pBitMemory[byte] |= other.m_pBitMemory[byte];
				byte++;
			}
			return *this;
		}

		inline bit_array & bit_array::operator^=(const bit_array &other)
		{
			assert(m_numBits == other.m_numBits);
			integer numBytes = (m_numBits + (8 - 1)) / 8;
			integer byte = 0;

			while (byte < numBytes)
			{
				m_pBitMemory[byte] ^= other.m_pBitMemory[byte];
				byte++;
			}
			return *this;
		}

		inline bit_array & bit_array::operator<<=(const unsigned int lShift)
		{
			if (lShift >= m_numBits)
			{
				this->Clear();

				return *this;
			}
			integer numBytes = (m_numBits + (8 - 1)) / 8;
			char *temp = new char[numBytes];
			integer i = 0;
			while (i < numBytes)
			{
				temp[i] = m_pBitMemory[i];
				i++;
			}
			this->Clear();
			integer numBytesDirectlyCopied = (m_numBits + (8 - 1)) / 8 - (lShift + (8 - 1)) / 8;
			integer byte = 0;
			integer offset = lShift / 8;
			unsigned char mask1 = ~maskLookUp[lShift % 8];
			unsigned char leftShift = lShift % 8;
			unsigned char mask2 = maskLookUp[lShift % 8];
			unsigned char rightShift = 8 - leftShift;
			while (byte < numBytesDirectlyCopied)
			{
				m_pBitMemory[byte] |= (mask1 & temp[byte + offset]) << leftShift;
				m_pBitMemory[byte] |= (mask2 & temp[byte + offset + 1]) >> rightShift;
				byte++;
			}
			integer totalNumberOfBitsToBeCopied = m_numBits - lShift;
			integer numberOfRemainingBits = totalNumberOfBitsToBeCopied - numBytesDirectlyCopied * 8;
			if (numberOfRemainingBits)
			{
				m_pBitMemory[byte] |= (mask1 & temp[byte + offset]) << leftShift;
				integer adjustment = numBytes * 8 - m_numBits;
				unsigned char mask3 = maskLookUp[8 - adjustment];
				m_pBitMemory[byte] &= mask3;
			}
			free(temp);
			return *this;
		}

		inline bit_array & bit_array::operator>>=(const unsigned int rShift)
		{
			if (rShift >= m_numBits)
			{
				this->Clear();

				return *this;
			}
			integer numBytes = (m_numBits + (8 - 1)) / 8;
			char *temp = new char[numBytes];
			integer i = 0;
			while (i < numBytes)
			{
				temp[i] = m_pBitMemory[i];
				i++;
			}
			this->Clear();
			integer numBytesDirectlyCopied = (m_numBits + (8 - 1)) / 8 - (rShift + (8 - 1)) / 8;
			integer byte = 0;
			integer offset = rShift / 8;
			unsigned char mask1 = maskLookUp[8 - rShift % 8];
			unsigned char rightShift = rShift % 8;
			unsigned char mask2 = ~maskLookUp[8 - rShift % 8];
			unsigned char leftShift = 8 - rightShift;
			while (byte < numBytesDirectlyCopied)
			{
				m_pBitMemory[byte + offset] |= (mask1 & temp[byte]) >> rightShift;
				m_pBitMemory[byte + offset + 1] |= (mask2 & temp[byte]) << leftShift;
				byte++;
			}
			integer totalNumberOfBitsToBeCopied = m_numBits - rShift;
			integer numberOfRemainingBits = totalNumberOfBitsToBeCopied - numBytesDirectlyCopied * 8;
			if (numberOfRemainingBits)
			{
				m_pBitMemory[byte + offset] |= (mask1 & temp[byte]) >> rightShift;
				integer adjustment = numBytes * 8 - m_numBits;
				unsigned char mask3 = maskLookUp[8 - adjustment];
				m_pBitMemory[byte + offset] &= mask3;
			}
			free(temp);
			return *this;
		}

		/** Inlined operators overloaded as non-members of the class */
		inline bit_array operator ~(const bit_array &other)
		{
			bit_array::integer numBytes = (other.m_numBits + (8 - 1)) / 8;
			bit_array::integer byte = 0;

			bit_array temp(other.m_numBits);
			while (byte < numBytes)
			{
				temp.m_pBitMemory[byte] = ~other.m_pBitMemory[byte];
				byte++;
			}
			return temp;

		}

		inline bit_array operator &(const bit_array &lhs, const bit_array &rhs)
		{
			bit_array temp(lhs.m_numBits);
			temp = lhs;
			temp &= rhs;

			return temp;
		}

		inline bit_array operator |(const bit_array &lhs, const bit_array &rhs)
		{
			bit_array temp(lhs.m_numBits);
			temp = lhs;
			temp |= rhs;

			return temp;
		}

		inline bit_array operator ^(const bit_array &lhs, const bit_array &rhs)
		{
			bit_array temp(lhs.m_numBits);
			temp = lhs;
			temp ^= rhs;

			return temp;
		}

		inline bit_array operator <<(const bit_array &other, const unsigned int lshift)
		{
			bit_array temp(other.m_numBits);
			temp = other;
			temp <<= lshift;

			return temp;
		}

		inline bit_array operator >>(const bit_array &other, const unsigned int rshift)
		{
			bit_array temp(other.m_numBits);
			temp = other;
			temp >>= rshift;

			return temp;
		}

		inline bool operator==(const bit_array &lhs, const bit_array &rhs)
		{
			assert(lhs.m_numBits == rhs.m_numBits);
			bit_array::integer numBytes = (lhs.m_numBits + (8 - 1)) / 8;
			bit_array::integer byte = 0;

			while (byte < numBytes)
			{
				if (lhs.m_pBitMemory[byte] != rhs.m_pBitMemory[byte])
					break;
				byte++;
			}

			if (byte < numBytes)
				return false;
			return true;
		}

		inline bool operator!=(const bit_array &lhs, const bit_array &rhs)
		{
			return !operator==(lhs, rhs);
		}
	}
}

#endif // !bit_array_inl_h