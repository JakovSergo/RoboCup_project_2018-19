//debugged drive function

#define MAX_SPEED 255


int PWM_pins [4] = { 2, 3, 4, 5};
int motor_in_pins [4][2] = {
  {22, 23 }, // 22 and 23 for Motor1
  {24, 25},
  {30, 31},
  {32, 33}
};
int stdby_pins [2] = {26, 34};




double mass = 0.685; //mass of the robot


void  drive (double ax, double ay, double omega, double speedLimit){ //speedLimit is a number from 0 to 1, indicating percentage of MAX_SPEED
      int i;
      int j;
      double maxWeight = 0.0;
      double val_vector[3];
      double f_weights [4];
      int motor_in [4][2]; //direction
      int wheel_speed[4];
  
      //  Moore - Penrose inverse matrix of coefficients multiplied with the mass of the robot, calculated for the following values:
      //mass = 0.685 kg, radius = 9 cm, inertia = 0.5*mass*pow(radisu,2)
      double inv_koef [4][3]= { 
       {-0.2422,0.2422 ,0.0077},
       {-0.2422,-0.2422 ,0.0077},
       {0.2422,-0.2422 ,0.0077},
       {0.2422,0.2422 ,0.0077}
        };

        digitalWrite(stdby_pins[0], LOW);
        digitalWrite(stdby_pins[1], LOW);
        
       val_vector [0] = ax;
       val_vector [1] = ay;
       val_vector [2] = omega;
        for(i = 0; i<4; i++){
          f_weights[i] = 0;
          for(j = 0; j<3; j++){

          f_weights[i] = f_weights[i] + inv_koef[i][j]*val_vector[j];
        }
        }

       for(i=0; i<4; i++){
        if (abs(f_weights[i]) > maxWeight){
          maxWeight = abs(f_weights[i]);
        }
       }

       for(i=0; i<4; i++){
       wheel_speed[i] = (int)MAX_SPEED * speedLimit / maxWeight * f_weights[i];
       }

       for(i=0; i<4; i++){
        if(wheel_speed[i]>0){
          motor_in[i][0] = 0;
          motor_in[i][1] = 1;
        }else if(wheel_speed[i]<0){
          motor_in[i][0] = 1;
          motor_in[i][1] = 0;
          wheel_speed[i]=-wheel_speed[i];
        }

        
       }
        for(i=0; i<4; i++){
        analogWrite(PWM_pins[i], wheel_speed[i]);
        digitalWrite(motor_in_pins[i][0], motor_in[i][0]);
        digitalWrite(motor_in_pins[i][1], motor_in[i][1]);
        }

        

        digitalWrite(stdby_pins[0], HIGH);
        digitalWrite(stdby_pins[1], HIGH);
      
     
    return;
}





void setup() {
  Serial.begin(9600);
  int i;
  pinMode(LED_BUILTIN, OUTPUT);
        for(i=0; i<4; i++){
         
        pinMode(PWM_pins[i], OUTPUT);
        pinMode(motor_in_pins[i][0], OUTPUT);
        pinMode(motor_in_pins[i][1],OUTPUT);
        }

        for(i=0; i<2; i++){
        pinMode(stdby_pins [i], OUTPUT);
        }
   

    
}


void loop() {

}


