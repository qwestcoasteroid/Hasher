#include "hasher.h"

#include <vector>

#define GET_BIT(x, bit) (((uint64_t)x & ((uint64_t)1 << (bit))) >> (bit))
#define SET_BIT(x, bit) (x |= ((uint64_t)1 << (bit)))
#define CLEAR_BIT (x, bit) (x &= x ^ ((uint64_t)1 << (bit)))

Hasher::Hasher(uint64_t _seed) : seed_(_seed) {}

std::vector<uint8_t> rand_permutation{
	36, 57, 25, 42, 18, 19, 47, 17,
	34, 46, 50, 16, 1, 21, 51, 55,
	7, 11, 3, 60, 38, 43, 61, 37,
	31, 40, 41, 8, 45, 26, 9, 20,
	4, 33, 10, 27, 64, 12, 59, 54,
	28, 24, 62, 30, 23, 44, 56, 48,
	35, 2, 13, 29, 63, 49, 58, 6,
	5, 39, 15, 14, 22, 32, 52, 53
};

std::vector<uint8_t> ext_permutation{
	1, 64, 63, 62, 61, 62, 61, 60,
	59, 58, 57, 58, 57, 56, 55, 54,
	53, 54, 53, 52, 51, 50, 49, 50,
	49, 48, 47, 46, 45, 46, 45, 44,
	43, 42, 41, 42, 41, 40, 39, 38,
	37, 38, 37, 36, 35, 34, 33, 34,
	33, 32, 31, 30, 29, 30, 29, 28,
	27, 26, 25, 26, 25, 24, 23, 64
};

std::vector<uint8_t> con_permutation{
	1, 32, 31, 30, 29, 30, 29, 28,
	27, 26, 25, 26, 25, 24, 23, 22,
	21, 22, 21, 20, 19, 18, 17, 18,
	17, 16, 15, 14, 13, 14, 13, 32
};

uint64_t Permutate(uint64_t _block, const std::vector<uint8_t>& _permutation) {
	uint64_t result{ 0 };
	for (size_t i = 0; i < _permutation.size(); ++i) {
		uint8_t temp_bit = GET_BIT(_block, i);
		if (temp_bit) {
			SET_BIT(result, _permutation[i] - 1);
		}
	}

	return result;
}

uint64_t Hasher::HashBlock(uint64_t _block, uint64_t _key) {
	return Permutate(_block, rand_permutation) ^
		Permutate(_key, ext_permutation) ^
		(Permutate(_block, con_permutation) << 31) ^ seed_;
}

uint64_t Hasher::Hash(const std::wstring& _messagae) {
	uint64_t result{ 0 };

	for (auto block : _messagae) {
		result = HashBlock(result ^ block, block) ^ block ^ result;
	}

	return result;
}