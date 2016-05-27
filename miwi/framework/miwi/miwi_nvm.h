/*
 The software supplied herewith by Microchip Technology Incorporated
 (the "Company") for its PIC(R) Microcontroller is intended and
 supplied to you, the Company's customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *******************************************************************/
#ifndef __NVM_EEPROM_H
    #define __NVM_EEPROM_H
    
    #include "system.h"
    #include "user.h"
    
    #if defined(ENABLE_NVM)

        #include "miwi_api.h"

        #define SPI_WRT_STATUS  0x01
        #ifndef SPI_WRITE
            #define SPI_WRITE       0x02
        #endif
        #ifndef SPI_READ
            #define SPI_READ        0x03
        #endif
        #define SPI_DIS_WRT     0x04
        #define SPI_RD_STATUS   0x05
        #define SPI_EN_WRT      0x06

        #define EEPROM_MAC_ADDR 0xFA

        extern uint16_t        nvmMyPANID;
        extern uint16_t        nvmCurrentChannel;
        extern uint16_t        nvmConnMode;
        extern uint16_t        nvmConnectionTable;
        extern uint16_t        nvmOutFrameCounter;
                            
        #if defined(PROTOCOL_MIWI)
            extern uint16_t        nvmMyShortAddress;
            extern uint16_t        nvmMyParent;

            #ifdef NWK_ROLE_COORDINATOR
                extern uint16_t    nvmRoutingTable;
                extern uint16_t    nvmKnownCoordinators;
                extern uint16_t    nvmRole;
            #endif
        #endif

        #if defined(PROTOCOL_MIWI_PRO)
            extern uint16_t        nvmMyShortAddress;
            extern uint16_t        nvmMyParent;

            #ifdef NWK_ROLE_COORDINATOR
                extern uint16_t    nvmRoutingTable;
                extern uint16_t    nvmFamilyTree;
                extern uint16_t    nvmNeighborRoutingTable;
                extern uint16_t    nvmRole;
            #endif
        #endif
        
        void NVMRead(uint8_t *dest, uint16_t addr, uint16_t count);
        void NVMWrite(uint8_t *source, uint16_t addr, uint16_t count);

        bool NVMInit(void);

        #define nvmGetMyPANID( x )                  NVMRead( (uint8_t *)x, nvmMyPANID, 2)
        #define nvmPutMyPANID( x )                  NVMWrite((uint8_t *)x, nvmMyPANID, 2)

        #define nvmGetCurrentChannel( x )           NVMRead( (uint8_t *)x, nvmCurrentChannel, 1)
        #define nvmPutCurrentChannel( x )           NVMWrite((uint8_t *)x, nvmCurrentChannel, 1)

        #define nvmGetConnMode( x )                 NVMRead( (uint8_t *)x, nvmConnMode, 1)
        #define nvmPutConnMode( x )                 NVMWrite((uint8_t *)x, nvmConnMode, 1)

        #define nvmGetConnectionTable( x )          NVMRead( (uint8_t *)x, nvmConnectionTable, (uint16_t)CONNECTION_SIZE * sizeof(CONNECTION_ENTRY))
        #define nvmPutConnectionTable( x )          NVMWrite((uint8_t *)x, nvmConnectionTable, (uint16_t)CONNECTION_SIZE * sizeof(CONNECTION_ENTRY))
        #define nvmPutConnectionTableIndex(x, y)    NVMWrite((uint8_t *)x, nvmConnectionTable+((uint16_t)y * sizeof(CONNECTION_ENTRY)), sizeof(CONNECTION_ENTRY))

        #define nvmGetOutFrameCounter( x )          NVMRead( (uint8_t *)x, nvmOutFrameCounter, 4)
        #define nvmPutOutFrameCounter( x )          NVMWrite((uint8_t *)x, nvmOutFrameCounter, 4)

        #if defined(PROTOCOL_MIWI)

            #define nvmGetMyShortAddress( x )       NVMRead( (uint8_t *)x, nvmMyShortAddress, 2)
            #define nvmPutMyShortAddress( x )       NVMWrite((uint8_t *)x, nvmMyShortAddress, 2)

            #define nvmGetMyParent( x )             NVMRead( (uint8_t *)x, nvmMyParent, 1)
            #define nvmPutMyParent( x )             NVMWrite((uint8_t *)x, nvmMyParent, 1)

            #if defined(NWK_ROLE_COORDINATOR)

                #define nvmGetRoutingTable( x )         NVMRead( (uint8_t *)x, nvmRoutingTable, 8)
                #define nvmPutRoutingTable( x )         NVMWrite((uint8_t *)x, nvmRoutingTable, 8)

                #define nvmGetKnownCoordinators( x )    NVMRead( (uint8_t *)x, nvmKnownCoordinators, 1)
                #define nvmPutKnownCoordinators( x )    NVMWrite((uint8_t *)x, nvmKnownCoordinators, 1)

                #define nvmGetRole( x )                 NVMRead( (uint8_t *)x, nvmRole, 1)
                #define nvmPutRole( x )                 NVMWrite((uint8_t *)x, nvmRole, 1)

            #endif

        #endif

        #if defined(PROTOCOL_MIWI_PRO)

            #define nvmGetMyShortAddress( x )       NVMRead( (uint8_t *)x, nvmMyShortAddress, 2)
            #define nvmPutMyShortAddress( x )       NVMWrite((uint8_t *)x, nvmMyShortAddress, 2)

            #define nvmGetMyParent( x )             NVMRead( (uint8_t *)x, nvmMyParent, 1)
            #define nvmPutMyParent( x )             NVMWrite((uint8_t *)x, nvmMyParent, 1)

            #if defined(NWK_ROLE_COORDINATOR)

                #define nvmGetRoutingTable( x )         NVMRead( (uint8_t *)x, nvmRoutingTable, NUM_COORDINATOR/8)
                #define nvmPutRoutingTable( x )         NVMWrite((uint8_t *)x, nvmRoutingTable, NUM_COORDINATOR/8)

                #define nvmGetNeighborRoutingTable( x ) NVMRead( (uint8_t *)x, nvmNeighborRoutingTable, ((uint16_t)NUM_COORDINATOR/8) * ((uint16_t)NUM_COORDINATOR))
                #define nvmPutNeighborRoutingTable( x ) NVMWrite((uint8_t *)x, nvmNeighborRoutingTable, ((uint16_t)NUM_COORDINATOR/8) * ((uint16_t)NUM_COORDINATOR))

                #define nvmGetFamilyTree( x )           NVMRead( (uint8_t *)x, nvmFamilyTree, NUM_COORDINATOR)
                #define nvmPutFamilyTree( x )           NVMWrite((uint8_t *)x, nvmFamilyTree, NUM_COORDINATOR)

                #define nvmGetRole( x )                 NVMRead( (uint8_t *)x, nvmRole, 1)
                #define nvmPutRole( x )                 NVMWrite((uint8_t *)x, nvmRole, 1)

            #endif
        #endif    
    #endif
#endif
