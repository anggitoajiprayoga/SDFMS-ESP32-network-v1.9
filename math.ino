void parsing_setDateTime(String date, String time) {
  //2000-4-1
  String value_date = "-" + date;

  int batasdate1 = value_date.indexOf('-');
  int batasdate2 = value_date.indexOf('-', batasdate1 + 1);
  int batasdate3 = value_date.indexOf('-', batasdate2 + 1);
  int batasdate4 = value_date.indexOf('-', batasdate3 + 1);

  value_year = value_date.substring(batasdate1 + 1, batasdate2);
  value_month = value_date.substring(batasdate2 + 1, batasdate3);
  value_day = value_date.substring(batasdate3 + 1, batasdate4);

  //12:59:59
  String value_time = ":" + time;

  int batastime1 = value_time.indexOf(':');
  int batastime2 = value_time.indexOf(':', batastime1 + 1);
  int batastime3 = value_time.indexOf(':', batastime2 + 1);
  int batastime4 = value_time.indexOf(':', batastime3 + 1);

  value_hour = value_time.substring(batastime1 + 1, batastime2);
  value_minute = value_time.substring(batastime2 + 1, batastime3);
  value_second = value_time.substring(batastime3 + 1, batastime4);
}

void total_waktu(String state, int jam_awal, int menit_awal, int detik_awal, int jam_akhir, int menit_akhir, int detik_akhir, int tanggal_awal, int bulan_awal, int tahun_awal, int tanggal_akhir, int bulan_akhir, int tahun_akhir) {
  //dtk,mnt,jam,hari,tgl,bln,tahun
  tmElements_t tanggalPertama = {detik_awal, menit_awal, jam_awal, 0, tanggal_awal, bulan_awal, CalendarYrToTm(tahun_awal)};
  tmElements_t tanggalKedua = {detik_akhir, menit_akhir, jam_akhir, 0, tanggal_akhir, bulan_akhir, CalendarYrToTm(tahun_akhir)};
  tmElements_t selisih;
  breakTime(makeTime(tanggalKedua) - makeTime(tanggalPertama), selisih);

  if (state == "eng_operation") {
    selisih_jamhm = selisih.Hour;
    selisih_mnthm = selisih.Minute;
    selisih_dtkhm = selisih.Second;
    sprintf (selisih_hm, "%02d:%02d:%02d", selisih_jamhm, selisih_mnthm, selisih_dtkhm);
  }
  else if (state == "eng_idle") {
    selisih_jamidle = selisih.Hour;
    selisih_mntidle = selisih.Minute;
    selisih_dtkidle = selisih.Second;
    sprintf (selisih_idle, "%02d:%02d:%02d", selisih_jamidle, selisih_mntidle, selisih_dtkidle);
  }
  else if (state == "eng_off") {
    selisih_jamstandby = selisih.Hour;
    selisih_mntstandby = selisih.Minute;
    selisih_dtkstandby = selisih.Second;
    sprintf (selisih_standby, "%02d:%02d:%02d", selisih_jamstandby, selisih_mntstandby, selisih_dtkstandby);
  }
  else if (state == "dumping") {
    selisih_jamdumping = selisih.Hour;
    selisih_mntdumping = selisih.Minute;
    selisih_dtkdumping = selisih.Second;
    sprintf (selisih_dumping, "%02d:%02d:%02d", selisih_jamdumping, selisih_mntdumping, selisih_dtkdumping);
  }
}

