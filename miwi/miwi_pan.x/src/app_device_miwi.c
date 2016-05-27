#include "app_device_miwi.h"
#include "miwi_api.h"

uint8_t myChannel = 25;

extern MODULE sysStatus;
extern uint32_t tenMsCounter;
extern uint32_t sec_time;

uint8_t pktCMD;
uint8_t pktMSG;
uint8_t pktIDX;


uint8_t miwiInit(uint8_t reset)
{

    // Simple check to see if it could be valid
    if ((myLongAddress[MY_ADDRESS_LENGTH - 1] == 0x00) ||
            (myLongAddress[MY_ADDRESS_LENGTH - 1] == 0xFF))
    {
        return MAC_ADDRESS_FAIL;
    }

    // +++++++++++++++++++++++++++++++++++
    // Radio Setup
    // -----------------------------------

    if ((MiApp_ProtocolInit(true) == false) || (reset == true))
    {
        // First time
        MiApp_ProtocolInit(false);

        // Set default channel
        if (MiApp_SetChannel(myChannel) == false)
        {
            return MY_CHANNEL_FAIL;
        }

        if (MiApp_StartConnection(START_CONN_DIRECT, 10, 0))
        {
            // Set Connection Mode
            MiApp_ConnectionMode(ENABLE_PREV_CONN);
            return MIWI_SUCCESS;
        }
        else
        {
            return MIWI_FAIL;
        }
    }
    else
    {
        return MIWI_SUCCESS;
    }
    return MIWI_FAIL;
}

void miwiProcess()
{
    // Basic counter
    // Connects rxIndex with ConnectionTable
    uint8_t rxIndex;

    if (MiApp_MessageAvailable())
    {
        // Gets Source address
        if ((rxMessage.flags.bits.srcPrsnt)&&(rxMessage.flags.bits.altSrcAddr))
        {
            // Find ConnectionTable index is linked with message Address
            for (rxIndex = 0; rxIndex < CONNECTION_SIZE; rxIndex++)
            {
                if ((rxMessage.SourceAddress[0] == ConnectionTable[rxIndex].AltAddress.v[0])&&
                    (rxMessage.SourceAddress[1] == ConnectionTable[rxIndex].AltAddress.v[1]))
                {
                    // rxIndex is the correct location
                    break;
                }
            }
            
            // Hasn't overflowed so it is in my connection table
            if (rxIndex < CONNECTION_SIZE)
            {
                pktIDX = rxIndex;
                pktCMD = rxMessage.Payload[0];
                pktMSG = rxMessage.Payload[1];  
            }
        } // End of sourceAddress present
        MiApp_DiscardMessage();        
    }
    else
    {
        if(pktIDX!=0xff) 
        {       
            uint8_t valid = 1;
            uint8_t buffer[2];
            buffer[0] = pktCMD;
            buffer[1] = pktMSG;
            
            // Send it to everyone I know
            for (rxIndex = 0; rxIndex < CONNECTION_SIZE; rxIndex++)
            {
                if ((ConnectionTable[rxIndex].status.bits.isValid)&&(rxIndex!=pktIDX))
                {
                    valid = miwiMsg(rxIndex,buffer,2);
                }
            }
            
            // if everyone got it send it to device who requested it
            if(valid)
            {
                miwiMsg(pktIDX,buffer,2);  
            }
            
            pktIDX = 0xff;
        }
    }
}

uint8_t miwiMsg(uint8_t map, uint8_t *data, uint8_t size)
{
    uint8_t iii;
    MiApp_FlushTx();
    for (iii = 0; iii < size; iii++)
    {
        MiApp_WriteData(data[iii]);
    }
    //return MiApp_UnicastAddress(ConnectionTable[map].Address, true, false);
    return MiApp_UnicastConnection(map, false);
}

