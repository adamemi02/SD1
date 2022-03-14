#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <algorithm>
using namespace std;
ifstream fin("test");
ofstream fout("rezultate");

bool corect(int *v,int n){
for(int i=1;i<=n-1;i++)
    if (v[i]>v[i+1])
        return 0;
    return 1;
}



void quicksort(int *v, int st, int dr)
{
	if(st < dr)
	{

		int m = (st + dr)>>1;
		swap(v[st],v[m]);
		int i = st , j = dr, d = 0;
		while(i < j)
		{
			if(v[i] > v[j])
			{
				swap(v[i],v[j]);
				d = 1 - d;
			}
			i=i+d;
			j = j-1+d;
		}
		quicksort(v, st , i - 1);
		quicksort(v, i + 1 , dr);
	}
}



void sort1(int st, int dr, int *v)
{
    if (v[st]>v[dr])
        swap(v[st],v[dr]);

}

void interclasare(int   st, int  dr, int m, int *v)
{
    int *b;
    b=new int;
    b=new int[dr-st+1];
    int i,j,k;
    i=st; j=m+1; k=0;
    while(i<=m && j<=dr)
    {
        if(v[i]<=v[j])
        {b[k]=v[i];
        i++;
        k++;}
        else{
            b[k]=v[j];
            j++;
            k++;
        }}
        int s;
        for( s=i;s<=m;s++)
        {b[k]=v[s];
        k++;}
        for(s=j;s<=dr;s++)
        {b[k]=v[s];
        k++;}
        k=1;
        for(i=st;i<=dr;i++)
        {v[i]=b[i-st];
        k++;}
        delete []b;

    }
    void mergesort(int st, int dr, int *v)
    {
        int m;
        if((dr-st)<=1)    sort1(st, dr, v);
        else  {m=(st+dr)>>1;
            mergesort(st,m,v);
            mergesort(m+1,dr,v);
            interclasare(st, dr, m,v);
        }
    }

    int minim(int *v, int n)
{
    int min1 = v[1];
    for (int i = 2; i <=n; i++)
        if (v[i] < min1)
            min1 = v[i];
    return min1;}

int maxim(int *v, int n)
{
    int max1 = v[1];
    for (int i = 2; i <=n; i++)
        if (v[i] > max1)
            max1 = v[i];
    return max1;
}

void countingsort(int *v, int n, int div,int b)
{
    int *output;
    output=new int;
    output=new int[n+1];

    int frv[b] = {0};

    for (int i = 1; i <=n; i++)
        frv[ (v[i]/div)%b]++;

    for (int i = 1; i <b; i++)
        frv[i] += frv[i - 1];

    for (int i =n; i >= 1; i--)
    {
        output[frv[ (v[i]/div)%b ]] = v[i];
        frv[ (v[i]/div)%b ]--;
    }

    for (int i = 1; i <=n; i++)
        v[i] = output[i];

        delete []output;
}


void radixsort(int *v, int n,int b)
{
    int m = maxim(v, n);
    for (int div = 1; m/div > 0; div=div*b)
        countingsort(v, n, div,b);
}




void  shellsort(int *v, int n)
{

    for (int d = n>>1; d >0; d=(d>>1))
    {
        for (int i = d; i <=n; i += 1)
        {
            int cons = v[i];
            int j;
            for (j = i; j >= d && v[j - d] > cons; j -= d)
                v[j] = v[j - d];
            v[j] = cons;
        }
    }


}


void count1(int *v,int n)
{
    int  max1=maxim(v,n);
    int min1=minim(v,n);

     int fr[max1-min1+1];
     for(int i=0;i<=max1-min1;i++)
        fr[i]=0;

     int *output;
     output=new int;
     output=new int[n+1];

        for (int i=1;i<=n;i++)
            fr[v[i]-min1]++;

        for(int i=1;i<=max1-min1;i++)
                fr[i]+=fr[i-1];

        for(int i=n;i>=1;i--)
        {
            output[fr[v[i]-min1]]=v[i];
            fr[v[i]-min1]--;
        }

        for(int i=1;i<=n;i++)
            v[i]=output[i];

        delete []output;

}

void bubblesort(int *v,int n)
{
    bool ok;
do
{
  ok = true;
  for(int i = 1; i <=n-1 ; i ++)
    if(v[i] > v[i+1])
    {
      swap(v[i],v[i+1]);
      ok = false;
    }
}
while(!ok);
}

int n,T,N,max2;
int main()
{
    fin>>T;
    for(int i=1;i<=T;i++)
    {
        cout<<"Testul cu numarul "<<i<<"\n";

        fin>>N>>max2;
        int *v;
        v=new int;
        v=new int[N+1];
        int *b;
        b=new int;
        b=new int[N+1];
        for(int i=1;i<=N;i++)
            {v[i]=rand()%max2;
            b[i]=v[i];}



            clock_t first=clock();
        count1(v,N);
        clock_t last=clock();
        cout<<"Timpul lui CountingSort este "<<float(last-first)/CLOCKS_PER_SEC<<" iar algoritmul a fost sortat ";
        if(corect(v,N))
            cout<<"corect";
        else cout<<"gresit";
            cout<<"\n";

          for(int j=1;j<=N;j++)
            v[j]=b[j];




         first=clock();
        radixsort(v,N,256);
         last=clock();
        cout<<"Timpul lui RadixSort cu baza 256 este "<<float(last-first)/CLOCKS_PER_SEC<<" iar algoritmul a fost sortat ";
        if(corect(v,N))
            cout<<"corect";
        else cout<<"gresit";
        cout<<"\n";

        for(int j=1;j<=N;j++)
            v[j]=b[j];


         first=clock();
        radixsort(v,N,65536);
         last=clock();
        cout<<"Timpul lui RadixSort cu baza 65536 este "<<float(last-first)/CLOCKS_PER_SEC<<" iar algoritmul a fost sortat ";
        if(corect(v,N))
            cout<<"corect";
        else cout<<"gresit";
        cout<<"\n";


       for(int j=1;j<=N;j++)
            v[j]=b[j];

            first=clock();
        mergesort(1,N,v);
         last=clock();
        cout<<"Timpul lui MergeSort este "<<float(last-first)/CLOCKS_PER_SEC<<" iar algoritmul a fost sortat ";
        if(corect(v,N))
            cout<<"corect";
        else cout<<"gresit";
        cout<<"\n";

           first=clock();
        quicksort(v,1,N);
         last=clock();
        cout<<"Timpul lui QuickSort este "<<float(last-first)/CLOCKS_PER_SEC<<" iar algoritmul a fost sortat ";
        if(corect(v,N))
            cout<<"corect";
        else cout<<"gresit";
        cout<<"\n";


        for(int j=1;j<=N;j++)
            v[j]=b[j];


        first=clock();
        shellsort(v,N);
         last=clock();
        cout<<"Timpul lui ShellSort este "<<float(last-first)/CLOCKS_PER_SEC<<" iar algoritmul a fost sortat ";
        if(corect(v,N))
            cout<<"corect";
        else cout<<"gresit";
        cout<<"\n";


        for(int j=1;j<=N;j++)
            v[j]=b[j];

        first=clock();
        sort(v+1,v+N+1);
         last=clock();
        cout<<"Timpul sortarii din C++ este "<<float(last-first)/CLOCKS_PER_SEC<<" iar algoritmul a fost sortat ";
        if(corect(v,N))
            cout<<"corect";
        else cout<<"gresit";
        cout<<"\n";

         cout<<"\n";

         delete []v;
         delete []b;






    }


}