void parsing_dumping() {
  String parse_dumpingOn = ":" + String(timer_dumpingOn);

  int batasdumping1On = parse_dumpingOn.indexOf(':');
  int batasdumping2On = parse_dumpingOn.indexOf(':', batasdumping1On + 1);
  int batasdumping3On = parse_dumpingOn.indexOf(':', batasdumping2On + 1);
  int batasdumping4On = parse_dumpingOn.indexOf(':', batasdumping3On + 1);

  jam_dumpingOn = parse_dumpingOn.substring(batasdumping1On + 1, batasdumping2On);
  mnt_dumpingOn = parse_dumpingOn.substring(batasdumping2On + 1, batasdumping3On);
  dtk_dumpingOn = parse_dumpingOn.substring(batasdumping3On + 1, batasdumping4On);

  String parse_dumpingOff = ":" + String(timer_dumpingOff);

  int batasdumping1Off = parse_dumpingOff.indexOf(':');
  int batasdumping2Off = parse_dumpingOff.indexOf(':', batasdumping1Off + 1);
  int batasdumping3Off = parse_dumpingOff.indexOf(':', batasdumping2Off + 1);
  int batasdumping4Off = parse_dumpingOff.indexOf(':', batasdumping3Off + 1);

  jam_dumpingOff = parse_dumpingOff.substring(batasdumping1Off + 1, batasdumping2Off);
  mnt_dumpingOff = parse_dumpingOff.substring(batasdumping2Off + 1, batasdumping3Off);
  dtk_dumpingOff = parse_dumpingOff.substring(batasdumping3Off + 1, batasdumping4Off);

  //2018-01-18
  String parse_tgldumpingOn = "-" + String(tanggal_dumpingOn);

  int batasdumping1tgl = parse_tgldumpingOn.indexOf('-');
  int batasdumping2tgl = parse_tgldumpingOn.indexOf('-', batasdumping1tgl + 1);
  int batasdumping3tgl = parse_tgldumpingOn.indexOf('-', batasdumping2tgl + 1);
  int batasdumping4tgl = parse_tgldumpingOn.indexOf('-', batasdumping3tgl + 1);

  tahun_dumpingOn = parse_tgldumpingOn.substring(batasdumping1tgl + 1, batasdumping2tgl);
  bulan_dumpingOn = parse_tgldumpingOn.substring(batasdumping2tgl + 1, batasdumping3tgl);
  hari_dumpingOn = parse_tgldumpingOn.substring(batasdumping3tgl + 1, batasdumping4tgl);

  String parse_tgldumpingOff = "-" + String(tanggal_dumpingOff);

  int batasdumping1tglOff = parse_tgldumpingOff.indexOf('-');
  int batasdumping2tglOff = parse_tgldumpingOff.indexOf('-', batasdumping1tglOff + 1);
  int batasdumping3tglOff = parse_tgldumpingOff.indexOf('-', batasdumping2tglOff + 1);
  int batasdumping4tglOff = parse_tgldumpingOff.indexOf('-', batasdumping3tglOff + 1);

  tahun_dumpingOff = parse_tgldumpingOff.substring(batasdumping1tglOff + 1, batasdumping2tglOff);
  bulan_dumpingOff = parse_tgldumpingOff.substring(batasdumping2tglOff + 1, batasdumping3tglOff);
  hari_dumpingOff = parse_tgldumpingOff.substring(batasdumping3tglOff + 1, batasdumping4tglOff);
}

