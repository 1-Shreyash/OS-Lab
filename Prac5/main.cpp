#include <stdio.h> //for sjf
#include <stdlib.h>
#include <iostream>
using namespace std;

struct process
{
    int bt, at, id, prior;
};

#include "fcfs.h"
#include "NprSrjf.h"
#include "PrSrjf.h"
#include "NprPrior.h"
#include "PrPrior.h"
#include "RR.h"
// struct gantt{
//     int prid, toa, endt, d;//time of arrival
// };

int main(){
    int choice, n;
    cout<<"\n\n1.FCFS\n2.SRJF(non-preemptive)\n3.SRJF(preemptive)\n4.Priority(non-preemptive)\n5.Priority(preemptive)\n6.Round Robin\n\n";
    cout<<"-------------->>> CHOOSE PROCESS SCHEDULING ALGO : ";
    cin>>choice;
    cout<<"Enter the number of Processes: ";
    cin>>n;
    struct process pr[n];
    switch (choice)
    {
    case 1:
        /* code */
        for(int i = 0 ; i < n; i++){
            cout<<"For P"<<i<<": \n";
            cout<<"\tBT : ";
            cin>>pr[i].bt;
            cout<<"\tAT : ";
            cin>>pr[i].at;
        }
        Fcfs(pr, n);
        break;
    case 2:
        for(int i = 0 ; i < n; i++){
            cout<<"For P"<<i<<": \n";
            cout<<"\tBT : ";
            cin>>pr[i].bt;
            cout<<"\tAT : ";
            cin>>pr[i].at;
        }
        /* code */
        break;
    case 3:
        for(int i = 0 ; i < n; i++){
            cout<<"For P"<<i<<": \n";
            cout<<"\tBT : ";
            cin>>pr[i].bt;
            cout<<"\tAT : ";
            cin>>pr[i].at;
        }
        /* code */
        break;
    case 4:
        for(int i = 0 ; i < n; i++){
            cout<<"For P"<<i<<": \n";
            cout<<"\tBT : ";
            cin>>pr[i].bt;
            cout<<"\tAT : ";
            cin>>pr[i].at;
            cout<<"\tPriority : ";
            cin>>pr[i].prior;
        }
        /* code */
        break;
    case 5:
        for(int i = 0 ; i < n; i++){
            cout<<"For P"<<i<<": \n";
            cout<<"\tBT : ";
            cin>>pr[i].bt;
            cout<<"\tAT : ";
            cin>>pr[i].at;
            cout<<"\tPriority : ";
            cin>>pr[i].prior;
        }
        /* code */
        break;
    case 6:
        int pn;
        for(int i = 0 ; i < n; i++){
            cout<<"For P"<<i<<": \n";
            cout<<"\tBT : ";
            cin>>pr[i].bt;
            cout<<"\tAT : ";
            cin>>pr[i].at;
        }
        cout<<"Enter p:";
        cin>>pn;
        /* code */
        break;
    
    default:
        break;
    }
}