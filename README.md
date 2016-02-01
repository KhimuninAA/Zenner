# Zenner
Arduino library (UNO Only) Modulated with a controllable duty cycle timer


ZENNER(int pin,int f,int t_on,int t_off);

pin   - arduino out pin;
f     - Frequency modulation 1..500 Hz
t_on  - Duration (sec)
t_off - Duration (sec)


      T_ON             T_OFF

   *************                   ****
   *           *                   *
   *           *                   *
****           *********************