void parsing_idle() {
  String parse_idleOn = ":" + String(timer_idleOn);

  int batasidle1On = parse_idleOn.indexOf(':');
  int batasidle2On = parse_idleOn.indexOf(':', batasidle1On + 1);
  int batasidle3On = parse_idleOn.indexOf(':', batasidle2On + 1);
  int batasidle4On = parse_idleOn.indexOf(':', batasidle3On + 1);

  jam_idleOn = parse_idleOn.substring(batasidle1On + 1, batasidle2On);
  mnt_idleOn = parse_idleOn.substring(batasidle2On + 1, batasidle3On);
  dtk_idleOn = parse_idleOn.substring(batasidle3On + 1, batasidle4On);

  String parse_idleOff = ":" + String(timer_idleOff);

  int batasidle1Off = parse_idleOff.indexOf(':');
  int batasidle2Off = parse_idleOff.indexOf(':', batasidle1Off + 1);
  int batasidle3Off = parse_idleOff.indexOf(':', batasidle2Off + 1);
  int batasidle4Off = parse_idleOff.indexOf(':', batasidle3Off + 1);

  jam_idleOff = parse_idleOff.substring(batasidle1Off + 1, batasidle2Off);
  mnt_idleOff = parse_idleOff.substring(batasidle2Off + 1, batasidle3Off);
  dtk_idleOff = parse_idleOff.substring(batasidle3Off + 1, batasidle4Off);

  //2018-01-18
  String parse_tglidleOn = "-" + String(tanggal_idleOn);

  int batasidle1tgl = parse_tglidleOn.indexOf('-');
  int batasidle2tgl = parse_tglidleOn.indexOf('-', batasidle1tgl + 1);
  int batasidle3tgl = parse_tglidleOn.indexOf('-', batasidle2tgl + 1);
  int batasidle4tgl = parse_tglidleOn.indexOf('-', batasidle3tgl + 1);

  tahun_idleOn = parse_tglidleOn.substring(batasidle1tgl + 1, batasidle2tgl);
  bulan_idleOn = parse_tglidleOn.substring(batasidle2tgl + 1, batasidle3tgl);
  hari_idleOn = parse_tglidleOn.substring(batasidle3tgl + 1, batasidle4tgl);

  String parse_tglidleOff = "-" + String(tanggal_idleOff);

  int batasidle1tglOff = parse_tglidleOff.indexOf('-');
  int batasidle2tglOff = parse_tglidleOff.indexOf('-', batasidle1tglOff + 1);
  int batasidle3tglOff = parse_tglidleOff.indexOf('-', batasidle2tglOff + 1);
  int batasidle4tglOff = parse_tglidleOff.indexOf('-', batasidle3tglOff + 1);

  tahun_idleOff = parse_tglidleOff.substring(batasidle1tglOff + 1, batasidle2tglOff);
  bulan_idleOff = parse_tglidleOff.substring(batasidle2tglOff + 1, batasidle3tglOff);
  hari_idleOff = parse_tglidleOff.substring(batasidle3tglOff + 1, batasidle4tglOff);
}

void parsing_hm() {
  String parse_hmOn = ":" + String(timer_hmOn);

  int batashm1On = parse_hmOn.indexOf(':');
  int batashm2On = parse_hmOn.indexOf(':', batashm1On + 1);
  int batashm3On = parse_hmOn.indexOf(':', batashm2On + 1);
  int batashm4On = parse_hmOn.indexOf(':', batashm3On + 1);

  jam_hmOn = parse_hmOn.substring(batashm1On + 1, batashm2On);
  mnt_hmOn = parse_hmOn.substring(batashm2On + 1, batashm3On);
  dtk_hmOn = parse_hmOn.substring(batashm3On + 1, batashm4On);

  String parse_hmOff = ":" + String(timer_hmOff);

  int batashm1Off = parse_hmOff.indexOf(':');
  int batashm2Off = parse_hmOff.indexOf(':', batashm1Off + 1);
  int batashm3Off = parse_hmOff.indexOf(':', batashm2Off + 1);
  int batashm4Off = parse_hmOff.indexOf(':', batashm3Off + 1);

  jam_hmOff = parse_hmOff.substring(batashm1Off + 1, batashm2Off);
  mnt_hmOff = parse_hmOff.substring(batashm2Off + 1, batashm3Off);
  dtk_hmOff = parse_hmOff.substring(batashm3Off + 1, batashm4Off);

  String parse_tglhmOn = "-" + String(tanggal_hmOn);

  int batashm1tgl = parse_tglhmOn.indexOf('-');
  int batashm2tgl = parse_tglhmOn.indexOf('-', batashm1tgl + 1);
  int batashm3tgl = parse_tglhmOn.indexOf('-', batashm2tgl + 1);
  int batashm4tgl = parse_tglhmOn.indexOf('-', batashm3tgl + 1);

  tahun_hmOn = parse_tglhmOn.substring(batashm1tgl + 1, batashm2tgl);
  bulan_hmOn = parse_tglhmOn.substring(batashm2tgl + 1, batashm3tgl);
  hari_hmOn = parse_tglhmOn.substring(batashm3tgl + 1, batashm4tgl);

  String parse_tglhmOff = "-" + String(tanggal_hmOff);

  int batashm1tglOff = parse_tglhmOff.indexOf('-');
  int batashm2tglOff = parse_tglhmOff.indexOf('-', batashm1tglOff + 1);
  int batashm3tglOff = parse_tglhmOff.indexOf('-', batashm2tglOff + 1);
  int batashm4tglOff = parse_tglhmOff.indexOf('-', batashm3tglOff + 1);

  tahun_hmOff = parse_tglhmOff.substring(batashm1tglOff + 1, batashm2tglOff);
  bulan_hmOff = parse_tglhmOff.substring(batashm2tglOff + 1, batashm3tglOff);
  hari_hmOff = parse_tglhmOff.substring(batashm3tglOff + 1, batashm4tglOff);
}

