#include"bit_array.h"

namespace Engine
{
	namespace Containers
	{
		void bit_array_UnitTest(void)
		{
			bit_array *bitArray = new bit_array(2000, false);

			/** Testing IsFull, IsEmpty, Clear and Set functions*/
			if (bitArray->IsFull())
				printf("The bit array is full\n");

			bitArray->Clear();
			if (bitArray->IsEmpty())
				printf("The bit array is empty\n");

			bitArray->Set();
			if (bitArray->IsFull())
				printf("The bit array is full\n");

			/** Testing ClearBit, IsBitClear, GetFirstClearBit, SetBit, IsBitSet, GetFirstSetBit functions */
			bitArray->ClearBit(1543);

			bit_array::integer i_dummyBit;

			if (bitArray->IsBitClear(1543))
				printf("The bit is clear\n");

			if (bitArray->GetFirstClearBit(i_dummyBit))
				printf("The first clear bit is : %d\n", i_dummyBit);

			bitArray->Clear();

			bitArray->SetBit(1280);

			if (bitArray->IsBitSet(1280))
				printf("The bit is set\n");

			if (bitArray->GetFirstSetBit(i_dummyBit))
				printf("The first set bit is : %d\n", i_dummyBit);

			/** Testing the overloaded [] operator */

			if ((*bitArray)[1280])
				printf("True\n");
			else
				printf("False\n");

			if ((*bitArray)[1798])
				printf("True\n");
			else
				printf("False\n");

			/** Testing the overloaded ~ & | ^ operators */
			bit_array A(100, false);

			bit_array B(100, false);

			bit_array C = A & B;

			bit_array D = ~A | ~B;

			bit_array E = A ^ B;

			/** Testing the overloaded == != operators */
			if (A == B)
				printf("A equal to B\n");

			if (A != D)
				printf("A not equal to D\n");

			/** Testing the overloaded &= |= ^= operators */
			bit_array F(100, false);

			bit_array G(100, true);

			F &= G;

			F |= ~G;

			F ^= ~G;

			/** Testing the overloaded <<= << >>= >> operators */
			bit_array H(77, false);

			H <<= 11;

			bit_array I(77, false);

			bit_array J = I << 11;

			bit_array K(77, false);

			K >>= 11;

			bit_array L(77, false);

			bit_array M = L >> 11;

			delete(bitArray);
		}
	}
}
