/*Herkese iyi çalışmalar diliyorum.
 Sabri Genç
 */
#include <LiquidCrystal_I2C.h>
#include <IRremote.h>


#define kabul_tusu 95 
#define sag_yon_tusu 159
#define sol_yon_tusu 223

struct pinler {
  const byte pinler[12] PROGMEM={2,3,4,5,6,7,8,9,
                               A0,A1,A2};
};

// 6.pin motor 1 etkinleştirme pinidir.
// 8.pin motor 1 hareket pinidir.
// 7.pin motor 2 etkinleştirme pinidir.
// 9.pin motor 2 hareket pinidir.

struct pinler pin;

union sensor_degerler {

  float sicaklik1,sicaklik2,batarya_durumu;
  byte kumanda_gelen;
};
union sensor_degerler sens;
byte ortalama_birinci_oda_sicaklik=15;byte ortalama_ikinci_oda_sicaklik=15;
IRrecv kumanda(pin.pinler[0]);
decode_results kaynak;
LiquidCrystal_I2C  lcd(32,16,2);
char ekran_karakterleri[]={'<','>','E'};
int sayac=8;
bool bayrak=false;
bool klima_durum=false;bool isik_durum=false;
bool isik_durum2=false;
bool klima_durum2=false;
unsigned long zaman=0;
int sicaklik1,sicaklik2;
bool klima_cikis1=false;bool klima_cikis2=false;
void setup()
{
  Serial.begin(9600);
  if(!Serial)
  {
    Serial.println(F("Seri haberlesme baslatilamadi"));
    while(1) lcd.clear();
  }
  else
  {
    for(int i=0; i<12; i++)
    {
      if(i>=0 and i<8) pinMode(pin.pinler[i],OUTPUT);
      else pinMode(pin.pinler[i],INPUT);
    }
    digitalWrite(pin.pinler[4],HIGH);digitalWrite(pin.pinler[5],HIGH);
    kumanda.enableIRIn();kumanda.start();
    baslatma_ekrani(); 
 
  }
}

void loop()
{                                    
  ekran_yonetimi();
  delay(1);

}

void baslatma_ekrani() {
 
  if(!bool(0))
  {
    lcd.init();lcd.backlight();lcd.noBlink();
    lcd.setCursor(4,0);lcd.print(F("AKILLI EV"));
    for(int i=4; i<13; i++)
    {
      lcd.setCursor(i,1);lcd.print(F("*"));
      delay(45);
    }
  }
    
}

