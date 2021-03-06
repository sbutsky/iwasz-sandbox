#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_sysctl.h"
#include "usblib/usblib.h"
#include "usblib/usbhid.h"
#include "usblib/device/usbdevice.h"
#include "usblib/device/usbdhid.h"
#include "usblib/device/usbdhidkeyb.h"

#include "driverlib/rom.h"
#include "driverlib/interrupt.h"

#ifdef DEBUG
void
__error__(char *pcFilename, unsigned long ulLine)
{
//
// Something horrible happened! You need to look
// at file "pcFilename" at line "ulLine" to see
// what error is being reported.
//
        while(1)
        {
        }
}
#endif

//****************************************************************************
//
// The languages supported by this device.
//
//****************************************************************************
const uint8_t g_pui8LangDescriptor[] =
{
    4,
    USB_DTYPE_STRING,
    USBShort(USB_LANG_EN_US)
};

//****************************************************************************
//
// The manufacturer string.
//
//****************************************************************************
const uint8_t g_pui8ManufacturerString[] =
{
    (17 + 1) * 2,
    USB_DTYPE_STRING,
    'T', 0, 'e', 0, 'x', 0, 'a', 0, 's', 0, ' ', 0, 'I', 0, 'n', 0, 's', 0,
    't', 0, 'r', 0, 'u', 0, 'm', 0, 'e', 0, 'n', 0, 't', 0, 's', 0,
};

//****************************************************************************
//
// The product string.
//
//****************************************************************************
const uint8_t g_pui8ProductString[] =
{
    (16 + 1) * 2,
    USB_DTYPE_STRING,
    'K', 0, 'e', 0, 'y', 0, 'b', 0, 'o', 0, 'a', 0, 'r', 0, 'd', 0, ' ', 0,
    'E', 0, 'x', 0, 'a', 0, 'm', 0, 'p', 0, 'l', 0, 'e', 0
};

//****************************************************************************
//
// The serial number string.
//
//****************************************************************************
const uint8_t g_pui8SerialNumberString[] =
{
    (8 + 1) * 2,
    USB_DTYPE_STRING,
    '1', 0, '2', 0, '3', 0, '4', 0, '5', 0, '6', 0, '7', 0, '8', 0
};

//*****************************************************************************
//
// The interface description string.
//
//*****************************************************************************
const uint8_t g_pui8HIDInterfaceString[] =
{
    (22 + 1) * 2,
    USB_DTYPE_STRING,
    'H', 0, 'I', 0, 'D', 0, ' ', 0, 'K', 0, 'e', 0, 'y', 0, 'b', 0,
    'o', 0, 'a', 0, 'r', 0, 'd', 0, ' ', 0, 'I', 0, 'n', 0, 't', 0,
    'e', 0, 'r', 0, 'f', 0, 'a', 0, 'c', 0, 'e', 0
};

//*****************************************************************************
//
// The configuration description string.
//
//*****************************************************************************
const uint8_t g_pui8ConfigString[] =
{
    (26 + 1) * 2,
    USB_DTYPE_STRING,
    'H', 0, 'I', 0, 'D', 0, ' ', 0, 'K', 0, 'e', 0, 'y', 0, 'b', 0,
    'o', 0, 'a', 0, 'r', 0, 'd', 0, ' ', 0, 'C', 0, 'o', 0, 'n', 0,
    'f', 0, 'i', 0, 'g', 0, 'u', 0, 'r', 0, 'a', 0, 't', 0, 'i', 0,
    'o', 0, 'n', 0
};
//*****************************************************************************
//
// The descriptor string table.
//
//*****************************************************************************
const uint8_t * const g_ppui8StringDescriptors[] =
{
    g_pui8LangDescriptor,
    g_pui8ManufacturerString,
    g_pui8ProductString,
    g_pui8SerialNumberString,
    g_pui8HIDInterfaceString,
    g_pui8ConfigString
};

#define NUM_STRING_DESCRIPTORS (sizeof(g_ppui8StringDescriptors) /            \
                                sizeof(uint8_t *))

#define VENDOR_ID 0x20a0
#define PRODUCT_ID 0x41ff


uint32_t USBCallback (void *pvCBData, uint32_t ui32Event, uint32_t ui32MsgParam, void *pvMsgData);


tUSBDHIDKeyboardDevice g_sKeyboardDevice = {
                VENDOR_ID,
                PRODUCT_ID,
                // The power consumption of your device in milliamps.
                0,
                // The value to be passed to the host in the USB configuration descriptor’s
                // bmAttributes field.
                USB_CONF_ATTR_SELF_PWR,
                // A pointer to your keyboard callback event handler.
                USBCallback,
                // A value that you want passed to the callback alongside every event.
                (void *)&g_sKeyboardDevice,
                // A pointer to your string table.
                g_ppui8StringDescriptors,
                // The number of entries in your string table. This must equal
                // (1 + (5 * (num languages))).
                NUM_STRING_DESCRIPTORS
};






uint32_t USBCallback (void *pvCBData, uint32_t ui32Event, uint32_t ui32MsgParam, void *pvMsgData)
{
        switch (ui32Event)
        {
            //
            // The host has connected to us and configured the device.
            //
            case USB_EVENT_CONNECTED:
            {
                break;
            }

            //
            // The host has disconnected from us.
            //
            case USB_EVENT_DISCONNECTED:
            {
                break;
            }

            //
            // We receive this event every time the host acknowledges transmission
            // of a report. It is used here purely as a way of determining whether
            // the host is still talking to us or not.
            //
            case USB_EVENT_TX_COMPLETE:
            {
                //
                // Enter the idle state since we finished sending something.
                //
                break;
            }

            //
            // This event indicates that the host has suspended the USB bus.
            //
            case USB_EVENT_SUSPEND:
            {
                break;
            }

            //
            // This event signals that the host has resumed signalling on the bus.
            //
            case USB_EVENT_RESUME:
            {
                break;
            }

            //
            // This event indicates that the host has sent us an Output or
            // Feature report and that the report is now in the buffer we provided
            // on the previous USBD_HID_EVENT_GET_REPORT_BUFFER callback.
            //
            case USBD_HID_KEYB_EVENT_SET_LEDS:
            {
                //
                // Set the LED to match the current state of the caps lock LED.
                //
                break;
            }

            //
            // We ignore all other events.
            //
            default:
            {
                break;
            }
        }

        return(0);
}

int main (void)
{
        SysCtlClockSet (SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

        // Konfiguracja GPIO
        //
        // Enable the GPIO port that is used for the on-board LED.
        //
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
        GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);


        // Konfiguracja USB

        // Enable the GPIO peripheral used for USB, and configure the USB
        // pins.
        //
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
        SysCtlGPIOAHBEnable(SYSCTL_PERIPH_GPIOD);
        GPIOPinTypeUSBAnalog(GPIO_PORTD_AHB_BASE, GPIO_PIN_4 | GPIO_PIN_5);

        //
        // Set the USB stack mode to Device mode.
        //
        USBStackModeSet(0, eUSBModeForceDevice, 0);


        void *pvDevice = USBDHIDKeyboardInit(0, &g_sKeyboardDevice);
        GPIOPinWrite (GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);

        if (!pvDevice) {
                while (1);
        }

        GPIOPinWrite (GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);

        uint32_t ui32Loop;

        while (1) {
                USBDHIDKeyboardKeyStateChange (pvDevice, 0, 0x04, true);

                // DELAY
                for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++)
                {
                }
        }
}
