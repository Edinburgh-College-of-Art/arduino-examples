//==============================================================================
/*
 * Feather M0 Timer Interrupt
 * 
 * This example demonstrates the usage of timer interrupts on the Feather M0
 *
 * It is essentially a massively over engineered way to blink an LED on and off.
 * The real beauty is in the fact that this is the most guarenteed way to regularly
 * perform an operation at a set interval.
 * 
 * If you want to sample data, or output data at a sampling rate (e.g. audio)
 * then this is where you would start
 *
 * If you want to change what happens at the interrupt, look at TC3_Handler
 * 
 * You should not need to look at startTimer or setTimerFrequency unless
 * you want to understand the M0 architecture better.
 * 
 */
//==============================================================================
// Function Decleration
void TC3_Handler();                      // the function executed by the interrupt
void startTimer(int frequencyHz);        // setup the timed interrupt
void setTimerFrequency(int frequencyHz); // set the interrupt frequency
//==============================================================================
// Globals
bool isLEDOn = false;
bool altLEDState = true;
const uint8_t LED_PIN = A5;
const uint8_t ALT_LED_PIN = 6;
//==============================================================================
void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(ALT_LED_PIN, OUTPUT);
  startTimer(2);
}
//==============================================================================
void loop() {} // no loop required
//==============================================================================

void setTimerFrequency(int frequencyHz)
{
  //----------------------------------------------------------------------------
  // Timer constants
  const uint CPU_HZ = 48000000;          // sampling rate
  const uint TIMER_PRESCALER_DIV = 1024;
  //----------------------------------------------------------------------------
  int compareValue = (CPU_HZ / (TIMER_PRESCALER_DIV * frequencyHz)) - 1;
  TcCount16* TC = (TcCount16*) TC3;
  // Make sure the count is in a proportional position to where it was
  // to prevent any jitter or disconnect when changing the compare value.
  TC->COUNT.reg = map(TC->COUNT.reg, 0, TC->CC[0].reg, 0, compareValue);
  TC->CC[0].reg = compareValue;
  Serial.println(TC->COUNT.reg);
  Serial.println(TC->CC[0].reg);
  while (TC->STATUS.bit.SYNCBUSY == 1);
}
//==============================================================================
void startTimer(int frequencyHz)
{
  REG_GCLK_CLKCTRL = (uint16_t) (GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_ID_TCC2_TC3) ;
  while ( GCLK->STATUS.bit.SYNCBUSY == 1 ); // wait for sync

  TcCount16* TC = (TcCount16*) TC3;

  TC->CTRLA.reg &= ~TC_CTRLA_ENABLE;
  while (TC->STATUS.bit.SYNCBUSY == 1); // wait for sync

  // Use the 16-bit timer
  TC->CTRLA.reg |= TC_CTRLA_MODE_COUNT16;
  while (TC->STATUS.bit.SYNCBUSY == 1); // wait for sync

  // Use match mode so that the timer counter resets when the count matches the compare register
  TC->CTRLA.reg |= TC_CTRLA_WAVEGEN_MFRQ;
  while (TC->STATUS.bit.SYNCBUSY == 1); // wait for sync

  // Set prescaler to 1024
  TC->CTRLA.reg |= TC_CTRLA_PRESCALER_DIV1024;
  while (TC->STATUS.bit.SYNCBUSY == 1); // wait for sync

  setTimerFrequency(frequencyHz);

  // Enable the compare interrupt
  TC->INTENSET.reg = 0;
  TC->INTENSET.bit.MC0 = 1;

  NVIC_EnableIRQ(TC3_IRQn);

  TC->CTRLA.reg |= TC_CTRLA_ENABLE;
  while (TC->STATUS.bit.SYNCBUSY == 1); // wait for sync
}
//==============================================================================
// Interrupt executed by timer
void TC3_Handler()
{
  TcCount16* TC = (TcCount16*) TC3;
  // If this interrupt is due to the compare register matching the timer count
  // we toggle the LED.
  if (TC->INTFLAG.bit.MC0 == 1)
  {
    TC->INTFLAG.bit.MC0 = 1;
    // Write callback here!!!
    digitalWrite(LED_PIN, isLEDOn);
    digitalWrite(ALT_LED_PIN, altLEDState);
    isLEDOn = !isLEDOn;
    altLEDState = !altLEDState;
  }
}

