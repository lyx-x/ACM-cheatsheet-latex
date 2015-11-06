const double zero = 1e-7;
double X1;
complex<double> X2, X3;
void shengjin(double a, double b, double c, double d){
	//A = b^2-3ac; B = bc-9ad; C = c^2-3bd;
	//delta = B^2-4AC;
	double A = b * b - 3 * a * c;
	double B = b * c - 9 * a * d;
	double C = c * c - 3 * b * d;
	if (abs(A) <= zero && abs(B) <= zero){
		//X1=X2=X3=-b/3a=-c/b=-3d/c;
		X1 = -b / (3 * a);
		X2 = X1;
		X3 = X1;
	}else{
		double delta = B * B - 4 * A * C;
		if (abs(delta) <= zero){
			//X1 = -b/a+K,X2=X3=-K/2,K=B/A
			X1 = (-b) / a + (B / A);
			X2.real(-(B / A) / 2);
			X2.imag(0.0);
			X3 = X2;
		}else{
			//X1=(-b-(Y1^(1/3)+Y2^(1/3)))/3a,
			//X2=(-b+sin30(Y1^1/3+Y2^1/3)+cos30(Y1^1/3-Y2^1/3)i)/3*a;
			//X3=(-b+sin30(Y1^1/3+Y2^1/3)-cos30(Y1^1/3-Y2^1/3)i)/3*a;
			//Y1 = Ab+3a(-B+(B^2-4AC)^(1/2))/2;
			//Y2 = Ab+3a(-B-(B^2-4AC)^(1/2))/2;
			double Y1 = A * b + 3 * a *(-B + sqrt(B * B - 4 * A * C)) / 2;
			double Y2 = A * b + 3 * a *(-B - sqrt(B * B - 4 * A * C)) / 2;
			X1 = (-b - (cbrt(Y1) + cbrt(Y2)))/(3 * a);
			X2.real((-b + 1/2 * (cbrt(Y1) + cbrt(Y2))) / (3 * a));
			X2.imag(sqrt(3) / 2 *(cbrt(Y1) - cbrt(Y2)) / (3 * a));
			X3.real((-b + 1/2 * (cbrt(Y1) + cbrt(Y2))) / (3 * a));
			X3.imag(-(-b + 1/2 * (cbrt(Y1) + cbrt(Y2))) / (3 * a));
		}
	}

}
