#include "includeheaders.h"

#define hidden1num 20
#define hidden2num 10
#define outputnum 2
#define inputnum 2
#define epochs 20000
#define lr 0.0001f



typedef struct data { double aix[epochs]; double bally[epochs]; double ballx[epochs]; double uballx[epochs]; double ubally[epochs]; } data;
typedef struct solution { double a[epochs]; double d[epochs]; } solution;

data trainingdata;
solution solutiondata;

double hidden1weights[inputnum][hidden1num];
double hidden2weights[hidden1num][hidden2num];
double outputweights[hidden1num][outputnum];

double hidden1bias[hidden1num];
double hidden2bias[hidden2num];
double outputbias[outputnum];

double hidden1val[hidden1num];
double hidden2val[hidden2num];
double outputval[outputnum];

double costs[outputnum];

double deltaoutput[outputnum];
double deltahidden1[hidden1num];
double deltahidden2[hidden2num];

double training[3][epochs];
double solutions[2][epochs];

double initweights() { return (double)(rand() / (double)RAND_MAX); }

double sigmoid(double x) { return (1 /(double) (1 + exp(-x))); }
double dsigmoid(double x) { return (double)(x * (1 - x)); }


void backwardprop(int e)
{
	for (int x = 0; x < outputnum; x++)
	{
		deltaoutput[x] = solutions[x][e]-outputval[x];
	}

	for (int x = 0; x < hidden2num; x++)
	{
		double error = 0;
		for (int y = 0; y < outputnum; y++)
		{
			error += deltaoutput[y] * outputweights[x][y] * lr;
		}
		deltahidden2[x] = error * dsigmoid(hidden2val[x]);
	}

	for (int x = 0; x <hidden1num ; x++)
	{
		double error=0;
		for (int y = 0; y < hidden2num; y++)
		{
			error += deltahidden2[y] * hidden2weights[x][y] * lr;
		}
		deltahidden1[x] = error * dsigmoid(hidden1val[x]);
	}

	for (int x = 0; x < outputnum; x++)
	{
		outputbias[x] += deltaoutput[x] * lr;
		for (int y = 0; y < hidden2num; y++)
		{
			outputweights[y][x] += hidden2val[y] * deltaoutput[x] * lr;
		}
	}

	for (int x = 0; x < hidden2num; x++)
	{
		hidden2bias[x] += deltahidden2[x] * lr;
		for (int y = 0; y < hidden1num; y++)
		{
			hidden2weights[y][x] += hidden1val[y] * deltahidden2[x] * lr;
		}
	}

	for (int x = 0; x < hidden1num; x++)
	{
		hidden1bias[x] += deltahidden1[x] * lr;
		for (int y = 0; y < inputnum; y++)
		{
			hidden1weights[y][x] += training[y][e] * deltahidden1[x] * lr;
		}
	}

}

void forwardprop(double input[3])
{
	//forward propogation
	for (int x = 0; x < hidden1num; x++)
	{
		hidden1val[x] = hidden1bias[x];
		for (int y = 0; y < inputnum; y++)
		{
			hidden1val[x] += input[y] * hidden1weights[y][x];
		}
		hidden1val[x] = sigmoid(hidden1val[x]);
	}

	for (int x = 0; x < hidden2num; x++)
	{
		hidden1val[x] = hidden1bias[x];
		for (int y = 0; y < hidden1num; y++)
		{
			hidden2val[x] += hidden1val[y] * hidden2weights[y][x];
		}
		hidden2val[x] = sigmoid(hidden2val[x]);
	}

	for (int x = 0; x < outputnum; x++)
	{
		outputval[x] = outputbias[x];
		for (int y = 0; y < hidden2num; y++)
		{
			outputval[x] += hidden2val[y] * outputweights[y][x];
		}
		outputval[x] = sigmoid(outputval[x]);
	}
	//if (outputval[0] > outputval[1])
	//	printf("a\n");
//	else printf("d\n");
}

void forwardproptraining(int e)
{
	//forward propogation
	for (int x = 0; x < hidden1num; x++)
	{
		hidden1val[x] = hidden1bias[x];
		for (int y = 0; y < inputnum; y++)
		{
			hidden1val[x] += training[y][e] * hidden1weights[y][x];
		}
		hidden1val[x] = sigmoid(hidden1val[x]);
	}

	for (int x = 0; x < hidden2num; x++)
	{
		hidden1val[x] = hidden1bias[x];
		for (int y = 0; y < hidden1num; y++)
		{
			hidden2val[x] += hidden1val[y] * hidden2weights[y][x];
		}
		hidden2val[x] = sigmoid(hidden2val[x]);
	}

	for (int x = 0; x < outputnum; x++)
	{
		outputval[x] = outputbias[x];
		for (int y = 0; y < hidden2num; y++)
		{
			outputval[x] += hidden2val[y] * outputweights[y][x];
		}
		outputval[x] = sigmoid(outputval[x]);
	}
}

