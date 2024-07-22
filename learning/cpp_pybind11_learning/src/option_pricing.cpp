#include "option_pricing.h"



Option_pricing::Option_pricing()
{

}



double Option_pricing::norm_pdf(double value)
{
    double pdf = (1.0/(sqrt(2*PI)))*exp(-pow(value,2)/2);

    return pdf;
};



double Option_pricing::norm_cdf(double value)
{
    // constants
    double a1 =  0.254829592;
    double a2 = -0.284496736;
    double a3 =  1.421413741;
    double a4 = -1.453152027;
    double a5 =  1.061405429;
    double p  =  0.3275911;
 
    // Save the sign of value
    int sign = 1;
    if (value < 0)
        sign = -1;
    value = fabs(value)/sqrt(2.0);
 
    // A&S formula 7.1.26
    double t = 1.0/(1.0 + p*value);
    double y = 1.0 - (((((a5*t + a4)*t) + a3)*t + a2)*t + a1)*t*exp(-value*value);
 
    return 0.5*(1.0 + sign*y);
};



MatrixXd Option_pricing::standard_brownian(int steps, int paths, double T, double S0)
{
    double dt = T / steps;
    MatrixXd S_path = MatrixXd::Zero(steps+1, paths);
    S_path.row(0).fill(S0); // 起点设置
    MatrixXd rn = MatrixXd::Random(S_path.rows(), S_path.cols());

    for (int i = 1; i < steps+1; ++i)
    {
        S_path.row(i) = S_path.row(i-1) + rn.row(i-1)*sqrt(dt);
    };

    return S_path;
};



MatrixXd Option_pricing::general_brownian(int steps, int paths, double T, double S0, int a, int b)
{
    double dt = T / steps;
    MatrixXd S_path = MatrixXd::Zero(steps+1, paths);
    S_path.row(0).fill(S0);
    MatrixXd rn = MatrixXd::Random(S_path.rows(), S_path.cols());

    for (int i = 1; i < steps+1; ++i)
    {
        S_path.row(i) = S_path.row(i-1).array() + a*dt + b*pow(dt,0.5)*rn.row(i-1).array();
    };

    return S_path;
};



MatrixXd Option_pricing::geo_brownian(int steps, int paths, double T, double S0, double u, double sigma)
{
    double dt = T / steps;
    MatrixXd S_path = MatrixXd::Zero(steps+1, paths);
    S_path.row(0).fill(S0);
    MatrixXd rn = MatrixXd::Random(S_path.rows(), S_path.cols());

    for (int i = 1; i < steps+1; ++i)
    {
        S_path.row(i) = S_path.row(i-1).array() + ((u-0.5*pow(sigma,2))*dt + (sigma*pow(dt,0.5)*rn.row(i)).array()).exp();
    };

    return S_path;
};



double Option_pricing::BSM(string CP, double S, double X, double sigma, double T, double r, double b)
{
    // CP : 看涨或看跌"C"or"P".
    // S : 标的价格.
    // X : 行权价格.
    // sigma : 波动率.
    // T : 年化到期时间.
    // r : 收益率.
    // b : 持有成本，当b=r时，为标准的无股利模型，b=0时，为期货期权，b为r-q时，为支付股利模型，b为r-rf时为外汇期权.
    
    double d1 = (log(S/X) + (b+pow(sigma,2)/2)*T) / (sigma*pow(T,0.5));
    double d2 = d1 - sigma*pow(T,0.5);
    if (CP.compare("C") == 0)
    {
        double value = S*exp((b-r)*T)*norm_cdf(d1) - X*exp(-r*T)*norm_cdf(d2);

        return value;
    }
    else
    {
        double value = X*exp(-r*T)*norm_cdf(-d2) - S*exp((b-r)*T)*norm_cdf(-d1);

        return value;
    };
};



double Option_pricing::BSM_binary(double V0, string CP, double S, double X, double T, double r, double b, double vol_est)
{
    // V0 : 期权价值.
    // vol_est : 预计的初始波动率.

    double start = 0; // 初始波动率下限
    double end = 2; // 初始波动率上限
    double e = 1; // 先给定一个值，让循环运转起来
    while (fabs(e) >= 0.0001) // 迭代差异的精度，根据需要调整
    {
        double val;

        try
        {
            val = BSM(CP, S, X, vol_est, T, r, b);
        }
        catch (const char* msg)
        {
            cerr << msg << endl;
            cout << "期权的内在价值大于期权的价格，无法收敛出波动率，会触发错误！" << endl;
            break;
        };
        
        if ((val-V0) > 0) // 若计算的期权价值大于实际价值，说明使用的波动率偏大
        {
            end = vol_est;
            vol_est = (start + end) / 2;
            e = end - vol_est;
        }
        else // 若计算的期权价值小于实际价值，说明使用的波动率偏小
        {
            start = vol_est;
            vol_est = (start + end) / 2;
            e = start - vol_est;
        };
    };

    return round(vol_est*10000)/10000;
};



