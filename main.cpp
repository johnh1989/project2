/*
John H.
This program takes user input for Sales Divisions. It calculates
sales, costs, profits, and cost per employee.
It then writes the data in xml format in cop2224_proj2.xml.
*/

#include <iostream>
#include "revenue.hpp"
#include <cstring>
#include <string>
#include <fstream>
#include <iomanip>


using namespace std;

int Revenue::totalDivisions = 0; //initialize the static members
int Revenue::quarter = 1;

void collectData(Revenue*, int);
bool checkDivNum(string);
int get_num_of_digits(string);
void writeToFile(Revenue*, int);


int main()
{
    char quit;
    int totalRecords, quarter;
    Revenue* rev;

    cout << "Do you want to exit y/n: ";
    cin >> quit;
    quit = toupper(quit);
    if (quit == 'Y'){
        cout << "goodbye";
        return 1;
    }
    cout << "How many revenue records will you enter?: ";
    cin >> totalRecords;
    rev = new Revenue[totalRecords]; //create dynamic array

    cout << "What quarter is this for: ";
    cin >> quarter;
    Revenue::setQuarter(quarter);

    /* can call right from main because we are passing pointers */
    collectData(rev, totalRecords);
    writeToFile(rev, Revenue::getTotalDivisions());

    delete[] rev; //clean up the allocated memory
    cin.get();
    return 0;
}

void collectData(Revenue* rev, const int index){
    string name,
           divnum;

    int numOfEmp,
        numOfDigits,
        totalDivs;

    double totalSales,
           totalCosts;

    bool isNumber = false;

    char addRecord = 'Y';

    for (int x = 0; x < index;  x++){

        cout << "Enter division name: ";
        cin >> name;
        rev[x].setDivName(name);

        do{
            cout << "Enter division number: ";
            cin >> divnum;
            isNumber = checkDivNum(divnum);
            numOfDigits = get_num_of_digits(divnum);
            rev[x].setDivisionNum(divnum);
        }while(numOfDigits != 4 || isNumber == false);

        cout << "Enter number of employees: ";
        cin >> numOfEmp;
        rev[x].setNumOfEmp(numOfEmp);

        cout << "Enter the total sales: $";
        cin >> totalSales;
        rev[x].setTotalSales(totalSales);

        cout << "Enter the total costs: $";
        cin >> totalCosts;
        rev[x].setTotalCosts(totalCosts);

        rev[x].calcProfits();

        rev[x].calcCostPerEmp();

        Revenue::setTotalDivisions((x+1)); // keeps an accurate count of divisions

        if (Revenue::getTotalDivisions() < index){ // if user hasn't entered every record they planned on
            cout << "Add another record? y/n";     // give them the option to exit and save data anyway
            cin >> addRecord;
            addRecord = toupper(addRecord);
            if(addRecord == 'N'){
                break; //most graceful and readable way to get out if the user wants to quit
            }
        }
    }
}

/*gets the length of the division number*/
int get_num_of_digits(string digits){
    int length;
    length = digits.size();
    return length;
}
/*Checks to make sure division num is a number*/
bool checkDivNum(string valid_num){
    bool isNumber = false;  //assume this is false

    for(int i = 0; i < valid_num.size(); ++i) {
        if (isdigit(valid_num[i])){
            isNumber = true;  //sets isNumber to true.
        }
        else{
            return false;  //end as soon as we see a non-integer
        }
    }
    return isNumber;
}

/*writes all of our data to xml file */
void writeToFile(Revenue* rev, const int newIndex){
    ofstream xml;
    xml.open("cop2224_proj2.xml", fstream::app);
    cout << "Writing revenue records to cop2224_proj2.xml" << endl;
    xml << "<revenue>\n";
    for (int x = 0; x < newIndex; x++){
        xml << "    <Division>\n";
        xml << "        <DivisionName>";
        xml << rev[x].getDivName() << "</DivisionName>\n";
        xml << "        <DivisionNumber>";
        xml << rev[x].getDivNum() << "</DivisionNumber>\n";
        xml << "        <NumberOfEmployees>";
        xml << rev[x].getNumOfEmp() << "</NumberOfEmployees>\n";
        xml << "        <TotalSales>";
        xml << fixed << setprecision(2) << rev[x].getTotalSales() << "</TotalSales>\n";
        xml << "        <TotalCosts>";
        xml << fixed << setprecision(2) << rev[x].getTotalCosts() << "</TotalCosts>\n";
        xml << "        <Profit>";
        xml << fixed << setprecision(2) << rev[x].getProfits() << "</Profits>\n";
        xml << "        <CostPerEmployee>";
        xml << rev[x].getCostPerEmp() << "</CostPerEmployee>\n";
        xml << "    </Division>\n";
    }
    xml << "    <Quarter>" << Revenue::getQuarter() << "</Quarter>\n";
    xml << "    <TotalDivisions>" << Revenue::getTotalDivisions() << "</TotalDivisions>\n";
    xml << "</revenue>\n";
}
