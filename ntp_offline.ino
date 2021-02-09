#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
//#include <DNSServer.h>
#include <WebSocketsServer.h>
#include <stdio.h>
#include "index_html.h"
#include "nastaw_html.h"

// Replace with your network credentials
const char* ssid = "ESP_TEST";
const char* password = "ESP#TEST";
//const byte DNS_PORT = 53;

int d_tyg=0, d_h=0, d_m=0, d_s=0, pn=0, wt=0, sr=0, cz=0, pt=0, sb=0, nd=0;
int pn_od=0, wt_od=0, sr_od=0, cz_od=0, pt_od=0, sb_od=0, nd_od=0, pn_do=0, wt_do=0, sr_do=0, cz_do=0, pt_do=0, sb_do=0, nd_do=0;
//String info_z_serwera="";

//String strona1 = index_html1;
//String strona2 = index_html2;
String strona = index_html;
String strona_nastaw = nastaw_html;

//DNSServer dnsServer;
ESP8266WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

void ICACHE_RAM_ATTR onTimerISR()
{
  if(d_s<59) d_s=d_s+1;
  else
  {
    d_s=0;
    if(d_m<59) d_m=d_m+1;
    else
    {
      d_m=0;
      if(d_h<23) d_h=d_h+1;
      else
      {
        d_h=0;
        if(d_tyg<6) d_tyg=d_tyg+1;
        else d_tyg=0;
      }
    }
  }
  /*if(d_s%20==0)
  {
    char t[] = "t";
    webSocket.broadcastTXT(t, sizeof(t));
    Serial.print(t);
  }
  Serial.println("");
  Serial.print(d_h); Serial.print(":"); Serial.print(d_m); Serial.print(":"); Serial.println(d_s);*/
}

String dzielString(String czas)
{
  String czas_nowy;
  char godz[]={0};
  czas.toCharArray(godz, 6);
  char dzielnik[] = ":";
  char *pointer = strtok(godz, dzielnik);
  while(pointer != NULL)
  {
    czas_nowy = czas_nowy + pointer;
    pointer = strtok(NULL, dzielnik);
  }
  return czas_nowy;
}

/*void dzielenieStringa(String do_podzialu, int godzina, int minuta, int sekunda, int dzien)
{
  int i=0;
  char do_podzialu_char[]={11};
  char *schowek = strtok(do_podzialu_char, ":");
  char *tablica[4];
  while (schowek != NULL)
  {
    tablica[i++] = schowek;
    schowek = strtok(NULL, ":");
  }
  //godzina = tablica[1].toInt();
  //minuta = tablica[2].toInt();
  //sekunda = tablica[3].toInt();
  //dzien = tablica[4].toInt();
  Serial.println(tablica[1]);
  Serial.println(tablica[2]);
  Serial.println(tablica[3]);
  Serial.println(tablica[4]);
}

String odbierzInfo(uint8_t num, WStype_t type, uint8_t * payload, size_t length)
{
  info_z_serwera="";
  if(type == WStype_TEXT)
  {
    for(int i=0;i<length;i++) info_z_serwera += (char)payload[i];
    //Serial.print((char) payload[i]);
  }
  return info_z_serwera;
}*/

void harmonogram(void)
{
  switch(d_tyg)
  {
    case 1:
      if(pn==1&&((d_h*100+d_m)==pn_od)&&d_s==0) {Serial.print("D"); digitalWrite(2, LOW);}
      else if(pn==1&&(d_h*100+d_m)>=pn_do&&d_s==0) {Serial.print("d"); digitalWrite(2, HIGH);}
      break;
    case 2:
      if(wt==1&&((d_h*100+d_m)==wt_od)&&d_s==0) {Serial.print("D"); digitalWrite(2, LOW);}
      else if(wt==1&&(d_h*100+d_m)>=wt_do&&d_s==0) {Serial.print("d"); digitalWrite(2, HIGH);}
      break;
    case 3:
      if(sr==1&&((d_h*100+d_m)==sr_od)&&d_s==0) {Serial.print("D"); digitalWrite(2, LOW);}
      else if(sr==1&&(d_h*100+d_m)>=sr_do&&d_s==0) {Serial.print("d"); digitalWrite(2, HIGH);}
      break;
    case 4:
      if(cz==1&&((d_h*100+d_m)==cz_od)&&d_s==0) {Serial.print("D"); digitalWrite(2, LOW);}
      else if(cz==1&&(d_h*100+d_m)>=cz_do&&d_s==0) {Serial.print("d"); digitalWrite(2, HIGH);}
      break;
    case 5:
      if(pt==1&&((d_h*100+d_m)==pt_od)&&d_s==0) {Serial.print("D"); digitalWrite(2, LOW);}
      else if(pt==1&&(d_h*100+d_m)>=pt_do&&d_s==0) {Serial.print("d"); digitalWrite(2, HIGH);}
      break;
    case 6:
      if(sb==1&&((d_h*100+d_m)==sb_od)&&d_s==0) {Serial.print("D"); digitalWrite(2, LOW);}
      else if(sb==1&&(d_h*100+d_m)>=sb_do&&d_s==0) {Serial.print("d"); digitalWrite(2, HIGH);}
      break;
    case 0:
      if(nd==1&&((d_h*100+d_m)==nd_od)&&d_s==0) {Serial.print("D"); digitalWrite(2, LOW);}
      else if(nd==1&&(d_h*100+d_m)>=nd_do&&d_s==0) {Serial.print("d"); digitalWrite(2, HIGH);}
      break;
    default:
      break;
  }
  if (server.hasArg("start")&&server.arg("start").toInt()==1) {Serial.print("D"); digitalWrite(2, LOW);}
  if (server.hasArg("stop")&&server.arg("stop").toInt()==1) {Serial.print("d"); digitalWrite(2, HIGH);}
}