void ekran_yonetimi() {
  
  
  if(!bool(0))
  {
    if(bayrak==false)
    {
      ilk_ekran_hatti();
      bayrak=!bayrak;
 
    }
    if(bayrak==true)
    { 
      zaman_fonksiyonu();
      buradan8:
      if(kumanda.decode(&kaynak))
      {
        sens.kumanda_gelen=kaynak.value;
        zaman_fonksiyonu();
        if(sens.kumanda_gelen==159)
        {
          sayac++;
          if(sayac>9) sayac=8;
        }
        if(sens.kumanda_gelen==223)
        {
          sayac--;
          if(sayac<7) sayac=8;
        }
        if(sens.kumanda_gelen==95 and sayac==9)
        { 
          buradan7:
          buradan3:
          ikinci_ekran_hatti();
          sayac=7;
          do
          {
            if(kumanda.decode(&kaynak))
            {
              sens.kumanda_gelen=kaynak.value;
              if(sens.kumanda_gelen==159)
              { 
                sayac++;
              	if(sayac>10) sayac=7;
              }
              if(sens.kumanda_gelen==223)
              {
                sayac--;
                if(sayac<6) sayac=7;
              }
              if(sens.kumanda_gelen==95 and sayac==6)
              {
                sayac=7;
                ilk_ekran_hatti();
                goto buradan8;
              }
              if(sens.kumanda_gelen==95 and sayac==8)
              {
                buradan6:
                ucuncu_ekran_hatti();
                sayac=7;
                while(true)
                {
                  if(kumanda.decode(&kaynak))
                  {
                    sens.kumanda_gelen=kaynak.value;                  
                    if(sens.kumanda_gelen==159)
                    {
                      sayac++;
                      if(sayac>10) sayac=7;
                    }
                    if(sens.kumanda_gelen==223)
                    {
                      sayac--;
                      if(sayac<6) sayac=7;
                    }
                    if(sens.kumanda_gelen==95 and sayac==6)
                    {
                      goto buradan7;
                    }
                    if(sens.kumanda_gelen==95 and sayac==8)
                    {
                      buradan9:
                      lcd.clear();
                      otomasyon_ekran_hatti();
                      while(true)
                      {
                        if(kumanda.decode(&kaynak))
                        {
                          sens.kumanda_gelen=kaynak.value;
                          if(sens.kumanda_gelen==159)
                          {
                            sayac++;
                            if(sayac>8) sayac=15;
                            if(sayac==1) sayac=7;
                          }
                          if(sens.kumanda_gelen==223)
                          {
                            sayac--;
                            if(sayac<6) sayac=0;
                            if(sayac==14) sayac=7;
                          }
                          if(sens.kumanda_gelen==95 and sayac==0)
                          {
                            goto buradan6;
                          }
                          if(sens.kumanda_gelen==95 and sayac==6)
                          {
                            buradan10:
                            sicakik_ekran_hatti1();
                            sayac=7;
                            do
                            {
                              if(kumanda.decode(&kaynak))
                              {
                                sens.kumanda_gelen=kaynak.value;
                                
                                if(sens.kumanda_gelen==159)
                                {
                                  sayac++;
                                  if(sayac>8) sayac=15;
                                  else if(sayac==1) sayac=7;
                                  
                                }
                                if(sens.kumanda_gelen==223)
                                {
                                  sayac--;
                                  if(sayac<6) sayac=0;
                                  else if(sayac==14) sayac=7;
                                }
                                
                                if(sens.kumanda_gelen==95 and sayac==6)
                                {                  
                                  birinci_sicaklik_ekran();            
                                  while(true)
                                  {
                                    if(kumanda.decode(&kaynak))
                                    {
                                      sens.kumanda_gelen=kaynak.value;
                                      if(sens.kumanda_gelen==159)
                                      {
                                        sayac++;
                                        if(sayac==5) sayac=7;
                                      }
                                      if(sens.kumanda_gelen==223)
                                      {
                                        sayac--;
                                        if(sayac==6) sayac=4;
                                      }
                                      if(sens.kumanda_gelen==95 and sayac==4)
                                      {
                                        ortalama_birinci_oda_sicaklik++;
                                        if(ortalama_birinci_oda_sicaklik==26) ortalama_birinci_oda_sicaklik=26;
                                        lcd.setCursor(5,1);lcd.print(ortalama_birinci_oda_sicaklik);
                                      }
                                      if(sens.kumanda_gelen==95 and sayac==7)
                                      {
                                        ortalama_birinci_oda_sicaklik--;
                                        if(ortalama_birinci_oda_sicaklik<14) ortalama_birinci_oda_sicaklik=14;
                                        lcd.setCursor(5,1);lcd.print(ortalama_birinci_oda_sicaklik);
                                      }
                                      if(sens.kumanda_gelen==95 and sayac==9)
                                      {
                                        guncelleme_ekrani(); 
                                        delay(10);
                                        lcd.clear();
                                        goto buradan10;
                                      }
                                   
                                      delay(10);
                                      lcd.setCursor(sayac,1);
                                    }                       
                                    kumanda.resume();
                                    delay(1);
                                  }
                                }
                                if(sens.kumanda_gelen==95 and sayac==0)
                                {
                                  goto buradan9;
                                }
                                if(sens.kumanda_gelen==95 and sayac==15)
                                {
                                  sayac=7;
                                  buradan11:
                                  sicakik_ekran_hatti2();
                                  do
                                  {
                                    if(kumanda.decode(&kaynak))
                                    {
                                      sens.kumanda_gelen=kaynak.value;
									  if(sens.kumanda_gelen==159)
                                      {
                                        sayac++;
                                        if(sayac>8) sayac=15;
                                        else if(sayac==1) sayac=7;
                                      }
                                      if(sens.kumanda_gelen==223)
                                      {
                                        sayac--;
                                        if(sayac<6) sayac=0;
                                      }          
                                      if(sens.kumanda_gelen==95 and sayac==6)
                                      {        
                                        ikinci_sicaklik_ekran();
                                        while(true)
                                        {
                                          if(kumanda.decode(&kaynak))
                                          {
                                            sens.kumanda_gelen=kaynak.value;
                                            if(sens.kumanda_gelen==159)
                                            {
                                              sayac++;
                                       		  if(sayac==5) sayac=7;
                                            }
                                            else if(sens.kumanda_gelen==223)
                                            {
                                              sayac--;
                                              if(sayac==6) sayac=4;
                                            }          
                                            if(sens.kumanda_gelen==95 and sayac==4)
                                            {
                                              ortalama_ikinci_oda_sicaklik++;
                                              if(ortalama_ikinci_oda_sicaklik==26) ortalama_ikinci_oda_sicaklik=26;
                                              lcd.setCursor(5,1);lcd.print(ortalama_ikinci_oda_sicaklik);
                                            }
                                            if(sens.kumanda_gelen==95 and sayac==7)
                                            {
                                              ortalama_ikinci_oda_sicaklik--;
                                              if(ortalama_ikinci_oda_sicaklik<14) ortalama_ikinci_oda_sicaklik=14;
                                              lcd.setCursor(5,1);lcd.print(ortalama_ikinci_oda_sicaklik);
                                            }
                                            if(sens.kumanda_gelen==95 and sayac==9)
                                            {
                                              guncelleme_ekrani(); 
                                        	  delay(10);
                                        	  lcd.clear();
                                        	  goto buradan11;
                                            }
                                            lcd.setCursor(sayac,1);
                                          }
                                          kumanda.resume();delay(1);
                                        }
                                      }
                                      if(sens.kumanda_gelen==95 and sayac==0)
                                      {
                                        goto buradan10;
                                      }
                                      if(sens.kumanda_gelen==95 and sayac==8)
                                      {
                                        goto buradan9;
                                      }
                                      if(sens.kumanda_gelen==95 and sayac==15)
                                      {
                                        sayac=7;
                                        lcd.clear();lcd.setCursor(1,0);lcd.print(F("OTOMASYON KONTR"));
                                        lcd.setCursor(0,1);lcd.print(F("<"));
                                        lcd.setCursor(6,1);lcd.print(F("A"));
                                        lcd.setCursor(8,1);lcd.print(F("K"));
                                        if(!bool(0))
                                        {
                                          do
                                          {
                                            if(kumanda.decode(&kaynak))
                                            {
                                              sens.kumanda_gelen=kaynak.value;
                                              if(sens.kumanda_gelen==159)
                                              {
                                                sayac++;
                                                if(sayac>8) sayac=7;
                                                if(sayac==1) sayac=7;
                                              }
                                              if(sens.kumanda_gelen==223)
                                              {
                                                sayac--;
                                                if(sayac<6) sayac=0;      
                                              }
                                              if(sens.kumanda_gelen==95 and sayac==6)
                                              {
                                                lcd.clear();
                                                lcd.setCursor(0,0);lcd.print(F("OTOMASYONU KAPATMAK"));
                                                lcd.setCursor(0,1);lcd.print(F("ICIN GUC BUTONU"));
                                                delay(1000);lcd.noBacklight();
                                                while(true)
                                                {
                                                  sicaklik1=birinci_oda_sicaklik();
                                                  sicaklik2=ikinci_oda_sicaklik();
                                                  otomasyon_baslatma(ortalama_birinci_oda_sicaklik,sicaklik1,ortalama_ikinci_oda_sicaklik,sicaklik2);
                                                  if(kumanda.decode(&kaynak))
                                                  {
                                                    sens.kumanda_gelen=kaynak.value;
                                                    if(sens.kumanda_gelen==255)
                                                    {
                                                      lcd.backlight();
                                                 	  lcd.clear();
                                                      delay(50);
                                                      lcd.setCursor(0,0);lcd.print(F("OTOMASYON KAPALI"));
                                                      if(!bool(0))
                                                      {
                                                        bitWrite(PORTB,0,LOW);bitWrite(PORTB,1,LOW);
                                                      }
                                                      goto buradan9;
                                                    }
                                                  }   
                                                  kumanda.resume();
                                                  delay(5);
                                                }
                                               
                                              }
                                              if(sens.kumanda_gelen==95 and sayac==8)
                                              {
                                               	goto buradan9;
                                              }
                                              lcd.setCursor(sayac,1);
                                            }
                                            kumanda.resume();
                                            delay(1);
                                            
                                          }while(true);
                                        }
                                      }
                                      lcd.setCursor(sayac,1);
                                    }
                                    kumanda.resume();delay(1);
                                    
                                  }while(true);
                                }
                                if(sens.kumanda_gelen==95 and sayac==8)
                                {
                                  goto buradan9;
                                }
                                lcd.setCursor(sayac,1);
                              }
                              kumanda.resume();delay(1);
                  
                            }while(true);
                          }
                          lcd.setCursor(sayac,1);
                          
                        }
                        kumanda.resume();
                        delay(1);
                      }
                    }
                    if(sens.kumanda_gelen==95 and sayac==10)
                    {
                      buradan4:
                      isik_kontrol_hatti();
                      sayac=7;
                      do
                      {
                        if(kumanda.decode(&kaynak))
                        {
                          sens.kumanda_gelen=kaynak.value;
                          if(sens.kumanda_gelen==159)
                          {
                            sayac++;
                            if(sayac>8) sayac=15;
                            else if(sayac==1) sayac=7;
                          }
                          if(sens.kumanda_gelen==223)
                          {
                            sayac--;
                            if(sayac<6) sayac=0;
                            else if(sayac==14) sayac=7;
                          }
                          if(sens.kumanda_gelen==95 and sayac==6)
                          {
                            isik_durum=!isik_durum;
                            bitWrite(PORTD,4,HIGH);
                            ilk_isik();lcd.noBlink();
                            delay(2000);
                            goto buradan4;
                           
                          }
                          if(sens.kumanda_gelen==95 and sayac==8)
                          {
                            bitWrite(PORTD,4,LOW);
                            ilk_isik();lcd.noBlink();
                            delay(2000);
                            goto buradan4;                    
                          }
                          if(sens.kumanda_gelen==95 and sayac==0)
                          {
                            goto buradan6;
                          }
                          if(sens.kumanda_gelen==95 and sayac==15)
                          {
                            buradan5:
                            isik_kontrol_hatti2();
                            sayac=7;
                            while(true)
                            {
                              if(kumanda.decode(&kaynak))
                              {
                                sens.kumanda_gelen=kaynak.value;
                                if(sens.kumanda_gelen==159)
                                {
                                  sayac++;
                            	  if(sayac>8) sayac=15;
                                  else if(sayac==1) sayac=7;
                                }
                                if(sens.kumanda_gelen==223)
                                {
                                  sayac--;
								  if(sayac<6) sayac=0;
                                  else if(sayac==14) sayac=7;
                                }
                                if(sens.kumanda_gelen==95 and sayac==6)
                                {
                                  isik_durum2=!isik_durum2;
                                  bitWrite(PORTD,5,HIGH);
                                  ikinci_isik();                              
                                  delay(2000);goto buradan5;
                                }
                                if(sens.kumanda_gelen==95 and sayac==8)
                                {
                                  bitWrite(PORTD,5,LOW);
                                  ikinci_isik();
                                  delay(2000);goto buradan5;
                                }
                                if(sens.kumanda_gelen==95 and sayac==0)
                                {
                                  goto buradan4;
                                }
                                lcd.setCursor(sayac,1);
                              }
                              kumanda.resume();
                              delay(1);
                            }                           
                          }
                          lcd.setCursor(sayac,1);
                        }
                        kumanda.resume();
                        delay(1);
                      }while(true);
                    }
                    lcd.setCursor(sayac,1);
                  }
                  kumanda.resume();
                  delay(1);
                }
              }
              if(sens.kumanda_gelen==95 and sayac==10)
              {
                buradan:
                klima_kontrol_hatti();
                
                while(true)
                {
                  if(kumanda.decode(&kaynak))
                  {
                    sens.kumanda_gelen=kaynak.value;
                    if(sens.kumanda_gelen==159)
                    {
                      sayac++;
                      if(sayac>8) sayac=15;
                      else if(sayac==1) sayac=7;
                    }
                    if(sens.kumanda_gelen==223)
                    {
                      sayac--;
               		  if(sayac<6) sayac=0;
                      else if(sayac==14) sayac=7;                  
                    }
                    if(sens.kumanda_gelen==95 and sayac==6)
                    {
                      klima_durum=!klima_durum;
                      bitWrite(PORTB,0,HIGH);
                      ilk_klima();
                      delay(1000);
                      goto buradan;
                    }
                    if(sens.kumanda_gelen==95 and sayac==8)
                    {
                      bitWrite(PORTB,0,LOW);
                      ilk_klima();
                      delay(1000);
                      goto buradan;
                    }
                    if(sens.kumanda_gelen==95 and sayac==0)
                    {
                      sayac=7;
                      goto buradan3;
                    }
                    if(sens.kumanda_gelen==95 and sayac==15)
                    {
                      buradan2:
                      klima_kontrol_hatti2();
                      while(true)
                	  {
                  		if(kumanda.decode(&kaynak))
                  		{
                   		   sens.kumanda_gelen=kaynak.value;
                    	   if(sens.kumanda_gelen==159)
                    	   {
                      			sayac++;
                      			if(sayac>8) sayac=15;
                      			else if(sayac==1) sayac=7;
                    		}
                    		if(sens.kumanda_gelen==223)
                    		{
                      			sayac--;
               		  			if(sayac<6) sayac=0;
                      			else if(sayac==14) sayac=7;                  
                    		}
                    		if(sens.kumanda_gelen==95 and sayac==6)
                    		{
                      			klima_durum2=!klima_durum2;
                      			bitWrite(PORTB,1,HIGH);
                      			ikinci_klima();
                      			delay(1000);
                      			goto buradan2;
                    		}
                    		if(sens.kumanda_gelen==95 and sayac==8)
                    		{
                     			
                      			bitWrite(PORTB,1,LOW);
                      			ikinci_klima();
                      			delay(1000);
                      			goto buradan2;
                            }
       						if(sens.kumanda_gelen==95 and sayac==0)
                            {
                              goto buradan;
                            }
                          	
                    		lcd.setCursor(sayac,1);
                  		}
                  		kumanda.resume();
                  		delay(1);
                		}
                      
                    }
                    lcd.setCursor(sayac,1);
                  }
                  kumanda.resume();
                  delay(1);
                }
               
              }
              lcd.setCursor(sayac,1);
              
            }
            kumanda.resume(); 
            delay(1);
          }while(true);
        }
        
      }
      kumanda.resume();      
    }
  }
}

