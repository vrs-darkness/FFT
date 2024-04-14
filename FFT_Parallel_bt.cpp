#include<bits/stdc++.h>
#include<random>
#include<complex>
#include<cmath>
#include<omp.h>
#include<vector>

#define NUM_OF_THREADS 16

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



vector<complex<double>> Splitter(vector<complex<double>> f,int st)
{
    vector<complex<double>> X ; 
    for (int i = st;i<f.size();i+=2)
    {
        X.push_back(f[i]);
    }
    return X;
}

vector<complex<double>> Split(vector<complex<double>> t)
{
    if(t.size()==1)
    {
        return t;
    }
    else
    {
        vector<complex<double>> even = Splitter(t,0);
        vector<complex<double>> odd = Splitter(t,1);
        #pragma omp parallel num_threads(NUM_OF_THREADS)
        {
            even = Split(even);
            odd =  Split(odd);
        }
        even.insert(even.end(),odd.begin(),odd.end());
        return even;
    }
}

complex<double> FFT(vector<complex<double>> f,int k,int N,int coef)
{
    if(f.size()==1)
    {
        return f[0];
    }
    else
    {
        vector<complex<double>> X ;
        for(int i=0;i<f.size();i+=2)
        {
            X.push_back(f[i] + Cal(coef*k,N) * f[i+1]);
        }
        complex<double> out ; 
        out =  FFT(X,k,N,(int)coef/2);
        return out ;
    }
}

int main()
{
    int N = 8;
    vector<complex<double>> Signal ;
    random_device rd{};
    for (int i =0;i<N;i++)
    {
        default_random_engine generator{rd()};
        Signal.push_back(complex<double>(Random(generator),0.0));
    }
    int pad = pow(2,ceil(log(N)/log(2))) - N ; 
    #pragma omp parallel for num_threads(NUM_OF_THREADS)
        for(int i = 0 ; i <pad;i++)
        {
            Signal.push_back(complex<double>(0.0,0.0));
        }
    vector<complex<double>> signal = Split(Signal);
    vector<complex<double>> X(Signal.size(),complex<double>(0.0,0.0));
    #pragma omp parallel for num_threads(NUM_OF_THREADS)
        for (int k =0;k<N;k++)
        {
            X[k] = FFT(Signal,k,Signal.size()-pad,Signal.size());
        }
    for(int i = 0 ; i<N;i++)
    {
        cout << X[i] << " " ;
    }
    return 0;
}