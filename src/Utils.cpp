// ============================================================================
// Utils.{hpp,cpp}
// Fonctions utilitaires générales utilisées dans tout le projet.
//
// Contient des helpers comme la validation d’URL, la sanitation des entrées,
// ou l’extraction de données depuis une chaîne (ex: host depuis une URL).
// ============================================================================

#include "../includes/Utils.hpp"
#include <cctype>      // pour std::isdigit
#include <string>

namespace Utils {

bool isValidURL(const std::string& url)
{
    // 1) Vérification basique : non vide | pas trop longue
    // Vérifier la longueur
    if (url.empty() || url.size() > 2048) {
        return false;
    }

    // 2) Accepter seulement http:// ou https://
    bool isHttp  = (url.rfind("http://", 0) == 0);   // rfind("...", 0) == 0 => commence par "..."
    bool isHttps = (url.rfind("https://", 0) == 0);

    if (!isHttp && !isHttps) {
        return false;
    }

    // 3) Trouver la position de "://"
    std::size_t pos = url.find("://");
    // Calcul du début de la partie domaine
    std::size_t domainStart = pos + 3; // après "://"

    // Vérifier qu'il y a bien quelque chose après "http://"
    if (domainStart >= url.size()) {
        return false;
    }

    // 4) Extraire la partie domaine (jusqu'au premier slash ou la fin)
    std::size_t slashPos = url.find('/', domainStart);
    if (slashPos == std::string::npos) {
        slashPos = url.size(); // pas de slash => prendre la fin
    }

    std::string domainPart = url.substr(domainStart, slashPos - domainStart);
    // Par exemple, si url = http://example.com:8080/test
    // domainPart = "example.com:8080"

    if (domainPart.empty()) {
        return false; // pas de domaine
    }

    // 5) Gérer éventuellement un port : "host:port"
    std::size_t colonPos = domainPart.find(':');
    if (colonPos != std::string::npos) {
        // On récupère la partie port
        std::string portStr = domainPart.substr(colonPos + 1);
        // On récupère la partie domaine sans le port
        domainPart = domainPart.substr(0, colonPos);

        if (portStr.empty()) {
            // Exemple: "http://example.com:"
            return false;
        }

        // Vérifier que le port est numérique
        for (char c : portStr) {
            if (!std::isdigit(static_cast<unsigned char>(c))) {
                return false;
            }
        }
    }

    // 6) Vérifier qu'il reste un nom de domaine non vide
    if (domainPart.empty()) {
        return false;
    }

    // 7) Vérifier la présence d'un point (sauf si c'est "localhost")
    //    (Choix de conception : on autorise "localhost")
    if (domainPart != "localhost" && domainPart.find('.') == std::string::npos) {
        return false;
    }

    // 8) Vérifier qu'il n'y a pas d'espace dans le domaine
    if (domainPart.find(' ') != std::string::npos) {
        return false;
    }

    // => A ce stade, c’est considéré comme valide
    return true;
}

std::string extractHostFromURL(const std::string& url)
{
    // Implémentation à venir…
    return {};
}

std::string sanitizeInput(const std::string& input)
{
    // Implémentation à venir…
    return input; // pour l’instant, on ne fait rien
}

} // namespace Utils
