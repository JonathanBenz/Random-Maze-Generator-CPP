#pragma once
#include <random>
#include <vector>
#include <map>

class Utils
{
public:
	/* ========================================================= */
	/* RANDOM NUMBER GENERATION UTILITIES */
	static std::mt19937& GetRNG()
	{
		static std::mt19937 rng(std::random_device{}());
		return rng;
	}

	// Return a random number in the domain of (0, Range]. 
	template <typename T>
	static T BoundedRand(T Range)
	{
		std::uniform_int_distribution<T> dist(0, Range - 1);
		return dist(GetRNG());
	}

	// 50/50 chance to return true.
	static bool FlipCoin()
	{
		return BoundedRand(2) == 0;
	}

	// Randomly pick an element
	template <typename T>
	static T* Sample(const std::vector<T*>& vec)
	{
		if (vec.empty()) return nullptr;
		return vec.at((Utils::BoundedRand(vec.size())));
	}

	// Randomly pick an element
	template <typename T>
	static T Sample(const std::vector<T>& vec)
	{
		if (vec.empty()) return nullptr;
		return vec.at((Utils::BoundedRand(vec.size())));
	}
	/* END OF RANDOM NUMBER GENERATION UTILITIES */
	/* ========================================================= */

	/* ========================================================= */
	/* KEY-VALUE FLIPPING UTILITIES */
	template<typename A, typename B>
	static std::pair<B, A> flip_pair(const std::pair<A, B>& p)
	{
		return std::pair<B, A>(p.second, p.first);
	}

	template<typename A, typename B>
	static std::multimap<B, A> flip_map(const std::map<A, B>& src)
	{
		std::multimap<B, A> dst;
		std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()),
			flip_pair<A, B>);
		return dst;
	}
	/* END OF KEY-VALUE FLIPPING UTILITIES */
	/* ========================================================= */
};