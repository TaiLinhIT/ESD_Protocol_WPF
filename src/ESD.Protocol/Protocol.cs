namespace ESD.Protocol;
public enum Command:ushort { Heartbeat=1,StatusReport=2,WorkerScan=0x10,Attach=0x11,Detach=0x12,EsdCheck=0x13,GetInfo=0x20,SetConfig=0x21,Ack=0xF0,Nack=0xF1,Error=0xFF }
[Flags] public enum FrameFlags:byte { None=0,AckRequested=1,Encrypted=2,Error=4 }
public enum ErrorCode:byte { Ok=0,BadVersion=1,BadLength=2,BadCrc=3,BadMac=4,Replay=5,UnknownCommand=6,DeviceNotAuthorized=7,Busy=8,InvalidPayload=9 }
public sealed record EsdFrame(byte Version,FrameFlags Flags,uint DeviceId,Command Command,uint Sequence,uint Timestamp,byte[] Payload,byte[] AuthTag);
public static class ProtocolConstants { public const byte Sof1=0xAA,Sof2=0x55,Eof1=0x0D,Eof2=0x0A,Version=1; public const int AuthTagSize=16,MaxPayload=256; }
