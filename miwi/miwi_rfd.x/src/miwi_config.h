/* 
 * File:   miwi_config.h
 * Author: Not Supported
 *
 */

#ifndef MIWI_CONFIG_H
#define	MIWI_CONFIG_H

/*********************************************************************/
// following codes defines the platforms as well as the hardware
// configuration
/*********************************************************************/

/*********************************************************************/
// ENABLE_CONSOLE will enable the print out on the hyper terminal
// this definition is very helpful in the debugging process
/*********************************************************************/
//#define ENABLE_CONSOLE

//------------------------------------------------------------------------
// Definition of Protocol Stack. ONLY ONE PROTOCOL STACK CAN BE CHOSEN
//------------------------------------------------------------------------
    /*********************************************************************/
    // PROTOCOL_P2P enables the application to use MiWi P2P stack. This
    // definition cannot be defined with PROTOCOL_MIWI.
    /*********************************************************************/
    //#define PROTOCOL_P2P

    /*********************************************************************/
    // PROTOCOL_MIWI enables the application to use MiWi mesh networking
    // stack. This definition cannot be defined with PROTOCOL_P2P.
    /*********************************************************************/
    #define PROTOCOL_MIWI

    /*********************************************************************/
    // PROTOCOL_MIWI_PRO enables the application to use MiWi PRO stack.
    // This definition cannot be defined with PROTOCOL_P2P or PROTOCOL_MIWI.
    /*********************************************************************/
    //#define PROTOCOL_MIWI_PRO

    /*********************************************************************/
    // NWK_ROLE_COORDINATOR is not valid if PROTOCOL_P2P is defined. It
    // specified that the node has the capability to be coordinator or PAN
    // coordinator. This definition cannot be defined with
    // NWK_ROLE_END_DEVICE.
    /*********************************************************************/
    //#define NWK_ROLE_COORDINATOR
    #define NWK_ROLE_END_DEVICE

 
//------------------------------------------------------------------------
// Definition of RF Transceiver. ONLY ONE TRANSCEIVER CAN BE CHOSEN
//------------------------------------------------------------------------

    /*********************************************************************/
    // Definition of MRF24J40 enables the application to use Microchip
    // MRF24J40 2.4GHz IEEE 802.15.4 compliant RF transceiver. Only one
    // RF transceiver can be defined.
    /*********************************************************************/
    //#define MRF24J40

    /*********************************************************************/
    // Definition of MRF24XA enables the application to use Microchip
    // MRF24XA 2.4GHz RF transceiver. Only one RF transceiver can be defined.
    /*********************************************************************/
    //#define MRF24XA

        /*****************************************************************/
        // Definition of IEEE_STANDARD_MODE is only effective for MRF24XA.
        // By defining this macro, IEEE 802.15.4 mode will be used with
        // 250Kbps data rate. By commenting out this definition, MRF24XA
        // proprietary mode will be used to get higher data rate and more
        // efficiency, but lack sniffer support for now
        /*****************************************************************/
        //#define IEEE_STANDARD_MODE

    /*********************************************************************/
    // Definition of MRF49XA enables the application to use Microchip
    // MRF49XA subGHz proprietary RF transceiver. Only one RF transceiver
    // can be defined.
    /*********************************************************************/
    //#define MRF49XA


    /*********************************************************************/
    // Definition of MRF89XA enables the application to use Microchip
    // MRF89XA subGHz proprietary RF transceiver
    /*********************************************************************/
    #define MRF89XA


/*********************************************************************/
// ENABLE_NETWORK_FREEZER enables the network freezer feature, which
// stores critical network information into non-volatile memory, so
// that the protocol stack can recover from power loss gracefully.
// The network info can be saved in data EPROM of MCU, external
// EEPROM or programming space, if enhanced flash is used in MCU.
// Network freezer feature needs definition of NVM kind to be
// used, which is specified in HardwareProfile.h
/*********************************************************************/
#define ENABLE_NETWORK_FREEZER


/*********************************************************************/
// MY_ADDRESS_LENGTH defines the size of wireless node permanent
// address in byte. This definition is not valid for IEEE 802.15.4
// compliant RF transceivers.
/*********************************************************************/
#define MY_ADDRESS_LENGTH       4

/*********************************************************************/
// EUI_x defines the xth byte of permanent address for the wireless
// node
/*********************************************************************/
#define EUI_7 0x11
#define EUI_6 0x22
#define EUI_5 0x33
#define EUI_4 0x44
#define EUI_3 0x55
#define EUI_2 0x66
#define EUI_1 0x77
#define EUI_0 0x01

/*********************************************************************/
// TX_BUFFER_SIZE defines the maximum size of application payload
// which is to be transmitted
/*********************************************************************/
#define TX_BUFFER_SIZE 40

/*********************************************************************/
// RX_BUFFER_SIZE defines the maximum size of application payload
// which is to be received
/*********************************************************************/
#define RX_BUFFER_SIZE 40

/*********************************************************************/
// MY_PAN_ID defines the PAN identifier. Use 0xFFFF if prefer a
// random PAN ID.
/*********************************************************************/
#define MY_PAN_ID 0x1234


/*********************************************************************/
// ADDITIONAL_NODE_ID_SIZE defines the size of additional payload
// will be attached to the P2P Connection Request. Additional payload
// is the information that the devices what to _RP14R with their peers
// on the P2P connection. The additional payload will be defined by
// the application and defined in main.c
/*********************************************************************/
#define ADDITIONAL_NODE_ID_SIZE   1


