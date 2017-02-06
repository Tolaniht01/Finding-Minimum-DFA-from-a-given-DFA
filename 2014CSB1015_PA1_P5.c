# include <stdio.h>
# include <string.h>

int transition[1000][1000];
int new_transition[5000][5000];
int states[1000][1000];
int copy_states[1000][1000];
int numb_state=0;
int trans0[1000];
int trans1[1000];



void make_copy()
{
	int i,j;
	for(i=0;i<numb_state;i++)
	{
		for(j=0;j<numb_state;j++)
		{
			copy_states[i][j]=states[i][j];
		}
	}
}

int check_equality()
{
	int i,j;
	for(i=0;i<numb_state;i++)
	{
		for(j=0;j<numb_state;j++)
		{
			if(copy_states[i][j]!=states[i][j])
			{
				return 0;
			}
		}
	}
	return 1;
}

void find_trans()
{
	int i=0,j;
	for(i=0;i<numb_state;i++)
	{
		for(j=0;j<numb_state;j++)
		{
			if(transition[i][j]==1)
			{
				trans0[i]=j;
				break;
			}
		}
	}

	for(i=0;i<numb_state;i++)
	{
		for(j=0;j<numb_state;j++)
		{
			if(transition[i+numb_state][j]==1)
			{
				trans1[i]=j;
				break;
			}
		}
	}

}

int main()
{
	char line[1000];
	int final_state[1000];
	FILE * file;
    file = fopen( "input.txt" , "r"); /********** ENTER THE NAME OF THE TEXT FILE FOR INPUT HERE *************/

    FILE * out;
	out=fopen("output.txt","w+");
    int i=0,j=0,k;

     while( fgets(line,1024,file) ) 
	   {
         //printf("%s\n",line);
         j=0;
        
        if(i==0)
        {
        	numb_state=strlen(line)/2;
        	for(k=0;k<strlen(line);k=k+2)
        	{
        		final_state[j]=line[k]-48;
        		j++;
			}
		}
		else
		{
		    for(k=0;k<strlen(line);k=k+2)
        	{
        		transition[i-1][j]=line[k]-48;
        		j++;
			}
		}
		
		i++;
        
       }

       /*printf("Final - state\n");
       for(i=0;i<numb_state;i++)
       {
       	printf("%d",final_state[i]);
       }
       printf("\n--------------\n");*/

        find_trans();


       //printf("%d numb state\n",numb_state);

       for(i=0;i<numb_state;i++)
       {
       		for(j=0;j<numb_state;j++)
       		{
       			states[i][j]=0;
       			copy_states[i][j]=0;
       		}
       }

       for(i=0;i<numb_state;i++)
       {
       		if(final_state[i]==1)
       		{
       			for(j=0;j<numb_state;j++)
       			{
       				if(i!=j)
       				{
       					//printf("%d Ha %d\n",i,j);
       					if(i>j)
       					{
       						states[i][j]=1;
       					}
       					else
       					{
       						states[j][i]=1;
       					}
       				}
       			}
       		}
       }

       /*printf("------------------------\n");
       for(i=0;i<numb_state;i++)
       {
       		for(j=0;j<numb_state;j++)
       		{
       			printf("%d ",states[i][j]);
       		}
       		printf("\n");
       }*/


       make_copy();
       int q1,q2,q3,q4;


       /*for(i=0;i<numb_state;i++)
       {
       	printf("%d ha %d\n",trans0[i],trans1[i]);
       }*/

       while(1)
       {
       		for(i=0;i<numb_state;i++)
       		{
       			for(j=0;j<i;j++)
       			{
       				if(states[i][j]==0)
       				{
       					q1=trans0[i];
       					q2=trans1[i];
       					q3=trans0[j];
       					q4=trans1[j];

       					if(states[q1][q3]==1 || states[q3][q1]==1 || states[q2][q4]==1 || states[q4][q2]==1)
       					{
       						states[i][j]=1;
       					}
       				}
       			}
       		}


       		
       		int flag=0;

       		flag=check_equality();
       		if(flag==1)
       		{
       			break;
       		}

       		make_copy();

       }

       /*printf("------------------------\n");
       for(i=0;i<numb_state;i++)
       {
       		for(j=0;j<numb_state;j++)
       		{
       			printf("%d ",states[i][j]);
       		}
       		printf("\n");
       }*/

       int state_numb[numb_state];
       for(i=0;i<numb_state;i++)
       {
       	state_numb[i]=-1;
       }

       int current=0;
       for(i=0;i<numb_state;i++)
       {
       		for(j=i+1;j<numb_state;j++)
       		{
       			if(states[j][i]==0)
       			{
       				if(state_numb[i]==-1 && state_numb[j]==-1)
       				{
       					state_numb[i]=current;
       					state_numb[j]=current;
       					current++;
       				}
       				else
       				{
       					if(state_numb[i]!=-1)
       					{
       						state_numb[j]=state_numb[i];
       					}
       				}
       			}
       		}
       }


       for(i=0;i<numb_state;i++)
       {
       	   if(state_numb[i]==-1)
       	   {
       	   	state_numb[i]=current;
       	   	current++;
       	   }
       }

       /*for(i=0;i<numb_state;i++)
       {
       	printf("%d\n",state_numb[i]);
       }
       printf("%d current\n",current);*/
       fprintf(out,"%d$\n",current);

       int ans_final[current];
       int ans_trans0[current][current];
       int ans_trans1[current][current];

       for(i=0;i<current;i++)
       {
       		for(j=0;j<current;j++)
       		{
       			ans_trans1[i][j]=0;
       			ans_trans0[i][j]=0;
       			ans_final[j]=0;
       		}
       }

       for(i=0;i<numb_state;i++)
       {
       		if(final_state[i]==1)
       		{
       			ans_final[state_numb[i]]=1;
       		}
       }

       for(i=0;i<numb_state;i++)
       {
       	  for(j=0;j<numb_state;j++)
       	  {
       	  	  if(transition[i][j]==1)
       	  	  {
       	  	  	ans_trans0[state_numb[i]][state_numb[j]]=1;
       	  	  }

       	  	  if(transition[numb_state+i][j]==1)
       	  	  {
       	  	  	ans_trans1[state_numb[i]][state_numb[j]]=1;
       	  	  }
       	  }
       }

       for(i=0;i<current;i++)
       {
       		fprintf(out, "%d ",ans_final[i] );
       }
       fprintf(out,"\n");

        for(i=0;i<current;i++)
       {
       		for(j=0;j<current;j++)
       		{
       			fprintf(out,"%d ",ans_trans0[i][j]);
       		}
       		fprintf(out,"\n");
       }


            for(i=0;i<current;i++)
       {
       		for(j=0;j<current;j++)
       		{
       			fprintf(out,"%d ",ans_trans1[i][j]);
       		}
       		fprintf(out,"\n");
       }



	return 0;
}