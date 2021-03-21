#pragma once

#include <cinttypes>
#include <string>

class Hasher {
public:
	Hasher() = default;
	explicit Hasher(uint64_t _seed);

	uint64_t Hash(const std::wstring& _message);

private:
	uint64_t HashBlock(uint64_t _block, uint64_t _key);

	uint64_t seed_{ 0xF942A8B71FF5E361ULL };
};