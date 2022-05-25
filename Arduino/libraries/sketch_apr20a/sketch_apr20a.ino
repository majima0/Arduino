#define LED_PIN1 3
#define LED_PIN2 13
#define LED_PIN3 6
#define LED_PIN4 2
#define LED_PIN5 4
#define LED_PIN6 7

int led_pins[]={9,10,11};
int r=4;
int sample[10];
int x=0;
int MAX,MIN;
// 25,50,100,200
int z=0;
int avg=0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_PIN2,OUTPUT);
  pinMode(LED_PIN1,OUTPUT);
  pinMode(LED_PIN3,OUTPUT);
  pinMode(LED_PIN4,OUTPUT);
  pinMode(LED_PIN5,OUTPUT);
  for(int i=0;i<3;i++){
    pinMode(led_pins[i],OUTPUT);
  }
}

void maxmin(){
  MAX=0;
  MIN=1024;
  int sum=0;
  for(int j=0;j<r;j++){
    if(MAX<sample[j]){
      MAX=sample[j];
    }
    if(MIN>sample[j]){
      MIN=sample[j];
    }
    sum=sample[j];
    sample[j]=0;
  }
  avg=sum/r;
}

void Light2(int i){
  int k=0;
  int x=5;
  int l=25;
  int sw=1;
  int add=1;
  int L=0;
  int sw2=1;
  int limit_l = 5;
  int limit_h = 97;
  while(true){
    int j=analogRead(1);
    if(j>150){
      k++;
    }else{
      k=0;
    }
    if(k>3){
      break;
    }
    int i=analogRead(0);
    Serial.print(limit_l,DEC);
    Serial.print(",");
    Serial.println(limit_h,DEC);
    Serial.print(add,DEC);
    Serial.print(",");
    Serial.print(i,DEC);
    Serial.print(",");
    Serial.println(L,DEC);
    sw=(sw==1?-1:1);
    if(sw==1){
      L = x*add + l*sw;
      add += sw2;
    }else{
      L = x*add + l*sw;
    }
    
    if(L>255){
      int LL = L - 250;
      digitalWrite(LED_PIN2,HIGH);
      analogWrite(led_pins[0],HIGH);
      analogWrite(led_pins[1],HIGH);
      analogWrite(led_pins[2],HIGH); 
      analogWrite(LED_PIN3,LL);
    }else{
      if(add<30){
        digitalWrite(LED_PIN2,LOW);
        analogWrite(LED_PIN3,LOW);
      }else{
        digitalWrite(LED_PIN2,HIGH);
        analogWrite(led_pins[0],255-L);
        analogWrite(led_pins[1],255-L);
        analogWrite(led_pins[2],255-L); 
        analogWrite(LED_PIN3,LOW);
      }
    }
    if(limit_h==add){
      sw2=-1;
      if(i>600){
        limit_h--;
      }else if(i<500){
        limit_h++;
      }
    }else if(limit_l==add){
      sw2=1;
      if(i<500){
        limit_l++;
      }else if(600<i){
        limit_l--;
      }
    }
    if(limit_h<15){
      limit_h=15;
    }
    if(limit_l<5){
      limit_l=5;
    }else if(limit_h>97){
      limit_h=97;
    }else if(limit_l>=limit_h){
      limit_l=limit_h-10;
    }

    if(add<0){
      add=10;
    }else if(add>97){
      add=90;
    }
  }
}

void Reset(){
    digitalWrite(LED_PIN2,LOW);
    digitalWrite(LED_PIN3,LOW);
    analogWrite(led_pins[0],LOW);
    analogWrite(led_pins[1],LOW);
    analogWrite(led_pins[2],LOW);
}

int k=0;
void loop(){
  digitalWrite(LED_PIN1,HIGH);
  int i,j;
  digitalWrite(LED_PIN2,HIGH);
  digitalWrite(led_pins[0],HIGH);
  digitalWrite(led_pins[1],HIGH);
  i=analogRead(0);
  j=analogRead(1);
  Serial.print(i,DEC);
  Serial.print(",");
  Serial.println(j,DEC);
  digitalWrite(LED_PIN4,HIGH);
  if(j>150){
    k++;
  }else{
    k=0;
  }
  if(k>3){
    k=0;
    Reset();
    bool switch1=true;
    for(int s=0;s<1000000&&switch1;s++){
      i=analogRead(0);
      Light2(i);
      for(int ss=0;ss<10000;ss++){
        j=analogRead(1);
        if(j<100){
          break;
        }else if(ss==9999){
          switch1=false;
          Reset();
          digitalWrite(LED_PIN2,HIGH);
          digitalWrite(led_pins[1],HIGH);
 
          delay(3000);
          Reset();
        }
      }
    }
  }else{
    Reset();
  }
}
