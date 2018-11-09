#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

class levenshtein_edit_distance
{
private:
	typedef std::vector<unsigned> array;
	typedef std::vector<array> array2D;

	enum edit {
		nothing_do = 0,
		remove     = 1,
		insert     = 1,
		replace    = 1
	};
public:
	typedef std::string termin;
public:
	levenshtein_edit_distance(const termin& from, const termin& to)
		: m_from(from)
		, m_to(to)
		, m_matrix(to.size() + 1, array(from.size() + 1, 0))
	{
		init();
	}

	void print_matrix() const
	{
		std::cout << "========== Matrix ==========\n";
		termin::size_type n = m_to.size();
		termin::size_type m = m_from.size();
		std::cout << "    ";
		for (unsigned i = 0; i < m; ++i) {
			std::cout << m_from[i] << " ";
		}
		std::cout << "\n";
		for (unsigned i = 0; i <= n; ++i) {
			if (i == 0) {
				std::cout << "  ";
			}
			else if (i <= n) {
				std::cout << m_to[i - 1] << " ";
			}
			for (unsigned j = 0; j <= m; ++j) {
				std::cout << m_matrix[i][j] << " ";
			}
			std::cout << "\n";
		}
		std::cout << "============================\n\n";
	}

	void print_edits() const
	{
		unsigned i = m_to.size();
		unsigned j = m_from.size();
		while (0 != i && 0 != j) {
			unsigned edit = m_matrix[i][j];
			bool equal = m_from[j - 1] == m_to[i - 1];
			std::cout << m_from[j - 1];
			if (edit - (equal ? nothing_do : replace) == m_matrix[i - 1][j - 1]) {
				if (!equal) {
					std::cout << " - Replace with " << m_to[i - 1];
				}
				--i;
				--j;
			}
			else if (edit - remove == m_matrix[i][j - 1]) {
				std::cout << " - Remove";
				--j;
			}
			else if (edit - insert == m_matrix[i - 1][j]) {
				std::cout << " - Insert " << m_to[i - 1];
				--i;
			}
			std::cout << std::endl;
		}
		std::cout << "\n";
	}

	int get_edit_distance() const
	{
		return m_matrix[m_to.size()][m_from.size()];
	}
private:
	void init()
	{
		termin::size_type n = m_to.size();
		for (unsigned i = 0; i <= n; ++i) {
			m_matrix[i][0] = i;
		}
		termin::size_type m = m_from.size();
		for (unsigned j = 0; j <= m; ++j) {
			m_matrix[0][j] = j;
		}
		for (unsigned i = 1; i <= n; ++i) {
			for (unsigned j = 1; j <= m; ++j) {
				unsigned edit = m_matrix[i - 1][j - 1];  // nothing_do
				if (m_to[i - 1] != m_from[j - 1]) {
					edit = min(m_matrix[i][j - 1]     + remove,
						   m_matrix[i - 1][j]     + insert,
						   m_matrix[i - 1][j - 1] + replace);
				}
				m_matrix[i][j] = edit;
			}
		}
	}

	unsigned min(unsigned x, unsigned y, unsigned z) const
	{
		return std::min(std::min(x, y), z);
	}
private:
	termin m_from;
	termin m_to;
	array2D m_matrix;
};

int main()
{
	levenshtein_edit_distance::termin from;
	levenshtein_edit_distance::termin to;

	std::cin >> from >> to;
	levenshtein_edit_distance l(from, to);
	l.print_matrix();
	l.print_edits();
	std::cout << "Edit distance: " << l.get_edit_distance() << "\n";
	return 0;
}
