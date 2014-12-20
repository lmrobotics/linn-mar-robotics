import sys, string, os, re
import xml.etree.ElementTree as ET
from collections import OrderedDict

class field:
   def __init__(self, tag, name, offset, length, type):
      self.tag = tag;
      self.name = name
      self.offset = offset
      self.length = length
      self.type = type

class message:
   def __init__(self, name, id, fields):
      self.name = name
      self.id = id
      self.fields = fields


tree = ET.parse(sys.argv[1])
messageCat = tree.getroot()
enumerations = OrderedDict()
messages = OrderedDict()
luaName = "messages"
port = 0
allowedBuiltInTypes = ["bool", "char", "int8", "int16", "int32", "uint8", "uint16", "uint32", "float", "fixed"]
         
def printEnum(enumDef):
   print (enumDef.tag, enumDef.attrib)
   for enum in enumDef:
      print (enum.tag, enum.attrib)
   return;
   
def parseEnum(enumDef):
   enumDict = OrderedDict()
   for enum in enumDef:
      enumDict.update({enum.attrib['name']:enum.attrib['value']})
   enumName = enumDef.attrib['name']
   enumerations.update({enumName : enumDict})
   return;
   
def printMessage(messageDef):
   for field in messageDef:
      print (field.tag, field.attrib)
   return;

def parseMessage(messageDef):
   msgName = messageDef.attrib['name']
   msgId = messageDef.attrib['id']
   fields = list()
   for f in messageDef:
      msgField = field(f.tag,
                       f.attrib['name'], 
                       f.attrib['offset'], 
                       f.attrib['length'],
                       f.attrib['type'])
      fields.append(msgField)
   msg = message(msgName, msgId, fields)
   messages.update({msgName : msg})
   return;
def printMessages():
   # print all message records
   print()      
   print()      
   print("MESSAGES")      
   print()      
   for msgK, msgV in messages.items():
      print (msgK, msgV.id)
      for f in msgV.fields:
         print ("", f.tag, f.name, f.offset, f.length, f.type )
      print()      
def lastElementUnbounded(msg):
   #todo use reverse loop to get last element first
   lastElementUnbounded = False
   for f in msg.fields:
      if f.length == "*":
         lastElementUnbounded = True
      else:
         lastElementUnbounded = False
   return lastElementUnbounded
   
   
def messageLength(msg):
   largestOffset = 0
   correspondingSize = 0
   for f in msg.fields:
      if int(f.offset) > largestOffset:
         largestOffset = int(f.offset)
         if f.length == "*":
            correspondingSize = 0
         else:
            correspondingSize = int(f.length)
   if lastElementUnbounded(msg):
      return "bufSize+2" #todo size of header should not be hard coded here
   else:
      return str(largestOffset + correspondingSize)
   
def printEnums():
# print all enumerations records
   print()      
   print()      
   print("ENUMERATIONS")      
   print()      
   for eK, eV in enumerations.items():
      print(eK)
      for e1K, e1V in eV.items():
         print (" ", e1K, e1V)
      print()      

def isMemberOfMessageTypesClass(thisType):
   if thisType in enumerations:
      return True
   else:
      return False
def convertCamel(name):
    s1 = re.sub('(.)([A-Z][a-z]+)', r'\1_\2', name)
    return re.sub('([a-z0-9])([A-Z])', r'\1_\2', s1).upper()
