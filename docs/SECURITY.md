# Production security
- Unique Device Key per device.
- HMAC-SHA256 authentication; AES-GCM if confidentiality is required.
- Sequence/session anti-replay.
- Never log secrets.
- Reject invalid version, length, MAC, device and command.
- Rate limit repeated authentication failures.
- Remove test authentication from production firmware.
