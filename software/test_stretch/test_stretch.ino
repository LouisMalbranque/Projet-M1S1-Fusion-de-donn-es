
/*
8 TERMS THAT NEEDS TO BE SPECIFY
 *1: an array of which dft need to be taken
 *2:size of an array
 *3:time interval between 2 reading in array in milliSECONDS
 *4:lower value of frequency range in Hz
 *5:upper value of frequency range in Hz
 *6:size of steps for frequency range
 *7:repeatation of a signal(minimum 1) higher number batter accuracy but increased solution time
 *8:  0 for no window, 1 for flat-top window, 2 for hann window, 3 for hamming window 
      (if you do not have any idea about selecting window keep default 3)
 example:
      dft(a,110,0.5,0,30,0.5,10,3);
      here a is an array of size 110 element to be checked for 0 Hz to 30 Hz with 0.5 step (0,0.5,1,1.5, ... ,29,29.5,30)
      10 repeatation and hamming window
      by- ABHILASH PATEL
*/
float dft(float a[],int arraysize,float interval,float f0,float fn,float stepsize,int detail,int window_status)
{
  float sum,sumi,sumr,sumti,sumtr,sumt=0;
  int j,k=0;
if(window_status==1)  //flat-top window
{
  for(int i=0;i<1+arraysize;i++)
  {
    float b=3.1415*i/(arraysize-1);
   a[i] = a[i]*( 1 - (1.93*cos(2*b)) + (1.29*cos(4*b)) - (0.388*cos(6*b)) + (0.028*cos(8*b)));
// Serial.println(a[i]);
  }
}

if(window_status==2) //hann window
{ 
  for(int i=0;i<1+arraysize;i++)
  {
   float b=2*3.1415*i/(arraysize-1);
   a[i] = a[i]*0.5*(1-cos(b));
  //Serial.println(a[i]);
  }
}

if(window_status==3)//hamming window
{ 
  for(int i=0;i<1+arraysize;i++)
  {
   float b=2*3.1415*i/(arraysize-1);
   a[i] = a[i]*(0.54-0.46*cos(b));
  //Serial.println(a[i]);
  }
}
  
for(float f=f0; f<=fn; f=f+stepsize)
     {
        
              for(int i=0;i<1+(arraysize*detail);i++)
              {
                j=i-k;
                if(j>=arraysize){k=k+arraysize;}
                sumti=a[j]*(sin(6.28*f*i*interval*0.001));
                sumtr=a[j]*(cos(6.28*f*i*interval*0.001));              
                sumi=sumi+sumti;
                sumr=sumr+sumtr; 
              }
     sum=sqrt(sumi*sumi+sumr*sumr)/(arraysize*detail);
     Serial.print(f);
     Serial.print("\t");
     Serial.println(sum);
     sumi=0;sumr=0;
     j=0;   k=0; 
     }
     
}




float data[250]; 
int i = 0;
long last = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  data[i] = analogRead(A0);
  i++;
  delay(12);
  if (millis() - last > 3000){
    Serial.println("dft");
    dft(data, 1000, 3, 0.1, 5, 0.1, 1, 0);
    i=0;
    last = millis();
  }
}

