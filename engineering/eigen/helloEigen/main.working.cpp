#include <QtGlobal>
#include <iostream>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <vector>
#define _USE_MATH_DEFINES
#include <cmath>

using namespace Eigen;
using namespace std;

void test1()
{
	MatrixXd m(2,3), a(2,3), b(2,3);
	m.setZero();
	m(0,0) = 3;
	m(1,0) = 2.5;
	m(0,1) = -1;
	m(1,1) = m(1,0) + m(0,1);

	std::cout << m << std::endl;

	a = m * 3;

	std::cout << a << std::endl;

	b = (a - m);

	std::cout << b << std::endl;
}

int polyDeg(std::vector<double>& xVec,
			std::vector<double>& yVec,
			std::vector<double>& ysVec)
{
	Map<MatrixXd> x(&xVec[0], xVec.size(), 1);
	Map<MatrixXd> y(&yVec[0], yVec.size(), 1);
	int N = (int)xVec.size();

	double meanY = y.mean();
	MatrixXd ys = MatrixXd::Constant(N,1,meanY);
	// cout << "ys = " << ys << endl;
	// cout << "y = " << y << endl;

	double sum_ys_y_2 = (ys - y).array().square().matrix().sum();
	double tobelog = 2*M_PI*sum_ys_y_2/N;
	double logtobelog = log(tobelog);
	double AIC = 2. + N*(logtobelog +1.) + 4./(N-2.);
	// cout << "AIC= " << AIC << endl;

	MatrixXd p = MatrixXd::Constant(2,2, 0);
	p(0,1) = x.mean();
	// cout << "AIC = " << AIC << endl;
	// cout << "p = " << p << endl;

	MatrixXd PL = MatrixXd::Constant(N,2, 1);
	// cout << "PL = " << PL << endl;

	PL.col(1) = x.array() - p(0,1);
	// cout << "PL = " << PL << endl;

	int n = 1;
	int nit = 0;

	MatrixXd ys1 = ys;
	MatrixXd ys2 = ys;
	MatrixXd ys3 = ys;
	MatrixXd ys4 = ys;

	while (nit<3) {
		int ni = n - 1;
		if (ni>0) {
			ArrayXd x_PL = x.array() * (PL.col(ni).array().square());
			double ppa = x_PL.sum();
			double ppb = PL.col(ni).array().square().sum();
			ArrayXd x_PL2 = x.array() * PL.col(ni-1).array() * PL.col(ni).array();
			p.conservativeResize(p.rows(), p.cols()+1);
			p(0,ni+1) = ppa / ppb;
			p(1,ni+1) = x_PL2.sum() / PL.col(ni-1).array().square().sum();

			PL.conservativeResize(PL.rows(), PL.cols()+1);
			PL.col(ni+1) = (x.array() - p(0,ni+1)) * PL.col(ni).array()
						   - p(1,ni+1)* PL.col(ni-1).array();
			//cout << "PL = " << PL << endl;
		}

		MatrixXd bsxfun_time_y_pl = y.asDiagonal() * PL;
		MatrixXd pl_square = PL.array().square();

		ArrayXd tmp = bsxfun_time_y_pl.colwise().sum().array() / pl_square.colwise().sum().array();
		ys = (PL * tmp.matrix().asDiagonal()).rowwise().sum();

		MatrixXd ys_minus_y = ys - y;
		ArrayXd ys_minus_y_square = ys_minus_y.array().square();
		sum_ys_y_2 = ys_minus_y_square.matrix().sum();

		double log_v = log(2.*M_PI*sum_ys_y_2/N);
		double aic = 2.*(n+1) + N*(log_v + 1.) +
					 2.*(n+1)*(n+2.)/(N-n-2.); // correction for small sample sizes

		// cout << "aic = " << aic << endl;
		if (aic>=AIC) {
			++nit;
		} else {
			nit = 0;
			AIC = aic;
		}
		++n;

		ys1 = ys2;
		ys2 = ys3;
		ys3 = ys4;
		ys4 = ys;

		if (n>=N) {
			ys1 = ys;
			break;
		}
	}

	ysVec.resize(ys1.rows());
	Map<MatrixXd> dest(&ysVec[0],ys1.rows(),1);
	dest = ys1;

	return n - nit - 1;
}


void test2()
{
	qsrand(1);
	std::vector<double> xVec, yVec, dyo, dyr;
	double STEPS = 5000;
	for (double x=0; x<=10.; x+=10./(STEPS-1)) {
		double pi3 = pow(x, 3.);
		double ans = pow(sin(pi3/100.), 2);
		double y = ans + 0.1 * (qrand()/double (RAND_MAX) - 0.5) * 2;
		xVec.push_back(x);
		yVec.push_back(y);
		dyo.push_back(y);
		dyr.push_back(ans);
		if (xVec.size() >= STEPS) {
			break;
		}
	}
	// xVec.resize(10);
	// int i = 0;
	// xVec[i++] = 1;
	// xVec[i++] = 3;
	// xVec[i++] = 5;
	// xVec[i++] = 7;
	// xVec[i++] = 9;
	// xVec[i++] = 8;
	// xVec[i++] = 7;
	// xVec[i++] = 6;
	// xVec[i++] = 5;
	// xVec[i++] = 4;
	// for (double xVal=1; xVal<=10; xVal+=1.) {
	// 	xVec.push_back(xVal);
	// 	yVec.push_back(xVal);
	// }
	// yVec = xVec;

	std::vector<double> ysVec;
	int n = polyDeg(xVec, yVec, ysVec);
	cout << "n = " << n << endl;
}


int main()
{
	test1();
	test2();
	return 0;
}


