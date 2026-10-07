# ESD Protocol WPF Gateway V1.0

.NET 8 WPF + SerialPort + Arduino UNO/Nano + MAX485-ready architecture.

## Build on Windows
Install .NET 8 SDK and Visual Studio 2022/2026 with **Desktop development with .NET**.

```powershell
dotnet restore
dotnet build -c Release
```

Open `ESD_Protocol_WPF.sln`, run `ESD.Wpf`.

## First hardware test
1. Arduino UNO/Nano via USB.
2. Upload `firmware/ESD_Arduino_Gateway/ESD_Arduino_Gateway.ino`.
3. WPF: select COM, 115200.
4. Connect.
5. Send HEARTBEAT.

## IMPORTANT security
The Arduino sketch intentionally uses `TestTag()` for transport/parser bring-up. It is NOT cryptographic and does NOT match the WPF HMAC-SHA256 tag. Do not use this firmware as production security. For production replace TestTag with a vetted HMAC-SHA256 implementation and provision a unique key per device. Then both sides will interoperate securely.

Production frame: AA55 | VER | FLAGS | DEVICE_ID | CMD | SEQ | TIMESTAMP | LEN | PAYLOAD | AUTH_TAG(16) | 0D0A
# ESD_Protocol_WPF