def writeLuaFile():
    f = open( luaName + ".lua", "w")
    f.write("--wireshark plug in\n")
    f.write( "local " + luaName + "_type = {\n");
    for eK, eV in enumerations.items():
      for e1K, e1V in eV.items():
        f.write( "    [" + e1V + "] = \"" + e1K + "\",\n");
    f.write( "}\n");
    for msgK, msgV in messages.items():
      f.write("local " + msgK + "_fields = " + msgK + "_proto.fields\n")
      for field in msgV.fields:
        if field.tag == "msgField":
		  if field.type == "bool":
            f.write( msgK + "_fields." + field.name + " = ProtoField." + "bool(")
            f.write( "\"" + msgK + "." + field.name + "\"" + "," + "\"" + field.name + "\",base.HEX)\n" )
          elif field.type == "float":
            f.write( msgK + "_fields." + field.name + "_exp" + " = ProtoField." + "int64(")
            f.write( "\"" + msgK + "." + field.name + "_exp" + "\"" + "," + "\"" + field.name + "\",base.HEX)\n" )
            f.write( msgK + "_fields." + field.name + "_mantissa" + " = ProtoField." + "int64(")
            f.write( "\"" + msgK + "." + field.name + "_mantissa" + "\"" + "," + "\"" + field.name + "\",base.HEX)\n" )
          elif field.type == "fixed":
            f.write( msgK + "_fields." + field.name + " = ProtoField." + "uint64(")
            f.write( "\"" + msgK + "." + field.name + "\"" + "," + "\"" + field.name + "\",base.HEX)\n" )
          elif field.type == "char":
          
          elif field.type == "int8":
          
          elif field.type == "int16":
          
          elif field.type == "int32":
          
          elif field.type == "uint8":
          
          elif field.type == "uint16":
          
          elif field.type == "uint32":
          
    f.write(luaName + "_proto = Proto(\"" + luaName + "\", \"" + luaName + "_1\")\n")
    f.write("udp_table = DissectorTable.get(\"udp.port\")\n")
    f.write("udp_table:add(" + port + "," + luaName + "_proto" + ")\n")
    f.close()
    return;
