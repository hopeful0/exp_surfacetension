#include <cstdio>
#include <list>
#include <math.h>

#define pi 3.14159265358979

using namespace std;
typedef list<double> ldouble;
typedef ldouble::iterator ildouble;

void clear_stdin(void)
{
	char c;
	do
	{
		c = getchar();
	}while(c != '\n' && c != EOF);
}

void ls(ldouble xs, ldouble ys, double& k, double& b,double& Sk, double& Sb, double& S, double& r)
{
	double ax = 0, ay = 0, axx = 0, ayy = 0, axy = 0, Q = 0;
	for(double x : xs)
	{
		ax += x;
		axx += pow(x,2);
	}
	ax /= xs.size();
	axx /= xs.size();
	for(double y : ys)
	{
		ay += y;
		ayy += pow(y,2);
	}
	ay /= ys.size();
	ayy /= ys.size();
	ildouble ix = xs.begin(), iy = ys.begin();
	int n = 0;
	while(ix != xs.end() || iy != ys.end())
	{
		axy += (*ix) * (*iy);
		n ++;
		ix ++;
		iy ++;
	}
	axy /= n;
	k = (ax * ay - axy) / (pow(ax,2) - axx);
	b = ay - k * ax;
	ix = xs.begin();
	iy = ys.begin();
	while(ix != xs.end() || iy != ys.end())
        {
                Q += pow((*iy) - k * (*ix) + b, 2);
                ix ++;
                iy ++;
        }
	S = sqrt(Q / (n - 2));
	Sk = S * sqrt(1.0 / n / (axx - pow(ax,2)));
	Sb = S * sqrt(axx / n / (axx - pow(ax,2)));
	r = (axy - ax * ay) / sqrt((axx - pow(ax,2)) * (ayy - pow(ay,2)));
}

double avg(ldouble data)
{
	double sum = 0;
	for(double d : data)
		sum += d;
	return sum / data.size();
}

double getU(ldouble data, double t, double di)
{
	double Sa,uA,uB;
	double var = 0, a = avg(data);
	for(double d : data)
		var += pow(d - a, 2);
	Sa = sqrt(var / data.size() / (data.size() - 1));
	uA = t * Sa;
	uB = di / sqrt(3);
	return sqrt(pow(uA,2)+pow(uB,2));
}

double getUsigma(ldouble sigmas, double* p, double* Up)
{
	double avgsigma = avg(sigmas);
	double Esigma = 0;
	Esigma += pow(Up[0] / p[0], 2);
	Esigma += pow(Up[1] / (p[1] + p[2]), 2);
	Esigma += pow(Up[2] / (p[1] + p[2]), 2);
	Esigma += pow(Up[3] / (p[4] - p[5]), 2);
	Esigma += pow(Up[4] / (p[4] - p[5]), 2);
	Esigma = sqrt(Esigma);
	return avgsigma * Esigma;
}

int main()
{
	printf("欢迎使用 表面张力系数数据处理程序!\n作者：hopeful from LZU\n");
	while(1)
	{
		printf("==================================================\n");
		printf("请选择功能：\n");
		printf("1.传感器灵敏度的测量\n");
		printf("2.环的直径的测量\n");
		printf("3.表面张力系数的测量\n");
		printf("其他：退出\n");
		printf("==================================================\n");
		int func;
		if(1 != scanf("%d",&func)) break;
		clear_stdin();
		switch(func)
		{
			case 1:
			{
				ldouble xs,ys;
				for(int i = 1; i < 7; i ++)
                			xs.push_back(i * 0.5);
				printf("依次输入6组电压值，输入q结束：\n");
				double temp;
				while(1 == scanf("%lf",&temp))
					ys.push_back(temp);
				double k,b,Sk,Sb,S,r;
				ls(xs,ys,k,b,Sk,Sb,S,r);
				printf("输出(c = 1 / k)：\nc = %lf\nk = %lf\nU(c) = %lf\nr = %lf\n",k,1/k,Sk,r);
				break;
			}
			case 2:
			{
				ldouble od,id;
				double temp,t,di;
				printf("依次输入n组外径值D1，输入q结束：\n");
				while(1 == scanf("%lf",&temp))
					od.push_back(temp);
				printf("依次输入n组内径值D2，输入q结束：\n");
				while(1 == scanf("%lf",&temp))
                                        id.push_back(temp);
				printf("输入A类不确定度的t因子：\n");
				scanf("%lf",&t);
				printf("输入游标卡尺的极限误差：\n");
				scanf("%lf",&di);
				printf("环的外径：\nD1 = %lf\nU(D1) = %lf\n环的内径：\nD2 = %lf\nU(D2) = %lf\n",avg(od),getU(od,t,di),avg(id),getU(id,t,di));
				break;
			}
			case 3:
			{
				//0 k 1 d1 2 d2 3 u1 4 u2
				ldouble sigma,U1,U2;
				double temp1,temp2;
				double p[5],Up[5];
				printf("输入传感器的c值及其的不确定度：\n");
				scanf("%lf %lf",&p[0],&Up[0]);
				printf("输入环的外径及其不确定度：\n");
				scanf("%lf %lf",&p[1],&Up[1]);
				printf("输入环的内径及其不确定度：\n");
				scanf("%lf %lf",&p[2],&Up[2]);
				printf("依次输入n组U1、U2的值，用空格隔开，输入q结束：\n");
				while(1 > scanf("%lf %lf",&temp1,&temp2))
				{
					U1.push_back(temp1);
					U2.push_back(temp2);
					double dU = temp2 - temp1;
					double f = dU / p[0];
					double s = f / pi / (p[1]+p[2]);
					printf("deltaU = %lf\nF = %lf\nsigma = %lf\n",dU,f,s);
					sigma.push_back(s);
				}
				double t,di;
				printf("输入测量U1、U2时的t因子和极限误差：\n");
				scanf("%lf %lf",&t,&di);
				p[3] = avg(U1);
				Up[3] = getU(U1,t,di);
				p[4] = avg(U2);
				Up[4] = getU(U2,t,di);
				printf("sigma = %lf,U(sigma) = %lf\n",avg(sigma),getUsigma(sigma,p,Up));
				break;
			}
			default:
				return 0;
		}
		printf("按回车键继续");
		clear_stdin();
		getchar();
	}
	return 0;
}