void zaman_fonksiyonu() {
 
  if(millis()-zaman>1000)
  {
    zaman=millis();
    lcd.setCursor(sayac,1);lcd.blink();
  }
}
void ilk_ekran_hatti() {
  
  lcd.noBlink();delay(5);
  lcd.clear();
  lcd.setCursor(4,0);lcd.print(F("ANA SAYFA"));
  lcd.setCursor(7,1);
  for(int i=0; i<2; i++)
  {
    lcd.print(ekran_karakterleri[i]);lcd.print(F(" "));
    delay(5);
  }
  lcd.blink();
  
}

void ikinci_ekran_hatti() {
 
  if(!bool(0))
  {
    lcd.noBlink();delay(5);
    lcd.clear();
    lcd.setCursor(2,0);lcd.print(F("KLIMA KONTROL"));
    lcd.setCursor(6,1);
    for(int i=0; i<3; i++)
  	{
       lcd.print(ekran_karakterleri[i]);lcd.print(F(" "));
       delay(5);
  	}  
  }
  lcd.blink();
  
}

void klima_kontrol_hatti()  {

  lcd.noBlink();sayac=7;
  delay(5);
  lcd.clear();
  if(!bool(0))
  {
    lcd.setCursor(0,0);lcd.print(F("1.ODA KLIMA "));
  	lcd.setCursor(6,1);lcd.print(F("A"));lcd.setCursor(8,1);
  	lcd.print(F("K"));
  	lcd.setCursor(0,1);lcd.print(F("<"));
  	lcd.setCursor(15,1);lcd.print(F(">"));
  }
  lcd.blink();
  
}
void klima_kontrol_hatti2()  {

  lcd.noBlink();sayac=7;
  delay(5);
  lcd.clear();
  if(!bool(0))
  {
    lcd.setCursor(0,0);lcd.print(F("2.ODA KLIMA"));
  	lcd.setCursor(6,1);lcd.print(F("A"));lcd.setCursor(8,1);
  	lcd.print(F("K"));
  	lcd.setCursor(0,1);lcd.print(F("<"));
  }  
  lcd.blink();
}
void ilk_klima()  {
 	
  lcd.noBlink();
  delay(5);
  if(klima_durum!=0)
  { 
    bool birinci_klima=bitRead(PORTB,0);
 	if(birinci_klima==true)
    {
      lcd.clear();lcd.print(F("1.KLIMA AKTIF"));
    }
  	else
  	{
      lcd.clear();lcd.print(F("1.KLIMA KAPALI"));
      
  	}
  }
  lcd.blink();
}