void settrainingdata()
{
	srand(500);

	for (int x = 0; x < epochs; x++)
	{
			trainingdata.bally[x] = rand() % 800;
			trainingdata.ballx[x] = rand() % 800;
			trainingdata.aix[x] = rand() % 800;

			if (trainingdata.aix[x] >= trainingdata.ballx[x])
			{
				solutiondata.a[x] = 1;
				solutiondata.d[x] = 0;
			}
			else
			{
				solutiondata.a[x] = 0;
				solutiondata.d[x] = 1;
			}
	}
}

/*void settrainingdata()
{
	srand(500);
	double ballgravity = 4;
	trainingdata.aix[0] = rand() % 800;
	trainingdata.bally[0] = rand() % 800;
	trainingdata.ballx[0] = rand()%800;
	trainingdata.uballx[0] = rand() % 10;
	trainingdata.ubally[0] = -(rand() % 6);
	for (int x = 0; x < epochs; x++)
	{
		if (x == 0)
			continue;
		if (trainingdata.bally[x-1] < 600&&trainingdata.bally[x-1]>0&&trainingdata.ballx[x-1]<800)
		{
			trainingdata.uballx[x] = trainingdata.uballx[x - 1];
			trainingdata.ubally[x] = trainingdata.ubally[x - 1] + 0.006944444f * ballgravity;
			trainingdata.bally[x] = trainingdata.bally[x - 1] + trainingdata.ubally[x - 1];
			trainingdata.ballx[x] = trainingdata.ballx[x - 1] + trainingdata.uballx[x - 1];
		}
		else
		{
			trainingdata.bally[x] = rand() % 800;
			trainingdata.uballx[x] = rand() % 10;
			trainingdata.ubally[x] = -(rand() % 6);
			trainingdata.aix[x] = rand() % 800;
		}

		if (trainingdata.aix[x-1] >= trainingdata.ballx[x])
		{
			solutiondata.a[x] = 1;
			solutiondata.d[x] = 0;
			trainingdata.aix[x] =trainingdata.aix[x-1]- 2;
		}
		else
		{
			solutiondata.a[x] = 0;
			solutiondata.d[x] = 1;
			trainingdata.aix[x] =trainingdata.aix[x-1]+ 2;
		}
	}
}*/


char ai(double ballposx, double ballposy, double posx)
{
	//printf("%lf %lf %lf ", ballposx-800, ballposy, posx-800);
	double input[3] = { ballposx - 800,ballposy, posx - 800 };
	forwardprop(input);
	if (outputval[0] > outputval[1])
		return 'a';
	else
		return 'd';
}

void aitrain()
{
	/*for (int x = 0; x < epochs; x++)
	{
		printf("bally: %f, ballx=%f, uballx: %f, ubally: %f, output= ", trainingdata.bally[x],trainingdata.ballx[x], trainingdata.uballx[x], trainingdata.ubally[x]);
		switch ((int)solutiondata.a[x])
		{
		case 0:printf("d\n");
			break;
		case 1:printf("a\n");
			break;
		}
	}*/


	{
		settrainingdata();

		for (int x = 0; x < hidden1num; x++)
		{
			hidden1bias[x] = initweights();
			for (int y = 0; y < inputnum; y++)
			{
				hidden1weights[y][x] = initweights();
			}
		}


		for (int x = 0; x < outputnum; x++)
		{
			outputbias[x] = initweights();
			for (int y = 0; y < hidden1num; y++)
			{
				outputweights[y][x] = initweights();
			}
		}

		for (int x = 0; x < epochs; x++)
		{
			solutions[0][x] = solutiondata.a[x];
			solutions[1][x] = solutiondata.d[x];
			training[0][x] = trainingdata.ballx[x];
			training[1][x] = trainingdata.bally[x];
			training[2][x] = trainingdata.aix[x];
		}


		for (int e = 0; e < epochs; e++)
		{
			forwardproptraining(e);
			backwardprop(e);
			//for (int x = 0; x < hidden1num; x++)
			//	printf("hidden1bias: %lf, outputbias: %lf\n", hidden1bias[x],outputbias[x]);
		    //	printf("output values:%lf %lf ", outputval[0], outputval[1]);

			char finaloutput = (outputval[0] > outputval[1]) ? 'a' : 'd';
			char expectedoutput = (solutiondata.a[e] > solutiondata.d[e]) ? 'a' : 'd';

			//printf("bally: %0.f, ballx: %0.f, aix: %0.f, uballx: %0.f, ubally: %0.f, Output: %c, ExpectedOutput= %c ", trainingdata.bally[e], trainingdata.ballx[e], trainingdata.aix[e], trainingdata.uballx[e], trainingdata.ubally[e], finaloutput, expectedoutput);
			//if (finaloutput == expectedoutput)\
				printf("%sCorrect\n%s", green, white);
			//else
			//	printf("%sWrong\n%s", magenta, white);
			
		}
		printf("Training done\n");
	}
	
}