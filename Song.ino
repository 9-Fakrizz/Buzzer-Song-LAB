#define LED 32
#define BUTTON 18
hw_timer_t *My_timer = NULL;

#define NOTE_A6  3520
#define NOTE_Gb6  3322
#define NOTE_G6   3700
#define NOTE_B6  3351
#define NOTE_C7  3100

int i = 0;
bool flag = false;
int speed_factor = 50;
int index_speed = 0;
int hz_factor = 2000;
String name_speed[5] = {"Snail","Slow","Normy","Rapid","Super Rap" };

int melody[28] ={NOTE_A6,NOTE_Gb6,NOTE_A6,NOTE_Gb6,
                        NOTE_A6,NOTE_Gb6,NOTE_A6,NOTE_Gb6,
                        NOTE_A6,NOTE_Gb6,NOTE_A6,NOTE_Gb6,
                        NOTE_A6,NOTE_Gb6,NOTE_A6,NOTE_Gb6,
                        
                        NOTE_G6,NOTE_G6,NOTE_G6,NOTE_G6,
                        
                        NOTE_C7,NOTE_C7,NOTE_B6,NOTE_G6,
                        
                        NOTE_A6,NOTE_A6,NOTE_A6,(hz_factor+1)
                        };

int durations[28] ={150,150,150,150
                  ,150,150,150,150,
                  150,150,150,150,
                  150,150,150,150,
                  
                  125,125,125,125,
                  
                  125,125,125,150,
                  150,150,300,150
                  };

// This is the Timer ISR. It is automatically called 
// on a timer alarm event.

void IRAM_ATTR IO_INT_ISR()
{
  flag = true;
}

void IRAM_ATTR onTimer(){
  digitalWrite(LED, !digitalRead(LED));
}

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  My_timer = timerBegin(0, 80, true);  // use tiemr 0 and set prescale to 80 so 1 tick is 1 uSec
  timerAttachInterrupt(My_timer, &onTimer, true); // point to the ISR
  // timerAlarmWrite(My_timer, 1047, true);  // set alarm every 1 sec
  // timerAlarmEnable(My_timer);  // enable the alarm

   pinMode(BUTTON, INPUT);
  attachInterrupt(BUTTON, IO_INT_ISR, RISING); // interrupt on rising edge
}

void loop() {

  timerAlarmWrite(My_timer, melody[i] - hz_factor  , true);  // set alarm every 1 sec
  timerAlarmEnable(My_timer);  // enable the alarm
  delay(durations[i]+200 - (index_speed * speed_factor));
  timerAlarmDisable(My_timer);
  delay(250 -(index_speed * speed_factor));
  i++;
  if(i == 27){
    i =0;
    delay(1000);
  }
  if(flag == true){  
    index_speed++;
    index_speed = index_speed % 5;
    Serial.println("Index_Speed : " +String(index_speed)+ " " + name_speed[index_speed]);  
    flag = false;
  }
  Serial.println("i >> "+String(i));
  

}
