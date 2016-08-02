
int sensorPin = A0;                                               //take analog readings from pin A0                                          
int Rsense = 2500;                                                //Sense resistor value!!! 
float R0 = 1000;                                                  //Reistance (ohms) at 0* C
float A = 0.00381;                                                //Constants for converting resistance to temperature 
float B = -0.000000602; 
float voltage;
float current;
float rtd;
float temperature;
int goalbit = 628;                                                //Goalbit is at hi temp generated from heat shrink heater.  




void setup()
{
  Serial.begin(9600);                                                             //Start the serial connection with the computer -- baud rate 9600
  pinMode(4, OUTPUT);                                                             //pin 4 for turning heaters on/off (ACTUALLY CONTROLS THE RELAY)
  analogReference(INTERNAL);                                                      //Voltage reference 1.1V from inside the arduino
}
 
void loop()                                                                       // run over and over again
{
                                                                                  //getting the voltage reading from the temperature sensor
 int reading = analogRead(sensorPin); 
 Serial.println(reading);                                                         //display integer val (0-1023) representing analog voltage


 float voltage = (reading/930.0);                                                  //Divide analog read by 930 to generate a voltage between 0 and 5V
 Serial.print(voltage); Serial.println(" volts");                                  //Print out the voltage

 float current = ((2.048-voltage)/(Rsense));                                      //Calculate current by taking voltage drop across Rsense and dividing by Rsense
 float rtd = voltage/current;                                                     //Calculate rtd resistance by dividing voltage by current

 float temperature = (-R0*A+sqrt(sq(R0)*sq(A)-4*R0*B*(R0-rtd)))/(2*R0*B);         //Calculate temp from Callendar-Van Dusen Equation
 Serial.print(temperature); Serial.println(" degrees C");                         //Print deg. C
 Serial.println();


 if(reading < goalbit){                                                           //refine precision for temperatures and figure out at what temp you want heaters to turn on
    digitalWrite(4, HIGH);
    Serial.println("Heater ON");
  }
  else{
    Serial.println("Heater OFF");
    digitalWrite(4, LOW); 
  }
  

 delay(1000);

                                                    
 


}
