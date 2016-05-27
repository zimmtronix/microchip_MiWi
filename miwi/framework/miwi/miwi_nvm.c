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
#include "system.h"
#include "user.h"

#if defined(ENABLE_NVM)
    #include "miwi_nvm.h"
	
#if defined(NWK_ROLE_COORDINATOR)
    #define TOTAL_NVM_BYTES 65536  // Per bank
    #define NVM_PAGE_SIZE 256
#else
    #define TOTAL_NVM_BYTES 256
    #define NVM_PAGE_SIZE 16
#endif
    
    extern void MacroNop(void);
            
    uint16_t        nvmMyPANID;
    uint16_t        nvmCurrentChannel;
    uint16_t        nvmConnMode;
    uint16_t        nvmConnectionTable;
    uint16_t        nvmOutFrameCounter;

    #if defined(PROTOCOL_MIWI)
        uint16_t        nvmMyShortAddress;
        uint16_t        nvmMyParent;

        #ifdef NWK_ROLE_COORDINATOR
            uint16_t    nvmRoutingTable;
            uint16_t    nvmKnownCoordinators;
            uint16_t    nvmRole;
        #endif
    #endif

    #if defined(PROTOCOL_MIWI_PRO)
        uint16_t        nvmMyShortAddress;
        uint16_t        nvmMyParent;

        #ifdef NWK_ROLE_COORDINATOR
            uint16_t    nvmRoutingTable;
            uint16_t    nvmNeighborRoutingTable;
            uint16_t    nvmFamilyTree;
            uint16_t    nvmRole;
        #endif
    #endif
    
    #if defined(USE_EXTERNAL_EEPROM)
        #if defined(EEPROM_SHARE_SPI)
        
            #define EESPIPut( x )       SPIPut( x )
            #define EESPIGet()          SPIGet()
            
        #else
            void SPIPut2(uint8_t);
            uint8_t SPIGet2(void);
            
            //#define EESPIPut( x )       SPIPut2( x )
            //#define EESPIGet()          SPIGet2()
            #define EESPIPut( x )       SPIWrite2( x )
            #define EESPIGet()          SPIWrite2(0)
  
        #endif
    #endif

    //  Bank 0 NVMRead/NVMWrite.  MIWI settings            
    //  Bank 1 sysRead/sysWrite.  device settings  
    // void sysRead(uint8_t *dest, uint16_t addr, uint16_t count);
    // void sysWrite(uint8_t *source, uint16_t addr, uint16_t count); 
    // uint16_t sysDiff(uint8_t *dest, uint16_t addr, uint16_t count);
    // void NVMRead(uint8_t *dest, uint16_t addr, uint16_t count);
    // void NVMWrite(uint8_t *source, uint16_t addr, uint16_t count); 
            
    void sysRead(uint8_t *dest, uint16_t addr, uint16_t count)
    {
        uint8_t oldRFIE = RFIE; 
        uint16_t PageCounter = 0;
        RFIE = 0;
        do
        {
            EES_nCS = 0;
            MacroNop();
            EESPIPut(SPI_RD_STATUS);
            PageCounter = EESPIGet();
            EES_nCS = 1;
            MacroNop();
        } 
        while(PageCounter & 0x01 );
        

        EES_nCS = 0;
        EESPIPut(SPI_READ);
        EESPIPut(0x01);     // allow system settings for second bank
	EESPIPut(addr >> 8);        
        EESPIPut(addr);

        while( count > 0 )
        {
            *dest++ = EESPIGet();
            count--;
        }
        EES_nCS = 1;

        RFIE = oldRFIE;
    }
    
    uint16_t sysDiff(uint8_t *dest, uint16_t addr, uint16_t count)
    {
        uint8_t oldRFIE = RFIE;                
        RFIE = 0; 
        EES_nCS = 0;
        EESPIPut(SPI_READ);
        EESPIPut(0x01);     // allow system settings for second bank
	EESPIPut(addr >> 8);        
        EESPIPut(addr);

        while( count > 0 )
        {
            if(*dest++ != EESPIGet())
            {
                EES_nCS = 1;
                RFIE = oldRFIE;
                return (count&0xFF);
            }
            count--;
        }
        EES_nCS = 1;

        RFIE = oldRFIE;
        return 0;
    }

    void sysWrite(uint8_t *source, uint16_t addr, uint16_t count)
    {
        uint16_t PageCounter = 0;
        uint8_t oldRFIE = RFIE;
        RFIE = 0;

EEPROM_NEXT_PAGE:
        do
        {
            EES_nCS = 0;
            MacroNop();
            EESPIPut(SPI_RD_STATUS);
            PageCounter = EESPIGet();
            EES_nCS = 1;
            MacroNop();
        } 
        while(PageCounter & 0x01 );

        EES_nCS = 0;
        MacroNop();
        EESPIPut(SPI_EN_WRT);
        EES_nCS = 1;
        MacroNop();
        EES_nCS = 0;
        MacroNop();

        EESPIPut(SPI_WRITE);
        EESPIPut(0x01); // allow system settings for second bank
        EESPIPut(addr >> 8);
        EESPIPut(addr);
        PageCounter = 0;

        while( count > 0 )
        {
            EESPIPut(*source++);
            count--;
            PageCounter++;
            if( ((addr + PageCounter) & (NVM_PAGE_SIZE-1)) == 0 )
            {
                EES_nCS = 1;
                addr += PageCounter;
                goto EEPROM_NEXT_PAGE;
            }
        }
        EES_nCS = 1;

        RFIE = oldRFIE;       
    }
    
    void sysErase()
    {
        uint32_t addr = 0;
        uint32_t count = 0x20000;
        uint16_t PageCounter = 0;
        uint8_t oldRFIE = RFIE;
        RFIE = 0;

EEPROM_NEXT_PAGE:
        do
        {
            EES_nCS = 0;
            MacroNop();
            EESPIPut(SPI_RD_STATUS);
            PageCounter = EESPIGet();
            EES_nCS = 1;
            MacroNop();
        } 
        while(PageCounter & 0x01 );

        EES_nCS = 0;
        MacroNop();
        EESPIPut(SPI_EN_WRT);
        EES_nCS = 1;
        MacroNop();
        EES_nCS = 0;
        MacroNop();

        EESPIPut(SPI_WRITE);
        EESPIPut(addr >> 16); // allow system settings for second bank
        EESPIPut(addr >> 8);
        EESPIPut(addr);
        PageCounter = 0;

        while( count > 0 )
        {
            EESPIPut(0xFF);
            count--;
            PageCounter++;
            if( ((addr + PageCounter) & (NVM_PAGE_SIZE-1)) == 0 )
            {
                EES_nCS = 1;
                addr += PageCounter;
                goto EEPROM_NEXT_PAGE;
            }
        }
        EES_nCS = 1;

        RFIE = oldRFIE;
    }

    void NVMRead(uint8_t *dest, uint16_t addr, uint16_t count)
    {
        uint8_t oldRFIE = RFIE;                
        RFIE = 0; 

        EES_nCS = 0;
        EESPIPut(SPI_READ);
        EESPIPut(0x00);     // allow MIWI for first bank
	EESPIPut(addr >> 8);
        EESPIPut(addr);

        while( count > 0 )
        {
            *dest++ = EESPIGet();
            count--;
        }
        EES_nCS = 1;

        RFIE = oldRFIE;
    }

    void NVMWrite(uint8_t *source, uint16_t addr, uint16_t count)
    {
        uint16_t PageCounter = 0;
        uint8_t oldRFIE = RFIE;
        RFIE = 0;


EEPROM_NEXT_PAGE:
        do
        {
            EES_nCS = 0;
            MacroNop();
            EESPIPut(SPI_RD_STATUS);
            PageCounter = EESPIGet();
            EES_nCS = 1;
            MacroNop();
        } 
        while(PageCounter & 0x01 );

        EES_nCS = 0;
        MacroNop();
        EESPIPut(SPI_EN_WRT);
        EES_nCS = 1;
        MacroNop();
        EES_nCS = 0;
        MacroNop();

        EESPIPut(SPI_WRITE);
        EESPIPut(0x00); // allow system settings for second bank
        EESPIPut(addr >> 8);
        EESPIPut(addr);
        PageCounter = 0;

        while( count > 0 )
        {
            EESPIPut(*source++);
            count--;
            PageCounter++;
            if( ((addr + PageCounter) & (NVM_PAGE_SIZE-1)) == 0 )
            {
                EES_nCS = 1;
                addr += PageCounter;
                goto EEPROM_NEXT_PAGE;
            }
        }
        EES_nCS = 1;

        RFIE = oldRFIE;        
    }
        
    uint16_t nextEEPosition;        
    bool NVMalloc(uint16_t size, uint16_t *location)
    {
        //WORD retval;

        if ((nextEEPosition + size) > TOTAL_NVM_BYTES)
        {
            return false;
        }

        *location = nextEEPosition;
        nextEEPosition += size;
        return true;
    }
        
    
    bool NVMInit(void)
    {
        bool result = true;

        nextEEPosition = 0;

        result &= NVMalloc(2, &nvmMyPANID);
        result &= NVMalloc(1, &nvmCurrentChannel);
        result &= NVMalloc(1, &nvmConnMode);
        result &= NVMalloc(sizeof(CONNECTION_ENTRY) * CONNECTION_SIZE, &nvmConnectionTable);
        result &= NVMalloc(4, &nvmOutFrameCounter);

        #if defined(PROTOCOL_MIWI)

            result &= NVMalloc(2, &nvmMyShortAddress);
            result &= NVMalloc(1, &nvmMyParent);

            #if defined(NWK_ROLE_COORDINATOR)
                result &= NVMalloc(8, &nvmRoutingTable);
                result &= NVMalloc(1, &nvmKnownCoordinators);
                result &= NVMalloc(1, &nvmRole);
            #endif
        #endif

        #if defined(PROTOCOL_MIWI_PRO)

            result &= NVMalloc(2, &nvmMyShortAddress);
            result &= NVMalloc(1, &nvmMyParent);

            #if defined(NWK_ROLE_COORDINATOR)
                result &= NVMalloc((NUM_COORDINATOR/8), &nvmRoutingTable);
                result &= NVMalloc(((uint16_t)NUM_COORDINATOR/8*(uint16_t)NUM_COORDINATOR), &nvmNeighborRoutingTable);
                result &= NVMalloc(NUM_COORDINATOR, &nvmFamilyTree);
                result &= NVMalloc(1, &nvmRole);
            #endif
        #endif

        return result;
    }
#else
    extern char bogusVar;    
#endif   
