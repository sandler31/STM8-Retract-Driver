# STM8 Retract Driver
This project aims to replace the default firmware on a generic retract driver that is sold with many RC retractable landing gear.

By default, the driver works with PWM, and in most cases is hooked to an output of some RF receiver. This firmware is controlled by GPIO's - one for signalling extend, and one for sinalling retract operation. When the requested operation is finished, the driver reports back on another GPIO.

Will this work for your driver? have a look at my blogpost, to see if you have a similar driver in hand:

<URL>

Core firmware parts
----

* main.c
  * As the name states - the main part of the firmware, which does all of the initialization:
    * Configuring the CPU prescaler
    * setting up GPIO's
    * enabling interrupts
* globs.c
  * Defines some usable names for the GPIO ports we are using
  * Defines global variables used throughout the firmware
* control.c
  * Contains control functions which allow the retract controller to control the retracts
* interrupts.c
  * The firmware I wrote, is based mostly on interrupts to accomplish it's tasks, the interrupts include:
    * Timer interrupt (used for periodic check of power draw once retract/extend operation is started)
    * GPIO interrupts - to sense when we are requested to do stuff
    * ADC interrupts - used for measuring the power draw (tl;dr ADC = Analog-to-Digital converter, converts the voltage on the measuring resistors to a number, which we can use in calculations)

License
----

GPL