double Option_pricing::BSM_newton(double V0, string CP, double S, double X, double T, double r, double b, double vol_est, int n_iter)
{
    for (int i = 0; i < n_iter; ++i) // n_iter表示迭代的次数
    {
        double d1 = (log(S/X) + (b + pow(vol_est,2)/2)*T) / (vol_est*pow(T,0.5));
        double vega = S * exp((b-r)*T) * norm_pdf(d1) * pow(T,0.5); // 计算vega
        vol_est = vol_est - (BSM(CP, S, X, vol_est, T, r, b) - V0) / vega; // 每次迭代都重新算一下波动率
    };

    return vol_est;
};



Greeks Option_pricing::Euro_greeks1(string CP, double S, double X, double sigma, double T, double r, double b)
{
    double d1 = (log(S/X) + (b+pow(sigma,2)/2)*T) / (sigma*pow(T,0.5));
    double d2 = d1 - sigma*pow(T,0.5);
    double option_value, delta, gamma, vega, theta, rho;
    if (CP.compare("C") == 0)
    {
        option_value = S*exp((b-r)*T)*norm_cdf(d1) - X*exp(-r*T)*norm_cdf(d2);
        delta = exp((b-r)*T) * norm_cdf(d1);
        gamma = exp((b-r)*T)*norm_pdf(d1) / (S*sigma*pow(T,0.5));
        vega = S * exp((b-r)*T) * norm_pdf(d1) * pow(T,0.5);
        theta = -exp((b-r)*T)*S*norm_pdf(d1)*sigma / (2*pow(T,0.5)) - r*X*exp(-r*T)*norm_cdf(d2) - (b-r)*S*exp((b-r)*T)*norm_cdf(d1);
        if (b != 0)
        {
            rho = X * T * exp(-r*T) * norm_cdf(d2);
        }
        else
        {
            rho = -exp(-r*T) * (S*norm_cdf(d1)-X*norm_cdf(d2));
        };
    }
    else
    {
        option_value = X*exp(-r*T)*norm_cdf(-d2) - S*exp((b-r)*T)*norm_cdf(-d1);
        delta = -exp((b-r)*T) * norm_cdf(-d1);
        gamma = exp((b-r)*T)*norm_pdf(d1) / (S*sigma*pow(T,0.5));
        vega = S * exp((b-r)*T) * norm_pdf(d1) * pow(T,0.5);
        theta = -exp((b-r)*T)*S*norm_pdf(d1)*sigma / (2*pow(T,0.5)) + r*X*exp(-r*T)*norm_cdf(-d2) + (b-r)*S*exp((b-r)*T)*norm_cdf(-d1);
        if (b != 0)
        {
            rho = -X * T * exp(-r*T) * norm_cdf(-d2);
        }
        else
        {
            rho = -exp(-r*T) * (X*norm_cdf(-d2) - S*norm_cdf(-d1));
        };
    };
    
    Greeks result;
    result.option_value = option_value;
    result.delta = delta;
    result.gamma = gamma;
    result.vega = vega;
    result.theta = theta;
    result.rho = rho;

    return result;
};



