# exp_surfacetension
物理力热试验：表面张力系数的测定实验数据处理程序。
The program used to process the data of the physics thermal experiment:Determination of surface tension ratio.
# 作者(author)
hopeful from LZU
# 日期(date)
2015.03.24
# 简介(brief)
本程序为处理表面张力系数的测定实验的数据而设计
程序分为3个模块：
1.传感器灵敏度的测量
依次输入在0.5g、1.0g、1.5g、2.0g、2.5g、3.0g的情况下，传感器的示数(输入单位为mV)。根据公式F=cU,利用最小二乘法线性拟合，输出灵敏度系数c(单位N/mV),系数k(=1/c,单位mV/N),c的(A类)不确定度U(c)与相关系数r
2.环的直径的测量
分别输入测得的环的外径和内径的数据(单位cm),查表并输入测量过程中的t因子(最好保证外径内径数据一致)和测量工具游标卡尺的极限误差(单位cm),程序将输出外径与内径的平均值(D1、D2,单位cm)和其不确定度U(D1)、U(D2)
3.表面张力系数的测量
输入通过1、2得到的结果，c、U(c)、D1、U(D1)、D2、U(D2),然后依次输入测量的U1、U2(单位mV),每输入一组数据，将输出通过改组数据得到的deltaU(=U2-U1)、表面张力f和表面张力系数sigma，然后输入测量U1、U2的t因子及极限误差，最后程序将输出由此得到的最终的表面张力系数sigma的平均值与不确定度(单位：N/m)