void ikinci_klima()  {
 	
  lcd.noBlink();
  delay(5);
  if(klima_durum2!=0)
  { 
    bool birinci_klima2=bitRead(PORTB,1);
 	if(birinci_klima2==true)
    {
      lcd.clear();lcd.print(F("2.KLIMA AKTIF"));
    }
  	else
  	{
      lcd.clear();lcd.print(F("2.KLIMA KAPALI"));
      
  	}
  }
  lcd.blink();
}


void ucuncu_ekran_hatti() {
 
  if(!bool(0))
  {
    lcd.noBlink();delay(5);
    lcd.clear();
    lcd.setCursor(2,0);lcd.print(F("ISIK KONTROL"));
    lcd.setCursor(6,1);
    for(int i=0; i<3; i++)
  	{
       lcd.print(ekran_karakterleri[i]);lcd.print(F(" "));
       delay(5);
  	}  
  }
  lcd.blink();
  
}

void isik_kontrol_hatti()  {

  lcd.noBlink();sayac=7;
  delay(5);
  lcd.clear();
  if(!bool(0))
  {
    lcd.setCursor(0,0);lcd.print(F("1.ODA ISIK "));
  	lcd.setCursor(6,1);lcd.print(F("A"));lcd.setCursor(8,1);
  	lcd.print(F("K"));
  	lcd.setCursor(0,1);lcd.print(F("<"));
  	lcd.setCursor(15,1);lcd.print(F(">"));
  }
  lcd.blink();
  
}

