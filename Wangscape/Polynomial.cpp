#include "Polynomial.h"

Polynomial Polynomial::makeDerivative(size_t order) const
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

Polynomial::Solutions Polynomial::makeSolutions() const
{
    Polynomial p(*this);
    p.normalize();
    const auto& d = p.data();
    if (p.degree() == 0)
        return Solutions();
    if (p.degree() == 1)
        return Solutions({-d[0]/d[1]});
    else if (p.degree() == 2)
    {
        Real det = d[1] * d[1] - 4. * d[2] * d[0];
        if (det < 0.)
            return Solutions();
        else if (det == 0.)
        {
            return Solutions({ -d[1] / (2.*d[2]) });
        }
        else
        {
            Real det_root = sqrt(det);
            Real divisor = 2.*d[2];
            return Solutions({ (-d[1] - det_root) / divisor,
                               (-d[1] + det_root) / divisor });
        }
    }
    else if (p.degree() == 3)
    {
        throw (std::domain_error("TODO: implement cubic solutions"));
    }
    else
    {
        throw(std::domain_error("Solutions to quartic and higher polynomials are not implemented"));
    }
}

PolynomialAugmented::PolynomialAugmented(const Polynomial & p):
    mPolynomial(p),
    mDerivative(p.makeDerivative())
{
}

const Polynomial & PolynomialAugmented::polynomial() const
{
    return mPolynomial;
}

const Polynomial & PolynomialAugmented::derivative() const
{
    return mDerivative;
}

const PolynomialAugmented::Extrema & PolynomialAugmented::extrema() const
{
    return mExtrema;
}

Interval PolynomialAugmented::makeRange(const Interval & domain) const
{
    return makeRange(domain, mExtrema);
}

Interval PolynomialAugmented::makeRange(const Interval & domain, const Extrema & restricted_extrema) const
{
    Real min = mPolynomial.evaluate(domain.a);
    Real max = min;
    min = std::min(min, mPolynomial.evaluate(domain.b));
    max = std::max(min, mPolynomial.evaluate(domain.b));
    for (auto it : restricted_extrema)
    {
        if (domain.contains(it.first)) {
            min = std::min(min, it.second);
            max = std::max(min, it.second);
        }
    }
    return Interval(min, max);
}

PolynomialAugmented::Extrema PolynomialAugmented::makeExtrema() const
{
    Extrema e;
    for (auto sol : mDerivative.makeSolutions())
    {
        e.push_back({ sol, mPolynomial.evaluate(sol) });
    }
    return e;
}
