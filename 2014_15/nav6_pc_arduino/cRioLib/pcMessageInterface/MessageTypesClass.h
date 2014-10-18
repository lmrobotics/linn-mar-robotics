#ifndef MESSAGE_TYPES_H
#define MESSAGE_TYPES_H

namespace Messages
{

   class MessageTypesClass
   {
      public:

         enum messageId {
            msgEnvDataRequestId = 0x01,
            msgSettingsCommandId = 0x02,
            msgEepromReadRequestId = 0x03,
            msgDebugDataRequestId = 0x04,
            msgEnvironmentalDataId = 0x81,
            msgSettingsResponseId = 0x82,
            msgEepromReadResponseId = 0x83,
            msgDebugDataResponseId = 0x84,
         };

         enum fanControlType {
            automatic = 0x5A,
            on = 0xA5,
         };

   };

}

#endif
