#include<bits/stdc++.h>
#include<random>
#include<complex>
#include<cmath>

using namespace std ;

double Random(default_random_engine generator)
{
    // default_random_engine generator ; 
    normal_distribution<double> distribution(0,1);
    double N =  distribution(generator) ;
    // distribution.reset();
    return N;
}


complex<double> Cal(int theta,int N)
{
    double angle =  -1  * acos(0.0) * (theta/N);
    return complex<double>(cos(angle),sin(angle));
}



vector<double> Splitter(vector<double> f,int st)
{
    vector<double> X ; 
    for (int i = st;i<f.size();i+=2)
    {
        X.push_back(f[i]);
    }
    return X;
}

complex<double> FFT(vector<double> f,int k,int N,int coef)
{
    if(f.size()==1)
    {
        return f[0];
    }
    else
    {
        vector<double> even = Splitter(f,0);
        vector<double> odd = Splitter(f,1); 
        
        complex<double> even_part = FFT(even,k,N,coef*2);
        complex<double> odd_part = FFT(odd,k,N,coef*2);

        return even_part + Cal(2 * coef * k, N) * odd_part ; 
    }
}

int main()
{
    int N = 5000;
    vector<double> Signal ;
    random_device rd{};
    for (int i =0;i<N;i++)
    {
        default_random_engine generator{rd()};
        Signal.push_back(Random(generator));
    }
    vector<complex<double>> X(Signal.size(),complex<double>(0.0,0.0));
    for (int k =0;k<N;k++)
    {
        X[k] = FFT(Signal,k,Signal.size(),1);
        // cout << X[i] <<" ";
    }
    for(int i = 0 ; i<N;i++)
    {
        cout << X[i] << " " ;
    }
    return 0;
}