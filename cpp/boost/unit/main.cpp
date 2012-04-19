#include <complex>
#include <iostream>

#include <boost/typeof/std/complex.hpp>

#include <boost/units/systems/si/energy.hpp>
#include <boost/units/systems/si/force.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/si/electric_potential.hpp>
#include <boost/units/systems/si/current.hpp>
#include <boost/units/systems/si/resistance.hpp>
#include <boost/units/systems/si/io.hpp>

using namespace boost::units;
using namespace boost::units::si;

quantity<energy>
work(const quantity<force>& F,const quantity<length>& dx)
{
    return F*dx;
}

int main()
{
    /// test calcuation of work
    quantity<force>     F(2.0*newton);
    quantity<length>    dx(2.0*meter);
    quantity<energy>    E(work(F,dx));

    std::cout << "F  = " << F << std::endl
              << "dx = " << dx << std::endl
              << "E  = " << E << std::endl
              << std::endl;

    /// check complex quantities
    typedef std::complex<double>    complex_type;

    quantity<electric_potential,complex_type> v = complex_type(12.5,0.0)*volts;
    quantity<current,complex_type>            i = complex_type(3.0,4.0)*amperes;
    quantity<resistance,complex_type>         z = complex_type(1.5,-2.0)*ohms;

    std::cout << "V   = " << v << std::endl
              << "I   = " << i << std::endl
              << "Z   = " << z << std::endl
              << "I*Z = " << i*z << std::endl
              << "I*Z == V? " << std::boolalpha << (i*z == v) << std::endl
              << std::endl;

    return 0;
}
