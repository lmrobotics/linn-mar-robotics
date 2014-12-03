local messageID_type = {
   [0x01] = "nav6ID",
   [0x80] = "nav6RespID",
}

-- Dissector for: nav6
nav6_proto = Proto("nav6", "nav6_1")
local nav6_fields = nav6_proto.fields
nav6_fields.nav6Yaw = ProtoField.uint64("nav6.nav6Yaw", "nav6Yaw", base.HEX)
nav6_fields.nav6Roll = ProtoField.bytes("nav6.nav6Roll", "nav6Yoll", base.HEX)
nav6_fields.nav6Pitch_exp = ProtoField.int64("nav6.nav6Pitch_exp", "nav6Pitch_exp")
nav6_fields.nav6Pitch_mantissa = ProtoField.int64("nav6.nav6Pitch_mantissa", "nav6Pitch_mantissa")

function nav6_proto.dissector(buffer, pinfo, tree)
   local subtree = tree:add(nav6_proto, buffer(), "nav6")
   subtree:add(nav6_fields.nav6Yaw,buffer(0, 6))
   subtree:add(nav6_fields.nav6Roll,buffer(6, 6))
   subtree:add(nav6_fields.nav6Pitch_exp,buffer(12, 2))
   subtree:add(nav6_fields.nav6Pitch_mantissa,buffer(14, 4))
end

-- Dissector for: nav6Messages
nav6Messages_proto = Proto("nav6Messages", "nav6Messages_1")
local nav6Messages_fields = nav6Messages_proto.fields
nav6Messages_fields.messageId = ProtoField.uint16("nav6Messages.messageId", "messageId", base.HEX, messageID_type)
nav6Messages_fields.messageLength = ProtoField.int16("nav6Messages.messageLength", "messageLength")

function nav6Messages_proto.dissector(buffer, pinfo, tree)
   pinfo.cols.protocol = "nav6Control"
   local subtree = tree:add(nav6Messages_proto, buffer(), "nav6Messages")
   subtree:add(nav6Messages_fields.messageId,buffer(0, 1))
   subtree:add(nav6Messages_fields.messageLength,buffer(1, 1))

   local discriminantValue = buffer(0, 1):uint()
   nextDiscriminant = 0;
   if discriminantValue == 1 then
      nextDiscriminant = Dissector.get("nav6")
      pinfo.cols.info = "nav6ID"
   end

   local subRecordSize = buffer:len()-2
   if (nextDiscriminant ~= 0) then
       nextDiscriminant:call(buffer(2, subRecordSize):tvb(),pinfo,tree)
   end

end

udp_table = DissectorTable.get("udp.port")
udp_table:add(8888,nav6Messages_proto)
