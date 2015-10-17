#ifndef __UNION_FIND_H__
#define __UNION_FIND_H__

#include <vector>

namespace amon {
class DisjointSet {
public:
	DisjointSet(int n);
	/**
	 * @brief      { Returns the group label for the element x. }
	 *
	 * @param[in]  x     { Index of the elemnt. }
	 */
	int find(int x);

	/**
	 * @brief      { Joins the groups of A and B }
	 *
	 * @param[in]  a     { The first element. }
	 * @param[in]  b     { The second element. }
	 */
	void join(int a, int b);

private:
	std::vector<int> v;
};

}
#endif

