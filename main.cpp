//PROJECT 1 ECE231L
#include <iostream>
#include <iomanip> // this libary helps with scientific notation.
#include "capacitor.h"
using namespace std; //using name space so i dont need to keep put ::std.

//prototyping my functions
void allocate_capacitor(Capacitor &cap , int step);
void free_capacitor(Capacitor &cap);
void outputs_capacitor(Capacitor &cap , const Capacitor &cap_v , int steps , int interval);


int main() {

    //intializing given values
    const double dt = 1e-10; // time steps in seconds
    const double final_time = 5e-6; // final time

    //i made this a static cast so it drops the decimal because you cant have half steps
    const double steps = static_cast <int> (final_time / dt); // this is the 50000 steps

    const double resistance = 1e3; // resistance value
    const double c_val = 100e-12; // capacator value
    const double I_cur = 1e-2; // current value
    const double V_0 = 10; // volatage value.

    //constant current source.
    Capacitor cap;
    cap.C = c_val;
    //this is where i allocate space  for the constate current.
    allocate_capacitor(cap, steps);

    cap.time[0] = 0;
    cap.voltage[0] = 0;
    cap.current[0] = I_cur;

    //this is for the calculations for the constant current supply
    for (int i = 0; i < steps - 1; i++) {

        cap.time[i + 1] = (i + 1) * dt;

        cap.current[i + 1] = I_cur; // Current remains constant

        cap.voltage[i + 1] = cap.voltage[i] + (cap.current[i] * dt / cap.C);
    }

    //this is for the constant voltage source supply
    Capacitor cv_cap;
    cv_cap.C = c_val;
    //this is where i allocate space fot the constant voltage.
    allocate_capacitor(cv_cap, steps);

    cv_cap.time[0] = 0;
    cv_cap.current[0] = V_0 / resistance;
    cv_cap.voltage[0] = 0;

    //calculates the constant volage supply
    for (int i = 0; i < steps - 1; i++) {

        cv_cap.time[i + 1] = (i + 1) * dt;

        cv_cap.current[i + 1] = cv_cap.current[i] - (cv_cap.current[i] / (resistance * cv_cap.C)) * dt;

        cv_cap.voltage[i + 1] = V_0 - (cv_cap.current[i + 1] * resistance);

    }

    //prints out the data from the voltage sources
    outputs_capacitor(cap , cv_cap , steps ,200);

    //frees the memory of the variables.
    free_capacitor(cap);
    free_capacitor(cv_cap);

    return 0;
}

//this function allocates memory for my capacator values.
void allocate_capacitor(Capacitor &cap , int step){

    cap.time = new double[step];

    cap.voltage = new double[step];

    cap.current = new double[step];
}

//this void is to free the memory.
void free_capacitor(Capacitor &cap) {
    //this frees all the variables in the struct.
    delete[] cap.time;
    delete[] cap.voltage;
    delete[] cap.current;

    //sets everything back to zero.
    cap.time = 0;
    cap.voltage = 0;
    cap.current = 0;
}

//function that prints out the data.
void outputs_capacitor(Capacitor &cap , const Capacitor &cap_v , int steps , int interval) {
    //this prints out the first case

    cout << scientific; // this makes the format in scientific notation.

    cout <<"============ Constant current circuit ============== \n"<<endl;

    //this makes it more clear to what the numbers are.
    cout<<"Step:\tTime:\t\tVoltage:\t\tCurrent:"<<endl;

    //uses a for loop to go through the array and print out the data.
    for (int i = 0; i < steps; i = i + interval) {

        cout << i << "\t" << cap.time[i] << "\t" << cap.voltage[i] << "\t" << cap.current[i] << endl;

    }

    //this prints out the se4cond case
    cout<<"\n";
    cout <<"===================================================="<<endl;

    cout << "========= Constant voltage circuit ================= \n"<<endl;
    cout <<"Step:\tTime:\t\tVoltage:\t\tCurrent:\t"<<endl;

    for (int i = 0; i < steps; i = i + interval) {

        cout << i << "\t" << cap_v.time[i] << "\t " << cap_v.voltage[i] << "\t" << cap_v.current[i] << endl;

    }

}