Greeks Option_pricing::Euro_greeks2(string CP, double S, double X, double sigma, double T, double r, double b, double pct_change)
{
    // pct_change : 表示价格变化的幅度.

    double option_value = BSM(CP, S, X, sigma, T, r, b);
    double delta = (BSM(CP, S+S*pct_change, X, sigma, T, r, b) - BSM(CP, S-S*pct_change, X, sigma, T, r, b)) / (2*S*pct_change);
    double gamma = (BSM(CP, S+S*pct_change, X, sigma, T, r, b) + BSM(CP, S-S*pct_change, X, sigma, T, r, b) - 2*BSM(CP, S, X, sigma, T, r, b)) / (pow(S*pct_change, 2));
    double vega = (BSM(CP, S, X, sigma+sigma*pct_change, T, r, b) - BSM(CP, S, X, sigma-sigma*pct_change, T, r, b)) / (2*sigma*pct_change);
    double theta = (BSM(CP, S, X, sigma, T-T*pct_change, r, b) - BSM(CP, S, X, sigma, T+T*pct_change, r, b)) / (2*T*pct_change);
    double rho;
    if (b != 0)
    {
        rho = (BSM(CP, S, X, sigma, T, r+r*pct_change, b+r*pct_change) - BSM(CP, S, X, sigma, T, r-r*pct_change, b-r*pct_change)) / (2*r*pct_change);
    }
    else
    {
        rho = (BSM(CP, S, X, sigma, T, r+r*pct_change, b) - BSM(CP, S, X, sigma, T, r-r*pct_change, b)) / (2*r*pct_change);
    }

    Greeks result;
    result.option_value = option_value;
    result.delta = delta;
    result.gamma = gamma;
    result.vega = vega;
    result.theta = theta;
    result.rho = rho;

    return result;
};



double Option_pricing::Ame_CCR(string CP, int m, double S0, double T, double sigma, double K, double r, double b)
{
    // m : 模拟的期数.

    double dt = T / m;
    double u = exp(sigma * pow(dt,0.5));
    double d = 1 / u;
    MatrixXd S = MatrixXd::Zero(m+1, m+1);
    S(0, 0) = S0;
    double p = (exp(b*dt) - d) / (u-d);
    for (int i = 1; i < m+1; ++i)
    {
        for (int a = 0; a < i; ++a)
        {
            S(a, i) = S(a, i-1) * u;
            S(a+1, i) = S(a, i-1) * d;
        };
    };
    MatrixXd Sv = MatrixXd::Zero(m+1, m+1);
    MatrixXd S_intrinsic;
    if (CP.compare("C") == 0)
    {
        S_intrinsic = (S.array() - K).cwiseMax(0);
    }
    else
    {
        S_intrinsic = (K - S.array()).cwiseMax(0);
    };
    Sv.rightCols(1) = S_intrinsic.rightCols(1);
    for (int i = m-1; i > -1; --i)
    {
        for (int a = 0; a < i+1; ++a)
        {
            Sv(a, i) = max((Sv(a, i+1)*p + Sv(a+1, i+1)*(1-p)) / exp(r*dt), S_intrinsic(a, i));
        };
    };

    return Sv(0, 0);
};



double Option_pricing::find_Sx(string CP, double X, double sigma, double T, double r, double b)
{
    double iteration_max_error = 0.00001; // 牛顿迭代法的精度
    double M = 2*r / pow(sigma,2);
    double N = 2*b / pow(sigma,2);
    double K = 1 - exp(-r*T);
    double q1 = (-(N-1) - pow(pow(N-1,2) + 4*M/K, 0.5)) / 2;
    double q2 = (-(N-1) + pow(pow(N-1,2) + 4*M/K, 0.5)) / 2;
    double S_infinite;
    if (CP.compare("C") == 0)
    {
        S_infinite = X / (1 - 2*pow(-(N-1) + pow(pow(N-1,2) + 4*M, 0.5), -1));
        double h2 = -(b*T + 2*sigma*pow(T,0.5)) * X / (S_infinite-X);
        double Si = X + (S_infinite-X) * (1-exp(h2)); // 计算种子值
        double LHS = Si - X;
        double d1 = (log(Si/X) + (b + pow(sigma,2)/2)*T) / (sigma*pow(T,0.5));
        double RHS = BSM("C", Si, X, sigma, T, r, b) + (1 - exp((b-r)*T)*norm_cdf(d1)) * Si / q2;
        double bi = exp((b-r)*T) * norm_cdf(d1) * (1 - 1/q2) + (1 - (exp((b-r)*T)*norm_pdf(d1)) / sigma / pow(T,0.5)) / q2; // bi为迭代使用的初始斜率
        while (fabs((LHS-RHS) / X) > iteration_max_error)
        {
            Si = (X + RHS - bi*Si) / (1-bi);
            LHS = Si - X;
            d1 = (log(Si/X) + (b+pow(sigma,2)/2)*T) / (sigma*pow(T,0.5));
            RHS = BSM("C", Si, X, sigma, T, r, b) + (1 - exp((b-r)*T)*norm_cdf(d1)) * Si / q2;
            bi = exp((b-r)*T) * norm_cdf(d1) * (1 - 1/q2) + (1 - (exp((b-r)*T)*norm_pdf(d1)) / sigma / pow(T,0.5)) / q2;
        };

        return Si;
    }
    else
    {
        S_infinite = X / (1 - 2*pow(-(N-1) - pow(pow(N-1,2) + 4*M, 0.5), -1));
        double h1 = -(b*T - 2*sigma*pow(T,0.5)) * X / (X-S_infinite);
        double Si = S_infinite + (X-S_infinite) * exp(h1); // 计算种子值
        double LHS = X - Si;
        double d1 = (log(Si/X) + (b + pow(sigma,2)/2)*T) / (sigma*pow(T,0.5));
        double RHS = BSM("P", Si, X, sigma, T, r, b) - (1 - exp((b-r)*T)*norm_cdf(-d1)) * Si / q1;
        double bi = -exp((b-r)*T) * norm_cdf(-d1) * (1 - 1/q1) - (1 + (exp((b-r)*T)*norm_pdf(-d1)) / sigma / pow(T,0.5)) / q1;
        while (fabs((LHS-RHS) / X) > iteration_max_error)
        {
            Si = (X - RHS + bi*Si) / (1+bi);
            LHS = X - Si;
            d1 = (log(Si/X) + (b + pow(sigma,2)/2)*T) / (sigma*pow(T,0.5));
            RHS = BSM("P", Si, X, sigma, T, r, b) - (1 - exp((b-r)*T)*norm_cdf(-d1)) * Si / q1;
            bi = -exp((b-r)*T) * norm_cdf(-d1) * (1 - 1/q1) - (1 + (exp((b-r)*T)*norm_pdf(-d1)) / sigma / pow(T,0.5)) / q1;
        };

        return Si;
    };
};



