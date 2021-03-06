/*
 * All the includes below are required because the Arduino IDE does not support
 * dependencies between libraries very well. The Arduino team have announced
 * that they plan to fix this in the next versions of the IDE.
 */
#include <PusherTrajectory.h>
#include <SdTrajectory.h>
#include <ServoControl.h>
#include <Trajectory.h>
#include <Action.h>
#include <Configuration.h>
#include <ContentAction.h>
#include <eepromAddresses.h>
#include <Email.h>
#include <Facebook.h>
#include <Foursquare.h>
#include <Gmail.h>
#include <Inbox.h>
#include <Resources.h>
#include <Rss.h>
#include <Service.h>
#include <Settings.h>
#include <SoundCloud.h>
#include <Twitter.h>
#include <Dispatcher.h>
#include <Fsm.h>
#include <Motion.h>
#include <Personality.h>
#include <Player.h>
#include <Signals.h>
#include <Api.h>
#include <Audio.h>
#include <BufferedStream.h>
#include <digitalWriteFast.h>
#include <Download.h>
#include <ExtendedStream.h>
#include <HttpClient.h>
#include <JsonStream.h>
#include <PusherClient.h>
#include <SerialStream.h>
#include <Sha256.h>
#include <Vs1011.h>
#include <Wifly.h>
#include <SdFat.h>
#include <Servo.h>
/*
 * Now these are the two includes we actually need.
 */
#include <Button.h>
#include <StatusLed.h>
/*
 * The Button class is a state machine that manages all time-related aspects of
 * interactions with the button: debouncing, detecting short clicks, long
 * clicks, etc.
 *
 * To create a Button object all we need is the pin connected to the button. On
 * the reaDIYmate board this is pin 2.
 */
Button button(2);
/*
 * The StatusLed class is a very simple wrapper that allows us to control the
 * dual-color LED on the reaDIYmate board.
 *
 * To create a StatusLed object we pass the pin numbers for the green LED and
 * the red LED to the constructor.
 */
StatusLed led(78, 79);

void setup() {
  /*
   * In the setup method we initialize the button and the LED, aswell as the
   * Serial port.
   */
  button.initialize();
  led.initialize();
  Serial.begin(9600);
}

void loop() {
    /*
     * We declare a buttonEvent variable in order to store the events generated
     * by our Button object.
     */
    Event buttonEvent;
    /*
     * Depending on the value we read on the button pin, we send either a
     * CONTACT_DETECTED or a NO_CONTACT_DETECTED event to the Button object by
     * calling its dispatch() method. At the same time, we update the LED color:
     * orange if the button is pressed, green if it isn't.
     */
    switch (digitalRead(2)) {
        case LOW :
            button.dispatch(Event(CONTACT_DETECTED), buttonEvent);
            led.colorOrange();
            break;
        case HIGH :
            button.dispatch(Event(NO_CONTACT_DETECTED), buttonEvent);
            led.colorGreen();
            break;
    }
    /*
     * Once the dispatch() method is finished, buttonEvent.signal will hold any
     * event generated by the Button object.
     */
    switch (buttonEvent.signal) {
        /*
         * A short click event is triggered if the button is pressed more than
         * 100ms but less than 1s.
         */
        case SHORT_CLICK_RELEASED :
            Serial.println(F("Short click released"));
            break;
        /*
         * A long click event is triggered if the button is pressed more than 1s
         * but less than 3s.
         */
        case LONG_CLICK_RELEASED :
            Serial.println(F("Long click released"));
            break;
        /*
         * A superlong click event is triggered if the button is pressed more
         * than 3s.
         */
        case SUPERLONG_CLICK_ARMED :
            Serial.println(F("Superlong click armed"));
            break;
    }
}
