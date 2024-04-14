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

vector<complex<double>> DFT(vector<double> f)
{
    vector<complex<double>> X ;
    for(int k = 0 ; k < f.size();k++)
    {
        complex <double> temp  = complex(0.0,0.0);
        for(int n = 0 ; n < f.size();n++)
        {
            double angle = -1 * (2 * acos(0.0) * k * n)/ f.size() ; 
            complex<double> Coef = complex(cos(angle),sin(angle));
            temp += f[n] * Coef ;
        }
        X.push_back(temp);;
    }
    return X ; 
}

int main()
{
    int N = 8192;
    vector<double> Signal ;
    random_device rd{};
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