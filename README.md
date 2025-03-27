# HTTP Interceptor

Ce projet a pour but de réaliser une API qui permettra de réaliser des interceptions HTTP. Un genre de burpsuite. Cela servira comme back end pour application Web que j'hosterai sur mon [serveur](https://github.com/Macbucheron1/srv-mac)

## Schema 

```mermaid
sequenceDiagram
    participant main.cpp
    participant ProxyServer
    participant Router
    participant Interceptor
    participant HttpClient
    participant Logger
    participant Utils

    main.cpp->>ProxyServer: start()
    ProxyServer->>Router: setupRoutes()
    note right of Router: Crée endpoints\nex: /intercept

    Router->>Interceptor: interceptRequest(req)
    note right of Interceptor: Vérifie l’URL, etc.
    Interceptor->>Utils: isValidURL(url)
    Utils-->>Interceptor: true/false

    alt URL valide
        Interceptor->>HttpClient: sendRequest(url, method)
        HttpClient->>Logger: logRequest(req)
        HttpClient->>RealServer: Connect + GET/POST
        HttpClient->>Logger: logResponse(res)
        HttpClient-->>Interceptor: HttpResponse
        Interceptor->>Router: interceptResponse(res)
    else URL invalide
        Interceptor->>Logger: logError("Invalid URL")
    end

    Router-->>ProxyServer: crow::response
    ProxyServer-->>main.cpp: Fin de la requête
```