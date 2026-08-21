import time
import pyb

pullup_pins = [
    'Y1', 'X11',
    'Y2', 'X12',
    'Y3', 'Y5',
    'Y4', 'Y6',
    'X8', 'X4',
    'X7', 'X3',
    'X6', 'X2',
    'X5', 'X1',
]

no_pull_pins = [
    'Y7', 'Y9',
    'Y8', 'Y10',
    'X9', 'Y11',
    'X10', 'Y12',
]

DEBUG_LED_HOLD_MS = 3000

input_pins = {}
leds = [pyb.LED(i) for i in range(1, 5)]


# Configure all test pins as inputs with their required pull settings.
def configure_input_pins():
    for pin_name in pullup_pins:
        input_pins[pin_name] = pyb.Pin(pin_name, pyb.Pin.IN, pyb.Pin.PULL_UP)

    for pin_name in no_pull_pins:
        input_pins[pin_name] = pyb.Pin(pin_name, pyb.Pin.IN, pyb.Pin.PULL_NONE)


# Count how many configured test pins are currently at logic zero.
def count_logic_zero_pins():
    count = 0

    for pin in input_pins.values():
        if pin.value() == 0:
            count += 1

    return count


# Show a 4-bit debug code on the board LEDs.
# LED1 = bit 0
# LED2 = bit 1
# LED3 = bit 2
# LED4 = bit 3
def show_debug_led_code(code):
    for blink_count in range(3):
        for led in leds:
            led.on()
        pyb.delay(200)

        for led in leds:
            led.off()
        pyb.delay(200)

    for bit_index, led in enumerate(leds):
        if code & (1 << bit_index):
            led.on()
        else:
            led.off()


# Report the final test result to the external device using Y6, Y7, and Y8.
# OK:
# Y6 = 0
# Y7 = 0
# Y8 = 1
#
# NOT OK:
# Y6 = 1
# Y7 = 1
# Y8 = 0
def report_result(is_ok):
    result_pins = {
        'Y6': pyb.Pin('Y6', pyb.Pin.OUT_PP),
        'Y7': pyb.Pin('Y7', pyb.Pin.OUT_PP),
        'Y8': pyb.Pin('Y8', pyb.Pin.OUT_PP),
    }

    if is_ok:
        result_pins['Y6'].low()
        result_pins['Y7'].low()
        result_pins['Y8'].high()
    else:
        result_pins['Y6'].high()
        result_pins['Y7'].high()
        result_pins['Y8'].low()


# Drive each test pin low and verify that exactly two pins are at logic zero.
def run_shunt_test():
    test_pin_names = pullup_pins + no_pull_pins

    for test_number, pin_name in enumerate(test_pin_names, 1):
        input_pins[pin_name] = pyb.Pin(pin_name, pyb.Pin.OUT_PP)
        input_pins[pin_name].low()
        pyb.delay(10)

        if count_logic_zero_pins() == 2:
            configure_input_pins()
        else:
            show_debug_led_code(test_number)
            report_result(False)
            pyb.delay(DEBUG_LED_HOLD_MS)
            return

    report_result(True)


configure_input_pins()
run_shunt_test()

while True:
    for led in leds:
        led.on()
        time.sleep(1)
        led.off()