void setup(void)
{
  pinMode(2, OUTPUT);
//  delay(50);
  digitalWrite(2, HIGH);

  Serial.begin(9600);
  IPAddress ip(192,168,104,104);
  IPAddress subnet(255,255,255,0);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(ip, ip, subnet);
  WiFi.softAP(ssid, password); //begin WiFi access point
//  dnsServer.start(DNS_PORT, "*", ip);
  webSocket.begin();
//  Serial.print("Adres IP: ");
//  Serial.println(WiFi.softAPIP());
//  webSocket.onEvent(odbierzInfo);

  timer1_isr_init();
  timer1_attachInterrupt(onTimerISR);
  timer1_enable(TIM_DIV16, TIM_EDGE, TIM_LOOP);
  timer1_write(5000000);
   
  server.on("/", []()
  {
    //dla odbioru danych z serwera
    //dzielenieStringa(info_z_serwera/*, d_h, d_m, d_s, t_tyg*/);
    if (server.hasArg("d_tyg"))
    {
      d_tyg = server.arg("d_tyg").toInt();
      d_h = server.arg("d_h").toInt();
      d_m = server.arg("d_m").toInt();
      d_s = server.arg("d_s").toInt();
    }
    
    if (server.hasArg("pn")) { pn=server.arg("pn").toInt(); pn_od = (dzielString(server.arg("pn_od"))).toInt(); pn_do = (dzielString(server.arg("pn_do"))).toInt(); }
    if (server.hasArg("wt")) { wt=server.arg("wt").toInt(); wt_od = (dzielString(server.arg("wt_od"))).toInt(); wt_do = (dzielString(server.arg("wt_do"))).toInt(); }
    if (server.hasArg("sr")) { sr=server.arg("sr").toInt(); sr_od = (dzielString(server.arg("sr_od"))).toInt(); sr_do = (dzielString(server.arg("sr_do"))).toInt(); }
    if (server.hasArg("cz")) { cz=server.arg("cz").toInt(); cz_od = (dzielString(server.arg("cz_od"))).toInt(); cz_do = (dzielString(server.arg("cz_do"))).toInt(); }
    if (server.hasArg("pt")) { pt=server.arg("pt").toInt(); pt_od = (dzielString(server.arg("pt_od"))).toInt(); pt_do = (dzielString(server.arg("pt_do"))).toInt(); }
    if (server.hasArg("sb")) { sb=server.arg("sb").toInt(); sb_od = (dzielString(server.arg("sb_od"))).toInt(); sb_do = (dzielString(server.arg("sb_do"))).toInt(); }
    if (server.hasArg("nd")) { nd=server.arg("nd").toInt(); nd_od = (dzielString(server.arg("nd_od"))).toInt(); nd_do = (dzielString(server.arg("nd_do"))).toInt(); }
//    server.send(200, "text/html", strona1+"Czas otwarcia strony według serwera: "+d_h+":"+d_m+":"+d_s+strona2);
    server.send(200, "text/html", strona);
  });
  
  server.on("/nastaw_html", []()
  {
    server.send(200, "text/html", strona_nastaw);
  });
  
  server.begin();
}


 
void loop(void)
{
  webSocket.loop();
//  dnsServer.processNextRequest();
  server.handleClient();
/*  Serial.print("Pn: ");  Serial.print(pn);  Serial.print(" od: ");  Serial.print(pn_od);  Serial.print(" do: ");  Serial.println(pn_do);
  Serial.print("Wt: ");  Serial.print(wt);  Serial.print(" od: ");  Serial.print(wt_od);  Serial.print(" do: ");  Serial.println(wt_do);
  Serial.print("Sr: ");  Serial.print(sr);  Serial.print(" od: ");  Serial.print(sr_od);  Serial.print(" do: ");  Serial.println(sr_do);
  Serial.print("Cz: ");  Serial.print(cz);  Serial.print(" od: ");  Serial.print(cz_od);  Serial.print(" do: ");  Serial.println(cz_do);
  Serial.print("Pt: ");  Serial.print(pt);  Serial.print(" od: ");  Serial.print(pt_od);  Serial.print(" do: ");  Serial.println(pt_do);
  Serial.print("Sb: ");  Serial.print(sb);  Serial.print(" od: ");  Serial.print(sb_od);  Serial.print(" do: ");  Serial.println(sb_do);
  Serial.print("Nd: ");  Serial.print(nd);  Serial.print(" od: ");  Serial.print(nd_od);  Serial.print(" do: ");  Serial.println(nd_do);*/
  harmonogram();
  if(Serial.available()>0)
  {
    char silnik[] = {(char)Serial.read()};
    webSocket.broadcastTXT(silnik, sizeof(silnik));
  }
  //delay(1000);
}
