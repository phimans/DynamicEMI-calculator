#include <bits/stdc++.h>

using namespace std;


vector<double> monthlyInterestPayment;      //Size is equal to Loan Term in Months
vector<double> monthlyPrincipalPayment;     //Size is equal to Loan Term in Months
vector<double> principalAmountLeft;         //Size is equal to Loan Term in Months + 1 ... 1st value is equal to principalLoanAmount and last value is 0



            /* In this function vector<double> fluctuationInBPS contains Fluctuations in Initial Interest Rate */

void includeFluctuations( vector<double> &fluctuationInBPS, int loanTerm ){

    int numberOfFluctuations;

    cout << "Enter Number of Fluctuations in your Entire Loan Duration" << endl;
    cin >> numberOfFluctuations;
    cout << endl;


    cout << "Enter " << numberOfFluctuations << " fluctuations in Basis Points ( BPS ) with respective Installment Number separated by space " << endl << endl;
    cout << "Correct format should be" << endl << endl;
    cout << "Inst. No.         Fluctuation in BPS" << endl;
    cout << "  3                    -40" <<endl << "  5                    35" << endl << "  8                    -10" << endl;
    cout << "Where Negative (-) sign represents Decrease in Interest Rate" << endl << endl;


    for ( int i=0; i<numberOfFluctuations; i++) {
        int instNo;
        double bps;
        cin >> instNo >> bps;
        fluctuationInBPS[instNo-1] = bps;
    }

    double val = 0;
    for ( int i=0; i<2*loanTerm; i++) {
        if( fluctuationInBPS[i] != 0 ) {
            val += fluctuationInBPS[i];
        }
        fluctuationInBPS[i] = val;
    }

    cout << endl;

}

            /* In this function variable installmentNumber is the installmentNumber in which loanee pays EMI + some surplus amount...
                        variable surplusAmount represents partial Pre Payed amount... */


void includePartialPrePayment( vector<double> &partialPrePayment ){

    int numberOfPrePayments;

    cout << "Enter Number of PrePayments you are doing within the Loan Duration" << endl;
    cin >> numberOfPrePayments ;
    cout << endl;

    cout << "Enter " << numberOfPrePayments << " Surplus Amounts in Rupees with respective Installment Number separated by space " << endl << endl;
    cout << "Correct format should be" << endl << endl;
    cout << "Inst. No.         Surplus Amount" << endl;
    cout << "  5                    20000" << endl << "  9                    25000" << endl << "  12                    10000" << endl<< endl;

    for ( int i = 0; i < numberOfPrePayments; i++ ) {

        int instNo;
        double surplusAmount;
        cin >> instNo >> surplusAmount;
        partialPrePayment[instNo-1] = surplusAmount;

    }
    cout << endl;
}

            /* In this function variable installmentNumber is the installmentNumber in which loanee pays total remaining amount */

void includeFullPrePayment( int &instNoOfFullPayment ){

    cout << "Enter the Installment Number in which you are Paying your Remaining Loan Amount" << endl;
    cin >> instNoOfFullPayment;
    cout << endl ;

}

void calculationOfEMI ( double &principalLoanAmount, int &loanTerm, double &rateOfInterest, double &emi, vector<double> fluctuationInBPS, vector<double> &partialPrePayment, int instNoOfFullPayment ) {


    rateOfInterest /= (12 * 100);

    emi = ( principalLoanAmount * rateOfInterest * pow( 1 + rateOfInterest, loanTerm ) ) / ( pow(1 + rateOfInterest, loanTerm) - 1 );


    principalAmountLeft.push_back( principalLoanAmount );

    int index = 0;
    while ( principalAmountLeft.back() > 10 ) {


        if( partialPrePayment[index-1] != 0 ) {
            principalAmountLeft[index] -= partialPrePayment[index-1];
        }

        monthlyInterestPayment.push_back( principalAmountLeft[index] * ( rateOfInterest + ( fluctuationInBPS[index]/120000.0 ) ) );
        monthlyPrincipalPayment.push_back( emi - monthlyInterestPayment[index] );
        principalAmountLeft.push_back( principalAmountLeft.back() - monthlyPrincipalPayment[index] );

        if ( instNoOfFullPayment == index + 1 ) {
            principalAmountLeft.back() = 0;
        }

        if( principalAmountLeft.back() < 10 ) {
            principalAmountLeft.back() = 0;
        }

        if ( principalAmountLeft.back() < 10 ) {
            monthlyPrincipalPayment.back() = principalAmountLeft[ principalAmountLeft.size() - 2 ];
        }

        index++;

    }


}

