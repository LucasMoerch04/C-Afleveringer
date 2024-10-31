#include <stdio.h>
#include <math.h>

// Initiate prototypes
void print_numbers(double *array, int length);
void print_points(double *xs, double *ys, int length);
void dists(double *xs, double *ys, int length, double *ds);

int main(void){

    double xs[] = {0,7,3,8,1};
    double ys[] = {4,0,3,3,5};
    int length = 5;

    printf("xs:\n");
    print_numbers(xs, length);
    printf("\nys:\n");
    print_numbers(ys, length);

    printf("\nPoints:\n");
    print_points(xs, ys, length);

    double ds[length-1];
    dists(ys,xs,length,ds);
    printf("\nDists:\n");
    print_numbers(ds,length-1);

    return 0;
}

// Function to print every double in given array
void print_numbers(double *array, int length){
    for (int i = 0; i < length; i++){
        printf("%lf\n", array[i]);
    }
}

// Function to print combined points in given arrays
void print_points(double *xs, double *ys, int length){
    for (int i = 0; i < length; i++){
        printf("(%lf, %lf)\n", xs[i], ys[i]);
    }    
}

// Function to calculate lines made by given points in arrays
void dists(double *xs, double *ys, int length, double *ds){
    for (int i = 0; i < length - 1; i++){
        double delta_x = xs[i] - xs[i+1];
        double delta_y = ys[i] - ys[i+1];
        
        ds[i] = sqrt(delta_x*delta_x + delta_y*delta_y);
    }  
}