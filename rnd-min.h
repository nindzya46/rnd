#include <windows.h>
#include <stdint.h>

#define RND_POLYNOM 0xE746D49A662FACC1ULL
#define RND_A 9
#define RND_B 46
#define RND_C 1
#define RND_D 26

struct rnd {

	__inline static uint64_t next_t() {
		const uint64_t c = __rdtsc();

		uint64_t t0 = (c * c + RND_POLYNOM) * c;
		uint64_t t1 = t0;

		t0 ^= _rotl64(((t0 & (1ULL << (-1 + RND_A))) == 0 ? ((t0 >> 1) ^ RND_POLYNOM) : (t0 >> 1)) + t0, RND_B);
		t1 ^= _rotr64(((t1 & (1ULL << (-1 + RND_C))) != 0 ? ((t1 << 1) ^ RND_POLYNOM) : (t1 << 1)) + t0, RND_D);
		//t1 ^= _rotl64(((t1 & (1ULL << (-1 + RND_A))) == 0 ? ((t1 >> 1) ^ RND_POLYNOM) : (t1 >> 1)) + t0, RND_B);
		//t0 ^= _rotr64(((t0 & (1ULL << (-1 + RND_C))) != 0 ? ((t0 << 1) ^ RND_POLYNOM) : (t0 << 1)) + t1, RND_D);

		return t0 + t1;
	}

	static uint32_t lnext_t() {
		return (uint32_t)next_t();
	}

	static uint16_t snext_t() {
		return (uint16_t)next_t();
	}

	static uint8_t bnext_t() {
		return (uint8_t)next_t();
	}

	static float fnext_t() {
		return next_t() * 5.4210108624275221703311375920553e-20f;
	}

	static double dnext_t() {
		return next_t() * 5.4210108624275221703311375920553e-20;
	}

	// 1 or -1
	static int sign_t(int i = 0) {
		return (next_t() >> i) & 1 ? 1 : -1;
	}

//#undef RND_POLYNOM
};