void printEMIChart( vector<double> monthlyPrincipalPayment, vector<double> monthlyInterestPayment, vector<double> principalAmountLeft, vector<double> partialPrePayment ) {

    double totalAmountPayable=0;
    double totalInterestPayable=0;

    cout << " Month No.      Principal     PrePayment       Interest      Total Payment        Balance " << endl;

    for( int i = 0; i < monthlyPrincipalPayment.size(); i++ ) {
        cout << "    " << i+1 << "             " << round(monthlyPrincipalPayment[i]) << "           " << round(partialPrePayment[i]) << "             " ;
        cout << round(monthlyInterestPayment[i]) << "             " << round(monthlyPrincipalPayment[i] + monthlyInterestPayment[i] + partialPrePayment[i]);
        cout << "             " << round(principalAmountLeft[i+1]) << endl;

        totalAmountPayable += monthlyPrincipalPayment[i] + monthlyInterestPayment[i] + partialPrePayment[i];
        totalInterestPayable += monthlyInterestPayment[i];
    }

    cout << endl;
    cout << "  Total Amount Payable by you is Rupees " << round(totalAmountPayable) << " which contains Total Interest of Rupees " << round(totalInterestPayable) << endl;

}

int main()
{
    double principalLoanAmount;
    int loanTerm;
    double rateOfInterest;
    double emi=0;


    cout << endl;
    cout << "Enter the Loan Amount in Rupees" << endl;
    cin >> principalLoanAmount;
    cout << endl;

    cout << "Enter the Loan Term / Tenure / Duration in Number of Months" << endl;
    cin >> loanTerm;
    cout << endl;

    cout << "Enter the Rate of Interest ( per annum ) in Percentage ( % )" << endl;
    cin >> rateOfInterest;
    cout << endl;







    string isFluctuated;
    vector<double> fluctuationInBPS( 2*loanTerm, 0 );     // A Factor of 2 is used to handle the case when there is Increase in Interest Rate and Loan Term is Increased

    cout<< "Do you want to Include Fluctuations in Interest Rate... Enter YES/NO" << endl;
    cin >> isFluctuated;
    cout << endl;

    if(isFluctuated == "YES" || isFluctuated == "yes" || isFluctuated == "Yes" || isFluctuated == "Y" || isFluctuated == "y") {

        includeFluctuations( fluctuationInBPS, loanTerm );

    }


    string partialPP;                                       // Yes if Loanee wants to Partially Prepay the Loan, No otherwise
    vector<double> partialPrePayment( 2*loanTerm, 0);       // A Factor of 2 is used to handle the case when there is Increase in Interest Rate and Loan Term is Increased

    cout << "Do you want to opt for Partial Prepayment... Enter YES/NO" << endl;
    cin >> partialPP;
    cout << endl;

    if(partialPP == "YES" || partialPP == "yes" || partialPP == "Yes" || partialPP == "Y" || partialPP == "y") {

        includePartialPrePayment( partialPrePayment );

    }



    string fullPP;                                            // Yes if Loanee wants to Fully prepay the Loan, No otherwise
    cout << "Do you want to opt for Full Prepayment... Enter YES/NO" << endl;
    cin >> fullPP;
    cout << endl;
    int instNoOfFullPayment=-1;

    if(fullPP=="YES" || fullPP=="yes" || fullPP=="Yes" || fullPP=="Y" || fullPP=="y") {

        includeFullPrePayment ( instNoOfFullPayment );

    }

    calculationOfEMI ( principalLoanAmount, loanTerm, rateOfInterest, emi, fluctuationInBPS, partialPrePayment, instNoOfFullPayment );

    printEMIChart( monthlyPrincipalPayment, monthlyInterestPayment, principalAmountLeft, partialPrePayment );



    return 0;
}
