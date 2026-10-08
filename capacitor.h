
#ifndef capacitor_h
#define capacitor_h

//this is where i create the struct for the capacitor.
struct _capacitor {
  double *time; //time array
  double *voltage; //voltage array
  double *current; //current array
  double C; // value of capacitor.
};

typedef struct _capacitor Capacitor;


#endif //PROJECT_ONE_ECE231L_CAPACITOR_H