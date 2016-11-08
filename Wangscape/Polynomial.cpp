#include "Polynomial.h"

Polynomial Polynomial::derivative(size_t order) const
{
	if (degree() <= order)
		return Polynomial();
	auto cbegin = data().cbegin() + order;
	Polynomial d(data().cbegin()+order, data().cend());
	for (size_t i = 0; i < d.degree()+1; i++)
		for(size_t j = 1; j <= order; j++)
			d[i] *= i + j;
	return d;
}