def writeMessageFiles():
   f = open("MessageTypesClass.h", "w")
   f.write("#ifndef MESSAGE_TYPES_H\n")
   f.write("#define MESSAGE_TYPES_H\n")
   f.write("\n")
   f.write("namespace " + catalogName + "\n")
   f.write("{\n")
   f.write("\n")
   f.write("   class MessageTypesClass\n")
   f.write("   {\n");
   f.write("      public:\n");
   f.write("\n");
   # create message types file
   for eK, eV in enumerations.items():
      f.write("         enum " + eK + " {\n")
      for e1K, e1V in eV.items():
         f.write ("            " + e1K + " = " + e1V + ",\n")
      f.write("         };\n")  
      f.write("\n")  
   f.write("   };\n");
   f.write("\n")  
   f.write("}\n");
   f.write("\n");
   f.write("#endif\n")
   f.close()
   # create message files
   for msgK, msgV in messages.items():
      f = open(msgK+".h", "w")
      f.write("#ifndef " + convertCamel(msgK) + "_H\n")
      f.write("#define " + convertCamel(msgK) + "_H\n")
      f.write("#include \"MessageTypesClass.h\"\n")
      f.write("#include \"BaseMessageClass.h\"\n")
      f.write("\n")
      f.write("namespace Messages\n")
      f.write("{\n")
      f.write("\n")
      f.write("   class " + msgK + " : public BaseMessageClass\n")
      f.write("   {\n")
      f.write("      public:\n")
      # message field member variables
      for field in msgV.fields:
         if field.tag == "msgField":
            prefix = ""
            if isMemberOfMessageTypesClass(field.type):
               prefix = "MessageTypesClass::"
            f.write("         " + prefix + field.type + " " + field.name + ";\n" )
      # receiver constructor
      f.write("\n")
      f.write("         " + msgK + "(unsigned char rawMessage[])\n")
      f.write("            : BaseMessageClass(rawMessage)\n")
      f.write("         {\n")
      for field in msgV.fields:
         if field.tag == "msgField":
            if field.type == "bool":
               f.write("            " + field.name + " = message[" + field.offset + "]==0 ? false : true;\n" )
            elif field.type == "float":
               f.write("               " + field.name + " = getFloat(" + field.offset + ");\n" )
            elif field.type == "fixed":
               f.write("               " + field.name + " = getFloat(" + field.offset + ");\n")
            elif field.type == "char":
               f.write("               " + field.name + " = getChar(" + field.offset + ");\n" )
            elif field.type == "int8":
               f.write("               " + field.name + " = getInt8(" + field.offset + ");\n" )
            elif field.type == "int16":
               f.write("               " + field.name + " = getInt16(" + field.offset + ");\n" )
            elif field.type == "int32":
               f.write("               " + field.name + " = getInt32(" + field.offset + ");\n" )
            elif field.type == "uint8":
               f.write("               " + field.name + " = getUint8(" + field.offset + ");\n" )
            elif field.type == "uint16":
               f.write("               " + field.name + " = getUint16(" + field.offset + ");\n" )
            elif field.type == "uint32":
               f.write("               " + field.name + " = getUint32(" + field.offset + ");\n" )
            elif field.type in allowedBuiltInTypes:
               f.write("               memcpy((char*)&" + field.name + ", &message[" + field.offset + "], " + field.length + ");\n" )
            elif isMemberOfMessageTypesClass(field.type):
               f.write("            " + field.name + " = (MessageTypesClass::" + field.type + ")message[" + field.offset + "];\n" )
      f.write("         }\n")
      # sender constructor constructor
      f.write("\n")
      f.write("         " + msgK + "(\n")
      first = True
      for field in msgV.fields:
         if field.tag == "msgField":
            typePrefix = ""
            if isMemberOfMessageTypesClass(field.type):
               typePrefix = "MessageTypesClass::"
            typeStr = "            " + typePrefix + field.type + " " + field.name
            if first:
               f.write(typeStr)
               first = False
            else:
               f.write(",\n" + typeStr )
      if lastElementUnbounded(msgV):
         f.write(",\n            int bufSize" )
      f.write("\n            ) : BaseMessageClass(MessageTypesClass::" + msgV.id + ", " + messageLength(msgV) + ")\n")
      f.write("         {\n")
      for field in msgV.fields:
         if field.tag == "msgField":
            if field.type == "bool":
               f.write("               message[" + field.offset + "] = " + field.name + " ? 1 : 0;\n" )
            elif field.type == "float":
               f.write("               putFloat(" + field.name + ", " + field.offset + ");\n" )
            elif field.type == "fixed":
               f.write("               putFixed(" + field.name + ", " + field.offset + ");\n" )
            elif field.type == "char":
               f.write("               putChar(" + field.name + ", " + field.offset + ");\n" )
            elif field.type == "uint8":
               f.write("               putUint8(" + field.name + ", " + field.offset + ");\n" )
            elif field.type == "uint16":
               f.write("               putUint16(" + field.name + ", " + field.offset + ");\n" )
            elif field.type == "uint32":
               f.write("               putUint32(" + field.name + ", " + field.offset + ");\n" )
            elif field.type == "int8":
               f.write("               putInt8(" + field.name + ", " + field.offset + ");\n" )
            elif field.type == "int16":
               f.write("               putInt16(" + field.name + ", " + field.offset + ");\n" )
            elif field.type == "int32":
               f.write("               putInt32(" + field.name + ", " + field.offset + ");\n" )
            # todo make arrays more generic
            elif field.length == "*":
               f.write("               memcpy(&message[" + field.offset + "], " + field.name + ", bufSize);\n" )
            else:
               f.write("               memcpy(&message[" + field.offset + "], (char*)&" + field.name + ", " + field.length + ");\n" )
   
      f.write("         }\n")
      f.write("   };\n")
      f.write("\n")
      f.write("\n")
      f.write("}\n");
      f.write("\n");
      f.write("#endif\n")
      f.close()

# ----------------------------------------
catalogName = messageCat.attrib['name']
for element in messageCat:
   if element.tag ==  "enumDefinition":
      parseEnum(element);
   if element.tag ==  "messageDefinition":
      parseMessage(element);
   if element.tag == "luaDefinition":
      global luaName
      luaName = element.attrib['name']
      global port
      port = element.attrib['port']
print()      
print()      
print("Message Catalog:", catalogName)
printEnums()
printMessages()
writeMessageFiles()
writeLuaFile()

      
