#include "generic.h"

static const char base64EncodingTable[64u] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                     'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                     'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                     'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                     'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                     'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                     'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                     '4', '5', '6', '7', '8', '9', '+', '/'};
static const uint8 base64ModTable[3u] = {0u, 2u, 1u};
static uint8 base64DecodingTable[256u];
                                        
uint32 Generic_hex2int(char *a, uint32 len)
{
    uint32 i;
    uint32 val = 0u;

    for(i=0u;i<len;i++)
    {
        if(a[i] <= 57u)
        {
            val += (a[i]-48u)*(1u<<(4u*(len-1u-i)));
        }
        else
        {
            val += (a[i]-87u)*(1u<<(4u*(len-1u-i)));
        }
    }
    
    return val;
}

void Generic_buildBase64DecodingTable() 
{
    uint16 i;
    uint8 j;
    
    for (i = 0u; (uint16)i < 256u; i++)
    {
        base64DecodingTable[i] = 65u;
    }
    for (j = 0u; j < 64u; j++)
    {
        base64DecodingTable[(uint8) base64EncodingTable[j]] = j;
    }
}

void Generic_base64Encode(const uint8 *data,
                          uint16 inputLength,
                          int8(*putFunction)(char))
{
    uint16 i;
    uint16 j;
    int16 i2;
    uint32 octetA;
    uint32 octetB;
    uint32 octetC;
    uint32 triple;
    uint16 outputLength;
    uint8 mod;
    
    outputLength = ((inputLength - 1u) / 3u) * 4u + 4u;
    mod = base64ModTable[inputLength % 3u];
    
    for (i = 0u, j = 0u; i < inputLength;)
    {
        if (i < inputLength)
        {
            octetA = data[i++];
        }
        else
        {
            octetA = 0u;
        }
        if (i < inputLength)
        {
            octetB = data[i++];
        }
        else
        {
            octetB = 0u;
        }
        if (i < inputLength)
        {
            octetC = data[i++];
        }
        else
        {
            octetC = 0u;
        }
        
        triple = (octetA << 0x10u) + (octetB << 0x08u) + octetC;
        
        for (i2 = 3; i2 >= 0; --i2)
        {
            if (j < (outputLength - mod))
            {
                putFunction(base64EncodingTable[(triple >> i2 * 6u) & 0x3Fu]);
                j++;
            }
            else
            {
                putFunction('=');
                return;
            }
        }
    }
}

int8 Generic_base64Decode(const char *data, uint16 inputLength, uint8 *outputData)
{
    uint16 i;
    uint16 j;
    int16 i2;
    uint32 sextetA;
    uint32 sextetB;
    uint32 sextetC;
    uint32 sextetD;
    uint32 triple;
    uint16 outputLength;

    if (inputLength % 4 != 0)
    {
        return (int8)(-1);
    }

    outputLength = inputLength / 4u * 3u;
    if (data[inputLength - 1u] == '=')
    {
        outputLength--;
    }
    if (data[inputLength - 2u] == '=')
    {
        outputLength--;
    }


    for (i = 0u, j = 0u; i < inputLength;)
    {

        if (data[i] == '=')
        {
            sextetA = 0u & i++;
        }
        else
        {
            sextetA = base64DecodingTable[(uint8)data[i++]];
        }
        if (data[i] == '=')
        {
            sextetB = 0u & i++;
        }
        else
        {
            sextetB = base64DecodingTable[(uint8)data[i++]];
        }
        if (data[i] == '=')
        {
            sextetC = 0u & i++;
        }
        else
        {
            sextetC = base64DecodingTable[(uint8)data[i++]];
        }
        if (data[i] == '=')
        {
            sextetD = 0u & i++;
        }
        else
        {
            sextetD = base64DecodingTable[(uint8)data[i++]];
        }
        
        if ((sextetA == 65u)        // if 65 is here wrong data was input
            || (sextetB == 65u) 
            || (sextetC == 65u) 
            || (sextetD == 65u))
        {
            return (int8)(-1);
        }

        triple = (sextetA << 3u * 6u)
        + (sextetB << 2u * 6u)
        + (sextetC << 1u * 6u)
        + (sextetD << 0u * 6u);

        for (i2 = 2; i2 >= 0; i2--)
        {
            if (j < outputLength)
            {
                outputData[j++] = (triple >> i2 * 8u) & 0xFFu;
            }
        }
    }

    return (int8)(0);
}