void ilk_isik()  {
 	
  lcd.noBlink();
  delay(5);
  if(isik_durum!=0)
  { 
    bool birinci_isik=bitRead(PORTD,4);
 	if(birinci_isik==true)
    {
      lcd.clear();lcd.print(F("1.ISIK AKTIF"));
    }
  	else
  	{
      lcd.clear();lcd.print(F("1.ISIK KAPALI"));
      
  	}
  }
  lcd.blink();
}


void isik_kontrol_hatti2()  {

  lcd.noBlink();sayac=7;
  delay(5);
  lcd.clear();
  if(!bool(0))
  {
    lcd.setCursor(0,0);lcd.print(F("2.ODA ISIK"));
  	lcd.setCursor(6,1);lcd.print(F("A"));lcd.setCursor(8,1);
  	lcd.print(F("K"));
  	lcd.setCursor(0,1);lcd.print(F("<"));
  }  
  lcd.blink();
}
void ikinci_isik()  {
  
  lcd.noBlink();
  delay(5);
  if(isik_durum2!=0)
  { 
    bool birinci_isik2=bitRead(PORTD,5);
 	if(birinci_isik2==true)
    {
      lcd.clear();lcd.print(F("2.ISIK AKTIF"));
    }
  	else
  	{
      lcd.clear();lcd.print(F("2.ISIK KAPALI"));
      
  	}
  }
  lcd.blink();
}

