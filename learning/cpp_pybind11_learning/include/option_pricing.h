#ifndef __OPTION_PRICING_H__
#define __OPTION_PRICING_H__

#include <iostream>
#include <math.h>

#include <Eigen/Dense>

using namespace std;
using namespace Eigen;



struct Greeks
{
    double option_value;
    double delta;
    double gamma;
    double vega;
    double theta;
    double rho;
};



class Option_pricing
{
private:
    string editor = "zhaobo";
    double PI = acos(-1.0); // 利用反余弦函数acos特性计算π
    double norm_pdf(double value); // 计算标准正态分布的pdf值
    double norm_cdf(double value); // 计算标准正态分布的cdf值

public:
    Option_pricing();
    MatrixXd standard_brownian(int steps, int paths, double T, double S0); // 1.1、标准布朗运动
    MatrixXd general_brownian(int steps, int paths, double T, double S0, int a, int b); // 1.2、广义布朗运动
    MatrixXd geo_brownian(int steps, int paths, double T, double S0, double u, double sigma); // 1.3、几何布朗运动
    double BSM(string CP, double S, double X, double sigma, double T, double r, double b); // 2.1、BSM定价公式
    double BSM_binary(double V0, string CP, double S, double X, double T, double r, double b, double vol_est=0.2); // 2.2、二分法求解欧式期权隐含波动率
    double BSM_newton(double V0, string CP, double S, double X, double T, double r, double b, double vol_est=0.2, int n_iter=1000); // 2.3、牛顿法求解欧式期权隐含波动率
    Greeks Euro_greeks1(string CP, double S, double X, double sigma, double T, double r, double b); // 3.1、在解析解下实现欧式期权希腊字母的计算
    Greeks Euro_greeks2(string CP, double S, double X, double sigma, double T, double r, double b, double pct_change); // 3.2、差分方式实现欧式期权希腊字母的计算
    double Ame_CCR(string CP, int m, double S0, double T, double sigma, double K, double r, double b); // 4.1、二叉树模型对美式期权定价
    double find_Sx(string CP, double X, double sigma, double T, double r, double b); // 4.2.1、牛顿迭代法
    double BAW(string CP, double S, double X, double sigma, double T, double r, double b); // 4.2.2、BAW定价公式，采用牛顿迭代法
    double BAW_binary(double V0, string CP, double S, double X, double T, double r, double b, double sigma=0.2); // 4.2.3、二分法求解美式期权隐含波动率

};



#endif