void parsing_standby() {
  String parse_standbyOn = ":" + String(timer_standbyOn);

  int batas_standby1On = parse_standbyOn.indexOf(':');
  int batas_standby2On = parse_standbyOn.indexOf(':', batas_standby1On + 1);
  int batas_standby3On = parse_standbyOn.indexOf(':', batas_standby2On + 1);
  int batas_standby4On = parse_standbyOn.indexOf(':', batas_standby3On + 1);

  jam_standbyOn = parse_standbyOn.substring(batas_standby1On + 1, batas_standby2On);
  mnt_standbyOn = parse_standbyOn.substring(batas_standby2On + 1, batas_standby3On);
  dtk_standbyOn = parse_standbyOn.substring(batas_standby3On + 1, batas_standby4On);

  String parse_standbyOff = ":" + String(timer_standbyOff);

  int batas_standby1Off = parse_standbyOff.indexOf(':');
  int batas_standby2Off = parse_standbyOff.indexOf(':', batas_standby1Off + 1);
  int batas_standby3Off = parse_standbyOff.indexOf(':', batas_standby2Off + 1);
  int batas_standby4Off = parse_standbyOff.indexOf(':', batas_standby3Off + 1);

  jam_standbyOff = parse_standbyOff.substring(batas_standby1Off + 1, batas_standby2Off);
  mnt_standbyOff = parse_standbyOff.substring(batas_standby2Off + 1, batas_standby3Off);
  dtk_standbyOff = parse_standbyOff.substring(batas_standby3Off + 1, batas_standby4Off);

  //2018-01-18
  String parse_tglstandbyOn = "-" + String(tanggal_standbyOn);

  int batasstandby1tgl = parse_tglstandbyOn.indexOf('-');
  int batasstandby2tgl = parse_tglstandbyOn.indexOf('-', batasstandby1tgl + 1);
  int batasstandby3tgl = parse_tglstandbyOn.indexOf('-', batasstandby2tgl + 1);
  int batasstandby4tgl = parse_tglstandbyOn.indexOf('-', batasstandby3tgl + 1);

  tahun_standbyOn = parse_tglstandbyOn.substring(batasstandby1tgl + 1, batasstandby2tgl);
  bulan_standbyOn = parse_tglstandbyOn.substring(batasstandby2tgl + 1, batasstandby3tgl);
  hari_standbyOn = parse_tglstandbyOn.substring(batasstandby3tgl + 1, batasstandby4tgl);

  String parse_tglstandbyOff = "-" + String(tanggal_standbyOff);

  int batasstandby1tglOff = parse_tglstandbyOff.indexOf('-');
  int batasstandby2tglOff = parse_tglstandbyOff.indexOf('-', batasstandby1tglOff + 1);
  int batasstandby3tglOff = parse_tglstandbyOff.indexOf('-', batasstandby2tglOff + 1);
  int batasstandby4tglOff = parse_tglstandbyOff.indexOf('-', batasstandby3tglOff + 1);

  tahun_standbyOff = parse_tglstandbyOff.substring(batasstandby1tglOff + 1, batasstandby2tglOff);
  bulan_standbyOff = parse_tglstandbyOff.substring(batasstandby2tglOff + 1, batasstandby3tglOff);
  hari_standbyOff = parse_tglstandbyOff.substring(batasstandby3tglOff + 1, batasstandby4tglOff);
}
