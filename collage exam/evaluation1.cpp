#include <stdio.h>

int prime(int num)
{
        int flage;
        int d;
        if(num<2) printf("Entered number is invalid");
        int s;
        for (s=1; s<=num; s++)
        {
                if (num%s==0)
                {
                        for (d=2; d<=s/2; d++)//num
                        {
                                if(s%d==0) flage =1 ;
                                else if (s%d!=0) flage =0;
                        }
                        if(flage==1)
                        {
                                printf("the non prime divisor is %d \n", s);
                        }
                        else
                        {
                                printf("the prime divisor is %d \n", s);
                        }

                }
        }
        return 0;
}

int factorial(int num)
{

        int x;
        int mult=1;
        for(x=1; x<=num; x++)
        {
                mult= mult*x;
        }
        printf("%d", mult);
        return mult;
}

int main()
{

        //input the number n
        int n;
        printf("Enter a number in range 0 to 999,999,999");
        scanf("%d",&n);

        //calculating the digit of a enter the number
        int num = n;
        int count=0;
        int digit;
        while(num>0)
        {
                digit = num%10;
                count++;
                num=num/10;
        }

        //finding a odd even digit
        int temp=n;
        int digiteve;
        int digitodd;
        int i;//
        int arrayodd[10];
        int arrayeve[10];
        int numbr=0;
        for(i=1; i<=count; i++)
        {
                //for even digit number
                if(i%2==0)
                {
                        digiteve=temp%10;
                        printf("digit at even place of n is: %d\n", digiteve);
                        temp=temp/10;


                }
                //for odd digit number
                else if(i%2!=0)
                {
                        digitodd=temp%10;
                        printf("digit a odd place of n is: %d\n", digitodd);

                        numbr=numbr*10+digitodd;
                        temp=temp/10;
                }
        }
        int m;
        int fact;
        int sum=0;
        for(m=0; m<10; m++)
        {

                fact=factorial(digiteve);
                sum = sum+fact;

        }

        printf("sum of factorial of digit present at even place %d\n",sum);
        printf("number m is %d\n",numbr);
        int divisor = prime(numbr);
        printf("%d", divisor);

        return 0;

}
