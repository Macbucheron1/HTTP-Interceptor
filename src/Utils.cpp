// ============================================================================
// Utils.{hpp,cpp}
// Fonctions utilitaires générales utilisées dans tout le projet.
//
// Contient des helpers comme la validation d’URL, la sanitation des entrées,
// ou l’extraction de données depuis une chaîne (ex: host depuis une URL).
// ============================================================================

#include "../includes/Utils.hpp"
#include <string>

namespace Utils {

bool isValidURL(const std::string& url) {
    static const std::string HTTP_PREFIX  = "http://";
    static const std::string HTTPS_PREFIX = "https://";

    // 1) Vérifier longueur globale max (ex. 2048)
    if (url.size() > 2048) {
        return false;
    }

    // 2) Vérifier préfixes
    bool startsWithHttp  = (url.rfind(HTTP_PREFIX, 0) == 0);
    bool startsWithHttps = (url.rfind(HTTPS_PREFIX, 0) == 0);

    // Si ça ne commence pas par http:// ou https://, c'est invalide
    if (!startsWithHttp && !startsWithHttps) {
        return false;
    }

    // 3) Extraire la partie domaine (juste après "http://" ou "https://")
    std::string domain;
    if (startsWithHttp) {
        domain = url.substr(HTTP_PREFIX.size());
    } else {
        domain = url.substr(HTTPS_PREFIX.size());
    }

    // 4) Vérifier qu'il y a au moins un caractère
    //    autrement dit "http://"
    //    Si domain est vide => pas valide
    if (domain.empty()) {
        return false;
    }

    // 5) Vérifier si "localhost" OU si le domaine contient un "."
    //    => c'est un critère simpliste, mais ça suffira pour tes tests
    //    On peut ignorer tout le "/path" ou "?id=xxx" en cherchant le 1er '/'
    auto slashPos = domain.find('/');
    std::string domainPart = (slashPos == std::string::npos)
        ? domain
        : domain.substr(0, slashPos);

    // Traite les cas "localhost:8080", "example.com:8080"
    auto colonPos = domainPart.find(':');
    if (colonPos != std::string::npos) {
        domainPart = domainPart.substr(0, colonPos);
    }

    // Si c'est "localhost", ok
    if (domainPart == "localhost") {
        return true;
    }

    // Sinon, exiger un '.'
    if (domainPart.find('.') == std::string::npos) {
        return false;
    }

    // 6) Tout le reste passe
    return true;
}


std::string extractHostFromURL(const std::string& url) {
    std::string url_copy = url;
    std::string host;

    // Supprimer le protocole s'il existe
    if (url_copy.find("http://") == 0) {
        url_copy = url_copy.substr(7);
    } else if (url_copy.find("https://") == 0) {
        url_copy = url_copy.substr(8);
    }

    if (url_copy.empty()) return "";

    // Si IPv6, conserver les crochets
    if (url_copy[0] == '[') {
        size_t end = url_copy.find(']');
        if (end != std::string::npos) {
            host = url_copy.substr(0, end + 1);  // inclut les crochets
        }
    } else {
        // Extraire jusqu’au premier "/", "?" ou ":"
        size_t end = url_copy.find_first_of("/:?");
        host = url_copy.substr(0, end);
    }

    return host;
}
std::string sanitizeInput(const std::string& input) {
    // Stub ou implémentation naive
    return input;
}

/**
 * @brief Extrait le composant chemin d'une URL donnée.
 * 
 * Cette fonction supprime le protocole (http:// ou https://) de l'URL,
 * puis extrait et retourne le composant chemin à partir du premier '/'.
 * Si aucun chemin n'est trouvé dans l'URL, elle retourne "/" par défaut.
 * 
 * @param url L'URL d'entrée sous forme de chaîne.
 * @return Une chaîne représentant le composant chemin de l'URL, incluant le '/' initial.
 */
std::string extractPathFromURL(const std::string& url) {
    std::string no_protocol = url;
    if (no_protocol.find("http://") == 0) {
        no_protocol = no_protocol.substr(7);
    } else if (no_protocol.find("https://") == 0) {
        no_protocol = no_protocol.substr(8);
    }

    size_t slash = no_protocol.find('/');
    if (slash == std::string::npos)
        return "/";

    return no_protocol.substr(slash); // inclut le "/"
}


} // namespace Utils

