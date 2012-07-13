#include <QtGlobal>
#include <QVector>
#include <iostream>
#include <Eigen/QtAlignedMalloc>
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

int polyDegOld(std::vector<double>& xVec,
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

		MatrixXd y_x_pl = y.asDiagonal() * PL;
		MatrixXd pl_square = PL.array().square();

		ArrayXd tmp = (y_x_pl.colwise().sum().array()) / (pl_square.colwise().sum().array());
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

int polyDeg(std::vector<double>& xVec,
			std::vector<double>& yVec,
			std::vector<double>& ysVec)
{
	Map<MatrixXd> x(&xVec[0], xVec.size(), 1);
	Map<MatrixXd> y(&yVec[0], yVec.size(), 1);
	int N = (int)xVec.size();

	// % 0th order
	// meanY = mean(y);
	// ys = ones(N,1)*p;
	double meanY = y.mean();
	MatrixXd ys = MatrixXd::Constant(N,1,meanY);

	// AIC = 2+N*(log(2*pi* sum((ys-y).^2) /N)+1)+...
	//       4/(N-2);  % correction for small sample sizes
	double sum_ys_y_2 = (ys - y).array().square().matrix().sum();
	double AIC = 2. + N*(log(2*M_PI*sum_ys_y_2/N) +1.) + 4./(N-2.);

	// p = zeros(2,2);
	// p(1,2) = mean(x);
	MatrixXd p = MatrixXd::Constant(2,2, 0);
	p(0,1) = x.mean();

	// PL = ones(N,2);
	// PL(:,2) = x-p(1,2);
	MatrixXd PL = MatrixXd::Constant(N,2, 1);
	PL.col(1) = x.array() - p(0,1);

	// n = 1;
	// nit = 0;
	// if nargout==2, [ys1,ys2,ys3,ys4] = deal(ys); end
	int n = 1;
	int nit = 0;
	MatrixXd ys1 = ys;
	MatrixXd ys2 = ys;
	MatrixXd ys3 = ys;
	MatrixXd ys4 = ys;

	while (nit<3) {
		int ni = n - 1; // matlab index <-> cpp index
		if (ni>0) {
			ArrayXd x_PL = x.array() * (PL.col(ni).array().square());
			double ppa = x_PL.sum();
			double ppb = PL.col(ni).array().square().sum();
			ArrayXd x_PL2 = x.array() * PL.col(ni-1).array() * PL.col(ni).array();
			p.conservativeResize(p.rows(), p.cols()+1);

			// p(1,n+1) = sum(x.*PL(:,n).^2)/sum(PL(:,n).^2);
			p(0,ni+1) = ppa / ppb;
			// p(2,n+1) = sum(x.*PL(:,n-1).*PL(:,n))/sum(PL(:,n-1).^2);
			p(1,ni+1) = x_PL2.sum() / PL.col(ni-1).array().square().sum();

			PL.conservativeResize(PL.rows(), PL.cols()+1);
			// PL(:,n+1) = (x-p(1,n+1)).*PL(:,n)-p(2,n+1)*PL(:,n-1);
			PL.col(ni+1) = (x.array() - p(0,ni+1)) * (PL.col(ni).array())
						   - p(1,ni+1)* (PL.col(ni-1).array());
		}

		MatrixXd y_x_pl = y.asDiagonal() * PL;
		MatrixXd pl_square = PL.array().square();

		// tmp = sum(bsxfun(@times,y,PL))./sum(PL.^2);
		ArrayXd tmp = y_x_pl.colwise().sum().array() / pl_square.colwise().sum().array();
		// ys = sum(bsxfun(@times,PL,tmp),2);
		ys = (PL * tmp.matrix().asDiagonal()).rowwise().sum();

		double log_v = log(2.*M_PI*((ys - y).array().square().matrix().sum())/N);

		// % -- Akaike's Information Criterion
		// aic = 2*(n+1)+N*( log(2*pi*sum( (ys-y(:)).^2 )/N) +1)+...
		//     2*(n+1)*(n+2)/(N-n-2); % correction for small sample sizes
		double aic = 2.*(n+1.) + N*(log_v + 1.) +
					 2.*(n+1.)*(n+2.)/(N-n-2.); // correction for small sample sizes

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

	std::vector<double> ysVec, ys2Vec;
	int n = polyDeg(xVec, yVec, ysVec);
	int m = polyDegOld(xVec, yVec, ys2Vec);
	int* oops = 0;
	for (int i=0; i<ysVec.size(); ++i) {
		if(ysVec[i]!=ys2Vec[i]) {
			*oops = 1;
		}
	}
	cout << "n = " << n << endl;
}


int main()
{
	QVector<double> xData(1000);
	for (int i =0 ; i < 1000; ++i) {
		xData[i] = i;
	}

	test1();
	test2();
	return 0;
}


