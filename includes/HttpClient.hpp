// ============================================================================
// HttpClient.{hpp,cpp}
// Module responsable de l'envoi de requêtes HTTP sortantes vers l'URL cible.
//
// Construit les requêtes, gère les headers, exécute la connexion réseau,
// récupère la réponse et retourne un objet HttpResponse structuré.
// ============================================================================

#ifndef HTTPCLIENT_HPP
#define HTTPCLIENT_HPP

#include <string>

/**
 * @file HttpClient.hpp
 * @brief Déclaration du module responsable des requêtes HTTP sortantes.
 *
 * Ce module permet d'envoyer des requêtes HTTP vers un serveur externe
 * et de récupérer la réponse, tout en gérant les erreurs réseau et HTTP.
 */

namespace HttpClient {

    /**
     * @struct HttpResponse
     * @brief Contient les informations retournées par une requête HTTP.
     */
    struct HttpResponse {
        int status_code = 0;           ///< Code HTTP (ex: 200, 404, 500)
        std::string body;             ///< Corps de la réponse HTTP
        std::string error;            ///< Message d'erreur réseau ou parsing
    };

    /**
     * @brief Envoie une requête HTTP vers une URL externe.
     *
     * @param url URL cible (ex: "http://example.com")
     * @param method Méthode HTTP ("GET", "POST", "OPTIONS", etc.)
     * 
     * @return Une structure HttpResponse contenant les données de la réponse.
     */
    HttpResponse sendRequest(const std::string& url, const std::string& method = "GET");

    // Si tu veux, plus tard :
    // HttpResponse sendPost(const std::string& url, const std::string& body);

} // namespace HttpClient

#endif // HTTPCLIENT_HPP