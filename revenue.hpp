#ifndef REVENUE_HPP_INCLUDED
#define REVENUE_HPP_INCLUDED
#include <string>

/*
profits = totalSales - totalCosts
costPerEmp = totalCosts / numOfEmp
*/

using namespace std;

class Revenue{
private:
    string divisionName,
           divisionNumber; //set to string for validation purposes

    int numOfEmp;

    double totalSales,
           totalCosts,
           profits,
           costPerEmp;

    static int totalDivisions;
    static int quarter;

public:

    Revenue(){
        divisionName = "UNNAMED";
        divisionNumber = 1;
        numOfEmp = 1;
        totalSales = 1.00;
        totalCosts = 1.00;
        profits = 1.00;
        costPerEmp = 1.00;
    }

    /*Begin setters */
    void setDivName(string name){
        divisionName = name;
    }

    void setDivisionNum(string n){
        divisionNumber = n;
    }

    void setNumOfEmp(int e){
        numOfEmp = e;
    }

    void setTotalSales(double s){
        totalSales = s;
    }

    void  setTotalCosts(double c){
        totalCosts = c;
    }

    void calcProfits(){
        profits = totalSales - totalCosts;
    }

    void calcCostPerEmp(){
        costPerEmp = totalCosts / numOfEmp;
    }

    /*Begin getters */
    string getDivName(){
        return divisionName;
    }

    string getDivNum(){
        return divisionNumber;
    }

    int getNumOfEmp(){
        return numOfEmp;
    }

    double getTotalSales(){
        return totalSales;
    }

    double getTotalCosts(){
        return totalCosts;
    }

    double getProfits(){
        return profits;
    }

    double  getCostPerEmp(){
        return costPerEmp;
    }

    /* static functions */
    static void setTotalDivisions(int d){
        totalDivisions = d;
    }
    static int getTotalDivisions(){
        return totalDivisions;
    }

    static void setQuarter(int q){
        quarter = q;
    }

    static int getQuarter(){
        return quarter;
    }



    ~Revenue(){}
};


#endif // REVENUE_HPP_INCLUDED