// otomasyon kontrol hatti

void otomasyon_ekran_hatti() {
  
  lcd.clear();delay(2);sayac=7;
  lcd.noBlink();
  if(!bool(0))
  {
    lcd.setCursor(0,0);lcd.print(F("OTOMASYON BOLUMU"));
  	lcd.setCursor(6,1);lcd.print(F("A"));lcd.setCursor(8,1);
  	lcd.print(F("K"));
  	lcd.setCursor(0,1);lcd.print(F("<"));
  }
  lcd.blink();
  
}

void sicakik_ekran_hatti1() {
 
  lcd.noBlink();sayac=7;
  delay(5);
  lcd.clear();
  if(!bool(0))
  {
    lcd.setCursor(0,0);lcd.print(F("1.ODA SICAKLIK"));
  	lcd.setCursor(6,1);lcd.print(F("A"));lcd.setCursor(8,1);
  	lcd.print(F("K"));
  	lcd.setCursor(0,1);lcd.print(F("<"));
  	lcd.setCursor(15,1);lcd.print(F(">"));
  }
  lcd.blink();
  
  
}
                                               

int birinci_oda_sicaklik() {
 
  if(!bool(0))
  {
    sens.sicaklik1=analogRead(pin.pinler[10]);
    sens.sicaklik1=(sens.sicaklik1/1023)*5000;
    sens.sicaklik1=sens.sicaklik1/10;
  }
  
  return sens.sicaklik1;
 
}
                                             
