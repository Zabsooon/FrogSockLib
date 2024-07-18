# FrogSockLib
---

# Docs:
For purpose of development this madness I provide simple yet chaotic documentation.

## Implementation:
---
### Address:
Address implementation needs refactoring. Mostly because of the fact that I used
bad structure. The Address should be operational and ready to bind on call.
I used struct sockaddr and need to rewrite the whole thing so it stores struct addrinfo.
