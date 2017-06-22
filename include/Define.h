#ifndef Define_h_
#define Define_h_

/***************************/

#ifndef PI
#define PI 3.14159265359
#endif

#ifndef Randf_
#define Randf_
//0~1の一様乱数の作成する関数
inline double randf(void){
    //rand();rand();rand();rand();rand();rand();
    return rand()*(1.0/RAND_MAX);
}
#endif

#ifndef Poisson_
#define Poisson_
/* random function (poison distribution) */
int poisson(double lambda){
	if( lambda<30 ){
		double x;
		int k = 0;
		x = randf();
		while( x>=exp(-lambda) ) {
			x = x*randf();
			k = k+1;
		}
		return k;
	}
	else{
		double sigma = sqrt(lambda);
		double z = sqrt(-2.0*log(randf()))*sin(2.0*PI*randf());
		int k = lambda+sigma*z;
		return k;
	}
}
#endif


/***************************/

#endif //"Define_h_"
