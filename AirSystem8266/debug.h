// === STATUS LED ================================================
#ifndef DEBUG_LED
  #define LedBlinkHandle()
#else
unsigned long LastLedMillis  = 0;
unsigned int  LedBlinkPeriod = 250;
bool statusLedInited = false;
void LedBlinkHandle() {
  if(!statusLedInited) {
    statusLedInited = true;
    pinMode(DEBUG_LED, OUTPUT);
  } else {
    if(millis()-LastLedMillis>=LedBlinkPeriod) {
      digitalWrite(DEBUG_LED, !digitalRead(DEBUG_LED));
      LastLedMillis = millis();
    }
  }
}
void setLedPeriod(unsigned int _period) {
  LedBlinkPeriod = _period;
}
#endif

// === DEBUG =====================================================
#ifdef USE_DEBUG
  #ifndef PROGRAMM_NAME
    #define PROGRAMM_NAME "unknown"
  #endif
  #ifndef PROGRAMM_VERSION
    #define PROGRAMM_VERSION "unknown"
  #endif
  #ifndef PROGRAMM_AUTHOR
    #define PROGRAMM_AUTHOR "unknown"
  #endif
  #ifndef PROGRAMM_CONTACT
    #define PROGRAMM_CONTACT "unknown"
  #endif
  #ifndef DEBUG_BAUD_RATE
    #define DEBUG_BAUD_RATE 115200
  #endif
  #ifndef DEBUG
    #define DEBUG Serial
  #endif
  #ifndef DEBUG_TEST_PERIOD
  #define DEBUG_TEST_PERIOD   0
  #endif
  #ifndef DEBUG_INIT_DELAY
  #define DEBUG_INIT_DELAY   0
  #endif
  bool debugInited = false;
  unsigned long LastSerialMillis = 0;
  void DebugHandle() {
    LedBlinkHandle();
    if(!debugInited) {
      if(millis()>=DEBUG_INIT_DELAY*1000) {
        DEBUG.begin(DEBUG_BAUD_RATE);
        DEBUG.println("#=======================================");
        DEBUG.println("# Programm : " + String(PROGRAMM_NAME));
        DEBUG.println("# Version  : " + String(PROGRAMM_VERSION));
        DEBUG.println("# Author   : " + String(PROGRAMM_AUTHOR));
        DEBUG.println("# Contact  : " + String(PROGRAMM_CONTACT));
        DEBUG.println("#=======================================\r\n");
        debugInited = true;
        if(DEBUG_TEST_PERIOD) setLedPeriod((DEBUG_TEST_PERIOD*1000)/2);
        else setLedPeriod(500);
        LastSerialMillis = millis();
      }
    } else {
      if(DEBUG_TEST_PERIOD) {
        if(millis()-LastSerialMillis>=DEBUG_TEST_PERIOD*1000) {
          DEBUG.print("Time from start: ");
          DEBUG.print(millis()/1000);
          DEBUG.println("s");
          LastSerialMillis = millis();
        }
      }
    }
  }
#else
   struct {
    template<typename... ARGS> void begin(ARGS...) {}
    template<typename... ARGS> void print(ARGS...) {}
    template<typename... ARGS> void println(ARGS...) {}
    template<typename... ARGS> void printf(ARGS...) {}
    template<typename... ARGS> void write(ARGS...) {}
    template<typename... ARGS> int  available(ARGS...) {}
    template<typename... ARGS> byte read(ARGS...) {}
   } DEBUG;
   #define DebugHandle(...)
   #define pirntSerialTest(...)
#endif
