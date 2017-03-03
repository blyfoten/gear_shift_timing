#define CLUTCH_PIN 3
#define SHIFT_LAMP_PIN 2
#define BUZZER_PIN 4

// Tider i millisekunder
unsigned int time_to_2nd_gear = 1100;
unsigned int time_to_3nd_gear = 1600;
unsigned int time_to_4nd_gear = 2400;
unsigned int time_to_5nd_gear = 3700;

unsigned int lamp_on_time = 300;


unsigned long time_since_release = 0;
unsigned long release_time = 0;
boolean lamp_state_on = false;
boolean shift_in_progress = false;

void setup()
{
    pinMode(CLUTCH_PIN, INPUT_PULLUP);
    pinMode(SHIFT_LAMP_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
}

void loop()
{
    if ( digitalRead(CLUTCH_PIN) == LOW )
    {
        // Koppling nere
        release_time = millis(); 
        time_since_release = 0;
        shift_in_progress = true;
        digitalWrite(SHIFT_LAMP_PIN, LOW);
        noTone(BUZZER_PIN);
        lamp_state_on = false;
    }
    else if (shift_in_progress == true)
    {
        time_since_release = millis() - release_time;
    }
    
    if ( ( (time_since_release > time_to_2nd_gear ) &&
           (time_since_release < time_to_2nd_gear + lamp_on_time ) ) 
         || 
         ( (time_since_release > time_to_3nd_gear ) &&
           (time_since_release < time_to_3nd_gear + lamp_on_time ) ) 
         || 
         ( (time_since_release > time_to_4nd_gear ) &&
           (time_since_release < time_to_4nd_gear + lamp_on_time ) ) 
         || 
         ( (time_since_release > time_to_5nd_gear ) &&
           (time_since_release < time_to_5nd_gear + lamp_on_time ) ) )
    {
        if ( lamp_state_on == false ) 
        {
          lamp_state_on = true;
          digitalWrite(SHIFT_LAMP_PIN, HIGH);
          tone(BUZZER_PIN, 1000);
        }
    }
    else if ( lamp_state_on == true )
    {
        lamp_state_on = false;
        digitalWrite(SHIFT_LAMP_PIN, LOW);
        noTone(BUZZER_PIN);
    }
    if ( time_since_release > time_to_5nd_gear + lamp_on_time + 100 )
    {
        shift_in_progress = false;
    }
}
