void setup_rtc() {
  Rtc.Begin();
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  printDateTime(compiled);
  Serial.println(String(waktux));
  Serial.println(String(tanggalx));

  if (!Rtc.IsDateTimeValid())
  {
    eror_rtc = true;
    if (Rtc.LastError() != 0)
    {
      Serial.print("RTC communications error = ");
      Serial.println(Rtc.LastError());
    }
    else
    {
      eror_rtc = false;
      Serial.println("RTC lost confidence in the DateTime!");
      Rtc.SetDateTime(compiled);
    }
  }
}

void loop_RTC() {
  RtcDateTime now = Rtc.GetDateTime();
  printDateTime(now);
  Year = now.Year();
  Month = now.Month();
  Day = now.Day();
  Hour = now.Hour();
  Minute = now.Minute();
  Second = now.Second();

  times = String(waktux);
  dates = String(tanggalx);
  date_time = dates + " " + times;
}

#define countof(a) (sizeof(a) / sizeof(a[0]))
void printDateTime(const RtcDateTime& dt)
{
  snprintf_P(tanggalx,
             countof(tanggalx),
             PSTR("%04u-%02u-%02u"), 
             dt.Year(),
             dt.Month(),
             dt.Day());

  snprintf_P(waktux,
             countof(waktux),
             PSTR("%02u:%02u:%02u"), 
             dt.Hour(),
             dt.Minute(),
             dt.Second() );
}