double Option_pricing::BAW(string CP, double S, double X, double sigma, double T, double r, double b)
{
    double value, M, N, K, Si, d1, d2, q1, q2, A1, A2;
    if (b > r) // b>r时，美式期权价值和欧式期权相同
    {
        value = BSM(CP, S, X, sigma, T, r, b);
    }
    else
    {
        M = 2 * r / pow(sigma, 2);
        N = 2 * b / pow(sigma, 2);
        K = 1 - exp(-r*T);
        Si = find_Sx(CP, X, sigma, T, r, b);
        d1 = (log(Si/X) + (b + pow(sigma,2)/2)*T) / (sigma*pow(T,0.5));
        if (CP.compare("C") == 0)
        {
            q2 = (-(N-1) + pow(pow(N-1,2) + 4*M/K, 0.5)) / 2;
            A2 = Si / q2 * (1 - exp((b-r)*T)*norm_cdf(d1));
            if (S < Si)
            {
                value = BSM(CP, S, X, sigma, T, r, b) + pow(A2*(S/Si), q2);
            }
            else
            {
                value = S - X;
            };
        }
        else
        {
            q1 = (-(N-1) - pow(pow(N-1,2) + 4*M/K, 0.5)) / 2;
            A1 = -Si / q1 * (1 - exp((b-r)*T)*norm_cdf(-d1));
            if (S > Si)
            {
                value = BSM(CP, S, X, sigma, T, r, b) + A1*pow(S/Si, q1);
            }
            else
            {
                value = X - S;
            };
        };
    };

    return value;
};



double Option_pricing::BAW_binary(double V0, string CP, double S, double X, double T, double r, double b, double sigma)
{
    // V0 : 期权价值.
    // sigma : 预计的初始波动率.

    double start = 0; // 初始波动率下限
    double end = 2; // 初始波动率上限
    double e = 1; // 先给定一个值，让循环运转起来
    while (fabs(e) >= 0.0001) // 迭代差异的精度，根据需要调整
    {
        double val;

        try
        {
            val = BAW(CP, S, X, sigma, T, r, b);
        }
        catch (const char* msg)
        {
            cerr << msg << endl;
            cout << "期权的内在价值大于期权的价格，无法收敛出波动率，会触发错误！" << endl;
            break;
        };
        
        if ((val-V0) > 0) // 若计算的期权价值大于实际价值，说明使用的波动率偏大
        {
            end = sigma;
            sigma = (start + end) / 2;
            e = end - sigma;
        }
        else // 若计算的期权价值小于实际价值，说明使用的波动率偏小
        {
            start = sigma;
            sigma = (start + end) / 2;
            e = start - sigma;
        };
    };

    return round(sigma*10000)/10000;
};


