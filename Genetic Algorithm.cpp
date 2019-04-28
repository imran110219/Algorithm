#include<cstdio>	//to use the printf function
#include<cstdlib>         		//to use the rand function
#include<cmath>
#include<vector>

typedef struct Chrom             		// creating the chrom structure
{
    //short int position[64];
    int position[16] =  {-1};
    //short int position_2[6];
    int fit;
} chrom;                           	// now we have a chrom type that we can use

void *evpop(chrom popcurrent[2]);    	//defining the functions that we will use
int x(chrom popcurrent);
void *pickchroms(chrom popcurrent[2]);
//void *crossover(chrom popnext[2]);
//void *mutation(chrom popnext[2]);

int Map[16][3] ={
                        {0, 1, 7},   /*  initializers for row indexed by 0 */
                        {1, 1, 11},   /*  initializers for row indexed by 1 */
                        {10, 3, 14},   /*  initializers for row indexed by 2 */
                        {11, 3, 1},   /*  initializers for row indexed by 3 */
                        {100, 5, 8},   /*  initializers for row indexed by 4 */
                        {101, 6, 11},   /*  initializers for row indexed by 5 */
                        {110, 6, 4},   /*  initializers for row indexed by 6 */
                        {111, 8, 4},   /*  initializers for row indexed by 7 */
                        {1000, 10, 1},   /*  initializers for row indexed by 8 */
                        {1001, 10, 7},   /*  initializers for row indexed by 9 */
                        {1010, 10, 11},   /*  initializers for row indexed by 10 */
                        {1011, 11, 14},   /*  initializers for row indexed by 11 */
                        {1100, 13, 12},   /*  initializers for row indexed by 12 */
                        {1101, 12, 2},   /*  initializers for row indexed by 13 */
                        {1110, 14, 3},   /*  initializers for row indexed by 14 */
                        {1111, 14, 8},   /*  initializers for row indexed by 15 */
                    };

int main()								// the main function
{
    short int start = 0;         // start point (0, 0)
    short int goal = 15;          // end point (7, 7)

    //vector<vector<int>> Map;

    int num;								// num is the no. of iterations
    int i,j;

    printf("\nWelcome to the Genetic Algorithm coded by Sadman Sobhan:https://github.com/imran110219/Genetic-Algorithm \nThe Algorithm is based on the function d = sqrt(x^2 + y^2) to find the maximum value of the function...\n"); // introduction to the program


enter:
    printf("\nPlease enter the no. of iterations:  ");
    scanf("%d",&num);             	// enter the no. of iterations in num

    chrom popcurrent[2];                        	// we make 2 chromes of popcurrent
    chrom popnext[2];                           	// we make 2 chromes of popnext

    if(num<1)                               	// if a -ve number is inserted .. enter num again
        goto enter;

    evpop(popcurrent);                       	//initialise pop current

    for(i=0; i<num; i++)                      	// loop num times
    {
        printf("\ni = %d\n",i);        	// print the iteration number

        for(j=0; j<2; j++)
            popnext[j]=popcurrent[j];            	//copy popcurrent to popnext in order to adjust it

        pickchroms(popnext);                    	//pick best chromes
        //crossover(popnext);                      	//cross over to get children chromes
        //mutation(popnext);                       	//mutate with a low probability

        for(j=0; j<2; j++)
            popcurrent[j]=popnext[j];             	//copy the chromes of popnext to popcurrent

    }                                           // loop back until no. of iterations is exceeded

    printf("\nPress any key to end ! ");

    //flushall();                             		// flush the input buffer
    //getche();                                	// wait for a character from the keyboard to end

}                                            	//end of main


void *evpop(chrom popcurrent[2])               	//takes a pointer to a chrom of 2 elements
{
    int i,j;
    int random;
    for(j=0; j<2; j++)                        // loop of j to choose chromes from [0] to [3]
    {
        popcurrent[j].position[0]=0;
        int repeat[16] = {0};
        for(i=1; i<16; i++)            			// loop of i to choose the gen of the chrom from  [0] to [5]
        {
            random=rand();               		// creating random value
            random=(random%16);        			// make the random value 0 to 15
            if(repeat[random] == 0 && random != 0)
            {
                popcurrent[j].position[i]=random;
                repeat[random] = 1;
            }
            else
            {
                i--;
            }  		// initialising the bit[i] of chrom[j] with random
            if(random == 15)
            {
                break;
            }

        }   // end of for(i)

        popcurrent[j].fit=x(popcurrent[j]);	// calcualte the fitness of chrom[j]
        printf("\n popcurrent[%d]=%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d    fitness = %d",j,
               popcurrent[j].position[0], popcurrent[j].position[1], popcurrent[j].position[2],
               popcurrent[j].position[3], popcurrent[j].position[4], popcurrent[j].position[5],
               popcurrent[j].position[6], popcurrent[j].position[7], popcurrent[j].position[8],
               popcurrent[j].position[9], popcurrent[j].position[10], popcurrent[j].position[11],
               popcurrent[j].position[12], popcurrent[j].position[13], popcurrent[j].position[14],
               popcurrent[j].position[15], popcurrent[j].fit);     // print the chrom[j]

    }    // end of for(j)


    return(0);
}                              	//end of evpop function