void birinci_sicaklik_ekran() {
  
 	lcd.clear();sayac=4;							  
 	lcd.setCursor(1,0);lcd.print(F("SICAKLIK AYARI")); 
    lcd.setCursor(4,1);lcd.print(F("+"));            
    lcd.setCursor(7,1);lcd.print(F("-"));lcd.setCursor(9,1);lcd.print(F("D")); 
}
                                             
void sicakik_ekran_hatti2() {
 
  lcd.noBlink();sayac=7;
  delay(5);
  lcd.clear();
  if(!bool(0))
  {
    lcd.setCursor(0,0);lcd.print(F("2.ODA SICAKLIK"));
  	lcd.setCursor(6,1);lcd.print(F("A"));lcd.setCursor(8,1);
  	lcd.print(F("K"));
  	lcd.setCursor(0,1);lcd.print(F("<"));lcd.setCursor(15,1);
    lcd.print(F(">"));
  }
  lcd.blink();
  
  
}

void ikinci_sicaklik_ekran() {
  
 	lcd.clear();sayac=4;							  
 	lcd.setCursor(1,0);lcd.print(F("SICAKLIK AYARI")); 
    lcd.setCursor(4,1);lcd.print(F("+"));            
    lcd.setCursor(7,1);lcd.print(F("-"));lcd.setCursor(9,1);lcd.print(F("D")); 
}
int ikinci_oda_sicaklik() {
 
  if(!bool(0))
  {
    sens.sicaklik2=analogRead(pin.pinler[9]);
    sens.sicaklik2=(sens.sicaklik1/1023)*5000;
    sens.sicaklik2=sens.sicaklik1/10;
  }
  return sens.sicaklik2;

}
void guncelleme_ekrani() {
  
  lcd.clear();lcd.setCursor(2,0);
  lcd.print("GUNCELLENIYOR");
  for(int i=3; i<13; i++) 
  {
    lcd.setCursor(i,1);lcd.print(F("*"));
    delay(40);
  }
  
}

void otomasyon_baslatma(int gelen1,int sicaklik1,int gelen2,int sicaklik2) {
  
  if(!bool(0)) //1. oda sıcaklık kontrolü
  {
    if(sicaklik1<gelen1)
  	{
      bitWrite(PORTB,0,LOW);
  	}
  	else if(sicaklik1>gelen1)
  	{
      bitWrite(PORTB,0,HIGH);
  	}
  }
  if(!bool(0)) // 2. oda sıcaklık kontrolü
  {
    if(sicaklik2<gelen2)
  	{
      bitWrite(PORTB,1,LOW);
  	}
  	else if(sicaklik2>gelen2)
  	{
      bitWrite(PORTB,1,HIGH);
  	}
  }
  
  
}

