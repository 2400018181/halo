#include <iostream>
#include <conio.h>
#include <stdlib.h>

using namespace std;

int hasil;

int faktorial (int nilai){
    hasil = nilai;
    while (nilai > 1){
        hasil = hasil * (nilai - 1);
        nilai = nilai - 1;
    }
    return hasil;
}
int main(){
    int p, nq, max, x, i, j, n, k, r, s, tr, no;
    string a[100];
    div_t xx;
    
    cout<<"-----------------------------\n";
	cout<<"PROGRAM GENERATE PERMUTASI\n\n";
	
    cout<<"Masukkan nilai n : ";
    cin>>n;

    for (i = 1; i <= n; i++){
        cout<<"masukkan nilai himpunan a["<<i<<"] : ";
        cin>>a[i];
    }
    cout<<"nilai r : ";
    cin>>tr;
    
    p = faktorial(n);
    nq = faktorial(n - tr);
    if (nq == 0) nq = 1;
    max = p / nq;

    cout<<"nilai permutasi : "<<max<<endl;
    cout<<"\ntekan enter untuk melihat hasil generate permutasi....."<<endl;
    getch();

    no = 1;
    
    for(x=1; x<=max;x++){
    	cout << no << ". ";
        for (i = 1; i <= tr; i++)
            cout << a[i] << " ";
        cout << endl;
        no++;
	
	
	j=n-1;
	while (a[j]>a[j+1]) j--;
	k=n;
	while (a[j]>a[k]) k--;
	
	string i =a[k];
	a[k]=a[j];
	a[j]=i;
	
	r=n;
	s=j+1;
	while(r>s){
		i=a[r];
		a[r]=a[s];
		a[s]=i;
		r--;
		s++;
	}
		
	}
	cout<<"selesaiiiiiiiii";

	return 0; 
	
	
}
 