int x(chrom popcurrent)        	//x function that evaluate the value of a given chrom
{
    int p1, p2, distancex, distancey, distance = 0;
    for(int i=0; i<15; i++)
    {
        p1 = popcurrent.position[i];
        p2 = popcurrent.position[i+1];
        distancex = pow((Map[p1][1] - Map[p2][1]), 2);
        distancey = pow((Map[p1][2] - Map[p2][2]), 2);
        distance = distance + sqrt(distancex + distancey);
    }

    return distance;
}                             	// end x function                            	// end of y function

void *pickchroms(chrom popcurrent[2])   	// pickchroms takes a pointer to array of chroms
{
    int i;
    chrom temp;                            	//temp chrome to use in sorting

    for(i=0; i<2; i++)               		//sorting the given set due to fitness
    {
        if(popcurrent[i+1].fit<popcurrent[i].fit)
        {
            temp=popcurrent[i+1];
            popcurrent[i+1]=popcurrent[i];
            popcurrent[i]=temp;

        }   // end of if
    }                // end of for loop

    for(i=0; i<2; i++)
        printf("\nSorting:popnext[%d] fitness=%d",i,popcurrent[i].fit);   	//printing the result
    printf("\n");                 //print new line
    //flushall();                                                       //flush the input buffer
    return(0);
}                       //end of pick chromes function

void *crossover(chrom popnext[2]) // crossover function takes a pointer to array of chromes
{
    int random;
    int i;
    random=rand();                                  	//random cross over point
    random=((random%15)+1);                    		// cross point should be between (1 - 5)
    for(i=0; i<random; i++)                     	//crossing the bits below the cross point index
    {
        popnext[0].position[i]=popnext[1].position[i];        	//child 1 cross over

    } // end of for

    for(i=random; i<16; i++)                        	// crossing the bits beyond the cross point index
    {
        popnext[1].position[i]=popnext[0].position[i];     	// child 1 cross over

    }    // end of for

    for(i=0; i<2; i++)
        popnext[i].fit=x(popnext[i]);     	// calculating the fitness values for the new set

    for(i=0; i<2; i++)
        printf("\nCrossOver popnext[%d]=%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d    fitness = %lf",i,
               popnext[i].position[0],popnext[i].position[1],popnext[i].position[2],popnext[i].position[3],popnext[i].position[4],popnext[i].position[5],
               popnext[i].position[6],popnext[i].position[7],popnext[i].position[8],popnext[i].position[9],popnext[i].position[10],popnext[i].position[11],
               popnext[i].position[12],popnext[i].position[13],popnext[i].position[14],popnext[i].position[15],
               popnext[i].fit);
    // printing the bits, value and fitness for the chromes of the new set

    return(0);
}                  // end crossover function

void *mutation(chrom popnext[2])   // mutation funtion given a pointer to array of chromes
{
    printf("Mutation\n");
    int random;
    int row,col;
    random=rand()%50;                  //random value is between ( 0 - 49 )

    if (random==25)    // Suppusiong Probability of mutation is 2 %
    {
        col=rand()%16;                           	// random column (gene) choosing
        row=rand()%2;                           	// random row ( chrome ) choosing

        if (popnext[row].position[col]!=0 && popnext[row].position[col]!=15)          	// invert the bit to 0 if it was 1
        {
            if(popnext[row].position[col]%2 == 0)                                     // if even it increases value
                popnext[row].position[col]++;
            else                                                                        // if odd it decreases value
                popnext[row].position[col]--;
        }

        popnext[row].fit=x(popnext[row]);   	// calculate the fitness for the mutated chrome

        printf("\nMutation occured in popnext[%d] bit[%d]:=%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d    fitness=%d",
               row,col,
               popnext[row].position[0],popnext[row].position[1],popnext[row].position[2], popnext[row].position[3],popnext[row].position[4],popnext[row].position[5],
               popnext[row].position[6],popnext[row].position[7],popnext[row].position[8], popnext[row].position[9],popnext[row].position[10],popnext[row].position[11],
               popnext[row].position[12],popnext[row].position[13],popnext[row].position[14], popnext[row].position[15],
               popnext[row].fit);

        // print the chrome index,bits,value, fintness of the mutated chrome
    }         	// end of if

    return(0);
}                       //end of mutation
