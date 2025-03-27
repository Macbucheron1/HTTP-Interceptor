// ============================================================================
// HttpClient.{hpp,cpp}
// Module responsable de l'envoi de requêtes HTTP sortantes vers l'URL cible.
//
// Construit les requêtes, gère les headers, exécute la connexion réseau,
// récupère la réponse et retourne un objet HttpResponse structuré.
// ============================================================================

#include "../includes/HttpClient.hpp"
#include "../includes/Utils.hpp"

#include <iostream>
#include <sstream>
#include <cstring>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>

namespace HttpClient {

HttpResponse sendRequest(const std::string& url, const std::string& method) {
    HttpResponse response;

    // 1. Extraire l'hôte depuis l'URL
    std::string host = Utils::extractHostFromURL(url);
    if (host.empty()) {
        response.error = "URL invalide ou hôte introuvable";
        return response;
    }

    // 2. Résolution DNS
    addrinfo hints{}, *res;
    hints.ai_family = AF_INET;        // IPv4
    hints.ai_socktype = SOCK_STREAM;  // TCP

    if (getaddrinfo(host.c_str(), "80", &hints, &res) != 0) {
        response.error = "Échec de la résolution DNS";
        return response;
    }

    // 3. Création de la socket
    int sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sock < 0) {
        response.error = "Échec création socket";
        freeaddrinfo(res);
        return response;
    }

    // 4. Connexion
    if (connect(sock, res->ai_addr, res->ai_addrlen) < 0) {
        response.error = "Connexion échouée";
        close(sock);
        freeaddrinfo(res);
        return response;
    }

    freeaddrinfo(res); // Plus besoin de res

    // 5. Construction de la requête HTTP
    std::ostringstream request;

    std::string path = Utils::extractPathFromURL(url);
    request << method << " " << path << " HTTP/1.1\r\n";
    request << "Host: " << host << "\r\n";
    request << "Connection: close\r\n";
    request << "\r\n";

    std::string reqStr = request.str();

    // 6. Envoi
    if (send(sock, reqStr.c_str(), reqStr.size(), 0) < 0) {
        response.error = "Échec d'envoi de la requête";
        close(sock);
        return response;
    }

    // 7. Réception
    char buffer[4096];
    std::ostringstream response_stream;
    ssize_t bytes_received;

    while ((bytes_received = recv(sock, buffer, sizeof(buffer), 0)) > 0) {
        response_stream.write(buffer, bytes_received);
    }

    if (bytes_received < 0) {
        response.error = "Erreur lors de la lecture de la réponse";
        close(sock);
        return response;
    }

    close(sock);
    std::string full_response = response_stream.str();

    // 8. Parsing simple : extraire le code HTTP + body
    size_t status_start = full_response.find("HTTP/");
    if (status_start != std::string::npos) {
        size_t code_start = full_response.find(' ', status_start);
        if (code_start != std::string::npos) {
            response.status_code = std::stoi(full_response.substr(code_start + 1, 3));
        }
    }

    size_t header_end = full_response.find("\r\n\r\n");
    if (header_end != std::string::npos) {
        response.body = full_response.substr(header_end + 4);
    } else {
        response.body = full_response;
    }

    return response;
}

} // namespace HttpClient
