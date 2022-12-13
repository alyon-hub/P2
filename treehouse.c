#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Avriel Lyon
//9/28/2021
//P2 Tree House Walking

//For the max amount of trees you can have, N = (2n)
#define N 16

//struct to contain the coordinates of one tree
typedef struct tree {
    int x;
    int y;
}
tree;

//declaring functions
tree ** readInTrees(int numTrees);
tree * readTree();
double calculateDistance(tree ** treeArray, int i, int j);
double perm(int array[], int numTrees, int k, int used[]);
void precompDistance(tree ** treeArray, int numTrees);
double getDistance(int * array, int numTrees);

//save the distance of each combination here
double distance[N][N];

int main() {
    int numCases;
    struct tree ** treeArray;
    int numTrees;
    int i, k;

    scanf("%d", &numCases);

    for (i = 0; i < numCases; i++) {

        scanf("%d", &numTrees);
        numTrees = numTrees * 2;

        //get the coordinate values of each tree
        treeArray = readInTrees(numTrees);

        //precalculate the distance
        precompDistance(treeArray, numTrees);

        int used[N];

        //initialize used to zero, will equal one when number is used
        for (k = 0; k < N; k++) {
            used[k] = 0;
        }

        int order[N];

        //each relevant permutation will begin with 0
        order[0] = 0;
        
        //gets min distance
        //pass in 1 instead of 0 since we set order[0] to 0
        double minDistance = perm(order, numTrees, 1, used);

        //print to three decimal places
        printf("%.3lf\n", minDistance);
    }

    //free memory used
    for (i = 0; i < numTrees; i++) {
        free(treeArray[i]);
    }
    free(treeArray);

    return 0;
}

//makes an array of the tree struct
//based off of the previous smoothie assignment
tree ** readInTrees(int numTrees) {
    struct tree ** array = malloc(N * sizeof(struct tree * ));
    int i;

    for (i = 0; i < numTrees; i++) {
        array[i] = malloc(sizeof(struct tree * ));
        array[i] = readTree();
    }

    return array;
}

//makes the individual tree struct
tree * readTree() {
    struct tree * thisTree = malloc(sizeof(tree * ));

    scanf("%d %d", & thisTree->x, & thisTree->y);

    return thisTree;
}

//precalculates the distance and puts it into the distance array
void precompDistance(tree ** treeArray, int numTrees) {
    int i, j;

    for (i = 0; i < numTrees; i++) {
        for (j = 0; j < numTrees; j++) {
            distance[i][j] = calculateDistance(treeArray, i, j);
        }
    }
}

//calculates the distance
double calculateDistance(tree ** treeArray, int i, int j) {
    double ropeAmount = 0;

    //calculates the distance/rope amount using the formula given
    ropeAmount = sqrt(pow((treeArray[i]->x - treeArray[j]->x), 2) + pow((treeArray[i]->y - treeArray[j]->y), 2));

    return ropeAmount;
}

//adds the distances together for the permutation
double getDistance(int * array, int numTrees) {
    double result = 0;
    int i;

    //reads in each pair and adds each value
    for (i = 0; i < numTrees - 1; i++) {
        result += distance[array[i]][array[i + 1]];
        i++;
    }

    return result;
}

//Finds the minimum amount of distance to solve the problem
double perm(int array[], int numTrees, int k, int used[]) {
    int i;
    double newRes;

    //if the permutation array is full, get the distance
    if (k == numTrees) {
        return getDistance(array, numTrees);
    }

    //set high to compare each permutation result
    //since you could have 0,0 and -1000,1000 which would be 1414.214 on its own
    double res = 15000;

    //for even values in the array
    if (k % 2 == 0) {
        for (i = array[k - 2] + 1; i < numTrees; i++) {
            //if the number is used, don't use it again
            if (used[i]) {
                continue;
            }

            array[k] = i;

            //for when k is not 0, each even value is greater than the previous even value
            if(k != 0 && array[k] < array[k-2]) {
                continue;
            }

            used[i] = 1;

            //calls itself
            newRes = perm(array, numTrees, k + 1, used);

            //compares results
            if (newRes < res) {
                res = newRes;
            }

            //resets used
            used[i] = 0;
        }
    }

    //for odd values in the array
    else {
        for (i = array[k - 1] + 1; i < numTrees; i++) {
            //if the number is used, don't use it again
            if (used[i]) {
                continue;
            }

            array[k] = i;

            //each odd value is greater than the previous value
            if(array[k] < array[k-1]) {
                continue;
            }

            used[i] = 1;

            //calls itself
            newRes = perm(array, numTrees, k + 1, used);

            //compares results
            if (newRes < res) {
                res = newRes;
            }

            //resets used
            used[i] = 0;
        }
    }

    //return the distance for the correct permutation
    return res;
}

