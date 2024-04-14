#include<bits/stdc++.h>
#include<random>
#include<complex>
#include<cmath>
#include<omp.h>


#define NUM_OF_THREADS 8


using namespace std ;

double Random(default_random_engine generator)
{
    // default_random_engine generator ; 
    normal_distribution<double> distribution(0,1);
    double N =  distribution(generator) ;
    // distribution.reset();
    return N;
}

vector<complex<double>> DFT(vector<double> f)
{
    vector<complex<double>> X(f.size(),complex<double>(0.0,0.0));
    #pragma omp parallel for
        for(int k = 0 ; k < f.size();k++)
        {
            complex <double> temp  = complex<double>(0.0,0.0);
            // #pragma omp parallel for
            for(int n = 0 ; n < f.size();n++)
            {
                double angle = -1 * (2 * acos(0.0) * k * n)/ f.size() ; 
                complex<double> Coef = complex<double>(cos(angle),sin(angle));
                temp += f[n] * Coef ;
            }
            X[k] = temp;
        }
    return X ; 
}

int main()
{
    int N = 10000;
    vector<double> Signal ;
    random_device rd{};
    omp_set_num_threads(NUM_OF_THREADS);
    for (int i =0;i<N;i++)
    {
        default_random_engine generator{rd()};
        Signal.push_back(Random(generator));
    }
    vector<complex<double>> X = DFT(Signal);
    for (int i =0;i<N;i++)
    {
        cout << X[i] <<" ";
    }
    return 0;
}