/*********************************************************************/
// P2P_CONNECTION_SIZE defines the maximum P2P connections that this
// device allows at the same time.
/*********************************************************************/
#define CONNECTION_SIZE             16


/*********************************************************************/
// TARGET_SMALL will remove the support of inter PAN communication
// and other minor features to save programming space
/*********************************************************************/
//#define TARGET_SMALL


/*********************************************************************/
// ENABLE_PA_LNA enable the external power amplifier and low noise
// amplifier on the RF board to achieve longer radio communication
// range. To enable PA/LNA on RF board without power amplifier and
// low noise amplifier may be harmful to the transceiver.
/*********************************************************************/
//#define ENABLE_PA_LNA


/*********************************************************************/
// ENABLE_HAND_SHAKE enables the protocol stack to hand-shake before
// communicating with each other. Without a handshake process, RF
// transceivers can only broadcast, or hard-coded the destination address
// to perform uni-cast.
/*********************************************************************/
#define ENABLE_HAND_SHAKE


/*********************************************************************/
// ENABLE_SLEEP will enable the device to go to sleep and wake up
// from the sleep
/*********************************************************************/
//#define ENABLE_SLEEP


/*********************************************************************/
// ENABLE_ED_SCAN will enable the device to do an energy detection scan
// to find out the channel with least noise and operate on that channel
/*********************************************************************/
//#define ENABLE_ED_SCAN


/*********************************************************************/
// ENABLE_ACTIVE_SCAN will enable the device to do an active scan to
// to detect current existing connection.
/*********************************************************************/
#define ENABLE_ACTIVE_SCAN


/*********************************************************************/
// ENABLE_SECURITY will enable the device to encrypt and decrypt
// information transferred
/*********************************************************************/
//#define ENABLE_SECURITY


/*********************************************************************/
// ENABLE_INDIRECT_MESSAGE will enable the device to store the packets
// for the sleeping devices temporarily until they wake up and ask for
// the messages
/*********************************************************************/
//#define ENABLE_INDIRECT_MESSAGE


/*********************************************************************/
// ENABLE_BROADCAST will enable the device to broadcast messages for
// the sleeping devices until they wake up and ask for the messages
/*********************************************************************/
#define ENABLE_BROADCAST


/*********************************************************************/
// RFD_WAKEUP_INTERVAL defines the wake up interval for RFDs in second.
// This definition is for the FFD devices to calculated various
// timeout. RFD depends on the setting of the watchdog timer to wake
// up, thus this definition is not used.
/*********************************************************************/
#define RFD_WAKEUP_INTERVAL     8


/*********************************************************************/
// ENABLE_FREQUENCY_AGILITY will enable the device to change operating
// channel to bypass the sudden change of noise
/*********************************************************************/
//#define ENABLE_FREQUENCY_AGILITY


// Constants Validation

#if !defined(MRF24J40) && !defined(MRF49XA) && !defined(MRF89XA) && !defined(MRF24XA)
    #error "One transceiver must be defined for the wireless application"
#endif

#if (defined(MRF24J40) && defined(MRF49XA)) || (defined(MRF24J40) && defined(MRF89XA)) || (defined(MRF49XA) && defined(MRF89XA))
    #error "Only one transceiver can be defined for the wireless application"
#endif

#if !defined(PROTOCOL_P2P) && !defined(PROTOCOL_MIWI) && !defined(PROTOCOL_MIWI_PRO)
    #error "One Microchip proprietary protocol must be defined for the wireless application."
#endif

#if defined(ENABLE_FREQUENCY_AGILITY)
    #define ENABLE_ED_SCAN
#endif

#if MY_ADDRESS_LENGTH > 8
    #error "Maximum address length is 8"
#endif

#if MY_ADDRESS_LENGTH < 2
    #error "Minimum address length is 2"
#endif

#if defined(NWK_ROLE_END_DEVICE ) && defined(NWK_ROLE_COORDINATOR)
    #error "NWK_ROLE needs to be END_DEVICE or COORDINATOR"
#endif

#if defined(MRF24J40)

    #define IEEE_802_15_4
    #undef MY_ADDRESS_LENGTH
    #define MY_ADDRESS_LENGTH 8

#endif

#if defined(MRF24XA) && defined(IEEE_STANDARD_MODE)

    #define IEEE_802_15_4
    #undef MY_ADDRESS_LENGTH
    #define MY_ADDRESS_LENGTH 8

#endif

#if defined(ENABLE_NETWORK_FREEZER)
    #define ENABLE_NVM
    #define ENABLE_NVM_MAC
#endif

#if defined(ENABLE_ACTIVE_SCAN) && defined(TARGET_SMALL)
    #error  Target_Small and Enable_Active_Scan cannot be defined together
#endif

#if defined(ENABLE_INDIRECT_MESSAGE) && !defined(RFD_WAKEUP_INTERVAL)
    #error "RFD Wakeup Interval must be defined if indirect message is enabled"
#endif

#if (RX_BUFFER_SIZE > 127)
    #error RX BUFFER SIZE too large. Must be <= 127.
#endif

#if (TX_BUFFER_SIZE > 127)
    #error TX BUFFER SIZE too large. Must be <= 127.
#endif

#if (RX_BUFFER_SIZE < 10)
    #error RX BUFFER SIZE too small. Must be >= 10.
#endif

#if (TX_BUFFER_SIZE < 10)
    #error TX BUFFER SIZE too small. Must be >= 10.
#endif

#if (CONNECTION_SIZE > 0xFE)
    #error NETWORK TABLE SIZE too large.  Must be < 0xFF.
#endif

#endif	/* MIWI_CONFIG_H */

