#include<mpi.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
char mess[5][20]={"Hello","RVCE","CSE","NEW"};

#define BUFSIZE 32

int main(int argc,char** argv)
{
	int root=0,tag=0,rank,numProcs;
	char single_mes[32];
	MPI_Init(&argc,&argv);
	MPI_Status status;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&numProcs);
	if(rank!=0)
	{
		strcpy(single_mes,mess[rank-1]);
		MPI_Send(&single_mes,BUFSIZE,MPI_CHAR,root,tag,MPI_COMM_WORLD);
	}
	else
	{
		for(int i=1;i<numProcs;i++)
		{	MPI_Recv(&single_mes,BUFSIZE,MPI_CHAR,i,tag,MPI_COMM_WORLD,&status);
			printf("\n%s is message from %d process: ",single_mes,i);
		}
	}
	
	MPI_Finalize();
	return 0;
}