#pragma once
#include <random>
#include <vector>
#include <map>
#include <set>

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

	// Randomly pick an element from a set
	template <typename T>
	static T* Sample(const std::set<T*>& set)
	{
		if (set.empty()) return nullptr;
		auto it = std::begin(set);
		std::advance(it, Utils::BoundedRand(set.size()));
		return *it;
	}

	// Randomly pick an element
	template <typename T>
	static T Sample(const std::vector<T>& vec)
	{
		if (vec.empty()) return nullptr;
		return vec.at((Utils::BoundedRand(vec.size())));
	}

	// Randomly pick an element from a set
	template <typename T>
	static T Sample(const std::set<T>& set)
	{
		if (set.empty()) return nullptr;
		auto it = std::begin(set);
		std::advance(it, Utils::BoundedRand(set.size()));
		return *it;
	}
	/* END OF RANDOM NUMBER GENERATION UTILITIES */
	/* ========================================================= */

	/* ========================================================= */
	/* KEY-VALUE FLIPPING UTILITIES */
	template<typename A, typename B>
	static std::pair<B, A> FlipPair(const std::pair<A, B>& p)
	{
		return std::pair<B, A>(p.second, p.first);
	}

	template<typename A, typename B>
	static std::multimap<B, A> FlipMap(const std::map<A, B>& src)
	{
		std::multimap<B, A> dst;
		std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()),
			FlipPair<A, B>);
		return dst;
	}
	/* END OF KEY-VALUE FLIPPING UTILITIES */
	/* ========================================================= */

	// Return how far away an element is from the head of the vector. 
	// Returns -1 if the element does not exist. 
	template<typename T>
	static int GetIndex(const std::vector<T*>& vec, T* elem)
	{
		int idx = -1;
		auto it = std::find(vec.begin(), vec.end(), elem);

		if (it != vec.end()) 
			idx = static_cast<int>(std::distance(vec.begin(), it));

		return idx;
	}
};